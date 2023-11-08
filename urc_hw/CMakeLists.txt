cmake_minimum_required(VERSION 3.8)
project(urc_hw)


if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(hardware_interface REQUIRED)
find_package(rclcpp REQUIRED)
find_package(pluginlib REQUIRED)
find_package(nanopb REQUIRED)
find_package(urc_util REQUIRED)
find_package(urc_nanopb REQUIRED)

add_library(
    urc_hw
    SHARED
    src/hardware/serial.cpp
    src/hardware_interfaces/imu.cpp
    src/hardware_interfaces/status_light.cpp
    src/hardware_interfaces/battery_management.cpp
    include/urc_hw/hardware/serial.hpp
    include/urc_hw/hardware_interfaces/imu.hpp
    include/urc_hw/hardware_interfaces/status_light.hpp
    include/urc_hw/hardware_interfaces/battery_management.hpp
    include/urc_hw/hardware_interface_types.hpp

    include/async_sockets/basesocket.hpp
    include/async_sockets/udpsocket.hpp
)

target_compile_features(urc_hw PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
target_include_directories(urc_hw PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
    urc_hw
    "hardware_interface"
    "rclcpp"
    "nanopb"
    "urc_util"
    "urc_nanopb"
    "pluginlib"
)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(urc_hw PRIVATE "urc_hw_BUILDING_LIBRARY")
pluginlib_export_plugin_description_file(hardware_interface urc_hw.xml)

install(
    DIRECTORY include/
    DESTINATION include
)
install(
    TARGETS urc_hw
    EXPORT export_${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

if (BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif ()

ament_export_include_directories(
    include
)
ament_export_libraries(
    urc_hw
)
ament_export_targets(
    export_${PROJECT_NAME}
)

ament_package()
