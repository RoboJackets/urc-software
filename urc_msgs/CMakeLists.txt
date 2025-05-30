cmake_minimum_required(VERSION 3.5)
project(urc_msgs)

include(../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/VelocityPair.msg"
  "msg/LandingLocations.msg"
  "msg/ArucoDetection.msg"
  "msg/ArucoLocation.msg"
  "msg/BatteryInfo.msg"
  "msg/Waypoint.msg"
  "msg/NavigationStatus.msg"
  "msg/StatusLightCommand.msg"
  "msg/GridLocation.msg"
  "srv/GeneratePlan.srv"
  "action/FollowPath.action"
  "srv/UpdateBehaviorTree.srv"

  DEPENDENCIES
  std_msgs
  geometry_msgs
  nav_msgs
  builtin_interfaces
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  # the following line skips the copyright linker
  set(ament_cmake_copyright_FOUND TRUE)

  # the following line skips cpplint (only works in a git repo)
  set(ament_cmake_cpplint_FOUND TRUE)

  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)
ament_package()
