#include "follower_action_server.hpp"
#include "geometry_util.hpp"
#include "pure_pursuit.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/exceptions.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

namespace follower_action_server
{
FollowerActionServer::FollowerActionServer(const rclcpp::NodeOptions & options)
: Node("follower_action_server", options)
{
  RCLCPP_INFO(this->get_logger(), "Follower node has been started.");

  declare_parameter("lookahead_distance", 2.0);
  declare_parameter("desired_linear_velocity", 0.2);
  declare_parameter("cmd_vel_topic", "/cmd_vel");
  declare_parameter("odom_topic", "base_link");
  declare_parameter("map_frame", "map");
  declare_parameter("goal_tolerance", 0.5);
  declare_parameter("cmd_vel_stamped", false);
  declare_parameter("lethal_cost_threshold", 50);

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  stamped_ = get_parameter("cmd_vel_stamped").as_bool();

  if (stamped_) {
    cmd_vel_stamped_pub_ =
      create_publisher<geometry_msgs::msg::TwistStamped>(
      get_parameter(
        "cmd_vel_topic")
      .as_string(),
      10);
  } else {
    cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>(
      get_parameter(
        "cmd_vel_topic")
      .as_string(),
      10);
  }

  carrot_pub_ = create_publisher<geometry_msgs::msg::PointStamped>("carrot", 10);
  marker_pub_ = create_publisher<visualization_msgs::msg::Marker>("lookahead_circle", 10);

  odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
    get_parameter("odom_topic").as_string(),
    10,
    [this](const nav_msgs::msg::Odometry::SharedPtr msg)
    {
      geometry_msgs::msg::PoseStamped pose;
      pose.header = msg->header;
      pose.pose = msg->pose.pose;
      current_pose_ = pose;
    });

  // Setup the costmap
  costmap_subscriber_ = create_subscription<nav_msgs::msg::OccupancyGrid>(
    "/costmap",
    rclcpp::SystemDefaultsQoS(),
    std::bind(&FollowerActionServer::handleCostmap, this, std::placeholders::_1));

  // Create an action server for the navigate_to_waypoint action
  navigate_server_ = rclcpp_action::create_server<urc_msgs::action::NavigateToWaypoint>(
    this,
    "navigate_to_waypoint",
    std::bind(
      &FollowerActionServer::handle_navigate_goal, this, std::placeholders::_1,
      std::placeholders::_2),
    std::bind(&FollowerActionServer::handle_navigate_cancel, this, std::placeholders::_1),
    std::bind(&FollowerActionServer::handle_navigate_accepted, this, std::placeholders::_1));

  // Create a client for the path planning service
  planning_client_ = create_client<urc_msgs::srv::GeneratePlan>("plan");

  rover_position_pub_ = create_publisher<geometry_msgs::msg::PointStamped>("rover_position", 10);
}

void FollowerActionServer::handleCostmap(const nav_msgs::msg::OccupancyGrid::SharedPtr msg)
{
  current_costmap_ = *msg;
}

geometry_msgs::msg::TransformStamped FollowerActionServer::lookup_transform(
  std::string target_frame, std::string source_frame)
{
  geometry_msgs::msg::TransformStamped transform;
  try {
    // RCLCPP_INFO(this->get_logger(), "Looking up transform from %s to %s", source_frame.c_str(), target_frame.c_str());
    transform = tf_buffer_->lookupTransform(target_frame, source_frame, tf2::TimePointZero);
  } catch (tf2::TransformException & ex) {
    RCLCPP_ERROR(this->get_logger(), "Could not lookup transform: %s", ex.what());
  }
  return transform;
}

FollowerActionServer::~FollowerActionServer()
{
  RCLCPP_INFO(this->get_logger(), "Follower action server has been stopped.");
}

