cmake_minimum_required(VERSION 3.10)
project(cartesian_controller_simulation)

find_package(ament_cmake REQUIRED)

install(
  DIRECTORY config etc urdf meshes
  DESTINATION share/${PROJECT_NAME}
)

install(PROGRAMS scripts/gripper_telemetry.py
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
