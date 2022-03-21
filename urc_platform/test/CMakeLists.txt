find_package(ament_cmake_pytest REQUIRED)
find_package(launch_testing_ament_cmake REQUIRED)
find_package(ament_cmake_gtest REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(urc_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(laser_geometry REQUIRED)

set(test_dependencies
  rclcpp
  rclcpp_components
  urc_msgs
  std_msgs
  nav_msgs
  sensor_msgs
  tf2
  tf2_ros
  laser_geometry
)

ament_export_dependencies(${test_dependencies})

ament_add_gtest(test_scan_to_pointcloud test_scan_to_pointcloud.cpp)
ament_target_dependencies(test_scan_to_pointcloud ${test_dependencies})
