#ifndef TRAJECTORY_FACTORY_HPP_
#define TRAJECTORY_FACTORY_HPP_

#include "urc_trajectory_following/trajectory_controller.hpp"

#include <memory>
#include <string>

#include <rclcpp/node.hpp>

namespace trajectory_following
{
class TrajectoryFactory
{
public:
  static bool supports(const std::string & controller_type);

  static std::unique_ptr<TrajectoryController> create(
    const std::string & controller_type,
    const rclcpp::Node & node);
};
}  // namespace trajectory_following

#endif  // TRAJECTORY_FACTORY_HPP_
