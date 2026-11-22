#ifndef URC_PERCEPTION__DETECTION_LOCALIZER_HPP_
#define URC_PERCEPTION__DETECTION_LOCALIZER_HPP_

#include <deque>
#include <memory>
#include <optional>
#include <string>

#include <geometry_msgs/msg/point_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <tf2/time.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <urc_msgs/msg/detection_bounding_box.hpp>

#include "urc_perception/detection_projection.hpp"

namespace urc_perception
{

// Locates YOLO detections in `target_frame` (SLAM's `map` by default) by sampling a
// depth image registered to the detection colour image and transforming with tf2.
class DetectionLocalizer : public rclcpp::Node
{
public:
  explicit DetectionLocalizer(const rclcpp::NodeOptions & options);

private:
  using Detection = urc_msgs::msg::DetectionBoundingBox;
  using Image = sensor_msgs::msg::Image;

  void onCameraInfo(const sensor_msgs::msg::CameraInfo::ConstSharedPtr & msg);
  void onDepth(const Image::ConstSharedPtr & msg);
  void onDetection(const Detection::ConstSharedPtr & detection);

  Image::ConstSharedPtr depthFrameNear(const rclcpp::Time & stamp) const;
  std::optional<double> boxDepth(
    const Image::ConstSharedPtr & depth_msg, const Detection & detection);
  std::optional<geometry_msgs::msg::PointStamped> toTargetFrame(
    const geometry_msgs::msg::PointStamped & camera_point);

  std::string target_frame_;
  rclcpp::Duration max_depth_stamp_gap_;
  tf2::Duration transform_timeout_;
  double box_core_fraction_;
  size_t depth_buffer_size_;

  std::optional<PinholeIntrinsics> intrinsics_;
  std::deque<Image::ConstSharedPtr> depth_frames_;

  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr camera_info_sub_;
  rclcpp::Subscription<Image>::SharedPtr depth_sub_;
  rclcpp::Subscription<Detection>::SharedPtr detection_sub_;
  rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr point_pub_;
};

}  // namespace urc_perception

#endif  // URC_PERCEPTION__DETECTION_LOCALIZER_HPP_
