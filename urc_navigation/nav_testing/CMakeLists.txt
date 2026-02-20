cmake_minimum_required(VERSION 3.5)
project(nav_testing)

include(../../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(urc_msgs REQUIRED)

include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/nav_coordinator.cpp
)

set(dependencies
  rclcpp
  rclcpp_action
  rclcpp_components
  geometry_msgs
  std_msgs
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

ament_package()
