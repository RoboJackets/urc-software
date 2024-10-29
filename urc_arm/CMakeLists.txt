cmake_minimum_required(VERSION 3.8)
project(urc_arm)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(eigen3_cmake_module REQUIRED)
find_package(Eigen3)
find_package(pinocchio REQUIRED)
find_package(realtime_tools REQUIRED)


include_directories(
  include
)

# Library creation
add_library(${PROJECT_NAME} SHARED
  src/arm_rt.cpp
)

set(dependencies
  rclcpp
  rclcpp_components
  std_msgs
  std_srvs
  geometry_msgs
  sensor_msgs
  realtime_tools
  pinocchio
  Eigen3
)

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
)
# target_link_libraries(${PROJECT_NAME} pinocchio)

# Node Registration
rclcpp_components_register_node(
  ${PROJECT_NAME}
  PLUGIN "urc_arm::ArmRT"
  EXECUTABLE arm_rt_pinocchio
)

# Install launch files.
install(
  DIRECTORY
  DESTINATION share/${PROJECT_NAME}/
)

# Install library
install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

# # Install Python modules
# ament_python_install_package(${PROJECT_NAME})
# # Install Python executables
# install(PROGRAMS
#   scripts/armjoy.py
#   DESTINATION lib/${PROJECT_NAME}
# )

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the copyright linker
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_libraries(${PROJECT_NAME})

ament_package()
