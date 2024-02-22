#include "aruco_detector.hpp"

namespace aruco_detector
{
  ArucoDetector::ArucoDetector(const rclcpp::NodeOptions &options)
      : rclcpp::Node("aruco_detector", options)
  {
    tagWidth = declare_parameter<int>("tagWidth");

    aruco_publisher = create_publisher<urc_msgs::msg::ArucoDetection>(
        "~/aruco_detection",
        rclcpp::SystemDefaultsQoS());

    // See --> https://github.com/ros-perception/image_common/issues/121 for imagetransport pub/subs
    camera_subscriber_center_ = image_transport::create_camera_subscription(
        this, "/image/center_img",
        std::bind(
            &ArucoDetector::imageCallback, this, std::placeholders::_1,
            std::placeholders::_2, "center"),
        "raw", rclcpp::SensorDataQoS().get_rmw_qos_profile());
    camera_subscriber_left_ = image_transport::create_camera_subscription(
        this, "/image/left_img",
        std::bind(
            &ArucoDetector::imageCallback, this, std::placeholders::_1,
            std::placeholders::_2, "left"),
        "raw", rclcpp::SensorDataQoS().get_rmw_qos_profile());
    camera_subscriber_right_ = image_transport::create_camera_subscription(
        this, "/image/right_img",
        std::bind(
            &ArucoDetector::imageCallback, this, std::placeholders::_1,
            std::placeholders::_2, "right"),
        "raw", rclcpp::SensorDataQoS().get_rmw_qos_profile());
  }

  void ArucoDetector::imageCallback(
      const sensor_msgs::msg::Image::ConstSharedPtr &image_msg,
      const sensor_msgs::msg::CameraInfo::ConstSharedPtr &info_msg,
      const std::string which_camera)
  {
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(
        cv::aruco::DICT_4X4_50);

    // Get image in gray scale
    const auto cv_image = cv_bridge::toCvCopy(image_msg, "bgr8");
    cv::cvtColor(cv_image->image, cv_image->image, cv::COLOR_BGR2GRAY);

    const auto camera_matrix = cv::Mat(info_msg->k).reshape(1, 3); // camera intrinsics
    cv::Mat distCoeffs = cv::Mat(info_msg->d);

    // Hasn't seen any tags yet
    for (int i = 0; i < numTags; ++i)
    {
      detectedTags[i] = 0;
    }

    // Converts the image to B&W with 4 different thresholds
    for (int i = 0; i < 3; ++i)
    {
      // detects all of the tags with the current b&w threshold
      cv::aruco::detectMarkers(
          (cv_image->image > i * 60 + 40), dictionary, corners, MarkerIDs, parameters,
          rejects);
      cv::aruco::estimatePoseSingleMarkers(
          corners, tagWidth / 100.0, camera_matrix, distCoeffs,
          rvecs, tvecs);

      /*
      The below code makes some assumptions:
         1. The only tags that should be published are the tags used at the URC
         2. Only at most one of each tag should be detected
         3. There will be no false positives for tags ids being used at the URC
       */
      for (int id = 0; id < static_cast<int>(MarkerIDs.size()); ++id)
      {
        // checks if this tag has already been seen in this image and that it is a valid URC tag
        if (MarkerIDs[id] > numTags - 1 || detectedTags[MarkerIDs[id]] == 1)
        {
          continue;
        }
        detectedTags[MarkerIDs[id]] = 1;

        // Tvecs is a translation vector of the marker relative to the camera in x,y,z
        // Rvecs is a rodriguez rotation vector describing the marker orientation relative to the
        // marker itself.
        xAngle = atan(tvecs[i][0] / tvecs[i][2]);
        yAngle = atan(tvecs[i][1] / tvecs[i][2]);
        distance = sqrt(pow(tvecs[i][0], 2) + pow(tvecs[i][1], 2) + pow(tvecs[i][2], 2));
        urc_msgs::msg::ArucoDetection aruco_message;
        aruco_message.header.stamp = info_msg->header.stamp;
        aruco_message.x_angle = xAngle;
        aruco_message.y_angle = yAngle;
        aruco_message.distance = distance;
        aruco_message.id = MarkerIDs[id];
        aruco_message.which_camera = which_camera;

        aruco_publisher->publish(aruco_message);
      }
    }
  }

}

RCLCPP_COMPONENTS_REGISTER_NODE(aruco_detector::ArucoDetector)
