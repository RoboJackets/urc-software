#ifndef URC_SLAM__IMU_BUFFER_HPP_
#define URC_SLAM__IMU_BUFFER_HPP_

#include <cstddef>
#include <deque>
#include <optional>
#include <vector>

#include <gtsam/base/Vector.h>
#include <rclcpp/time.hpp>

namespace urc_slam
{

struct ImuSample
{
  rclcpp::Time stamp;
  gtsam::Vector3 acceleration;
  gtsam::Vector3 angular_velocity;
};

struct ImuMeasurement
{
  gtsam::Vector3 acceleration;
  gtsam::Vector3 angular_velocity;
  double dt;
};

enum class ImuWindowStatus
{
  Ready,
  // The newest buffered sample is older than the requested end stamp
  WaitingForData,
  // The requested end stamp is not after the current window start
  StaleStamp
};

struct ImuWindow
{
  ImuWindowStatus status = ImuWindowStatus::WaitingForData;
  std::vector<ImuMeasurement> measurements;
  double largest_gap_s = 0.0;
};

// Buffers IMU samples and cuts them into integration windows that start and
// end exactly at requested stamps. Each sample is applied over the interval
// ending at its own stamp; the sample straddling a window end is split.
class ImuBuffer
{
public:
  explicit ImuBuffer(std::size_t capacity);

  // Drops samples whose stamp is not after the newest buffered sample
  void push(const ImuSample & sample);

  // Discards samples up to stamp and starts the next window there
  void startWindowAt(const rclcpp::Time & stamp);

  // Returns the measurements covering (window start, end_stamp] and
  // advances the window start to end_stamp when Ready
  ImuWindow takeUntil(const rclcpp::Time & end_stamp);

private:
  std::size_t capacity;
  std::deque<ImuSample> samples;
  std::optional<rclcpp::Time> window_start;
};

}  // namespace urc_slam

#endif  // URC_SLAM__IMU_BUFFER_HPP_
