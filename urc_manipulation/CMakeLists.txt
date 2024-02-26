cmake_minimum_required(VERSION 3.5)
project(urc_manipulation)

include(../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(moveit_servo REQUIRED)


include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/joy_to_servo_pub.cpp
  src/arm_rt_server.cpp
)

set(dependencies
  rclcpp
  rclcpp_components
  sensor_msgs
  geometry_msgs
  std_srvs
  moveit_msgs
  control_msgs
  moveit_servo
)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

# Node registration
rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "joy_to_servo_pub::JoyToServoPub"
  EXECUTABLE ${PROJECT_NAME}_JoyToServoPub
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "urc_manipulation::ArmRTServer"
  EXECUTABLE ${PROJECT_NAME}_ArmRT
)

add_executable(arm_servo src/servo_node.cpp)
target_include_directories(arm_servo PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(arm_servo PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  arm_servo
  ${dependencies}
)
install(TARGETS arm_servo
  DESTINATION lib/${PROJECT_NAME})

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

ament_export_include_directories(include)

ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

ament_package()
