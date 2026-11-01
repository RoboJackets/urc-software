cmake_minimum_required(VERSION 3.5)
project(urc_hw_description)

include(../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(urdf REQUIRED)
find_package(xacro REQUIRED)
find_package(gz_ros2_control REQUIRED)
find_package(ros_gz_sim REQUIRED)
find_package(ros_gz_bridge REQUIRED)
find_package(joint_state_broadcaster REQUIRED)
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

ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  rclcpp_components
  urc_msgs
)

target_link_libraries(${PROJECT_NAME}
  ignition-msgs8::core
  ignition-transport11::core
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "urc_hw_description::SimStatusLight"
  EXECUTABLE ${PROJECT_NAME}_SimStatusLight
)

install(
  DIRECTORY
    urdf
    config
    world
    models
    launch
    rviz
  DESTINATION share/${PROJECT_NAME}
)

install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/hooks/gz_sim_resource_path.sh")
ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/hooks/gz_sim_resource_path.dsv")
ament_package()
