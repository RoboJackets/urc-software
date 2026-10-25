cmake_minimum_required(VERSION 3.5)
project(urc_state_machine)

include(../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geodesy REQUIRED)
find_package(geographic_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(urc_msgs REQUIRED)

include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/nav_coordinator.cpp
  src/ros/mission_parameters.cpp
  src/fsm/mission_state.cpp
  src/fsm/mission_timeouts.cpp
  src/fsm/mission_resume.cpp
  src/fsm/astronaut_fsm.cpp
  src/navigation/navigation_client.cpp
  src/navigation/spiral_search_client.cpp
  src/navigation/mission_geometry.cpp
  src/navigation/astronaut_tracking.cpp
  src/ros/mission_actions.cpp
  src/ros/mission_commands.cpp
  src/ros/mission_inputs.cpp
  src/ros/mission_status_light.cpp
  src/ros/mission_drive_control.cpp
  src/missions/mission_execution.cpp
  src/missions/route_mission.cpp
  src/missions/route_search.cpp
  src/missions/astronaut_mission.cpp
  src/missions/mission_recovery.cpp
  src/missions/mission_completion.cpp
  src/ros/waypoint_requests.cpp
  src/navigation/gps_waypoint_conversion.cpp
)

set(dependencies
  builtin_interfaces
  rclcpp
  rclcpp_action
  rclcpp_components
  geometry_msgs
  nav_msgs
  geodesy
  geographic_msgs
  std_msgs
  std_srvs
  tf2_geometry_msgs
  tf2_ros
  urc_msgs
)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

# Node registration
rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "nav_coordinator::NavCoordinator"
  EXECUTABLE ${PROJECT_NAME}_NavCoordinator
)

install(
  DIRECTORY include/
  DESTINATION include
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

ament_export_include_directories(include)

ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

install(DIRECTORY config docs DESTINATION share/${PROJECT_NAME})

ament_package()
