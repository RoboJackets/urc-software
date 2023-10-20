#ifndef ARUCO_LOCATION_H
#define ARUCO_LOCATION_H

#include <vector>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <urc_msgs/msg/aruco_detection.hpp>
#include <urc_msgs/msg/aruco_location.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <string>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <geometry_msgs/msg/quaternion.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>


namespace aruco_location
{

class ArucoLocation : public rclcpp::Node
{
public:
  explicit ArucoLocation(const rclcpp::NodeOptions & options);

private:
  double getNextLatitude(double d, double xAngle, double yaw);
  double getNextLongitude(double d, double xAngle, double yaw);
  double findD(double trueD, double yAngle, double pitch);

  rclcpp::Publisher<urc_msgs::msg::ArucoLocation>::SharedPtr location_publisher;
  rclcpp::Subscription<urc_msgs::msg::ArucoDetection>::SharedPtr aruco_subscriber;
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr gps_subscriber;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr orientation_subscriber;

  //Variables given by Aruco Detector Node, GPS and IMU sensors.
  //gpsRead and orientationRead have the purpose of determining whether data has been received for those yet.
  double xAngle, yAngle;
  double trueDist;
  double tagId;
  bool arucoRead = false;
  std::string which_camera;

  double droneLat, droneLon, droneAlt;
  bool gpsRead = false;

  double yaw = -1, pitch = -1, roll = -1;
  bool orientationRead = false;

  void arucoCallback(const urc_msgs::msg::ArucoDetection & aruco_msg);
  void gpsCallback(const sensor_msgs::msg::NavSatFix & gps_msg);
  void orientationCallback(const sensor_msgs::msg::Imu & imu_msg);
};

}


#endif
