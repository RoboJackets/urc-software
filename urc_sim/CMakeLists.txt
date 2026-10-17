cmake_minimum_required(VERSION 3.5)
project(urc_sim)

include(../cmake/default_settings.cmake)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(urc_msgs REQUIRED)
find_package(ignition-msgs8 REQUIRED)
find_package(ignition-transport11 REQUIRED)

include_directories(
  include
)

add_library(${PROJECT_NAME} SHARED
  src/status_light_color.cpp
  src/sim_status_light.cpp
)

set(dependencies
  rclcpp
  rclcpp_components
  urc_msgs
)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

target_link_libraries(${PROJECT_NAME}
  ignition-msgs8::core
  ignition-transport11::core
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "urc_sim::SimStatusLight"
  EXECUTABLE ${PROJECT_NAME}_SimStatusLight
)

install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}/
)

install(
  DIRECTORY include/
  DESTINATION include
)

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
ament_export_dependencies(${dependencies} ignition-msgs8 ignition-transport11)

ament_package()
