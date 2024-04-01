#ifndef GEOMETRY_UTIL_HPP_
#define GEOMETRY_UTIL_HPP_

#include <geometry_msgs/msg/point.hpp>

namespace geometry_util
{

constexpr double MAX_CURVATURE = 1e9;

double magnitude(const geometry_msgs::msg::Point & p);

double dist2D(const geometry_msgs::msg::Point & a, const geometry_msgs::msg::Point & b);

double distSquared2D(const geometry_msgs::msg::Point & a, const geometry_msgs::msg::Point & b);

double calcCurvature(const geometry_msgs::msg::Point & lookahead);

/**
   * @brief Calculate the intersection of a line segment and a circle. The derivation of the formula can be visualized here: https://www.desmos.com/calculator/vatao173by.
   * This assumes that the circle is cenetered at robots pose and both points are in the same frame as the robot.
   * @param a The first point of the line segment in the robot frame
   * @param b The second point of the line segment in the robot frame
   * @parma r The radius of the circle
   */
geometry_msgs::msg::Point circleSegmentIntersection(
  const geometry_msgs::msg::Point & a,
  const geometry_msgs::msg::Point & b, double r);

} // namespace geometry_util

#endif // GEOMETRY_UTIL_HPP_
