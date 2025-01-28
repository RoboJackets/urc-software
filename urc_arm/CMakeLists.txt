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
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(glfw3 REQUIRED)

# Build and install simulator
add_executable(
  arm_mjsim
  src/arm_mjsim.cpp
)
ament_target_dependencies(
  arm_mjsim

  rclcpp
  sensor_msgs
  std_msgs
  geometry_msgs
  std_srvs
)
target_link_libraries(
  arm_mjsim
  ${CMAKE_SOURCE_DIR}/lib/mujoco/libmujoco.so.3.2.2
  glfw
)
target_include_directories(
  arm_mjsim
  PUBLIC
  ${CMAKE_SOURCE_DIR}/lib/mujoco
)
install(
  TARGETS arm_mjsim
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files.
install(
  DIRECTORY launch config
  DESTINATION share/${PROJECT_NAME}/
)

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
