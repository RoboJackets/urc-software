#include "urc_slam/imu_buffer.hpp"

#include <algorithm>

namespace urc_slam
{

ImuBuffer::ImuBuffer(std::size_t capacity)
: capacity(capacity)
{
}

void ImuBuffer::push(const ImuSample & sample)
{
  if (!samples.empty() && sample.stamp <= samples.back().stamp) {
    return;
  }
  samples.push_back(sample);
  while (samples.size() > capacity) {
    samples.pop_front();
  }
}

void ImuBuffer::startWindowAt(const rclcpp::Time & stamp)
{
  while (!samples.empty() && samples.front().stamp <= stamp) {
    samples.pop_front();
  }
  window_start = stamp;
}

ImuWindow ImuBuffer::takeUntil(const rclcpp::Time & end_stamp)
{
  ImuWindow window;
  if (!window_start || end_stamp <= *window_start) {
    window.status = ImuWindowStatus::StaleStamp;
    return window;
  }
  if (samples.empty() || samples.back().stamp < end_stamp) {
    window.status = ImuWindowStatus::WaitingForData;
    return window;
  }

  rclcpp::Time previous_stamp = *window_start;
  while (!samples.empty() && samples.front().stamp <= end_stamp) {
    const ImuSample & sample = samples.front();
    const double dt = (sample.stamp - previous_stamp).seconds();
    window.measurements.push_back({sample.acceleration, sample.angular_velocity, dt});
    window.largest_gap_s = std::max(window.largest_gap_s, dt);
    previous_stamp = sample.stamp;
    samples.pop_front();
  }

  const double remaining_dt = (end_stamp - previous_stamp).seconds();
  if (remaining_dt > 0.0) {
    const ImuSample & straddling_sample = samples.front();
    window.measurements.push_back(
      {straddling_sample.acceleration, straddling_sample.angular_velocity, remaining_dt});
    window.largest_gap_s = std::max(
      window.largest_gap_s, (straddling_sample.stamp - previous_stamp).seconds());
  }

  window_start = end_stamp;
  window.status = ImuWindowStatus::Ready;
  return window;
}

}  // namespace urc_slam