rclcpp_action::GoalResponse FollowerActionServer::handle_navigate_goal(
  const rclcpp_action::GoalUUID & uuid,
  std::shared_ptr<const urc_msgs::action::NavigateToWaypoint::Goal> goal)
{
  RCLCPP_INFO(this->get_logger(), "Received navigate to waypoint goal request");

  (void)uuid;

  if (!goal->has_path && !goal->has_goal) {
    RCLCPP_ERROR(this->get_logger(), "Neither path nor goal provided");
    return rclcpp_action::GoalResponse::REJECT;
  }

  if (goal->has_goal && !planning_client_->service_is_ready()) {
    RCLCPP_WARN(this->get_logger(), "Planning service not available");
    return rclcpp_action::GoalResponse::REJECT;
  }

  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse FollowerActionServer::handle_navigate_cancel(
  const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::NavigateToWaypoint>> goal_handle)
{
  RCLCPP_INFO(this->get_logger(), "Received request to cancel navigate goal");

  (void)goal_handle;

  return rclcpp_action::CancelResponse::ACCEPT;
}

void FollowerActionServer::handle_navigate_accepted(
  const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::NavigateToWaypoint>> goal_handle)
{
  std::thread{std::bind(&FollowerActionServer::execute_navigate, this, std::placeholders::_1),
    goal_handle}
  .detach();
}

nav_msgs::msg::Path FollowerActionServer::callPlanningService(
  const geometry_msgs::msg::PoseStamped & start,
  const geometry_msgs::msg::PoseStamped & goal,
  bool & success)
{
  auto request = std::make_shared<urc_msgs::srv::GeneratePlan::Request>();
  request->start = start;
  request->goal = goal;

  RCLCPP_INFO(this->get_logger(), "Calling planning service...");

  auto result = planning_client_->async_send_request(request);

  if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result, std::chrono::seconds(10)) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    auto response = result.get();
    if (response->error_code == urc_msgs::srv::GeneratePlan::Response::SUCCESS) {
      RCLCPP_INFO(this->get_logger(), "Planning successful, path has %ld poses", response->path.poses.size());
      success = true;
      return response->path;
    } else {
      RCLCPP_ERROR(this->get_logger(), "Planning failed with error code %d", response->error_code);
      success = false;
      return nav_msgs::msg::Path();
    }
  } else {
    RCLCPP_ERROR(this->get_logger(), "Planning service call timed out");
    success = false;
    return nav_msgs::msg::Path();
  }
}

