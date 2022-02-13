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
find_package(ament_cmake REQUIRED COMPONENTS
        rclcpp
        rclcpp_components
        rclcpp_action
        gazebo_ros_pkgs
        tf2_ros
        sensor_msgs
        nav_msgs
        urc_msgs
        geodesy
        laser_geometry
        tf2
        tf2_ros
        tf2_eigen
        )

# Library creation
add_library(${PROJECT_NAME}_gazebo SHARED
  src/scan_to_pointcloud.cpp
  #add more .cpp files here
)

ament_target_dependencies(${PROJECT_NAME}_components SHARED
  "rclcpp"
  "rclcpp_components"
  "rclcpp_action"
  "gazebo_ros_pkgs"
  "tf2_ros"
  "sensor_msgs"
  "nav_msgs"
  "urc_msgs"
  "geodesy"
  "laser_geometry"
  "tf2"
  "tf2_ros"
  "tf2_eigen"
)

# Node registration
rclcpp_components_register_node(
  ${PROJECT_NAME}_gazebo
  PLUGIN "scan_to_pointcloud::ScanToPointCloud"
  EXECUTABLE ${PROJECT_NAME}ScanToPointCloud_node
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
install(TARGETS ${PROJECT_NAME}_gazebo
  ARCHIVE DESTIVATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()