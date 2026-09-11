#include "urc_state_machine/nav_coordinator.hpp"

#include <functional>
#include <rclcpp_components/register_node_macro.hpp>

namespace nav_coordinator
{
NavCoordinator::NavCoordinator(const rclcpp::NodeOptions & options)
: rclcpp::Node("nav_coordinator", options)
{
  declare_parameter<std::string>("waypoint_topic", "/nav/waypoint");
  declare_parameter<std::string>("gps_waypoint_topic", "/waypoint");
  declare_parameter<std::string>("follower_action_name", "navigate_to_waypoint");
  declare_parameter<bool>("cancel_on_new_waypoint", true);
  declare_parameter<std::string>("map_frame_id", "map");
  declare_parameter<std::string>("utm_frame_id", "utm");

  follower_action_name_ = get_parameter("follower_action_name").as_string();
  cancel_on_new_waypoint_ = get_parameter("cancel_on_new_waypoint").as_bool();
  map_frame_id_ = get_parameter("map_frame_id").as_string();
  utm_frame_id_ = get_parameter("utm_frame_id").as_string();

  tf_buffer_ = std::make_shared<tf2_ros::Buffer>(get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  state_publisher_ = create_publisher<std_msgs::msg::String>("nav_coordinator_state", 10);
  follower_client_ = rclcpp_action::create_client<NavigateToWaypoint>(this, follower_action_name_);

  waypoint_subscriber_ = create_subscription<geometry_msgs::msg::PoseStamped>(
    get_parameter("waypoint_topic").as_string(),
    rclcpp::SystemDefaultsQoS(),
    std::bind(&NavCoordinator::handleWaypoint, this, std::placeholders::_1));

  gps_waypoint_subscriber_ = create_subscription<urc_msgs::msg::Waypoint>(
    get_parameter("gps_waypoint_topic").as_string(),
    rclcpp::SystemDefaultsQoS(),
    std::bind(&NavCoordinator::handleGpsWaypoint, this, std::placeholders::_1));

  RCLCPP_INFO(
    get_logger(),
    "Nav Coordinator ready. Pose waypoints on '%s', GPS waypoints on '%s', forwarding to action '%s'.",
    get_parameter("waypoint_topic").as_string().c_str(),
    get_parameter("gps_waypoint_topic").as_string().c_str(),
    follower_action_name_.c_str());

  if (state_publisher_) {
    publishState();
  }
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(nav_coordinator::NavCoordinator)
