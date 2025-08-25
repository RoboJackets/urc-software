cmake_minimum_required(VERSION 3.8)
project(urc_controllers)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(controller_interface REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(realtime_tools REQUIRED)
find_package(pluginlib REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(urc_hw REQUIRED)
find_package(urc_msgs REQUIRED)
find_package(urc_nanopb REQUIRED)
find_package(joint_trajectory_controller REQUIRED)
find_package(control_toolbox REQUIRED)

add_library(
  ${PROJECT_NAME}
  SHARED
  src/status_light_controller.cpp
  src/bms_broadcaster.cpp
  include/urc_controllers/status_light_controller.hpp
  include/urc_controllers/bms_broadcaster.hpp
)

target_compile_features(urc_controllers PUBLIC c_std_99 cxx_std_17)
target_include_directories(urc_controllers PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

ament_target_dependencies(
  ${PROJECT_NAME}
  controller_interface
  hardware_interface
  realtime_tools
  pluginlib
  rclcpp
  rclcpp_lifecycle
  urc_hw
  urc_nanopb
  urc_msgs
)

target_compile_definitions(urc_controllers PRIVATE "urc_hw_BUILDING_LIBRARY")
pluginlib_export_plugin_description_file(controller_interface urc_controllers.xml)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
    TARGETS urc_controllers
    EXPORT export_${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

ament_export_include_directories(
  include
)
ament_export_libraries(
  ${PROJECT_NAME}
)
ament_export_dependencies(
  controller_interface
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  urc_hw
)

ament_export_targets(
    export_${PROJECT_NAME}
)

ament_package()
