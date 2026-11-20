#include "spiral_search.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <vector>

namespace urc_perception
{
namespace
{
constexpr double kTwoPi = 2.0 * M_PI;
constexpr int kMaxNewtonIterations = 32;
constexpr double kArcLengthToleranceMeters = 1e-9;

/// Fraction of a waypoint spacing below which the trailing partial step is dropped.
constexpr double kEndpointMergeFraction = 0.05;

bool isUsableLength(double value)
{
  return std::isfinite(value) && value > 0.0;
}

double spiralCoefficient(const SpiralSearchParameters & parameters)
{
  return parameters.track_spacing / kTwoPi;
}

/**
 * @brief Arc length from the pole of the spiral r = b * u, where u = r / b = theta + offset.
 *
 * Closed form of the integral of sqrt(r^2 + (dr/dtheta)^2) dtheta for an Archimedean spiral.
 */
double arcLengthFromPole(double u, double b)
{
  return 0.5 * b * (u * std::sqrt(1.0 + u * u) + std::asinh(u));
}

/**
 * @brief Invert the arc-length integral for the u that lies `target` meters past `u_start`.
 *
 * ds/du = b * sqrt(1 + u^2) is positive and increasing, so the large-u approximation
 * s ~ b * u^2 / 2 always overestimates u and Newton's method converges monotonically from it.
 */
double radiusParameterAtArcLength(double target, double u_start, double b)
{
  const double start_length = arcLengthFromPole(u_start, b);
  double u = std::sqrt(u_start * u_start + 2.0 * target / b);

  for (int iteration = 0; iteration < kMaxNewtonIterations; ++iteration) {
    const double error = arcLengthFromPole(u, b) - start_length - target;
    if (std::abs(error) < kArcLengthToleranceMeters) {
      break;
    }
    u -= error / (b * std::sqrt(1.0 + u * u));
  }

  return u;
}

SpiralWaypoint waypointAt(double u, double u_start, double b)
{
  const double theta = u - u_start;
  const double radius = b * u;
  const double sin_theta = std::sin(theta);
  const double cos_theta = std::cos(theta);

  SpiralWaypoint waypoint;
  waypoint.x = radius * cos_theta;
  waypoint.y = radius * sin_theta;
  waypoint.heading = std::atan2(
    b * sin_theta + radius * cos_theta,
    b * cos_theta - radius * sin_theta);

  return waypoint;
}

double totalArcLength(const SpiralSearchParameters & parameters)
{
  const double b = spiralCoefficient(parameters);
  return arcLengthFromPole(parameters.search_radius / b, b) -
         arcLengthFromPole(parameters.start_radius / b, b);
}

std::size_t plannedWaypointCount(double arc_length, double waypoint_spacing)
{
  const auto full_steps = static_cast<std::size_t>(std::floor(arc_length / waypoint_spacing));
  const double remainder = arc_length - static_cast<double>(full_steps) * waypoint_spacing;
  const bool needs_endpoint = remainder > kEndpointMergeFraction * waypoint_spacing;
  return full_steps + (needs_endpoint ? 2 : 1);
}
} // namespace

double trackSpacingFromCoverage(const CameraCoverage & coverage)
{
  const double swath = 2.0 * coverage.max_detection_range *
    std::sin(0.5 * coverage.horizontal_fov);
  return swath * (1.0 - coverage.overlap_fraction);
}

std::string validateCameraCoverage(const CameraCoverage & coverage)
{
  if (!std::isfinite(coverage.horizontal_fov) || coverage.horizontal_fov <= 0.0 ||
    coverage.horizontal_fov >= M_PI)
  {
    return "horizontal field of view must be between 0 and pi radians";
  }

  if (!isUsableLength(coverage.max_detection_range)) {
    return "maximum detection range must be positive";
  }

  if (!std::isfinite(coverage.overlap_fraction) || coverage.overlap_fraction < 0.0 ||
    coverage.overlap_fraction >= 1.0)
  {
    return "coverage overlap fraction must be within [0, 1)";
  }

  return {};
}

double innerTrackRadius(double track_spacing)
{
  return 0.5 * track_spacing;
}

std::string validateSpiralParameters(const SpiralSearchParameters & parameters)
{
  if (!isUsableLength(parameters.track_spacing)) {
    return "track spacing must be positive";
  }

  if (!isUsableLength(parameters.waypoint_spacing)) {
    return "waypoint spacing must be positive";
  }

  if (!std::isfinite(parameters.start_radius) || parameters.start_radius < 0.0) {
    return "start radius must be zero or positive";
  }

  if (!isUsableLength(parameters.search_radius)) {
    return "search radius must be positive";
  }

  if (parameters.search_radius <= parameters.start_radius) {
    return "search radius must exceed the start radius";
  }

  if (parameters.max_waypoints < 2) {
    return "waypoint limit must allow at least two waypoints";
  }

  const std::size_t required =
    plannedWaypointCount(totalArcLength(parameters), parameters.waypoint_spacing);
  if (required > parameters.max_waypoints) {
    return "spiral needs " + std::to_string(required) + " waypoints but the limit is " +
           std::to_string(parameters.max_waypoints);
  }

  return {};
}

SpiralPath generateArchimedeanSpiral(const SpiralSearchParameters & parameters)
{
  const std::string error = validateSpiralParameters(parameters);
  if (!error.empty()) {
    throw std::invalid_argument("Cannot generate spiral: " + error);
  }

  const double b = spiralCoefficient(parameters);
  const double u_start = parameters.start_radius / b;
  const double u_end = parameters.search_radius / b;

  SpiralPath path;
  path.arc_length = totalArcLength(parameters);

  const std::size_t count = plannedWaypointCount(path.arc_length, parameters.waypoint_spacing);
  path.waypoints.reserve(count);

  for (std::size_t index = 0; index + 1 < count; ++index) {
    const double distance = static_cast<double>(index) * parameters.waypoint_spacing;
    path.waypoints.push_back(
      waypointAt(radiusParameterAtArcLength(distance, u_start, b), u_start, b));
  }
  path.waypoints.push_back(waypointAt(u_end, u_start, b));

  return path;
}

} // namespace urc_perception
