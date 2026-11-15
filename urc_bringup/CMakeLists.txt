cmake_minimum_required(VERSION 3.5)
project(urc_bringup)

include(../cmake/default_settings.cmake)

find_package(ament_cmake REQUIRED)

install(
  DIRECTORY
  launch
  config
  models
  DESTINATION share/${PROJECT_NAME}/
)

ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/hooks/gz_sim_resource_path.dsv")

install(PROGRAMS
  scripts/aruco_detector.py
  scripts/aruco_test_publisher.py
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the copyright linker
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
