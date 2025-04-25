#include "search_path_planner.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include "urc_msgs/action/search_aruco.hpp"

namespace search_path_planner
{
SearchPathPlanner::SearchPathPlanner(const rclcpp::NodeOptions & options)
: Node("search_for_aruco", options)
{
  RCLCPP_INFO(this->get_logger(), "Search for ARUCO behavior server has been started.");

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  generate_search_path_service_ = create_service<urc_msgs::srv::GenerateSearchPath>(
    "generate_search_path",
    std::bind(&SearchPathPlanner::generateSearchPath, this, std::placeholders::_1, std::placeholders::_2));

  // Get current pose
  robot_pose_subscriber_ = create_subscription<nav_msgs::msg::Odometry>(
    "/odometry/filtered_global",
    rclcpp::SystemDefaultsQoS(),
    [this](const nav_msgs::msg::Odometry::SharedPtr msg) {
      current_pose_ = msg->pose.pose;
    });
}

void SearchPathPlanner::generateSearchPath(
  const std::shared_ptr<urc_msgs::srv::GenerateSearchPath::Request> request,
  std::shared_ptr<urc_msgs::srv::GenerateSearchPath::Response> response)
{
  // Wait until base_link to map transform is available
  while (!tf_buffer_->canTransform("map", "base_link", tf2::TimePointZero)) {
    RCLCPP_INFO(this->get_logger(), "Waiting for transform from base_link to map...");
    rclcpp::sleep_for(std::chrono::seconds(1));
  }

  const double spiral_coeff = 0.1;

  RCLCPP_INFO(this->get_logger(), "Transform from base_link to map is available.");

  // Generate a search path
  rclcpp::Time now = this->now();
  nav_msgs::msg::Path path;
  path.header.frame_id = "map";
  path.header.stamp = now;

  // Lookup transform from base_link to map
  geometry_msgs::msg::TransformStamped transform;
  try {
    transform = tf_buffer_->lookupTransform("map", "base_link", tf2::TimePointZero);
  } catch (tf2::TransformException & ex) {
    RCLCPP_ERROR(this->get_logger(), "Failed to lookup transform: %s", ex.what());
    throw std::runtime_error("Failed to lookup transform.");
  }

  for (double t = 0; t < 12 * M_PI; t += M_PI / 4) {
    geometry_msgs::msg::PoseStamped pose;
    pose.header.frame_id = "map";
    pose.header.stamp = now;

    pose.pose.position.x = spiral_coeff * t * cos(t);
    pose.pose.position.y = spiral_coeff * t * sin(t);
    pose.pose.orientation.w = 1.0;

    // Transform pose to map frame
    tf2::doTransform(pose.pose, pose.pose, transform);

    path.poses.push_back(pose);
  }

  response->path = path;
  response->error_code = urc_msgs::srv::GenerateSearchPath::Response::SUCCESS;
}

} // namespace search_path_planner

#include <rclcpp_components/register_node_macro.hpp>