void FollowerActionServer::execute_navigate(
  const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::NavigateToWaypoint>> goal_handle)
{
  RCLCPP_INFO(this->get_logger(), "Executing navigate to waypoint goal");

  auto feedback = std::make_shared<urc_msgs::action::NavigateToWaypoint::Feedback>();
  feedback->distance_to_goal = std::numeric_limits<double>::max();
  feedback->is_planning = false;
  feedback->replan_count = 0;

  auto result = std::make_shared<urc_msgs::action::NavigateToWaypoint::Result>();
  const auto & goal_msg = goal_handle->get_goal();

  nav_msgs::msg::Path path;
  geometry_msgs::msg::PoseStamped goal_pose;

  // Determine the path to follow
  if (goal_msg->has_goal) {
    // Need to call planning service
    feedback->is_planning = true;
    goal_handle->publish_feedback(feedback);

    goal_pose = goal_msg->goal;
    
    geometry_msgs::msg::PoseStamped start_pose;
    start_pose.header = current_pose_.header;
    start_pose.pose = current_pose_.pose;

    bool planning_success = false;
    path = callPlanningService(start_pose, goal_pose, planning_success);

    feedback->is_planning = false;

    if (!planning_success || path.poses.empty()) {
      result->error_code = urc_msgs::action::NavigateToWaypoint::Result::PLANNING_FAILED;
      goal_handle->abort(result);
      RCLCPP_ERROR(this->get_logger(), "Initial planning failed");
      publishZeroVelocity();
      return;
    }
  } else {
    // Use provided path
    path = goal_msg->path;
    goal_pose.header = path.header;
    goal_pose.pose = path.poses.back().pose;
  }

  // Create a PurePursuit object
  pure_pursuit::PurePursuitParams params;
  params.lookahead_distance = get_parameter("lookahead_distance").as_double();
  params.desired_linear_velocity = get_parameter("desired_linear_velocity").as_double();
  pure_pursuit::PurePursuit pure_pursuit(params);

  pure_pursuit.setPath(path);
  RCLCPP_INFO(this->get_logger(), "Lookahead distance: %f", params.lookahead_distance);
  RCLCPP_INFO(this->get_logger(), "Desired linear velocity: %f", params.desired_linear_velocity);
  RCLCPP_INFO(this->get_logger(), "Following path with %ld poses", path.poses.size());

  pure_pursuit::PurePursuitOutput output;
  rclcpp::Rate rate(10);

  while (rclcpp::ok()) {
    if (goal_handle->is_canceling()) {
      goal_handle->canceled(result);
      RCLCPP_INFO(this->get_logger(), "Goal has been canceled");
      break;
    } else if (feedback->distance_to_goal < get_parameter("goal_tolerance").as_double()) {
      result->error_code = urc_msgs::action::NavigateToWaypoint::Result::SUCCESS;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal has been reached!");
      break;
    } else if (getCost(
        current_costmap_, output.lookahead_point.point.x,
        output.lookahead_point.point.y) > get_parameter("lethal_cost_threshold").as_int())
    {
      // Obstacle detected - attempt to re-plan
      RCLCPP_WARN(this->get_logger(), "Obstacle detected! Attempting to re-plan...");
      
      feedback->is_planning = true;
      feedback->replan_count++;
      goal_handle->publish_feedback(feedback);

      geometry_msgs::msg::PoseStamped start_pose;
      start_pose.header = current_pose_.header;
      start_pose.pose = current_pose_.pose;

      bool planning_success = false;
      nav_msgs::msg::Path new_path = callPlanningService(start_pose, goal_pose, planning_success);

      feedback->is_planning = false;

      if (!planning_success || new_path.poses.empty()) {
        result->error_code = urc_msgs::action::NavigateToWaypoint::Result::PLANNING_FAILED;
        goal_handle->abort(result);
        RCLCPP_ERROR(this->get_logger(), "Re-planning failed");
        break;
      }

      // Update the path and continue
      path = new_path;
      pure_pursuit.setPath(path);
      RCLCPP_INFO(this->get_logger(), "Re-planning successful, following new path with %ld poses", path.poses.size());
    }

    output =
      pure_pursuit.getCommandVelocity(this->get_logger(),
      lookup_transform(
        "base_link",
        get_parameter("map_frame").as_string()));

    auto odom_to_map_ = lookup_transform(get_parameter("map_frame").as_string(), "base_link");

    if (stamped_) {
      cmd_vel_stamped_pub_->publish(output.cmd_vel);
    } else {
      cmd_vel_pub_->publish(output.cmd_vel.twist);
    }

    geometry_msgs::msg::PoseStamped current_pose_map_frame_;
    tf2::doTransform(current_pose_, current_pose_map_frame_, odom_to_map_);

    // Publish rover position as PointStamped for rqt_plot
    geometry_msgs::msg::PointStamped rover_point;
    rover_point.header = current_pose_map_frame_.header;
    rover_point.point = current_pose_map_frame_.pose.position;
    rover_position_pub_->publish(rover_point);

    auto circle =
      create_lookahead_circle(
      current_pose_map_frame_.pose.position.x, current_pose_map_frame_.pose.position.y,
      params.lookahead_distance, get_parameter("map_frame").as_string());
    marker_pub_->publish(circle);

    // Publish the carrot point
    carrot_pub_->publish(output.lookahead_point);

    // Publish feedback
    feedback->distance_to_goal =
      geometry_util::dist2D(current_pose_map_frame_.pose.position, goal_pose.pose.position);
    goal_handle->publish_feedback(feedback);

    rate.sleep();
  }

  publishZeroVelocity();
}

} // namespace follower_action_server

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(follower_action_server::FollowerActionServer)
