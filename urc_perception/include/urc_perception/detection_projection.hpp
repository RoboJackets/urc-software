#ifndef URC_PERCEPTION__DETECTION_PROJECTION_HPP_
#define URC_PERCEPTION__DETECTION_PROJECTION_HPP_

#include <opencv2/core.hpp>

#include <optional>

namespace urc_perception
{

// Pinhole intrinsics in pixels, taken from CameraInfo::k.
struct PinholeIntrinsics
{
  double fx;
  double fy;
  double cx;
  double cy;
};

// Pixel-space box as published by the YOLO detector.
struct PixelBox
{
  int x_min;
  int y_min;
  int x_max;
  int y_max;
};

// Median of the finite, positive depths (metres, CV_32FC1) inside the central core of
// `box`. `core_fraction` in (0, 1] is the kept width/height share; box edges are mostly
// background. Returns nullopt when the core has no valid depth.
std::optional<double> medianCoreDepth(
  const cv::Mat &depth_m, 
  const PixelBox &box, 
  double core_fraction
);

// Back-projects the centre of `box` at `depth_m` into the camera optical frame
// (x right, y down, z forward), in metres.
cv::Point3d deprojectBoxCenter(
  const PinholeIntrinsics &intrinsics, 
  const PixelBox &box, 
  double depth_m
);

}  // namespace urc_perception

#endif  // URC_PERCEPTION__DETECTION_PROJECTION_HPP_
