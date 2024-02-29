#include "orchestrator.hpp"

// 3 relevant poses to maintain: Base Station, Rover Position, Waypoint Position
// 3 relevant frames to maintain: Absolute GPS, Metric Offset, Costmap Location
// At minimum, the x and y for each position is needed.
// This means a minimum of 18 numbers to track.

namespace orchestrator
{
Orchestrator::Orchestrator(const rclcpp::NodeOptions & options)
: rclcpp::Node("orchestrator", options)
{
  this->currentlyPlanning = false;
  this->purePursuitEnabled = 0; // IMPORTANT! Singular point tracking or path planning.
  this->maxDelta = 1.0;
  this->actualLongitude = -1;
  this->actualLatitude = -1;
  this->baseLatitude = -1;
  this->baseLongitude = -1;
  this->waypointLatitude = -1;
  this->waypointLongitude = -1;
  this->initialYaw = -1;
  this->currentYaw = -1;
  this->gpsTimestamp = this->get_clock()->now();
  current_metric_pose.position.x = -1;
  current_metric_pose.position.y = -1;
  current_metric_pose.position.z = -1;

  current_state_publisher = create_publisher<urc_msgs::msg::NavigationStatus>(
    "/current_navigation_state",
    rclcpp::SystemDefaultsQoS()
  );
  cmd_vel_publisher = create_publisher<geometry_msgs::msg::TwistStamped>(
    "/rover_drivetrain_controller/cmd_vel",
    rclcpp::SystemDefaultsQoS()
  );

  metric_offset_pose_publisher = create_publisher<geometry_msgs::msg::Pose>(
    "/metric_pose_offset",
    rclcpp::SystemDefaultsQoS()
  );
  costmap_offset_pose_publisher = create_publisher<geometry_msgs::msg::Pose>(
    "/costmap_pose",
    rclcpp::SystemDefaultsQoS()
  );

  metric_offset_pose_publisher = create_publisher<geometry_msgs::msg::Pose>(
    "/pose/metric", rclcpp::SystemDefaultsQoS()
  );
  costmap_offset_pose_publisher = create_publisher<geometry_msgs::msg::Pose>(
    "/pose/costmap", rclcpp::SystemDefaultsQoS()
  );

  imu_subscriber = create_subscription<sensor_msgs::msg::Imu>(
    "/imu/data", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Imu msg) {IMUCallback(msg);});
  set_base_subscriber = create_subscription<std_msgs::msg::Bool>(
    "/set_base", rclcpp::SystemDefaultsQoS(),
    [this](const std_msgs::msg::Bool msg) {SetBaseCallback(msg);});
  waypoint_subscriber = create_subscription<urc_msgs::msg::Waypoint>(
    "/waypoint", rclcpp::SystemDefaultsQoS(),
    [this](const urc_msgs::msg::Waypoint msg) {WaypointCallback(msg);});
  gps_subscriber = create_subscription<nav_msgs::msg::Odometry>(
    "/odometry/gps", rclcpp::SystemDefaultsQoS(),
    [this](const nav_msgs::msg::Odometry msg) {GPSCallback(msg);});
}

// Maintain robot pose->position
void Orchestrator::GPSCallback(const nav_msgs::msg::Odometry & msg)
{
  this->actualLongitude = msg.pose.pose.position.x;
  this->actualLatitude = msg.pose.pose.position.y;
  if (this->baseLatitude == -1) {
    this->baseLongitude = this->actualLongitude;
    this->baseLatitude = this->actualLatitude;
  }
  if (this->actualLatitude != -1 && this->actualLongitude != -1 &&
    this->waypointLatitude != -1 && this->waypointLongitude != -1)
  {
    RCLCPP_INFO(this->get_logger(), "Publishing Poses");
    PublishMetricPose(
      this->actualLatitude - this->baseLatitude,
      this->actualLongitude - this->baseLongitude);
    PublishCostmapPose(
      this->actualLatitude - this->baseLatitude,
      this->actualLongitude - this->baseLongitude);
  }
  DetermineState();
}

// Maintain robot pose->orientation
void Orchestrator::IMUCallback(const sensor_msgs::msg::Imu & msg)
{
  this->current_metric_pose.orientation.x = msg.orientation.x;
  this->current_metric_pose.orientation.y = msg.orientation.y;
  this->current_metric_pose.orientation.z = msg.orientation.z;
  this->current_metric_pose.orientation.w = msg.orientation.w;
  double x = msg.orientation.x;
  double y = msg.orientation.y;
  double z = msg.orientation.z;
  double w = msg.orientation.w;
  double yaw = atan2(2 * (w * x + y * z), 1 - 2 * (pow(2, x) + pow(2, y)));
  if (this->initialYaw == -1) {
    this->initialYaw = yaw;
  }
  this->currentYaw = yaw;
}

void Orchestrator::SetBaseCallback(const std_msgs::msg::Bool & msg)
{
  this->baseLongitude = this->actualLongitude;
  this->baseLatitude = this->actualLatitude;
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

// Transform offset to place on the costmap. (0, 0) is the bottom left corner, and the base station is at (50, 50)
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

  double deltaX = abs(actualLongitude - waypointLongitude);
  double deltaY = abs(actualLatitude - waypointLatitude);
  double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
  if (distance < maxDelta) {
    state_message.message = "Goal";
    this->waypointLongitude = -1;
    this->waypointLatitude = -1;
  } else {
    state_message.message = "Navigating";
  }
  current_state_publisher->publish(state_message);
  if (this->purePursuitEnabled) { // IMPORTANT: only for very basic testing
    PurePursuit(deltaX, deltaY);
  } else {
    PathPlanning();
  }
  return;
}

void Orchestrator::PurePursuit(double deltaX, double deltaY)
{
  // Publishing of Command Velocities.
  double errorDThreshold = 0.1;
  double errorZThreshold = 0.1;

  geometry_msgs::msg::TwistStamped cmd_vel;
  double errorD = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
  double currentAngle = currentYaw - initialYaw;
  double errorZ = currentAngle - atan2(deltaY, deltaX);

  if (abs(errorZ >= errorZThreshold)) {
    cmd_vel.twist.angular.z = errorZ; // Will probably need to multiply by some constant.
  } else if (errorD >= errorDThreshold) {
    cmd_vel.twist.linear.x = errorD; // Will probably need to multiply by some constant.
  }
  cmd_vel_publisher->publish(cmd_vel);
}

void Orchestrator::PathPlanning() {
  // Make a request to path plan
  if (this->currentlyPlanning) {
    return;
  }
  this->currentlyPlanning = true;
  nav_msgs::msg::Path path;
  for (int i = 0; i < path.poses.size(); ++i) {
    double currentCostmapX = floor(((this->actualLongitude - this->baseLongitude) * 111139) * 4 + 50);
    double currentCostmapY = floor(((this->actualLatitude - this->baseLatitude) * 111139) * 4 + 50);
    while (abs(currentCostmapX - path.poses[i].pose.position.x) > 1 or abs(currentCostmapY - path.poses[i].pose.position.y) > 1) {
      PurePursuit(currentCostmapX - path.poses[i].pose.position.x, currentCostmapY - path.poses[i].pose.position.y);
    }
  }


  this->currentlyPlanning = false;
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(orchestrator::Orchestrator)
