#include "orchestrator.hpp"

namespace orchestrator
{
Orchestrator::Orchestrator(const rclcpp::NodeOptions & options)
: rclcpp::Node("orchestrator", options)
{
  this->purePursuitEnabled = 1;
  this->maxDelta = 1.0;
  this->actualLongitude = -1;
  this->actualLatitude = -1;
  this->baseLatitude = -1;
  this->baseLongitude = -1;
  this->waypointLatitude = -1;
  this->waypointLongitude = -1;
  this->gpsTimestamp = this->get_clock()->now();
  current_metric_pose.position.x = -1;
  current_metric_pose.position.y = -1;
  current_metric_pose.position.z = -1;

  current_state_publisher = create_publisher<urc_msgs::msg::NavigationStatus>(
    "/current_navigation_state",
    rclcpp::SystemDefaultsQoS()
  );
  cmd_vel_publisher = create_publisher<geometry_msgs::msg::Twist>(
    "/rover_drivetrain_controller/cmd_vel_unstamped",
    rclcpp::SystemDefaultsQoS()
  );

  imu_subscriber = create_subscription<sensor_msgs::msg::Imu>(
    "/imu", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Imu msg) {IMUCallback(msg);});
  set_base_subscriber = create_subscription<std_msgs::msg::Bool>(
    "/set_base", rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::Bool msg) {SetBaseCallback(msg);});
  waypoint_subscriber = create_subscription<urc_msgs::msg::Waypoint>(
    "/waypoint", rclcpp::SystemDefaultsQoS(),
    [this](const urc_msgs::msg::Waypoint msg) {WaypointCallback(msg);});
  gps_subscriber = create_subscription<sensor_msgs::msg::NavSatFix>(
    "/gps/data", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::NavSatFix msg) {GPSCallback(msg);});
}

void Orchestrator::GPSCallback(const sensor_msgs::msg::NavSatFix & msg)
{
  this->actualLatitude = msg.latitude;
  this->actualLongitude = msg.longitude;
  if (this->baseLatitude == -1) {
    this->baseLatitude = this->actualLatitude;
    this->baseLongitude = this->actualLongitude;
  }
  PublishMetricPose(
    this->actualLatitude - this->baseLatitude,
    this->actualLongitude - this->baseLongitude);
  PublishCostmapPose(
    this->actualLatitude - this->baseLatitude,
    this->actualLongitude - this->baseLongitude);
  DetermineState();
}

void Orchestrator::IMUCallback(const sensor_msgs::msg::Imu & msg)
{
  this->current_metric_pose.orientation.x = msg.orientation.x;
  this->current_metric_pose.orientation.y = msg.orientation.y;
  this->current_metric_pose.orientation.z = msg.orientation.z;
  this->current_metric_pose.orientation.w = msg.orientation.w;
}

void Orchestrator::SetBaseCallback(const std_msgs::msg::Bool & msg)
{
  this->baseLatitude = this->actualLatitude;
  this->baseLongitude = this->actualLongitude;
}

void Orchestrator::WaypointCallback(const urc_msgs::msg::Waypoint & msg)
{
  this->waypointLatitude = msg.latitude;
  this->waypointLongitude = msg.longitude;
  DetermineState();
}

void Orchestrator::PublishMetricPose(double gpsOffsetX, double gpsOffsetY)
{
  this->current_metric_pose.position.x = gpsOffsetX * 111139;
  this->current_metric_pose.position.y = gpsOffsetY * 111139;
  metric_offset_pose_publisher->publish(current_metric_pose);
}

void Orchestrator::PublishCostmapPose(double gpsOffsetX, double gpsOffsetY)
{
  this->current_costmap_pose.position.x = floor((gpsOffsetX * 111139) * 4 + 50);
  this->current_costmap_pose.position.y = floor((gpsOffsetY * 111139) * 4 + 50);
  costmap_offset_pose_publisher->publish(current_costmap_pose);
}

void Orchestrator::DetermineState()
{
  this->gpsTimestamp = this->get_clock()->now();

  urc_msgs::msg::NavigationStatus state_message;
  if (actualLatitude == -1 || actualLongitude == -1) {
    state_message.message = "NoGPS";
    current_state_publisher->publish(state_message);
    return;
  } else if (waypointLatitude == -1 || waypointLongitude == -1) {
    state_message.message = "NoWaypoint";
    current_state_publisher->publish(state_message);
    return;
  }

  double deltaX = abs(actualLatitude - waypointLatitude);
  double deltaY = abs(actualLongitude - waypointLongitude);
  double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
  if (distance < maxDelta) {
    state_message.message = "Goal";
    this->waypointLatitude = -1;
    this->waypointLongitude = -1;
  } else {
    state_message.message = "Navigating";
  }
  current_state_publisher->publish(state_message);
  if (this->purePursuitEnabled) { // IMPORTANT: only for very basic testing
    PurePursuit(deltaX, deltaY);
  }
}

void Orchestrator::PurePursuit(double deltaX, double deltaY)
{
  // Publishing of Command Velocities.
  double errorDThreshold = 0.1;
  double errorZThreshold = 0.1;

  geometry_msgs::msg::Twist cmd_vel;
  double errorD = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
  double currentAngle = 0; // NEED TO CHANGE THIS
  double errorZ = currentAngle - atan2(deltaY, deltaX);

  if (abs(errorZ >= errorZThreshold)) {
    cmd_vel.angular.z = errorZ; // Will probably need to multiply by some constant.
  } else if (errorD >= errorDThreshold) {
    cmd_vel.linear.x = errorD; // Will probably need to multiply by some constant.
  }

  cmd_vel_publisher->publish(cmd_vel);
  // sleep(15);
  // RCLCPP_INFO(this->get_logger(), "15 seconds");
  // if ((this->get_clock()->now() - this->gpsTimestamp).seconds() > 15) {
  //   RCLCPP_INFO(this->get_logger(), "True");
  // }
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(orchestrator::Orchestrator)
