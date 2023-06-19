#include "aruco_location.hpp"

namespace aruco_location
{
ArucoLocation::ArucoLocation(const rclcpp::NodeOptions & options)
: rclcpp::Node("aruco_location", options)
{
  location_publisher = create_publisher<urc_msgs::msg::ArucoLocation>(
    "~/aruco_location",
    rclcpp::SystemDefaultsQoS()
  );

  //Aruco Tag Angles and Distance relative to camera.
  aruco_subscriber = create_subscription<urc_msgs::msg::ArucoDetection>(
    "/aruco_detection", rclcpp::SystemDefaultsQoS(), [this](const urc_msgs::msg::ArucoDetection
    aruco_msg) {
      arucoCallback(aruco_msg);
    });

  gps_subscriber = create_subscription<sensor_msgs::msg::NavSatFix>(
    "/gps/data", rclcpp::SensorDataQoS(), [this](const sensor_msgs::msg::NavSatFix gps_msg) {
      gpsCallback(gps_msg);
    });

  //Yaw, Pitch and Roll (Orientation)
  orientation_subscriber = create_subscription<sensor_msgs::msg::Imu>(
    "/imu/data", rclcpp::SensorDataQoS(), [this](const sensor_msgs::msg::Imu imu_msg) {
      orientationCallback(imu_msg);
    });
}


/*
All units need to be converted into radians
Latitude and Longtitude calculations using Aviation Formulary V1.47:
See --> http://www.edwilliams.org/avform147.htm#LL
*/
double ArucoLocation::getNextLatitude(double d, double xAngle, double yaw)
{
  if (!gpsRead || !orientationRead) {
    return -1.0;
  }
  return asin(sin(droneLat) * cos(d) + cos(droneLat) * sin(d) * cos(xAngle + yaw));

}

double ArucoLocation::getNextLongitude(double d, double xAngle, double yaw)
{
  if (!gpsRead || !orientationRead) {
    return -1.0;
  }
  double dlon =
    atan2(
    sin(xAngle + yaw) * sin(d) * cos(droneLat),
    cos(d) - sin(droneLat) * sin(getNextLatitude(d, xAngle, yaw)));
  return std::fmod(((droneLon - dlon) + M_PI), 2.0 * M_PI) - M_PI;
}

double ArucoLocation::findD(double trueD, double yAngle, double pitch)
{
  if (!gpsRead || !orientationRead) {
    return -1.0;
  }
  return trueD * cos(pitch + yAngle);
}


/*
This code assumes that the polling rate of the GPS and IMU sensors are high enough
so that when the aruco callback meets its requirements (GPS and Orientation read) the
sensor values will be recent enough to make a Lat/Lon calculation.

If this becomes a problem, try using callback groups using single-threaded executors
*/
void ArucoLocation::arucoCallback(const urc_msgs::msg::ArucoDetection & aruco_msg)
{
  //RCLCPP_INFO(this->get_logger(), "Received aruco!");
  xAngle = aruco_msg.x_angle;
  yAngle = aruco_msg.y_angle;
  trueDist = aruco_msg.distance;
  tagId = aruco_msg.id;
  which_camera = aruco_msg.which_camera;

  if (gpsRead && orientationRead) {
    double d = findD(trueDist, yAngle, pitch);
    urc_msgs::msg::ArucoLocation location_message;
    location_message.header.stamp = aruco_msg.header.stamp;
    location_message.lon = getNextLongitude(d, xAngle, yaw);
    location_message.lat = getNextLatitude(d, xAngle, yaw);
    location_message.id = aruco_msg.id;
    location_message.which_camera = which_camera;

    location_publisher->publish(location_message);
  } else {
    RCLCPP_INFO(this->get_logger(), "ARUCO tag GPS and orientation out of date, waiting for their output");
  }

  orientationRead = false, gpsRead = false;
}

void ArucoLocation::gpsCallback(const sensor_msgs::msg::NavSatFix & gps_msg)
{
  droneLat = static_cast<double>(gps_msg.latitude);
  droneLon = static_cast<double>(gps_msg.longitude);
  droneAlt = static_cast<double>(gps_msg.altitude);
  gpsRead = true;
}


/*
  See http://wiki.ros.org/tf2/Tutorials/Quaternions and
  https://answers.ros.org/question/339528/quaternion-to-rpy-ros2/
*/
void ArucoLocation::orientationCallback(const sensor_msgs::msg::Imu & imu_msg)
{
  geometry_msgs::msg::Quaternion rawOrientation = imu_msg.orientation;
  tf2::Quaternion convertedOrientation;
  tf2::fromMsg(rawOrientation, convertedOrientation);
  tf2::Matrix3x3 m(convertedOrientation);
  m.getRPY(roll, pitch, yaw);

  roll = static_cast<double>(roll);
  pitch = static_cast<double>(pitch);
  yaw = static_cast<double>(yaw);
  orientationRead = true;
}

}
RCLCPP_COMPONENTS_REGISTER_NODE(aruco_location::ArucoLocation)
