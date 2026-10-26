#ifndef URC_SLAM__GPS_KEYFRAME_MATCHER_HPP_
#define URC_SLAM__GPS_KEYFRAME_MATCHER_HPP_

#include <cstddef>
#include <deque>
#include <optional>
#include <vector>

#include <gtsam/base/Matrix.h>
#include <gtsam/geometry/Point3.h>
#include <rclcpp/time.hpp>

namespace urc_slam
{

// Map-frame GPS position with its position covariance (m^2)
struct GpsMeasurement
{
  rclcpp::Time stamp;
  gtsam::Point3 position;
  gtsam::Matrix3 covariance;
};

enum class GpsAddResult
{
  Accepted,
  // Same or older stamp than the last accepted fix, e.g. a republished fix
  Duplicate,
  // Non-finite position or covariance not symmetric positive definite
  Invalid
};

struct GpsKeyframeMatch
{
  std::size_t keyframe_index;
  GpsMeasurement measurement;
};

// Buffers GPS fixes and assigns each to the keyframe nearest in time once a
// keyframe at or after the fix exists. Fixes outside the tolerance are dropped.
class GpsKeyframeMatcher
{
public:
  GpsKeyframeMatcher(double time_tolerance_s, std::size_t capacity);

  GpsAddResult add(const GpsMeasurement & measurement);

  // keyframe_stamps[i] is the stamp of keyframe i and must be increasing
  std::vector<GpsKeyframeMatch> takeMatches(
    const std::vector<rclcpp::Time> & keyframe_stamps);

private:
  double time_tolerance_s;
  std::size_t capacity;
  std::deque<GpsMeasurement> pending;
  std::optional<rclcpp::Time> last_accepted_stamp;
};

}  // namespace urc_slam

#endif  // URC_SLAM__GPS_KEYFRAME_MATCHER_HPP_
