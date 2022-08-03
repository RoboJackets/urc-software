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
    grid_map_ros
    pluginlib
    urc_util
)

# Traversability layer plugin
add_library(traversability_layer SHARED
    src/traversability_layer.cpp
    src/gridmap_layer.cpp
)
target_include_directories(traversability_layer PRIVATE include)
pluginlib_export_plugin_description_file(nav2_costmap_2d traversability_layer_plugin.xml)
ament_target_dependencies(traversability_layer ${dependencies})

# Rolling layer plugin
add_library(rolling_layer SHARED
    src/rolling_layer.cpp
)
target_include_directories(rolling_layer PRIVATE include)
pluginlib_export_plugin_description_file(nav2_costmap_2d rolling_layer_plugin.xml)
ament_target_dependencies(rolling_layer ${dependencies})

# Unrolling layer plugin
add_library(unrolling_layer SHARED
    src/unrolling_layer.cpp
)
target_include_directories(unrolling_layer PRIVATE include)
pluginlib_export_plugin_description_file(nav2_costmap_2d unrolling_layer_plugin.xml)
ament_target_dependencies(unrolling_layer ${dependencies})

# Installing libraries
install(TARGETS 
    traversability_layer 
    rolling_layer
    unrolling_layer
    
    DESTINATION lib
)