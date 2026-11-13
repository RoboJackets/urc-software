#include "urc_slam/gps_keyframe_matcher.hpp"

#include <algorithm>
#include <cmath>

#include <Eigen/Cholesky>

namespace urc_slam
{

namespace
{
bool isValidCovariance(const gtsam::Matrix3 & covariance)
{
  if (!covariance.allFinite() || !covariance.isApprox(covariance.transpose())) {
    return false;
  }
  return Eigen::LLT<gtsam::Matrix3>(covariance).info() == Eigen::Success;
}

std::size_t nearestKeyframeIndex(
  const std::vector<rclcpp::Time> & keyframe_stamps,
  const rclcpp::Time & stamp
)
{
  const auto after = std::lower_bound(
    keyframe_stamps.begin(), keyframe_stamps.end(), stamp);
  if (after == keyframe_stamps.begin()) {
    return 0;
  }
  const auto before = std::prev(after);
  if (after == keyframe_stamps.end() ||
    (stamp - *before) <= (*after - stamp))
  {
    return static_cast<std::size_t>(before - keyframe_stamps.begin());
  }
  return static_cast<std::size_t>(after - keyframe_stamps.begin());
}
}  // namespace

GpsKeyframeMatcher::GpsKeyframeMatcher(double time_tolerance_s, std::size_t capacity)
: time_tolerance_s(time_tolerance_s),
  capacity(capacity)
{
}

GpsAddResult GpsKeyframeMatcher::add(const GpsMeasurement & measurement)
{
  if (!measurement.position.allFinite() || !isValidCovariance(measurement.covariance)) {
    return GpsAddResult::Invalid;
  }
  if (last_accepted_stamp && measurement.stamp <= *last_accepted_stamp) {
    return GpsAddResult::Duplicate;
  }

  pending.push_back(measurement);
  last_accepted_stamp = measurement.stamp;
  while (pending.size() > capacity) {
    pending.pop_front();
  }
  return GpsAddResult::Accepted;
}

std::vector<GpsKeyframeMatch> GpsKeyframeMatcher::takeMatches(
  const std::vector<rclcpp::Time> & keyframe_stamps
)
{
  std::vector<GpsKeyframeMatch> matches;
  if (keyframe_stamps.empty()) {
    return matches;
  }

  while (!pending.empty() && pending.front().stamp <= keyframe_stamps.back()) {
    const GpsMeasurement & measurement = pending.front();
    const std::size_t index = nearestKeyframeIndex(keyframe_stamps, measurement.stamp);
    const double offset_s =
      std::abs((keyframe_stamps[index] - measurement.stamp).seconds());
    if (offset_s <= time_tolerance_s) {
      matches.push_back({index, measurement});
    }
    pending.pop_front();
  }
  return matches;
}

}  // namespace urc_slam
