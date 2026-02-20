#include "follower_action_server.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_util.hpp"
#include "pure_pursuit.hpp"
#include "tf2/exceptions.h"
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <algorithm>

namespace follower_action_server {
FollowerActionServer::FollowerActionServer(const rclcpp::NodeOptions &options)
    : Node("follower_action_server", options) {
  RCLCPP_INFO(this->get_logger(), "Follower node has been started.");

  declare_parameter("lookahead_distance", 2.0);
  declare_parameter("desired_linear_velocity", 0.2);
  declare_parameter("max_angular_velocity", 1.0);
  declare_parameter("heading_alignment_tolerance", 0.2);
  declare_parameter("enable_swerve_motion", true);
  declare_parameter("cmd_vel_topic", "/cmd_vel");
  declare_parameter("map_frame", "map");
  declare_parameter("base_link_frame", "base_link");
  declare_parameter("goal_tolerance", 0.5);
  declare_parameter("cmd_vel_stamped", false);
  declare_parameter("lethal_cost_threshold", 50.0);
  declare_parameter("enforce_goal_heading", false);
  declare_parameter("goal_heading_tolerance", 0.1);
  declare_parameter("costmap_layer", "traversability_inflated");

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  stamped_ = get_parameter("cmd_vel_stamped").as_bool();
  costmap_layer_ = get_parameter("costmap_layer").as_string();

  if (stamped_) {
    cmd_vel_stamped_pub_ = create_publisher<geometry_msgs::msg::TwistStamped>(
        get_parameter("cmd_vel_topic").as_string(), 10);
  } else {
    cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>(
        get_parameter("cmd_vel_topic").as_string(), 10);
  }

  carrot_pub_ =
      create_publisher<geometry_msgs::msg::PointStamped>("carrot", 10);
  marker_pub_ =
      create_publisher<visualization_msgs::msg::Marker>("lookahead_circle", 10);

  // Setup the costmap
  costmap_subscriber_ = create_subscription<grid_map_msgs::msg::GridMap>(
      "/costmap", rclcpp::SystemDefaultsQoS(),
      std::bind(&FollowerActionServer::handleCostmap, this,
                std::placeholders::_1));

  // Create an action server for the navigate_to_waypoint action
  navigate_server_ =
      rclcpp_action::create_server<urc_msgs::action::NavigateToWaypoint>(
          this, "navigate_to_waypoint",
          std::bind(&FollowerActionServer::handle_navigate_goal, this,
                    std::placeholders::_1, std::placeholders::_2),
          std::bind(&FollowerActionServer::handle_navigate_cancel, this,
                    std::placeholders::_1),
          std::bind(&FollowerActionServer::handle_navigate_accepted, this,
                    std::placeholders::_1));

  // Create a client for the path planning service
  planning_client_ = create_client<urc_msgs::srv::GeneratePlan>("plan");

  rover_position_pub_ =
      create_publisher<geometry_msgs::msg::PointStamped>("rover_position", 10);
}

void FollowerActionServer::handleCostmap(
    const grid_map_msgs::msg::GridMap::SharedPtr msg) {
  current_costmap_ = *msg;
}

geometry_msgs::msg::TransformStamped
FollowerActionServer::lookup_transform(std::string target_frame,
                                       std::string source_frame) {
  geometry_msgs::msg::TransformStamped transform;
  try {
    // RCLCPP_INFO(this->get_logger(), "Looking up transform from %s to %s",
    // source_frame.c_str(), target_frame.c_str());
    transform = tf_buffer_->lookupTransform(target_frame, source_frame,
                                            tf2::TimePointZero);
  } catch (tf2::TransformException &ex) {
    RCLCPP_ERROR(this->get_logger(), "Could not lookup transform: %s",
                 ex.what());
  }
  return transform;
}

FollowerActionServer::~FollowerActionServer() {
  RCLCPP_INFO(this->get_logger(), "Follower action server has been stopped.");
}

rclcpp_action::GoalResponse FollowerActionServer::handle_navigate_goal(
    const rclcpp_action::GoalUUID &uuid,
    std::shared_ptr<const urc_msgs::action::NavigateToWaypoint::Goal> goal) {
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
    const std::shared_ptr<
        rclcpp_action::ServerGoalHandle<urc_msgs::action::NavigateToWaypoint>>
        goal_handle) {
  RCLCPP_INFO(this->get_logger(), "Received request to cancel navigate goal");

  (void)goal_handle;

  return rclcpp_action::CancelResponse::ACCEPT;
}

void FollowerActionServer::handle_navigate_accepted(
    const std::shared_ptr<
        rclcpp_action::ServerGoalHandle<urc_msgs::action::NavigateToWaypoint>>
        goal_handle) {
  std::thread{std::bind(&FollowerActionServer::execute_navigate, this,
                        std::placeholders::_1),
              goal_handle}
      .detach();
}

visualization_msgs::msg::Marker
FollowerActionServer::create_lookahead_circle(double x, double y, double radius,
                                              std::string frame_id) {
  visualization_msgs::msg::Marker circle;
  circle.header.frame_id = frame_id;
  circle.header.stamp = get_clock()->now();
  uint32_t shape = visualization_msgs::msg::Marker::CYLINDER;

  circle.ns = "basic_shapes";
  circle.id = 0;
  circle.type = shape;
  circle.action = visualization_msgs::msg::Marker::ADD;

  circle.pose.position.x = x;
  circle.pose.position.y = y;
  circle.pose.position.z = 0.0;
  circle.pose.orientation.x = 0.0;
  circle.pose.orientation.y = 0.0;
  circle.pose.orientation.z = 0.0;
  circle.pose.orientation.w = 1.0;

  circle.scale.x = 2 * radius;
  circle.scale.y = 2 * radius;
  circle.scale.z = 0.01;

  circle.color.r = 0.0f;
  circle.color.g = 0.0f;
  circle.color.b = 1.0f;
  circle.color.a = 0.3;

  return circle;
}

void FollowerActionServer::publishZeroVelocity() {
  geometry_msgs::msg::TwistStamped cmd_vel;
  cmd_vel.header.stamp = get_clock()->now();
  cmd_vel.twist.linear.x = 0.0;
  cmd_vel.twist.angular.z = 0.0;

  if (stamped_) {
    cmd_vel_stamped_pub_->publish(cmd_vel);
  } else {
    cmd_vel_pub_->publish(cmd_vel.twist);
  }
}

float FollowerActionServer::getCost(const grid_map_msgs::msg::GridMap &costmap,
                                  double x, double y) {
  // Find the layer index
  auto it = std::find(costmap.layers.begin(), costmap.layers.end(), costmap_layer_);
  if (it == costmap.layers.end()) {
    RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 5000,
                         "Costmap layer '%s' not found", costmap_layer_.c_str());
    return 0.0f;
  }
  size_t layer_index = std::distance(costmap.layers.begin(), it);

