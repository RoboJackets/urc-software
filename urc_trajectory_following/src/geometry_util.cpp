#include "urc_trajectory_following/geometry_util.hpp"

#include <math.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

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

std::optional<geometry_msgs::msg::Point> circleSegmentIntersection(
  const geometry_msgs::msg::Point & a,
  const geometry_msgs::msg::Point & b, double r)
{
  // Solve |a + t (b - a)| = r for t in [0, 1].
  const double dx = b.x - a.x;
  const double dy = b.y - a.y;
  const double qa = dx * dx + dy * dy;
  const double qb = 2.0 * (a.x * dx + a.y * dy);
  const double qc = a.x * a.x + a.y * a.y - r * r;
  const double discriminant = qb * qb - 4.0 * qa * qc;
  if (qa <= 0.0 || discriminant < 0.0) {
    return std::nullopt;
  }

  const double root = std::sqrt(discriminant);
  for (const double t : {(-qb + root) / (2.0 * qa), (-qb - root) / (2.0 * qa)}) {
    if (t >= 0.0 && t <= 1.0) {
      geometry_msgs::msg::Point intersection;
      intersection.x = a.x + t * dx;
      intersection.y = a.y + t * dy;
      return intersection;
    }
  }
  return std::nullopt;
}

double angularDistance(
  const geometry_msgs::msg::Quaternion & q1,
  const geometry_msgs::msg::Quaternion & q2)
{
  tf2::Quaternion tf_q1, tf_q2;
  tf2::fromMsg(q1, tf_q1);
  tf2::fromMsg(q2, tf_q2);

  double dot = tf_q1.dot(tf_q2);
  dot = std::clamp(dot, -1.0, 1.0);

  return std::acos(std::abs(dot)) * 2.0;
}

} // namespace geometry_util
