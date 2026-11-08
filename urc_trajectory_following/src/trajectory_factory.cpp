#include "urc_trajectory_following/trajectory_factory.hpp"

#include "urc_trajectory_following/pure_pursuit/pure_pursuit.hpp"

#include <stdexcept>

namespace trajectory_following
{
namespace
{
constexpr char kPurePursuit[] = "pure_pursuit";
}

bool TrajectoryFactory::supports(const std::string & controller_type)
{
  return controller_type == kPurePursuit;
}

std::unique_ptr<TrajectoryController> TrajectoryFactory::create(
  const std::string & controller_type,
  const rclcpp::Node & node)
{
  if (controller_type == kPurePursuit) {
    pure_pursuit::PurePursuitParams params{
      node.get_parameter("lookahead_distance").as_double(),
      node.get_parameter("desired_linear_velocity").as_double(),
      node.get_parameter("max_angular_velocity").as_double(),
      node.get_parameter("heading_alignment_tolerance").as_double(),
      node.get_parameter("enable_swerve_motion").as_bool()
    };
    return std::make_unique<pure_pursuit::PurePursuit>(params);
  }

  throw std::invalid_argument("Unsupported trajectory controller: " + controller_type);
}
}  // namespace trajectory_following
