find_package(ament_cmake_pytest REQUIRED)
find_package(launch_testing_ament_cmake REQUIRED)
find_package(ament_cmake_gtest REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(urc_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(laser_geometry REQUIRED)

# Library creation
add_library(${PROJECT_NAME}_tests SHARED
  #add more test .cpp files here  
  test_scan_to_pointcloud.cpp
)

set(test_dependencies
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

install(TARGETS 
  ${PROJECT_NAME}_tests
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

ament_target_dependencies(${PROJECT_NAME}_tests
  ${test_dependencies}
)

ament_export_libraries(${PROJECT_NAME}_tests)
ament_export_dependencies(${test_dependencies})

ament_add_gtest(test_scan_to_pointcloud test_scan_to_pointcloud.cpp)
target_link_libraries(test_scan_to_pointcloud ${PROJECT_NAME}_tests)
