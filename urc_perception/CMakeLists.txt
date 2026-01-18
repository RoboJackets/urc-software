cmake_minimum_required(VERSION 3.5)
project(urc_perception)

include(../cmake/default_settings.cmake)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_sensor_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
cmake_policy(SET CMP0074 NEW)
find_package(PCL 1.10 REQUIRED)
find_package(grid_map_core REQUIRED)
find_package(grid_map_ros REQUIRED)
find_package(grid_map_msgs REQUIRED)
find_package(grid_map_pcl REQUIRED)
find_package(grid_map_cv REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(filters REQUIRED)
find_package(pluginlib REQUIRED)


add_compile_options(-Wno-enum-constexpr-conversion)

include_directories(
  include
  ${PCL_INCLUDE_DIRS}
  ${filters_INCLUDE_DIRS}
)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/traversability_mapping.cpp
)



target_link_libraries(${PROJECT_NAME}
  ${PCL_LIBRARIES}
)

set(dependencies
  rclcpp
  rclcpp_components
  std_msgs
  sensor_msgs
  geometry_msgs
  tf2
  tf2_sensor_msgs
  tf2_geometry_msgs
  nav_msgs
  pcl_conversions
  grid_map_core
  grid_map_ros
  grid_map_msgs
  grid_map_pcl
  grid_map_cv
  filters
  pluginlib
)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)

rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "urc_perception::TraversabilityMapping"
  EXECUTABLE ${PROJECT_NAME}_TraversabilityMapping
)

# Install launch files.
install(
  DIRECTORY config launch
  DESTINATION share/${PROJECT_NAME}/
)

install(
  FILES filter_plugins.xml
  DESTINATION share/${PROJECT_NAME}
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
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(${dependencies})
ament_package()
