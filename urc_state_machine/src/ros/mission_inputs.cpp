#include "urc_state_machine/nav_coordinator.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include "urc_state_machine/mission_geometry.hpp"

namespace nav_coordinator
{
void NavCoordinator::initializeInputs()
{
  command_sub_ = create_subscription<Command>(
    parameters_.command_topic, rclcpp::QoS(10),
    [this](Command::ConstSharedPtr message) {
      command(*message);
    });
  astronaut_sub_ = create_subscription<Pose>(
    parameters_.astronaut_topic, rclcpp::SensorDataQoS(),
    [this](Pose::ConstSharedPtr message) {
      if (!fresh(message->header.stamp, parameters_.target_max_age)) {
        return;
      }
      auto pose = mapPose(*message);
      if (pose) {
        // Reacquisition must establish stationarity again after a detection gap.
        if (!astronautFresh()) {
          tracking_.reset();
        }
        tracking_.observe(*pose, parameters_.stationary_distance);
      }
    });
  aruco_sub_ = create_subscription<urc_msgs::msg::ArucoDetection>(
    parameters_.aruco_topic, rclcpp::SensorDataQoS(),
    [this](urc_msgs::msg::ArucoDetection::ConstSharedPtr message) {
      if (mission_.kind != Kind::ROUTE || !parameters_.aruco_refinement ||
      !fresh(message->pose.header.stamp, parameters_.target_max_age))
      {
        return;
      }
      auto pose = mapPose(message->pose);
      if (pose &&
      urc_state_machine::distanceTo(
        *pose,
        mission_.waypoint) <= parameters_.aruco_association_radius &&
      (!mission_.marker ||
      rclcpp::Time(pose->header.stamp) > rclcpp::Time(mission_.marker->header.stamp)))
      {
        mission_.marker = pose;
      }
    });
  waypoint_sub_ = create_subscription<Pose>(
    parameters_.waypoint_topic, rclcpp::QoS(10),
    [this](Pose::ConstSharedPtr message) {
      waypoint(*message);
    });
  gps_sub_ = create_subscription<urc_msgs::msg::Waypoint>(
    parameters_.gps_topic, rclcpp::QoS(10),
    [this](urc_msgs::msg::Waypoint::ConstSharedPtr message) {
      gpsWaypoint(*message);
    });
}

bool NavCoordinator::fresh(const builtin_interfaces::msg::Time & stamp, double max_age) const
{
  if (stamp.sec < 0 || stamp.nanosec >= 1000000000U || (stamp.sec == 0 && stamp.nanosec == 0)) {
    return false;
  }
  const double age = (now() - rclcpp::Time(stamp)).seconds();
  return age >= 0.0 && age <= max_age;
}

std::optional<NavCoordinator::Pose> NavCoordinator::mapPose(const Pose & input) const
{
  if (!urc_state_machine::validPose(input)) {
    return std::nullopt;
  }
  if (input.header.frame_id == parameters_.map_frame) {
    return input;
  }
  try {
    auto result = tf_buffer_->transform(input, parameters_.map_frame, tf2::durationFromSec(0.0));
    result.header.stamp = input.header.stamp;
    return result;
  } catch (const tf2::TransformException &) {
    return std::nullopt;
  }
}

std::optional<NavCoordinator::Pose> NavCoordinator::roverPose() const
{
  try {
    auto transform = tf_buffer_->lookupTransform(
      parameters_.map_frame, parameters_.base_frame, tf2::TimePointZero);
    if (!fresh(transform.header.stamp, parameters_.target_max_age)) {
      return std::nullopt;
    }
    Pose pose;
    pose.header = transform.header;
    pose.pose.position.x = transform.transform.translation.x;
    pose.pose.position.y = transform.transform.translation.y;
    pose.pose.position.z = transform.transform.translation.z;
    pose.pose.orientation = transform.transform.rotation;
    return urc_state_machine::validPose(pose) ? std::optional<Pose>(pose) : std::nullopt;
  } catch (const tf2::TransformException &) {
    return std::nullopt;
  }
}

bool NavCoordinator::astronautFresh() const
{
  return tracking_.pose() && fresh(tracking_.pose()->header.stamp, parameters_.target_max_age);
}
bool NavCoordinator::markerFresh() const
{
  return mission_.marker && fresh(mission_.marker->header.stamp, parameters_.target_max_age);
}
}  // namespace nav_coordinator
