cmake_minimum_required(VERSION 3.8)
project(urc_bt_nodes)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

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

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/base/log_info.cpp
  include/urc_bt_nodes/base/log_info.hpp
)

# Register Node
target_compile_features(${PROJECT_NAME} PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_compile_definitions(${PROJECT_NAME} PRIVATE BT_PLUGIN_EXPORT)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

install(
    DIRECTORY include/
    DESTINATION include
)
install(
    TARGETS ${PROJECT_NAME}
    EXPORT export_${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# ROS Nodes Plugin Creation
add_library(
  bt_call_trigger SHARED
  src/actions/call_trigger.cpp
  include/urc_bt_nodes/actions/call_trigger.hpp
)
ament_target_dependencies(bt_call_trigger ${dependencies})
target_compile_features(bt_call_trigger PUBLIC c_std_99 cxx_std_17)
target_compile_definitions(bt_call_trigger PRIVATE BT_PLUGIN_EXPORT)
install(
    TARGETS bt_call_trigger
    LIBRARY DESTINATION lib
)

add_library(
  bt_call_generate_plan SHARED
  src/actions/call_generate_plan.cpp
  include/urc_bt_nodes/actions/call_generate_plan.hpp
)
ament_target_dependencies(bt_call_generate_plan ${dependencies})
target_compile_features(bt_call_generate_plan PUBLIC c_std_99 cxx_std_17)
target_compile_definitions(bt_call_generate_plan PRIVATE BT_PLUGIN_EXPORT)
install(
    TARGETS bt_call_generate_plan
    LIBRARY DESTINATION lib
)

add_library(
  bt_follow_path SHARED
  src/actions/follow_path.cpp
  include/urc_bt_nodes/actions/follow_path.hpp
)
ament_target_dependencies(bt_follow_path ${dependencies})
target_compile_features(bt_follow_path PUBLIC c_std_99 cxx_std_17)
target_compile_definitions(bt_follow_path PRIVATE BT_PLUGIN_EXPORT)
install(
    TARGETS bt_follow_path
    LIBRARY DESTINATION lib
)

add_library(
  bt_status_light_publisher SHARED
  src/actions/status_light_publisher.cpp
  include/urc_bt_nodes/actions/status_light_publisher.hpp
)
ament_target_dependencies(bt_status_light_publisher ${dependencies})
target_compile_features(bt_status_light_publisher PUBLIC c_std_99 cxx_std_17)
target_compile_definitions(bt_status_light_publisher PRIVATE BT_PLUGIN_EXPORT)
install(
    TARGETS bt_status_light_publisher
    LIBRARY DESTINATION lib
)

add_library(
  bt_update_current_pose SHARED
  src/subscribers/update_current_pose.cpp
  include/urc_bt_nodes/subscribers/update_current_pose.hpp
)
ament_target_dependencies(bt_update_current_pose ${dependencies})
target_compile_features(bt_update_current_pose PUBLIC c_std_99 cxx_std_17)
target_compile_definitions(bt_update_current_pose PRIVATE BT_PLUGIN_EXPORT)
install(
    TARGETS bt_update_current_pose
    LIBRARY DESTINATION lib
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(
  include
)
ament_export_libraries(
  ${PROJECT_NAME}
)
ament_export_targets(
  export_${PROJECT_NAME}
)


ament_package()
