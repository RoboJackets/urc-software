#include "geometry_util.hpp"

#include <math.h>

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

double magnitude(const geometry_msgs::msg::Point & p)
{
  return std::sqrt(p.x * p.x + p.y * p.y);
}

double calcCurvature(
  const geometry_msgs::msg::Point & lookahead)
{
  double distSquared = lookahead.x * lookahead.x + lookahead.y * lookahead.y;

  if (fabs(distSquared) > 0.001) {
    return 2.0 * lookahead.y / distSquared;
  } else {
    return 0.0;
  }
}

geometry_msgs::msg::Point circleSegmentIntersection(
  const geometry_msgs::msg::Point & a,
  const geometry_msgs::msg::Point & b, double r)
{
  double dy, dx, dr, D, discriminant, x1, x2, y1, y2;

  dy = b.y - a.y;
  dx = b.x - a.x;
  dr = std::sqrt(dy * dy + dx * dx);
  D = a.x * b.y - b.x * a.y;

  discriminant = r * r * dr * dr - D * D;

  if (discriminant < 0) {
    throw std::runtime_error("No intersection found, discriminant is zero or negative.");
  }

  x1 = (D * dy + std::copysign(1.0, dy) * dx * std::sqrt(discriminant)) / (dr * dr);
  x2 = (D * dy - std::copysign(1.0, dy) * dx * std::sqrt(discriminant)) / (dr * dr);

  y1 = (-D * dx + std::abs(dy) * std::sqrt(discriminant)) / (dr * dr);
  y2 = (-D * dx - std::abs(dy) * std::sqrt(discriminant)) / (dr * dr);

  bool p1_in_segment =
    std::min(
    a.x,
    b.x) <= x1 &&
    x1 <= std::max(a.x, b.x) && std::min(a.y, b.y) <= y1 && y1 <= std::max(a.y, b.y);
  bool p2_in_segment =
    std::min(
    a.x,
    b.x) <= x2 &&
    x2 <= std::max(a.x, b.x) && std::min(a.y, b.y) <= y2 && y2 <= std::max(a.y, b.y);

  geometry_msgs::msg::Point intersection;

  if (p1_in_segment && !p2_in_segment) {
    intersection.x = x1;
    intersection.y = y1;
  } else if (p2_in_segment && !p1_in_segment) {
    intersection.x = x2;
    intersection.y = y2;
  } else if (p1_in_segment && p2_in_segment) {
    double d1 = distSquared2D(b, intersection);
    double d2 = distSquared2D(b, intersection);

    if (d1 < d2) {
      intersection.x = x1;
      intersection.y = y1;
    } else {
      intersection.x = x2;
      intersection.y = y2;
    }
  } else {
    throw std::runtime_error("No intersection found between the segment end points.");
  }

  return intersection;
}
} // namespace geometry_util
