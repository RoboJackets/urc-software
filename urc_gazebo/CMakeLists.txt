cmake_minimum_required(VERSION 3.5)
project(urc_gazebo)

include (../cmake/default_settings.cmake)

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

include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/scan_to_pointcloud.cpp
  src/control.cpp
  src/ground_truth.cpp
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
)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Node registration
rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "scan_to_pointcloud::ScanToPointCloud"
  EXECUTABLE ${PROJECT_NAME}_ScanToPointCloud
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "control::Control"
  EXECUTABLE ${PROJECT_NAME}_Control
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "ground_truth::GroundTruth"
  EXECUTABLE ${PROJECT_NAME}_GroundTruth
)

# Install robot spawn file.
install(
  PROGRAMS
  launch/spawn_wallii.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch, gazebo, and config files
install(
  DIRECTORY
  launch
  urdf
  config
  DESTINATION share/${PROJECT_NAME}/
)

# Install library
install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  #Calls the CMake for the unit tests
  add_subdirectory(test)
  # the following line skips the copyright linker
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  set(ament_cmake_cpplint_FOUND TRUE)

  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(include)

ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

ament_package()
