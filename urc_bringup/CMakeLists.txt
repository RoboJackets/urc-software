cmake_minimum_required(VERSION 3.5)
project(urc_bringup)

include(../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosbridge_server REQUIRED)
find_package(tf2_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(urc_msgs REQUIRED)
find_package(ros_gz REQUIRED)
find_package(effort_controllers REQUIRED)

include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/heartbeat_publisher.cpp
  src/ground_truth.cpp
  src/rocker_effort_pid.cpp
  src/rocker_tf_broadcaster.cpp
)

set(dependencies
  rclcpp
  rclcpp_components
  std_msgs
  rosbridge_server
  sensor_msgs
  nav_msgs
  tf2_msgs
  tf2_ros
  urc_msgs
  ros_gz
  effort_controllers
)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

# Node registration
rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "heartbeat_publisher::HeartbeatPublisher"
  EXECUTABLE ${PROJECT_NAME}_HeartbeatPublisher
)


rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "urc_bringup::RockerEffortPid"
  EXECUTABLE ${PROJECT_NAME}_RockerEffortPid
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "urc_bringup::RockerTfBroadcaster"
  EXECUTABLE ${PROJECT_NAME}_RockerTfBroadcaster
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "ground_truth::GroundTruth"
  EXECUTABLE ${PROJECT_NAME}_GroundTruth
)

# Install launch/config/model files and expose them to Gazebo resources.
install(
  DIRECTORY
  launch
  config
  models
  DESTINATION share/${PROJECT_NAME}/
)

ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/hooks/gz_sim_resource_path.dsv")

# Install Python scripts
install(PROGRAMS
  scripts/aruco_detector.py
  scripts/aruco_test_publisher.py
  DESTINATION lib/${PROJECT_NAME}
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
  # the following line skips the copyright linker
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(msg)

ament_export_include_directories(include)

ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

ament_package()
