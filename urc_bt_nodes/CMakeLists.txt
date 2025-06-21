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

add_library(bt_call_generate_plan SHARED src/call_generate_plan.cpp)
target_compile_definitions(bt_call_generate_plan PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(bt_call_generate_plan ${dependencies})

add_library(bt_call_follow_path SHARED src/call_follow_path.cpp)
target_compile_definitions(bt_call_follow_path PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(bt_call_follow_path ${dependencies})

add_library(bt_call_generate_search_path SHARED src/call_generate_search_path.cpp)
target_compile_definitions(bt_call_generate_search_path PRIVATE BT_PLUGIN_EXPORT)
ament_target_dependencies(bt_call_generate_search_path ${dependencies})

set(plugins
  bt_call_generate_plan
  bt_call_follow_path
  bt_call_generate_search_path
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
