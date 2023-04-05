cmake_minimum_required(VERSION 3.5)
project(urc_manipulation)

include(../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/arm_driver.cpp
)

set(dependencies
  rclcpp
  rclcpp_components

)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

# Node registration
rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "motor_controller::MotorControllerWrapper"
  EXECUTABLE ${PROJECT_NAME}_MotorController
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
endif()

ament_package()


