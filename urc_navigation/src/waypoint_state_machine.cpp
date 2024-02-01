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

  current_state_publisher->publish(state_message);
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(waypoint_state_machine::WaypointStateMachine)
