cmake_minimum_required(VERSION 3.5)
project(urc_gazebo)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(urc_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(laser_geometry REQUIRED)

include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME}_gazebo SHARED
  src/scan_to_pointcloud.cpp
  #add more .cpp files here
)

set(dependencies
  rclcpp
  rclcpp_components
  urc_msgs
  std_msgs
  nav_msgs
  sensor_msgs
  tf2
  tf2_ros
  laser_geometry
)

ament_target_dependencies(${PROJECT_NAME}_gazebo
  ${dependencies}
)

# Node registration
rclcpp_components_register_node(
  ${PROJECT_NAME}_gazebo
  PLUGIN "scan_to_pointcloud::ScanToPointCloud"
  EXECUTABLE ${PROJECT_NAME}_ScanToPointCloud_node
)

# Install launch files.
install(DIRECTORY
        launch
        DESTINATION share/${PROJECT_NAME}/
        )

# Install gazebo files
install(DIRECTORY
        urdf
        DESTINATION share/${PROJECT_NAME}/
        )

# Install library
install(TARGETS 
  ${PROJECT_NAME}_gazebo
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
ament_export_libraries(${PROJECT_NAME}_gazebo)
ament_export_dependencies(${dependencies})

ament_package()