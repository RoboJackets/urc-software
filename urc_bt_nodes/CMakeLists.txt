cmake_minimum_required(VERSION 3.8)
project(urc_bt_nodes)

include(../cmake/default_settings.cmake)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(behaviortree_cpp REQUIRED)
find_package(behaviortree_ros2 REQUIRED)
find_package(pluginlib REQUIRED)
find_package(std_srvs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(urc_msgs REQUIRED)

set(dependencies
  rclcpp
  behaviortree_cpp
  behaviortree_ros2
  pluginlib
  std_srvs
  nav_msgs
  urc_msgs
)

include_directories(
  include
)

add_library(bt_log_info SHARED src/base/log_info.cpp)
ament_target_dependencies(bt_log_info ${dependencies})
target_compile_definitions(bt_log_info PRIVATE BT_PLUGIN_EXPORT)

add_library(bt_call_trigger SHARED src/actions/call_trigger.cpp)
ament_target_dependencies(bt_call_trigger ${dependencies})
target_compile_definitions(bt_call_trigger PRIVATE BT_PLUGIN_EXPORT)

add_library(bt_call_generate_plan SHARED src/actions/call_generate_plan.cpp)
target_compile_definitions(bt_call_generate_plan PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(bt_call_generate_plan ${dependencies})

add_library(bt_follow_path SHARED src/actions/follow_path.cpp)
target_compile_definitions(bt_follow_path PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(bt_follow_path ${dependencies})

add_library(bt_status_light_publisher SHARED src/actions/status_light_publisher.cpp)
target_compile_definitions(bt_status_light_publisher PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(bt_status_light_publisher ${dependencies})

add_library(bt_update_current_pose SHARED src/subscribers/update_current_pose.cpp)
target_compile_definitions(bt_update_current_pose PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(bt_update_current_pose ${dependencies})

set(plugins
  bt_log_info
  bt_call_trigger
  bt_call_generate_plan
  bt_follow_path
  bt_status_light_publisher
  bt_update_current_pose
)

install(TARGETS
  ${plugins}
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  ${plugins}
  LIBRARY DESTINATION share/${PROJECT_NAME}/bt_plugins
  ARCHIVE DESTINATION share/${PROJECT_NAME}/bt_plugins
  RUNTIME DESTINATION share/${PROJECT_NAME}/bt_plugins
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
