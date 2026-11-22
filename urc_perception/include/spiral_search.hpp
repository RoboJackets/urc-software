#ifndef SPIRAL_SEARCH_HPP_
#define SPIRAL_SEARCH_HPP_

#include <cstddef>
#include <string>
#include <vector>

namespace urc_perception
{

/**
 * @brief Planar waypoint on the spiral, expressed relative to the search center.
 *
 * Positions are meters along the search frame's x and y axes. The heading is radians
 * counterclockwise from +x and points along the spiral tangent.
 */
struct SpiralWaypoint
{
  double x;
  double y;
  double heading;
};

/// Geometry of the outward Archimedean spiral r(theta) = start_radius + b * theta.
struct SpiralSearchParameters
{
  /// [m] Outward extent. Generation ends at the first waypoint reaching this radius.
  double search_radius;

  /// [m] Radius at theta = 0.
  double start_radius;

  /// [m] Radial growth per revolution, so b = track_spacing / (2 * pi).
  double track_spacing;

  /// [m] Arc length between consecutive waypoints.
  double waypoint_spacing;

  /// Upper bound on returned waypoints, so a large radius cannot exhaust memory.
  std::size_t max_waypoints;
};

/// Spiral samples together with the distance the rover travels to follow them.
struct SpiralPath
{
  std::vector<SpiralWaypoint> waypoints;

  /// [m] Arc length from the first to the last waypoint.
  double arc_length;
};

/// Ground coverage of a forward-facing detection camera, used to derive spiral spacing.
struct CameraCoverage
{
  /// [rad] Horizontal field of view.
  double horizontal_fov;

  /// [m] Range beyond which the target is no longer reliably detected.
  double max_detection_range;

  /// Fraction of the swath shared between neighboring spiral turns, in [0, 1).
  double overlap_fraction;
};

/**
 * @brief Radial spacing between spiral turns that keeps ground coverage continuous.
 *
 * A ground target at lateral offset y from a straight track can only enter the camera wedge
 * within detection range when |y| <= range * sin(fov / 2), so the swath the camera sweeps out
 * is 2 * range * sin(fov / 2). The overlap fraction narrows that swath to absorb pose error,
 * target orientation, and the curvature the straight-track model ignores.
 */
double trackSpacingFromCoverage(const CameraCoverage & coverage);

/// Describes why the coverage cannot produce a spacing, or an empty string when it is usable.
std::string validateCameraCoverage(const CameraCoverage & coverage);

/**
 * @brief Radius at which the spiral should start, given its track spacing.
 *
 * Half a track spacing out, the innermost turn's swath already sweeps the center disc, so
 * nothing is lost by skipping the pole. Skipping it matters because the spiral's curvature
 * radius shrinks to track_spacing / (4 * pi) there, tighter than the rover can steer.
 */
double innerTrackRadius(double track_spacing);

/// Describes why the parameters cannot produce a spiral, or an empty string when they can.
std::string validateSpiralParameters(const SpiralSearchParameters & parameters);

/**
 * @brief Sample an outward Archimedean spiral at uniform arc length.
 *
 * Uniform arc length rather than uniform theta keeps waypoint density constant, which matters
 * because a spiral sampled uniformly in theta bunches waypoints near the center and stretches
 * them apart on the outer turns.
 *
 * @throws std::invalid_argument when validateSpiralParameters rejects the parameters.
 */
SpiralPath generateArchimedeanSpiral(const SpiralSearchParameters & parameters);

} // namespace urc_perception

#endif // SPIRAL_SEARCH_HPP_
