cmake_minimum_required(VERSION 3.5)
project(urc_teleop)

include (../cmake/default_settings.cmake)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosbridge_server REQUIRED)

set(dependencies
  rosbridge_server
)

# Install launch files.
install(
  DIRECTORY
  launch
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

ament_export_dependencies(${dependencies})
ament_package()

