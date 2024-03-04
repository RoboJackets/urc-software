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
  dy = b.y - a.y;
  dx = b.x - a.x;
  dr = std::sqrt(dy * dy + dx * dx);
  D = a.x * b.y - b.x * a.y;

  discriminant = r * r * dr * dr - D * D;

  if (discriminant < 0) {
    throw std::runtime_error("No intersection found");
  }

  I_x1 = (D * dy + std::copysign(1.0, dy) * dx * std::sqrt(discriminant)) / (dr * dr);
  I_x2 = (D * dy - std::copysign(1.0, dy) * dx * std::sqrt(discriminant)) / (dr * dr);

  I_y1 = (-D * dx + std::abs(dy) * std::sqrt(discriminant)) / (dr * dr);
  I_y2 = (-D * dx - std::abs(dy) * std::sqrt(discriminant)) / (dr * dr);

  geometry_msgs::msg::Point intersection;

  if (std::min(a.x, b.x) <= I_x1 && I_x1 <= std::max(a.x, b.x) &&
    std::min(a.y, b.y) <= I_y1 && I_y1 <= std::max(a.y, b.y))
  {
    intersection.x = I_x1;
    intersection.y = I_y1;
  } else if (std::min(a.x, b.x) <= I_x2 && I_x2 <= std::max(a.x, b.x) &&
    std::min(a.y, b.y) <= I_y2 && I_y2 <= std::max(a.y, b.y))
  {
    intersection.x = I_x2;
    intersection.y = I_y2;
  } else {
    throw std::runtime_error("No intersection found");
  }

  return intersection;
}

}   // namespace geometry_util
} // namespace pure_pursuit
