#include "urc_state_machine/spiral_search_pattern.hpp"

#include <cmath>
#include <stdexcept>

namespace urc_state_machine
{
namespace
{
constexpr double kTwoPi = 2.0 * M_PI;
constexpr double kMaxSearchWaypoints = 2000.0;

bool isPositiveFinite(double value)
{
  return std::isfinite(value) && value > 0.0;
}
}  

void validateSpiralSearchConfig(const SpiralSearchConfig & config)
{
  if (!isPositiveFinite(config.radius_m) || !isPositiveFinite(config.ring_spacing_m) ||
    !isPositiveFinite(config.point_spacing_m))
  {
    throw std::invalid_argument("spiral search distances must be positive and finite");
  }
  if (config.ring_spacing_m > config.radius_m) {
    throw std::invalid_argument("search_ring_spacing_m must not exceed search_radius_m");
  }

  const double spiral_length = M_PI * config.radius_m * config.radius_m / config.ring_spacing_m;
  if (spiral_length / config.point_spacing_m > kMaxSearchWaypoints) {
    throw std::invalid_argument("spiral search would generate too many waypoints");
  }
}

std::vector<PlanarPose> generateSpiralSearch(
  double center_x, double center_y, const SpiralSearchConfig & config)
{
  validateSpiralSearchConfig(config);

  const double b = config.ring_spacing_m / kTwoPi;
  std::vector<PlanarPose> poses;

  for (double theta = kTwoPi; b * theta <= config.radius_m; ) {
    const double r = b * theta;
    const double cos_theta = std::cos(theta);
    const double sin_theta = std::sin(theta);

    PlanarPose pose;
    pose.x = center_x + r * cos_theta;
    pose.y = center_y + r * sin_theta;
    pose.yaw = std::atan2(b * sin_theta + r * cos_theta, b * cos_theta - r * sin_theta);
    poses.push_back(pose);

    theta += config.point_spacing_m / std::sqrt(r * r + b * b);
  }

  return poses;
}

}  