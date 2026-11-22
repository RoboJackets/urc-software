#ifndef PATH_GEOMETRY_HPP_
#define PATH_GEOMETRY_HPP_

#include <Eigen/Dense>

#include <vector>

namespace lqr
{
/** Rover pose in the path's frame: position (m) and heading (rad). */
struct PlanarPose
{
  Eigen::Vector2d position;
  double heading;
};

/**
 * Errors of the rover relative to the closest point on the path.
 * lateral_error is positive when the rover is left of the path; heading_error is rover heading
 * minus path heading, wrapped to [-pi, pi]; curvature is positive for left turns (1/m).
 */
struct PathTrackingError
{
  double lateral_error;
  double heading_error;
  double curvature;
  double arc_length;
};

/**
 * A polyline path with arc-length lookup. Heading and curvature are measured over
 * +-smoothing_window meters, which smooths the 45 degree steps of grid-based A* paths.
 */
class PathGeometry
{
public:
  /** @throws std::invalid_argument if the path has no two distinct points. */
  PathGeometry(std::vector<Eigen::Vector2d> points, double smoothing_window);

  PathTrackingError trackingError(const PlanarPose & pose) const;

  /** Point at the given arc length, clamped to the ends of the path. */
  Eigen::Vector2d pointAt(double arc_length) const;

  double length() const;

private:
  double closestArcLength(const Eigen::Vector2d & position) const;

  std::vector<Eigen::Vector2d> points_;
  std::vector<double> arc_lengths_;
  double smoothing_window_;
};
}  // namespace lqr

#endif  // PATH_GEOMETRY_HPP_
