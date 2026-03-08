#include "spiral_path_generator.hpp"

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <tf2/LinearMath/Quaternion.h>

#include <cmath>
#include <chrono>
#include <functional>

namespace trajectory_following
{

SpiralPathGenerator::SpiralPathGenerator(const rclcpp::NodeOptions & options)
: rclcpp::Node("spiral_path_generator", options)
{
  declare_parameter("frame_id", "map");
  declare_parameter("action_name", "navigate_to_waypoint");
  declare_parameter("auto_send", true);
  declare_parameter("send_period_ms", 500);
  declare_parameter("start_x", 0.0); //start position; we could modify it to take in a PoseStamped as a parameter
  declare_parameter("start_y", 0.0);
  declare_parameter("start_z", 0.0);
  declare_parameter("radius_step", 10.0);//radius step is every rotation how much the radius should increase, so ideally this is some fraction of the camera detection range
  declare_parameter("angle_step_deg", 5.0);//basically path resolution, every how many degrees should we add a new point, smaller is more points and smoother path but more computationally expensive
  declare_parameter("max_radius", 100.0); //max radius of the spiral, ideally should be some fraction of the camera detection range

  frame_id_ = get_parameter("frame_id").as_string();
  action_name_ = get_parameter("action_name").as_string();
  auto_send_ = get_parameter("auto_send").as_bool();
  start_x_ = get_parameter("start_x").as_double();
  start_y_ = get_parameter("start_y").as_double();
  start_z_ = get_parameter("start_z").as_double();
  radius_step_ = get_parameter("radius_step").as_double();
  angle_step_deg_ = get_parameter("angle_step_deg").as_double();
  max_radius_ = get_parameter("max_radius").as_double();
  const auto send_period_ms = get_parameter("send_period_ms").as_int();

  // Generate and publish the spiral path
  auto latched_qos = rclcpp::QoS(rclcpp::KeepLast(1)).transient_local().reliable();
  path_publisher_ = create_publisher<nav_msgs::msg::Path>("spiral_path", latched_qos);
  // also publish a marker so the spiral is visible in RViz
  marker_publisher_ = create_publisher<visualization_msgs::msg::Marker>("spiral_path_marker", latched_qos);
  action_client_ = rclcpp_action::create_client<urc_msgs::action::NavigateToWaypoint>(
    this, action_name_);

  generated_path_ = buildPath();

  if (generated_path_.poses.empty()) {
    completed_ = true;
    RCLCPP_WARN(get_logger(), "Generated spiral path is empty; no goals to send.");
    return;
  }

  if (auto_send_) {
    send_timer_ = create_wall_timer(
      std::chrono::milliseconds(send_period_ms),
      std::bind(&SpiralPathGenerator::sendNextPathGoal, this));
  }
}



nav_msgs::msg::Path SpiralPathGenerator::buildPath() const
{
  nav_msgs::msg::Path path;
  path.header.frame_id = frame_id_;
  path.header.stamp = this->now();
  std::vector<geometry_msgs::msg::Point> points;

  const double angle_step = angle_step_deg_ * M_PI / 180.0;
  if (angle_step <= 0.0 || radius_step_ <= 0.0 || max_radius_ <= 0.0) {
    return path;
  }

  double theta = 0.0;
  double r = 0;

  while (r <= max_radius_) {
    geometry_msgs::msg::PoseStamped pose;
    pose.header.frame_id = frame_id_;
    pose.header.stamp = path.header.stamp;

    const double x = start_x_ + r * std::cos(theta);
    const double y = start_y_ + r * std::sin(theta);
    pose.pose.position.x = x;
    pose.pose.position.y = y;
    pose.pose.position.z = start_z_;

    tf2::Quaternion q;
    q.setRPY(0.0, 0.0, theta);
    pose.pose.orientation.x = q.x();
    pose.pose.orientation.y = q.y();
    pose.pose.orientation.z = q.z();
    pose.pose.orientation.w = q.w();

    path.poses.push_back(pose);

    geometry_msgs::msg::Point p;
    p.x = x;
    p.y = y;
    p.z = start_z_;
    points.push_back(p);

    theta += angle_step;//increase angle by step
    r = (radius_step_ / (2.0 * M_PI)) * theta;
  }
  path_publisher_->publish(path);

  visualization_msgs::msg::Marker marker;
  marker.header = path.header;
  marker.ns = "spiral_path";
  marker.id = 0;
  marker.type = visualization_msgs::msg::Marker::LINE_STRIP;
  marker.action = visualization_msgs::msg::Marker::ADD;
  marker.scale.x = 0.15;
  marker.color.r = 0.1f;
  marker.color.g = 0.9f;
  marker.color.b = 0.2f;
  marker.color.a = 1.0f;
  marker.points = points;
  marker_publisher_->publish(marker);

  return path;
}

void SpiralPathGenerator::sendNextPathGoal()
{
  if (completed_ || goal_in_flight_) {
    return;
  }

  // publish the entire path for visualization/debug
  path_publisher_->publish(generated_path_);

  if (!action_client_->wait_for_action_server(std::chrono::seconds(0))) {
    RCLCPP_WARN_THROTTLE(
      get_logger(), *get_clock(), 5000,
      "Waiting for '%s' action server...", action_name_.c_str());
    return;
  }

  using NavigateAction = urc_msgs::action::NavigateToWaypoint;
  using GoalHandleNavigate = rclcpp_action::ClientGoalHandle<NavigateAction>;

  NavigateAction::Goal goal_msg;
  goal_msg.has_goal = false;
  goal_msg.has_path = true;
  goal_msg.path = generated_path_;
  goal_msg.enforce_goal_heading = false;

  rclcpp_action::Client<NavigateAction>::SendGoalOptions options;
  options.goal_response_callback = [this](std::shared_ptr<GoalHandleNavigate> goal_handle) {
      if (!goal_handle) {
        completed_ = true;
        goal_in_flight_ = false;
        RCLCPP_ERROR(get_logger(), "navigate_to_waypoint path goal was rejected.");
        if (send_timer_) {
          send_timer_->cancel();
        }
        return;
      }
      RCLCPP_INFO(get_logger(), "Accepted spiral path goal (%zu poses).",
                  generated_path_.poses.size());
    };

  options.feedback_callback =
    [](GoalHandleNavigate::SharedPtr,
      const std::shared_ptr<const NavigateAction::Feedback>) {};

  options.result_callback = [this](const GoalHandleNavigate::WrappedResult & wrapped_result) {
      goal_in_flight_ = false;

      if (wrapped_result.code != rclcpp_action::ResultCode::SUCCEEDED ||
        !wrapped_result.result ||
        wrapped_result.result->error_code != urc_msgs::action::NavigateToWaypoint::Result::SUCCESS)
      {
        completed_ = true;
        RCLCPP_ERROR(get_logger(), "Spiral path goal failed.");
        if (send_timer_) {
          send_timer_->cancel();
        }
        return;
      }

      completed_ = true;
      RCLCPP_INFO(get_logger(), "Spiral path completed successfully.");
    };

  goal_in_flight_ = true;
  action_client_->async_send_goal(goal_msg, options);
  completed_ = true; // only send once
}

void SpiralPathGenerator::sendGoalPose(const geometry_msgs::msg::PoseStamped & goal_pose)
{
  using NavigateAction = urc_msgs::action::NavigateToWaypoint;
  using GoalHandleNavigate = rclcpp_action::ClientGoalHandle<NavigateAction>;

  NavigateAction::Goal goal_msg;
  // always include a trivial path with the single pose so the follower
  // server doesn't need the planning service to be available
  goal_msg.goal = goal_pose;
  goal_msg.has_goal = true;
  goal_msg.has_path = true;
  goal_msg.path.header = goal_pose.header;
  goal_msg.path.poses.push_back(goal_pose);
  goal_msg.enforce_goal_heading = false;

  rclcpp_action::Client<NavigateAction>::SendGoalOptions options;
  options.goal_response_callback = [this](std::shared_ptr<GoalHandleNavigate> goal_handle) {
      if (!goal_handle) {
        completed_ = true;
        goal_in_flight_ = false;
        RCLCPP_ERROR(get_logger(), "navigate_to_waypoint goal was rejected.");
        if (send_timer_) {
          send_timer_->cancel();
        }
        return;
      }
      RCLCPP_INFO(
        get_logger(), "Accepted point goal %zu/%zu.",
        path_goal_idx_ + 1, generated_path_.poses.size());
    };

  options.feedback_callback =
    [](GoalHandleNavigate::SharedPtr,
      const std::shared_ptr<const NavigateAction::Feedback>) {};

  options.result_callback = [this](const GoalHandleNavigate::WrappedResult & wrapped_result) {
      goal_in_flight_ = false;

      if (wrapped_result.code != rclcpp_action::ResultCode::SUCCEEDED ||
        !wrapped_result.result ||
        wrapped_result.result->error_code != urc_msgs::action::NavigateToWaypoint::Result::SUCCESS)
      {
        completed_ = true;
        RCLCPP_ERROR(
          get_logger(), "Point goal %zu/%zu failed.",
          path_goal_idx_ + 1, generated_path_.poses.size());
        if (send_timer_) {
          send_timer_->cancel();
        }
        return;
      }

      ++path_goal_idx_;
      if (path_goal_idx_ >= generated_path_.poses.size()) {
        completed_ = true;
        RCLCPP_INFO(get_logger(), "All spiral point goals completed successfully.");
        if (send_timer_) {
          send_timer_->cancel();
        }
      }
    };

  goal_in_flight_ = true;
  action_client_->async_send_goal(goal_msg, options);
}

}  // namespace trajectory_following

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(trajectory_following::SpiralPathGenerator)
