#include "waypoint_state_machine.hpp"

namespace waypoint_state_machine
{
WaypointStateMachine::WaypointStateMachine(const rclcpp::NodeOptions & options)
: rclcpp::Node("waypoint_state_machine", options)
{
  this->maxDelta = 1.0;
  this->actualLongitude = -1;
  this->actualLatitude = -1;
  this->waypointLatitude = -1;
  this->waypointLongitude = -1;
  current_state_publisher = create_publisher<urc_msgs::msg::NavigationStatus>(
    "/current_navigation_state",
    rclcpp::SystemDefaultsQoS()
  );
  cmd_vel_publisher = create_publisher<geometry_msgs::msg::Twist>(
    "/rover_drivetrain_controller/cmd_vel_unstamped",
    rclcpp::SystemDefaultsQoS()
  );
  waypoint_subscriber = create_subscription<urc_msgs::msg::Waypoint>(
    "/waypoint", rclcpp::SystemDefaultsQoS(),
    [this](const urc_msgs::msg::Waypoint msg) {WaypointCallback(msg);});
  gps_subscriber = create_subscription<sensor_msgs::msg::NavSatFix>(
    "/gps/data", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::NavSatFix msg) {GPSCallback(msg);});
}

void WaypointStateMachine::WaypointCallback(const urc_msgs::msg::Waypoint & msg)
{
  this->waypointLatitude = msg.latitude;
  this->waypointLongitude = msg.longitude;
  DetermineState();
}

void WaypointStateMachine::GPSCallback(const sensor_msgs::msg::NavSatFix & msg)
{
  this->actualLatitude = msg.latitude;
  this->actualLongitude = msg.longitude;
  DetermineState();
}

void WaypointStateMachine::DetermineState()
{
  urc_msgs::msg::NavigationStatus state_message;
  if (actualLatitude == -1 || waypointLatitude == -1) {
    state_message.message = "NoGPS";
  }

  double deltaX = abs(actualLatitude - waypointLatitude);
  double deltaY = abs(actualLongitude - waypointLongitude);
  double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
  if (distance < maxDelta) {
    state_message.message = "Goal";
  } else {
    state_message.message = "Navigating";
  }

  // Publishing of Command Velocities.
  double errorDThreshold = 0.1;
  double errorZThreshold = 0.1;

  geometry_msgs::msg::Twist cmd_vel;
  double errorD = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
  if (errorD >= errorDThreshold) {
    cmd_vel.linear.x = errorD; // Will probably need to multiply by some constant.
  }

  double currentAngle = 0; // NEED TO CHANGE THIS
  double errorZ = currentAngle - atan2(deltaY, deltaX);
  if (abs(errorZ >= errorZThreshold)) {
    cmd_vel.angular.z = errorZ; // Will probably need to multiply by some constant.
  }

  cmd_vel_publisher->publish(cmd_vel);
  current_state_publisher->publish(state_message);
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(waypoint_state_machine::WaypointStateMachine)
