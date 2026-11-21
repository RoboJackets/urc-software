#include "urc_path_planning/bspline_smoother.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

namespace urc_path_planning {
namespace {
using Point = geometry_msgs::msg::Point;

constexpr std::size_t kDegree = 3; //
constexpr std::size_t kMinimumControlPoints = kDegree + 1; //
constexpr std::size_t kDenseSamplesPerSpan = 20; //
constexpr double kEpsilon = 1e-9; //

double distance(const Point & first, const Point & second) { //distance of change between the previous point and the new point
  const double delta_x = second.x - first.x;
  const double delta_y = second.y - first.y;
  const double delta_z = second.z - first.z;
  return std::sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

Point interpolate(const Point & first, const Point & second, double ratio) { //interpolates
  Point point;
  point.x = first.x + ratio * (second.x - first.x);
  point.y = first.y + ratio * (second.y - first.y);
  point.z = first.z + ratio * (second.z - first.z);
  return point;
}

std::vector<double> createClampedUniformKnots(std::size_t control_point_count) { //
  const std::size_t knot_count = control_point_count + kDegree + 1;
  std::vector<double> knots(knot_count, 0.0);

  for (std::size_t index = kDegree + 1; index < control_point_count; ++index) {
    knots[index] = static_cast<double>(index - kDegree) /
      static_cast<double>(control_point_count - kDegree);
  }

  std::fill(knots.begin() + control_point_count, knots.end(), 1.0);
  return knots;
}

std::size_t findKnotSpan(
  double parameter,
  std::size_t control_point_count,
  const std::vector<double> & knots) {
  if (parameter >= 1.0) {
    return control_point_count - 1;
  }

  for (std::size_t span = kDegree; span < control_point_count; ++span) {
    if (parameter >= knots[span] && parameter < knots[span + 1]) {
      return span;
    }
  }

  return kDegree;
}

Point evaluateCurve(
  double parameter,
  const std::vector<Point> & control_points,
  const std::vector<double> & knots) {
  if (parameter >= 1.0) {
    return control_points.back();
  }

  const std::size_t span = findKnotSpan(parameter, control_points.size(), knots);
  std::array<Point, kDegree + 1> working_points;

  for (std::size_t index = 0; index <= kDegree; ++index) {
    working_points[index] = control_points[span - kDegree + index];
  }

  for (std::size_t level = 1; level <= kDegree; ++level) {
    for (std::size_t index = kDegree; index >= level; --index) {
      const std::size_t knot_index = span - kDegree + index;
      const double denominator =
        knots[knot_index + kDegree - level + 1] - knots[knot_index];
      const double ratio = denominator > kEpsilon ?
        (parameter - knots[knot_index]) / denominator : 0.0;
      working_points[index] = interpolate(
        working_points[index - 1], working_points[index], ratio);
    }
  }

  return working_points[kDegree];
}

std::vector<Point> evaluateDenseCurve(
  const std::vector<Point> & control_points,
  const std::vector<double> & knots)
{
  const std::size_t span_count = control_points.size() - kDegree;
  const std::size_t segment_count = std::max(
    std::size_t{1}, span_count * kDenseSamplesPerSpan);

  std::vector<Point> curve;
  curve.reserve(segment_count + 1);
  for (std::size_t sample = 0; sample <= segment_count; ++sample) {
    const double parameter = static_cast<double>(sample) /
      static_cast<double>(segment_count);
    curve.push_back(evaluateCurve(parameter, control_points, knots));
  }

  return curve;
}

std::vector<Point> resampleByArcLength(
  const std::vector<Point> & dense_curve,
  double sample_spacing)
{
  std::vector<double> cumulative_distance(dense_curve.size(), 0.0);
  for (std::size_t index = 1; index < dense_curve.size(); ++index) {
    cumulative_distance[index] = cumulative_distance[index - 1] +
      distance(dense_curve[index - 1], dense_curve[index]);
  }

  const double total_length = cumulative_distance.back();
  if (total_length <= kEpsilon) {
    return {};
  }

  std::vector<Point> samples;
  samples.reserve(static_cast<std::size_t>(std::ceil(total_length / sample_spacing)) + 1);
  samples.push_back(dense_curve.front());

  std::size_t segment = 1;
  for (double target = sample_spacing; target < total_length; target += sample_spacing) {
    while (segment < cumulative_distance.size() && cumulative_distance[segment] < target) {
      ++segment;
    }

    if (segment >= cumulative_distance.size()) {
      break;
    }

    const double segment_start = cumulative_distance[segment - 1];
    const double segment_length = cumulative_distance[segment] - segment_start;
    if (segment_length <= kEpsilon) {
      continue;
    }

    const double ratio = (target - segment_start) / segment_length;
    samples.push_back(interpolate(dense_curve[segment - 1], dense_curve[segment], ratio));
  }

  if (distance(samples.back(), dense_curve.back()) > kEpsilon) {
    samples.push_back(dense_curve.back());
  } else {
    samples.back() = dense_curve.back();
  }

  return samples;
}

void setTangentOrientations(nav_msgs::msg::Path & path)
{
  for (std::size_t index = 0; index < path.poses.size(); ++index) {
    const std::size_t previous_index = index == 0 ? index : index - 1;
    const std::size_t next_index =
      index + 1 < path.poses.size() ? index + 1 : index;
    const Point & previous = path.poses[previous_index].pose.position;
    const Point & next = path.poses[next_index].pose.position;
    const double delta_x = next.x - previous.x;
    const double delta_y = next.y - previous.y;

    if (std::hypot(delta_x, delta_y) <= kEpsilon) {
      path.poses[index].pose.orientation.w = 1.0;
      continue;
    }

    const double yaw = std::atan2(delta_y, delta_x);
    path.poses[index].pose.orientation.z = std::sin(yaw / 2.0);
    path.poses[index].pose.orientation.w = std::cos(yaw / 2.0);
  }
}
}  // namespace

BSplineSmoother::BSplineSmoother(BSplineParameters parameters)
: parameters_(parameters)
{
  if (!std::isfinite(parameters_.sample_spacing) || parameters_.sample_spacing <= 0.0) {
    throw std::invalid_argument("B-spline sample spacing must be finite and positive");
  }
}

nav_msgs::msg::Path BSplineSmoother::smooth(
  const nav_msgs::msg::Path & control_path) const
{
  if (control_path.poses.size() < kMinimumControlPoints) {
    return control_path;
  }

  std::vector<Point> control_points;
  control_points.reserve(control_path.poses.size());
  for (const auto & pose : control_path.poses) {
    control_points.push_back(pose.pose.position);
  }

  const std::vector<double> knots = createClampedUniformKnots(control_points.size());
  const std::vector<Point> dense_curve = evaluateDenseCurve(control_points, knots);
  const std::vector<Point> samples =
    resampleByArcLength(dense_curve, parameters_.sample_spacing);
  if (samples.size() < 2) {
    return control_path;
  }

  nav_msgs::msg::Path smoothed_path;
  smoothed_path.header = control_path.header;
  smoothed_path.poses.reserve(samples.size());
  for (const Point & point : samples) {
    geometry_msgs::msg::PoseStamped pose;
    pose.header = control_path.header;
    pose.pose.position = point;
    smoothed_path.poses.push_back(std::move(pose));
  }

  setTangentOrientations(smoothed_path);
  smoothed_path.poses.front() = control_path.poses.front();
  smoothed_path.poses.back() = control_path.poses.back();
  return smoothed_path;
}
}  // namespace urc_path_planning
