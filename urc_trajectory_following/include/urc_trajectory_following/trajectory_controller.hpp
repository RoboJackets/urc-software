#ifndef TRAJECTORY_CONTROLLER_HPP_
#define TRAJECTORY_CONTROLLER_HPP_

#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/logger.hpp>

namespace trajectory_following
{
struct TrajectoryOutput
{
  geometry_msgs::msg::TwistStamped cmd_vel;
  geometry_msgs::msg::PointStamped tracking_point;
};

class TrajectoryController
{
public:
  virtual ~TrajectoryController() = default;

  virtual void setPath(const nav_msgs::msg::Path & path) = 0;

  virtual TrajectoryOutput getCommandVelocity(
    const rclcpp::Logger & logger,
    const geometry_msgs::msg::TransformStamped & map_to_base_link) = 0;
};
}  // namespace trajectory_following

#endif  // TRAJECTORY_CONTROLLER_HPP_
