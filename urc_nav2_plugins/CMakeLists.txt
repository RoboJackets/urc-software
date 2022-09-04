cmake_minimum_required(VERSION 3.5)
project(urc_nav2_plugins)

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

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav2_costmap_2d REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(map_msgs REQUIRED)
find_package(pluginlib REQUIRED)
find_package(grid_map_ros REQUIRED)
find_package(urc_util REQUIRED)

set(dependencies
    rclcpp
    nav2_costmap_2d
    nav2_msgs
    map_msgs
    std_msgs
    grid_map_ros
    pluginlib
    urc_util
)

# --------------------
# Costmap 2D Plugins
# --------------------

# Traversability layer plugin
add_library(traversability_layer SHARED
    src/traversability_layer.cpp
    src/gridmap_layer.cpp
)
target_include_directories(traversability_layer PRIVATE include)
ament_target_dependencies(traversability_layer ${dependencies})

# Rolling layer plugin
add_library(rolling_layer SHARED
    src/rolling_layer.cpp
)
target_include_directories(rolling_layer PRIVATE include)
ament_target_dependencies(rolling_layer ${dependencies})

# --------------------------
# Nav2 Behavior Tree Plugins
# --------------------------
add_library(bt_ARUCO_tag_detected SHARED
    src/bt_ARUCO_tag_detected.cpp
)
target_include_directories(bt_ARUCO_tag_detected PRIVATE include)
ament_target_dependencies(bt_ARUCO_tag_detected ${dependencies})


# Installing plugin libraries
install(TARGETS
    traversability_layer
    rolling_layer
    bt_ARUCO_tag_detected

    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/
  DESTINATION include/
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
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

pluginlib_export_plugin_description_file(nav2_costmap_2d costmap_2d_plugins.xml)

ament_package()