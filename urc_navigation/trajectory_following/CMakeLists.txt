cmake_minimum_required(VERSION 3.5)
project(trajectory_following)

include(../../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(urc_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(diagnostic_updater REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)

include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/pure_pursuit.cpp
  src/geometry_util.cpp
  src/follower_action_server.cpp
)

set(dependencies
  rclcpp
  rclcpp_components
  urc_msgs
  std_msgs
  sensor_msgs
  geometry_msgs
  diagnostic_updater
  tf2
  tf2_geometry_msgs
  nav_msgs
  visualization_msgs
)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "follower_action_server::FollowerActionServer"
  EXECUTABLE ${PROJECT_NAME}_FollowerActionServer
)

# Install launch files.
install(
  DIRECTORY
  launch
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
  # the following line skips the copyright linker
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(${PROJECT_NAME}_geometry_util_test test/geometry_util_test.cpp)
  target_include_directories(${PROJECT_NAME}_geometry_util_test PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  ament_target_dependencies(${PROJECT_NAME}_geometry_util_test
    ${dependencies}
  )
  target_link_libraries(${PROJECT_NAME}_geometry_util_test ${PROJECT_NAME})
endif()

ament_export_include_directories(msg)

ament_export_include_directories(include)

ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

ament_package()