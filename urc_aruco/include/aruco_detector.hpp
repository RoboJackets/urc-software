#ifndef ARUCO_DETECTOR_H
#define ARUCO_DETECTOR_H

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <urc_msgs/msg/aruco_detection.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/aruco.hpp>
#include <cv_bridge/cv_bridge.h>
#include <bits/stdc++.h>
#include <image_transport/image_transport.hpp>

namespace aruco_detector
{

class ArucoDetector : public rclcpp::Node
{
public:
  explicit ArucoDetector(const rclcpp::NodeOptions & options);

private:
  rclcpp::Publisher<urc_msgs::msg::ArucoDetection>::SharedPtr aruco_publisher;
  image_transport::CameraSubscriber camera_subscriber_;

  std::vector<std::vector<cv::Point2f>> corners, rejects;   // rejects will likely be unused
  std::vector<int> MarkerIDs;

  int tagWidth;   //actual tag width in cm
  double width;   //pixel width
  int xCenter, yCenter;
  double distance;   //Returned distance in m
  double xAngle, yAngle;   //Should be in radians

  std::vector<cv::Vec3d> rvecs, tvecs;


  const int numTags = 6;   //There are 6 valid tags at the URC in 2023
  int detectedTags[6];   //Keeps track of the tags that have already been detected in an image

  void imageCallback(
    const sensor_msgs::msg::Image::ConstSharedPtr & image_msg,
    const sensor_msgs::msg::CameraInfo::ConstSharedPtr & info_msg
  );
};
}

#endif
