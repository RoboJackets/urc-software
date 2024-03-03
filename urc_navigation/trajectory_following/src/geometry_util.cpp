#include "geometry_util.hpp"

#include <math.h>

namespace pure_pursuit
{
namespace geometry_util
{

double dist2D(const geometry_msgs::msg::Point & a, const geometry_msgs::msg::Point & b)
{
  return std::sqrt(distSquared2D(a, b));
}

double distSquared2D(const geometry_msgs::msg::Point & a, const geometry_msgs::msg::Point & b)
{
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return dx * dx + dy * dy;
}

double calcCurvature(
  const geometry_msgs::msg::Point & current,
  const geometry_msgs::msg::Point & goal)
{
  double distSquared = distSquared2D(goal, current);

  if (fabs(distSquared) > 0) {
    return 2.0 * goal.y / distSquared;
  } else {
    return MAX_CURVATURE;
  }
}

geometry_msgs::msg::Point circleSegmentIntersection(
  const geometry_msgs::msg::Point & a,
  const geometry_msgs::msg::Point & b, double r)
{
  geometry_msgs::msg::Point intersection;
  intersection.x = 0.0;
  intersection.y = 0.0;
  return intersection;
}

}     // namespace geometry_util
} // namespace pure_pursuit
