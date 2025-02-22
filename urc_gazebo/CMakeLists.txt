cmake_minimum_required(VERSION 3.5)
project(urc_gazebo)

include(../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(urc_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(laser_geometry REQUIRED)
find_package(velodyne_simulator REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(xacro REQUIRED)

include_directories(
  include
)

set(dependencies
  rclcpp
  rclcpp_components
  urc_msgs
  std_msgs
  nav_msgs
  sensor_msgs
  tf2
  tf2_ros
  tf2_geometry_msgs
  laser_geometry
  velodyne_simulator
  xacro
)

install(
  DIRECTORY
  urdf
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
