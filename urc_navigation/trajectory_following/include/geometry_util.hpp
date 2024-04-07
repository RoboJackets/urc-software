#ifndef GEOMETRY_UTIL_HPP_
#define GEOMETRY_UTIL_HPP_

#include <geometry_msgs/msg/point.hpp>

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
   * @brief Calculate the intersection of a line segment and a circle. The derivation of the formula can be visualized here: https://www.desmos.com/calculator/vatao173by.
   * This assumes that the circle is cenetered at robot's pose and both points are in the robot frame.
   * @param a The first point of the line segment in the robot frame
   * @param b The second point of the line segment in the robot frame
   * @parma r The radius of the circle
   */
geometry_msgs::msg::Point circleSegmentIntersection(
  const geometry_msgs::msg::Point & a,
  const geometry_msgs::msg::Point & b, double r);

} // namespace geometry_util

#endif // GEOMETRY_UTIL_HPP_
