#include "square_box_search_pattern.hpp"

#include <tf2/LinearMath/Quaternion.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <functional>
#include <vector>

namespace trajectory_following
{

SquareBoxSearchPattern::SquareBoxSearchPattern(const rclcpp::NodeOptions & options)
: rclcpp::Node("square_box_search_pattern", options)
{
  declare_parameter("frame_id", "map");
  declare_parameter("action_name", "navigate_to_waypoint");
  declare_parameter("auto_send", true);
  declare_parameter("send_period_ms", 500);
  declare_parameter("start_x", 0.0);
  declare_parameter("start_y", 0.0);
  declare_parameter("start_z", 0.0);
  declare_parameter("leg_step", 2.5);
  declare_parameter("segment_resolution", 1.0);
  declare_parameter("max_radius", 100.0);

  frame_id_ = get_parameter("frame_id").as_string();
  action_name_ = get_parameter("action_name").as_string();
  auto_send_ = get_parameter("auto_send").as_bool();
  start_x_ = get_parameter("start_x").as_double();
  start_y_ = get_parameter("start_y").as_double();
  start_z_ = get_parameter("start_z").as_double();
  leg_step_ = get_parameter("leg_step").as_double();
  segment_resolution_ = get_parameter("segment_resolution").as_double();
  max_radius_ = get_parameter("max_radius").as_double();
  const auto send_period_ms = get_parameter("send_period_ms").as_int();

  auto latched_qos = rclcpp::QoS(rclcpp::KeepLast(1)).transient_local().reliable();
  path_publisher_ = create_publisher<nav_msgs::msg::Path>("square_box_path", latched_qos);
  marker_publisher_ =
    create_publisher<visualization_msgs::msg::Marker>("square_box_path_marker", latched_qos);
  action_client_ = rclcpp_action::create_client<urc_msgs::action::NavigateToWaypoint>(
    this, action_name_);

  generated_path_ = buildPath();

  if (generated_path_.poses.empty()) {
    completed_ = true;
    RCLCPP_WARN(get_logger(), "Generated square-box path is empty; no goals to send.");
    return;
  }

  if (auto_send_) {
    send_timer_ = create_wall_timer(
      std::chrono::milliseconds(send_period_ms),
      std::bind(&SquareBoxSearchPattern::sendNextPathGoal, this));
  }
}

nav_msgs::msg::Path SquareBoxSearchPattern::buildPath() const
{
  nav_msgs::msg::Path path;
  path.header.frame_id = frame_id_;
  path.header.stamp = now();
  std::vector<geometry_msgs::msg::Point> points;

  if (leg_step_ <= 0.0 || segment_resolution_ <= 0.0 || max_radius_ <= 0.0) {
    return path;
  }

  auto append_pose = [this, &path, &points](double x, double y, double yaw) {
      geometry_msgs::msg::PoseStamped pose;
      pose.header = path.header;
      pose.pose.position.x = x;
      pose.pose.position.y = y;
      pose.pose.position.z = start_z_;

      tf2::Quaternion q;
      q.setRPY(0.0, 0.0, yaw);
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
    };

  static constexpr std::array<std::array<double, 2>, 4> kDirections = {{
    {{1.0, 0.0}},   // +x
    {{0.0, 1.0}},   // +y
    {{-1.0, 0.0}},  // -x
    {{0.0, -1.0}}   // -y
  }};

  double x = start_x_;
  double y = start_y_;
  std::size_t direction_index = 1;
  double leg_length = leg_step_;

  append_pose(x, y, 0.0);

  bool exceeded_radius = false;
  while (!exceeded_radius) {
    const auto & direction = kDirections[direction_index];
    const double dx = direction[0];
    const double dy = direction[1];
    const double yaw = std::atan2(dy, dx);
    const int samples = std::max(1, static_cast<int>(std::ceil(leg_length / segment_resolution_)));
    const double sample_step = leg_length / static_cast<double>(samples);

    for (int sample = 1; sample <= samples; ++sample) {
      x += dx * sample_step;
      y += dy * sample_step;
      append_pose(x, y, yaw);

      const double radius = std::max(std::abs(x - start_x_), std::abs(y - start_y_));
      if (radius > max_radius_) {
        exceeded_radius = true;
        break;
      }
    }

    direction_index = (direction_index + 1) % kDirections.size();
    leg_length += leg_step_;
  }

  path_publisher_->publish(path);

  visualization_msgs::msg::Marker marker;
  marker.header = path.header;
  marker.ns = "square_box_path";
  marker.id = 0;
  marker.type = visualization_msgs::msg::Marker::LINE_STRIP;
  marker.action = visualization_msgs::msg::Marker::ADD;
  marker.scale.x = 0.15;
  marker.color.r = 0.1f;
  marker.color.g = 0.4f;
  marker.color.b = 0.9f;
  marker.color.a = 1.0f;
  marker.points = points;
  marker_publisher_->publish(marker);

  return path;
}

void SquareBoxSearchPattern::sendNextPathGoal()
{
  // Keep publishing for RViz even after goal dispatch so visualization does not depend on QoS/history timing.
  path_publisher_->publish(generated_path_);

  if (completed_ || goal_in_flight_) {
    return;
  }

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
        RCLCPP_ERROR(get_logger(), "navigate_to_waypoint square path goal was rejected.");
        if (send_timer_) {
          send_timer_->cancel();
        }
        return;
      }
      RCLCPP_INFO(get_logger(), "Accepted square path goal (%zu poses).", generated_path_.poses.size());
    };

  options.feedback_callback =
    [](GoalHandleNavigate::SharedPtr, const std::shared_ptr<const NavigateAction::Feedback>) {};

  options.result_callback = [this](const GoalHandleNavigate::WrappedResult & wrapped_result) {
      goal_in_flight_ = false;

      if (wrapped_result.code != rclcpp_action::ResultCode::SUCCEEDED ||
        !wrapped_result.result ||
        wrapped_result.result->error_code != urc_msgs::action::NavigateToWaypoint::Result::SUCCESS)
      {
        completed_ = true;
        RCLCPP_ERROR(get_logger(), "Square path goal failed.");
        if (send_timer_) {
          send_timer_->cancel();
        }
        return;
      }

      completed_ = true;
      RCLCPP_INFO(get_logger(), "Square path completed successfully.");
    };

  goal_in_flight_ = true;
  action_client_->async_send_goal(goal_msg, options);
  completed_ = true;  // only send once
}

}  // namespace trajectory_following

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(trajectory_following::SquareBoxSearchPattern)
