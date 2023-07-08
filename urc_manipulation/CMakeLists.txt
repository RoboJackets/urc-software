cmake_minimum_required(VERSION 3.5)
project(urc_manipulation)

set(CMAKE_BUILD_TYPE "Release")

include(../cmake/default_settings.cmake)

# C++ Libraries #################################################

# Core C++ library for calculations and collision checking.
# Provides interface used by the component node.
set(SERVO_LIB_NAME moveit_servo_lib)
# C++ library containing the parameters initialization
# - This is intended to use with the component node when you
# -   need to read the parameters loaded into servo in a separate
# -   node.
set(SERVO_PARAM_LIB_NAME ${SERVO_LIB_NAME}_parameters)

# Pose Tracking
set(POSE_TRACKING pose_tracking)

# Component Nodes (Shared libraries) ############################
set(SERVO_COMPONENT_NODE servo_node)
set(SERVO_CONTROLLER_INPUT servo_controller_input)

# Executable Nodes ##############################################
set(SERVO_NODE_MAIN_NAME servo_node_main)
#set(POSE_TRACKING_DEMO_NAME servo_pose_tracking_demo)
#set(FAKE_SERVO_CMDS_NAME fake_command_publisher)

#################################################################

find_package(moveit_common REQUIRED)
moveit_package()

set(THIS_PACKAGE_INCLUDE_DEPENDS
  controller_manager
  controller_manager_msgs
  control_msgs
  control_toolbox
  geometry_msgs
  moveit_core
  moveit_msgs
  moveit_ros_planning
  pluginlib
  rclcpp
  rclcpp_components
  sensor_msgs
  std_msgs
  std_srvs
  tf2_eigen
  trajectory_msgs
)

# find dependencies
find_package(ament_cmake REQUIRED)

foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

include_directories(
  include
)

###################
## C++ Libraries ##
###################

# This library provides a way of loading parameters for servo
add_library(${SERVO_PARAM_LIB_NAME} SHARED
  src/servo_parameters.cpp
  src/parameter_descriptor_builder.cpp
)
set_target_properties(${SERVO_PARAM_LIB_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
ament_target_dependencies(${SERVO_PARAM_LIB_NAME} ${THIS_PACKAGE_INCLUDE_DEPENDS})

# This library provides a C++ interface for sending realtime twist or joint commands to a robot
add_library(${SERVO_LIB_NAME} SHARED
  # These files are used to produce differential motion
  src/collision_check.cpp
  src/enforce_limits.cpp
  src/servo.cpp
  src/servo_calcs.cpp
  src/utilities.cpp
)
set_target_properties(${SERVO_LIB_NAME} PROPERTIES VERSION "${${PROJECT_NAME}_VERSION}")
ament_target_dependencies(${SERVO_LIB_NAME} ${THIS_PACKAGE_INCLUDE_DEPENDS})
target_link_libraries(${SERVO_LIB_NAME} ${SERVO_PARAM_LIB_NAME})

add_library(${POSE_TRACKING} SHARED src/pose_tracking.cpp)
ament_target_dependencies(${POSE_TRACKING} ${THIS_PACKAGE_INCLUDE_DEPENDS})
target_link_libraries(${POSE_TRACKING} ${SERVO_LIB_NAME})


#####################
## Component Nodes ##
#####################

# Add and export library to run as a ROS node component, and receive commands via topics
add_library(${SERVO_COMPONENT_NODE} SHARED src/servo_node.cpp)
ament_target_dependencies(${SERVO_COMPONENT_NODE} ${THIS_PACKAGE_INCLUDE_DEPENDS})
target_link_libraries(${SERVO_COMPONENT_NODE} ${SERVO_LIB_NAME})
rclcpp_components_register_nodes(${SERVO_COMPONENT_NODE} "moveit_servo::ServoNode")

# Add executable for using a controller
#add_library(${SERVO_CONTROLLER_INPUT} SHARED src/joy_to_servo_pub.cpp)
#ament_target_dependencies(${SERVO_CONTROLLER_INPUT} ${THIS_PACKAGE_INCLUDE_DEPENDS})
#rclcpp_components_register_nodes(${SERVO_CONTROLLER_INPUT} "joy_to_servo_pub::JoyToServoPub")

# Manual controls for the robotic arm
add_library(${SERVO_CONTROLLER_INPUT} SHARED
  src/joy_to_servo_pub.cpp
)

ament_target_dependencies(${SERVO_CONTROLLER_INPUT}
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)
# Node registration
rclcpp_components_register_node(
  ${SERVO_CONTROLLER_INPUT}
  PLUGIN "joy_to_servo_pub::JoyToServoPub"
  EXECUTABLE ${SERVO_CONTROLLER_INPUT}_JoyToServoPub
)

######################
## Executable Nodes ##
######################

# An executable node for the servo server
add_executable(${SERVO_NODE_MAIN_NAME} src/servo_node_main.cpp)
target_link_libraries(${SERVO_NODE_MAIN_NAME} ${SERVO_COMPONENT_NODE})
ament_target_dependencies(${SERVO_NODE_MAIN_NAME} ${THIS_PACKAGE_INCLUDE_DEPENDS})

# An example of pose tracking
#add_executable(${POSE_TRACKING_DEMO_NAME} src/cpp_interface_demo/pose_tracking_demo.cpp)
#target_link_libraries(${POSE_TRACKING_DEMO_NAME} ${POSE_TRACKING})
#ament_target_dependencies(${POSE_TRACKING_DEMO_NAME} ${THIS_PACKAGE_INCLUDE_DEPENDS})

# Add executable to publish fake servo commands for testing/demo purposes
#add_executable(${FAKE_SERVO_CMDS_NAME} test/publish_fake_jog_commands.cpp)
#ament_target_dependencies(${FAKE_SERVO_CMDS_NAME}
#  rclcpp
#  geometry_msgs
#  std_srvs
#)

#############
## Install ##
#############

# Install Libraries
install(
  TARGETS
    ${SERVO_LIB_NAME}
    ${SERVO_LIB_NAME}_parameters
    ${POSE_TRACKING}
    ${SERVO_COMPONENT_NODE}
    ${SERVO_CONTROLLER_INPUT}
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# Install launch files.
install(DIRECTORY include/ DESTINATION include)
install(
  DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}/
)

# Install Binaries
install(TARGETS
  #${PROJECT_NAME}
  ${SERVO_NODE_MAIN_NAME}
  ${CPP_DEMO_NAME}
  ${POSE_TRACKING_DEMO_NAME}
  ${FAKE_SERVO_CMDS_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

#############
## TESTING ##
#############

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
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})

ament_package()