  // Get grid dimensions from the data layout
  if (costmap.data.empty() || layer_index >= costmap.data.size()) {
    return 0.0f;
  }

  const auto &layer_data = costmap.data[layer_index];
  if (layer_data.layout.dim.size() < 2) {
    return 0.0f;
  }

  // GridMap uses center of grid as origin
  double origin_x = costmap.info.pose.position.x;
  double origin_y = costmap.info.pose.position.y;
  double resolution = costmap.info.resolution;
  
  // Calculate map indices (GridMap stores data row-major)
  int width = layer_data.layout.dim[1].size;
  int height = layer_data.layout.dim[0].size;
  
  // Transform world coordinates to grid coordinates
  double rel_x = x - origin_x;
  double rel_y = y - origin_y;
  
  int map_x = static_cast<int>(rel_x / resolution + width / 2.0);
  int map_y = static_cast<int>(rel_y / resolution + height / 2.0);

  if (map_x < 0 || map_x >= width || map_y < 0 || map_y >= height) {
    return 0.0f;
  }

  // Access data in row-major order
  size_t index = map_y * width + map_x;
  if (index >= layer_data.data.size()) {
    return 0.0f;
  }

  return layer_data.data[index];
}

nav_msgs::msg::Path FollowerActionServer::callPlanningService(
    const geometry_msgs::msg::PoseStamped &start,
    const geometry_msgs::msg::PoseStamped &goal, bool &success) {
  auto request = std::make_shared<urc_msgs::srv::GeneratePlan::Request>();
  request->start = start;
  request->goal = goal;

  RCLCPP_INFO(this->get_logger(), "Calling planning service...");

  auto result = planning_client_->async_send_request(request);

  if (result.wait_for(std::chrono::seconds(10)) == std::future_status::ready) {
    auto response = result.get();
    if (response->error_code ==
        urc_msgs::srv::GeneratePlan::Response::SUCCESS) {
      RCLCPP_INFO(this->get_logger(), "Planning successful, path has %ld poses",
                  response->path.poses.size());
      success = true;
      return response->path;
    } else {
      RCLCPP_ERROR(this->get_logger(), "Planning failed with error code %d",
                   response->error_code);
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
    const std::shared_ptr<
        rclcpp_action::ServerGoalHandle<urc_msgs::action::NavigateToWaypoint>>
        goal_handle) {
  RCLCPP_INFO(this->get_logger(), "Executing navigate to waypoint goal");

  auto feedback =
      std::make_shared<urc_msgs::action::NavigateToWaypoint::Feedback>();
  feedback->distance_to_goal = std::numeric_limits<double>::max();
  feedback->is_planning = false;
  feedback->replan_count = 0;

  auto result =
      std::make_shared<urc_msgs::action::NavigateToWaypoint::Result>();
  const auto &goal_msg = goal_handle->get_goal();

  // Determine if we should enforce goal heading (from request or config)
  bool enforce_heading = goal_msg->enforce_goal_heading ||
                         get_parameter("enforce_goal_heading").as_bool();

  nav_msgs::msg::Path path;
  geometry_msgs::msg::PoseStamped goal_pose;

  // Determine the path to follow
  if (goal_msg->has_goal) {
    // Need to call planning service
    feedback->is_planning = true;
    goal_handle->publish_feedback(feedback);

    goal_pose = goal_msg->goal;

    // Get current pose from TF
    geometry_msgs::msg::PoseStamped start_pose;
    try {
      auto transform = tf_buffer_->lookupTransform(
          get_parameter("map_frame").as_string(),
          get_parameter("base_link_frame").as_string(), tf2::TimePointZero);
      start_pose.header = transform.header;
      start_pose.pose.position.x = transform.transform.translation.x;
      start_pose.pose.position.y = transform.transform.translation.y;
      start_pose.pose.position.z = transform.transform.translation.z;
      start_pose.pose.orientation = transform.transform.rotation;
    } catch (tf2::TransformException &ex) {
      RCLCPP_ERROR(this->get_logger(), "Could not get current pose: %s",
                   ex.what());
      result->error_code =
          urc_msgs::action::NavigateToWaypoint::Result::PLANNING_FAILED;
      goal_handle->abort(result);
      publishZeroVelocity();
      return;
    }

    bool planning_success = false;
    path = callPlanningService(start_pose, goal_pose, planning_success);

    feedback->is_planning = false;

    if (!planning_success || path.poses.empty()) {
      result->error_code =
          urc_msgs::action::NavigateToWaypoint::Result::PLANNING_FAILED;
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
  params.desired_linear_velocity =
      get_parameter("desired_linear_velocity").as_double();
  params.max_angular_velocity =
      get_parameter("max_angular_velocity").as_double();
  params.heading_alignment_tolerance =
      get_parameter("heading_alignment_tolerance").as_double();
  params.enable_swerve_motion = get_parameter("enable_swerve_motion").as_bool();
  pure_pursuit::PurePursuit pure_pursuit(params);

  pure_pursuit.setPath(path);
  RCLCPP_INFO(this->get_logger(), "Lookahead distance: %f",
              params.lookahead_distance);
  RCLCPP_INFO(this->get_logger(), "Desired linear velocity: %f",
              params.desired_linear_velocity);
  RCLCPP_INFO(this->get_logger(), "Max angular velocity: %f",
              params.max_angular_velocity);
  RCLCPP_INFO(this->get_logger(), "Heading alignment tolerance: %f rad",
              params.heading_alignment_tolerance);
  RCLCPP_INFO(this->get_logger(), "swerve motion enabled: %s",
              params.enable_swerve_motion ? "true" : "false");
  RCLCPP_INFO(this->get_logger(), "Following path with %ld poses",
              path.poses.size());

  pure_pursuit::PurePursuitOutput output;
  rclcpp::Rate rate(10);

  while (rclcpp::ok()) {
    // Get current pose in map frame from TF
    geometry_msgs::msg::PoseStamped current_pose_map_frame_;
    try {
      auto transform = tf_buffer_->lookupTransform(
          get_parameter("map_frame").as_string(),
          get_parameter("base_link_frame").as_string(), tf2::TimePointZero);
      current_pose_map_frame_.header = transform.header;
      current_pose_map_frame_.pose.position.x =
          transform.transform.translation.x;
      current_pose_map_frame_.pose.position.y =
          transform.transform.translation.y;
      current_pose_map_frame_.pose.position.z =
          transform.transform.translation.z;
      current_pose_map_frame_.pose.orientation = transform.transform.rotation;
    } catch (tf2::TransformException &ex) {
      RCLCPP_WARN(this->get_logger(), "Could not get current pose: %s",
                  ex.what());
      rate.sleep();
      continue;
    }

    // Update feedback distance
    feedback->distance_to_goal = geometry_util::dist2D(
        current_pose_map_frame_.pose.position, goal_pose.pose.position);

    if (goal_handle->is_canceling()) {
      goal_handle->canceled(result);
      RCLCPP_INFO(this->get_logger(), "Goal has been canceled");
      break;
    } else if (feedback->distance_to_goal <
               get_parameter("goal_tolerance").as_double()) {
      bool heading_satisfied = true;

      if (enforce_heading) {
        double heading_error = geometry_util::angularDistance(
            current_pose_map_frame_.pose.orientation,
            goal_pose.pose.orientation);
        heading_satisfied =
            heading_error < get_parameter("goal_heading_tolerance").as_double();

        if (!heading_satisfied) {
          // For swerve drive, perform in-place turning to align heading
          if (get_parameter("enable_swerve_motion").as_bool()) {
            // Calculate signed heading error for proper turn direction
            tf2::Quaternion current_quat, goal_quat;
            tf2::fromMsg(current_pose_map_frame_.pose.orientation,
                         current_quat);
            tf2::fromMsg(goal_pose.pose.orientation, goal_quat);

            double current_yaw = tf2::getYaw(current_quat);
            double goal_yaw = tf2::getYaw(goal_quat);
            double signed_error = goal_yaw - current_yaw;

            // Normalize to [-pi, pi]
            while (signed_error > M_PI)
              signed_error -= 2.0 * M_PI;
            while (signed_error < -M_PI)
              signed_error += 2.0 * M_PI;

            geometry_msgs::msg::TwistStamped align_cmd;
            align_cmd.header.stamp = get_clock()->now();
            align_cmd.twist.linear.x = 0.0;
            align_cmd.twist.linear.y = 0.0;
            align_cmd.twist.angular.z =
                std::clamp(signed_error * 2.0, // Proportional control
                           -get_parameter("max_angular_velocity").as_double(),
                           get_parameter("max_angular_velocity").as_double());

            if (stamped_) {
              cmd_vel_stamped_pub_->publish(align_cmd);
            } else {
              cmd_vel_pub_->publish(align_cmd.twist);
            }

            RCLCPP_DEBUG(
                this->get_logger(),
                "Aligning final heading: error %.3f rad, omega %.3f rad/s",
                signed_error, align_cmd.twist.angular.z);

            goal_handle->publish_feedback(feedback);
            rate.sleep();
            continue;
          } else {
            RCLCPP_DEBUG(this->get_logger(),
                         "Position reached but heading error %.3f rad exceeds "
                         "tolerance %.3f rad",
                         heading_error,
                         get_parameter("goal_heading_tolerance").as_double());
          }
        }
      }

      if (heading_satisfied) {
        result->error_code =
            urc_msgs::action::NavigateToWaypoint::Result::SUCCESS;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Goal has been reached!");
        break;
      }
    } else if (getCost(current_costmap_, output.lookahead_point.point.x,
                       output.lookahead_point.point.y) >
               get_parameter("lethal_cost_threshold").as_double()) {
      // Obstacle detected - attempt to re-plan
      RCLCPP_WARN(this->get_logger(),
                  "Obstacle detected! Attempting to re-plan...");

      feedback->is_planning = true;
      feedback->replan_count++;
      goal_handle->publish_feedback(feedback);

      // Get current pose from TF for replanning
      geometry_msgs::msg::PoseStamped start_pose;
      try {
        auto transform = tf_buffer_->lookupTransform(
            get_parameter("map_frame").as_string(),
            get_parameter("base_link_frame").as_string(), tf2::TimePointZero);
        start_pose.header = transform.header;
        start_pose.pose.position.x = transform.transform.translation.x;
        start_pose.pose.position.y = transform.transform.translation.y;
        start_pose.pose.position.z = transform.transform.translation.z;
        start_pose.pose.orientation = transform.transform.rotation;
      } catch (tf2::TransformException &ex) {
        RCLCPP_ERROR(this->get_logger(),
                     "Could not get current pose for replanning: %s",
                     ex.what());
        result->error_code =
            urc_msgs::action::NavigateToWaypoint::Result::PLANNING_FAILED;
        goal_handle->abort(result);
        publishZeroVelocity();
        return;
      }

      bool planning_success = false;
      nav_msgs::msg::Path new_path =
          callPlanningService(start_pose, goal_pose, planning_success);

      feedback->is_planning = false;

      if (!planning_success || new_path.poses.empty()) {
        result->error_code =
            urc_msgs::action::NavigateToWaypoint::Result::PLANNING_FAILED;
        goal_handle->abort(result);
        RCLCPP_ERROR(this->get_logger(), "Re-planning failed");
        break;
      }

      // Update the path and continue
      path = new_path;
      pure_pursuit.setPath(path);
      RCLCPP_INFO(this->get_logger(),
                  "Re-planning successful, following new path with %ld poses",
                  path.poses.size());
    }

    output = pure_pursuit.getCommandVelocity(
        this->get_logger(),
        lookup_transform(get_parameter("base_link_frame").as_string(),
                         get_parameter("map_frame").as_string()));

    if (stamped_) {
      cmd_vel_stamped_pub_->publish(output.cmd_vel);
    } else {
      cmd_vel_pub_->publish(output.cmd_vel.twist);
    }

    // Publish rover position as PointStamped for rqt_plot
    geometry_msgs::msg::PointStamped rover_point;
    rover_point.header = current_pose_map_frame_.header;
    rover_point.point = current_pose_map_frame_.pose.position;
    rover_position_pub_->publish(rover_point);

    auto circle = create_lookahead_circle(
        current_pose_map_frame_.pose.position.x,
        current_pose_map_frame_.pose.position.y, params.lookahead_distance,
        get_parameter("map_frame").as_string());
    marker_pub_->publish(circle);

    // Publish the carrot point
    carrot_pub_->publish(output.lookahead_point);

    // Publish feedback
    goal_handle->publish_feedback(feedback);

    rate.sleep();
  }

  publishZeroVelocity();
}

} // namespace follower_action_server

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(follower_action_server::FollowerActionServer)
