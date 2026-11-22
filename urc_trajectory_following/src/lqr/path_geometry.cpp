#include "urc_trajectory_following/lqr/path_geometry.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <utility>

namespace lqr
{
namespace
{
constexpr double kMinimumSegmentLength = 1e-6;

double wrapAngle(double angle)
{
  return std::atan2(std::sin(angle), std::cos(angle));
}

double cross(const Eigen::Vector2d & a, const Eigen::Vector2d & b)
{
  return a.x() * b.y() - a.y() * b.x();
}

/** Signed curvature of the circle through three points (Menger curvature). */
double curvatureThrough(
  const Eigen::Vector2d & back, const Eigen::Vector2d & middle, const Eigen::Vector2d & ahead)
{
  const Eigen::Vector2d first = middle - back;
  const Eigen::Vector2d second = ahead - middle;
  const double denominator = first.norm() * second.norm() * (ahead - back).norm();
  if (denominator < kMinimumSegmentLength) {
    return 0.0;
  }
  return 2.0 * cross(first, second) / denominator;
}
}  // namespace

PathGeometry::PathGeometry(std::vector<Eigen::Vector2d> points, double smoothing_window)
: smoothing_window_(smoothing_window)
{
  for (auto & point : points) {
    if (points_.empty() || (point - points_.back()).norm() > kMinimumSegmentLength) {
      points_.push_back(std::move(point));
    }
  }
  if (points_.size() < 2) {
    throw std::invalid_argument("PathGeometry needs at least two distinct points");
  }
  arc_lengths_.push_back(0.0);
  for (std::size_t i = 1; i < points_.size(); ++i) {
    arc_lengths_.push_back(arc_lengths_.back() + (points_[i] - points_[i - 1]).norm());
  }
}

double PathGeometry::length() const
{
  return arc_lengths_.back();
}

Eigen::Vector2d PathGeometry::pointAt(double arc_length) const
{
  const double clamped = std::clamp(arc_length, 0.0, length());
  const auto upper = std::upper_bound(arc_lengths_.begin(), arc_lengths_.end(), clamped);
  const std::size_t segment = std::min<std::size_t>(
    std::max<std::ptrdiff_t>(std::distance(arc_lengths_.begin(), upper) - 1, 0),
    points_.size() - 2);
  const double segment_length = arc_lengths_[segment + 1] - arc_lengths_[segment];
  const double fraction = (clamped - arc_lengths_[segment]) / segment_length;
  return points_[segment] + fraction * (points_[segment + 1] - points_[segment]);
}

double PathGeometry::closestArcLength(const Eigen::Vector2d & position) const
{
  double best_distance = std::numeric_limits<double>::infinity();
  double best_arc_length = 0.0;
  for (std::size_t i = 0; i + 1 < points_.size(); ++i) {
    const Eigen::Vector2d segment = points_[i + 1] - points_[i];
    const double fraction = std::clamp(
      (position - points_[i]).dot(segment) / segment.squaredNorm(), 0.0, 1.0);
    const double distance = (points_[i] + fraction * segment - position).norm();
    if (distance < best_distance) {
      best_distance = distance;
      best_arc_length = arc_lengths_[i] + fraction * segment.norm();
    }
  }
  return best_arc_length;
}

PathTrackingError PathGeometry::trackingError(const PlanarPose & pose) const
{
  const double arc_length = closestArcLength(pose.position);
  const Eigen::Vector2d back = pointAt(arc_length - smoothing_window_);
  const Eigen::Vector2d middle = pointAt(arc_length);
  const Eigen::Vector2d ahead = pointAt(arc_length + smoothing_window_);

  const Eigen::Vector2d tangent = (ahead - back).normalized();
  const double path_heading = std::atan2(tangent.y(), tangent.x());

  PathTrackingError error;
  error.lateral_error = cross(tangent, pose.position - middle);
  error.heading_error = wrapAngle(pose.heading - path_heading);
  error.curvature = curvatureThrough(back, middle, ahead);
  error.arc_length = arc_length;
  return error;
}
}  // namespace lqr
