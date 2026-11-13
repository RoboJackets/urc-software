#include "urc_trajectory_following/trajectory_factory.hpp"

#include "urc_trajectory_following/lqr/lqr_tracker.hpp"
#include "urc_trajectory_following/pure_pursuit/pure_pursuit.hpp"

#include <stdexcept>

namespace trajectory_following
{
namespace
{
constexpr char kPurePursuit[] = "pure_pursuit";
constexpr char kLqr[] = "lqr";
}

bool TrajectoryFactory::supports(const std::string & controller_type)
{
  return controller_type == kPurePursuit || controller_type == kLqr;
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
  if (controller_type == kLqr) {
    lqr::LqrParams params{
      node.get_parameter("desired_linear_velocity").as_double(),
      node.get_parameter("max_angular_velocity").as_double(),
      node.get_parameter("heading_alignment_tolerance").as_double(),
      node.get_parameter("lookahead_distance").as_double(),
      node.get_parameter("control_period").as_double(),
      node.get_parameter("lqr_max_lateral_error").as_double(),
      node.get_parameter("lqr_max_heading_error").as_double(),
      node.get_parameter("lqr_max_angular_correction").as_double()
    };
    return std::make_unique<lqr::LqrTracker>(params);
  }

  throw std::invalid_argument("Unsupported trajectory controller: " + controller_type);
}
}  // namespace trajectory_following
