#ifndef GEOMETRY_UTIL_HPP_
#define GEOMETRY_UTIL_HPP_

#include <optional>

#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/quaternion.hpp>

namespace geometry_util
{

double magnitude(const geometry_msgs::msg::Point & p);

double dist2D(const geometry_msgs::msg::Point & a, const geometry_msgs::msg::Point & b);

double distSquared2D(const geometry_msgs::msg::Point & a, const geometry_msgs::msg::Point & b);

/**
   * @brief Calculate the curvature (1/R) of the circle that intersects the lookahead point and is tangent to the robot's current pose.
   * @param lookahead The lookahead point in the robot's frame
   */
double calcCurvature(const geometry_msgs::msg::Point & lookahead);

/**
   * @brief Intersect segment a->b with a circle of radius r centered at the robot frame origin.
   * @param a The first point of the line segment in the robot frame
   * @param b The second point of the line segment in the robot frame
   * @param r The radius of the circle
   * @return The intersection farthest along a->b, or std::nullopt when the segment does not
   *         reach the circle.
   */
std::optional<geometry_msgs::msg::Point> circleSegmentIntersection(
  const geometry_msgs::msg::Point & a,
  const geometry_msgs::msg::Point & b, double r);

/**
   * @brief Calculate the shortest angular difference between two quaternions (in radians).
   * @param q1 The first quaternion
   * @param q2 The second quaternion
   * @return The absolute angular difference in radians [0, pi]
   */
double angularDistance(
  const geometry_msgs::msg::Quaternion & q1,
  const geometry_msgs::msg::Quaternion & q2);

} // namespace geometry_util

#endif // GEOMETRY_UTIL_HPP_
