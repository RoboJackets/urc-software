find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav2_costmap_2d REQUIRED)
find_package(pluginlib REQUIRED)

set(dependencies
    rclcpp
    nav2_costmap_2d
    pluginlib
)

# Traversability layer plugin
add_library(traversability_layer SHARED
    traversability_layer/traversability_layer.cpp
    traversability_layer/traversability_layer.hpp
    gridmap_layer/gridmap_layer.cpp
    gridmap_layer/gridmap_layer.hpp
)
pluginlib_export_plugin_description_file(nav2_costmap_2d back_circle_layer/back_circle_layer_plugin.xml)
ament_target_dependencies(traversability_layer ${dep_pkgs})

# Rolling layer plugin
add_library(rolling_layer SHARED
    rolling_layer/rolling_layer.cpp
    rolling_layer/rolling_layer.hpp
)
pluginlib_export_plugin_description_file(nav2_costmap_2d rolling_layer/rolling_layer_plugin.xml)
ament_target_dependencies(rolling_layer ${dep_pkgs})

# Unrolling layer plugin
add_library(unrolling_layer SHARED
    unrolling_layer.cpp
    unrolling_layer.hpp
)
pluginlib_export_plugin_description_file(nav2_costmap_2d unrolling_layer/unrolling_layer_plugin.xml)
ament_target_dependencies(unrolling_layer ${dep_pkgs})

# Back circle plugin
add_library(back_circle_layer SHARED
	back_circle_layer.cpp
    back_circle_layer.hpp
)
pluginlib_export_plugin_description_file(nav2_costmap_2d back_circle_layer/back_circle_layer_plugin.xml)
ament_target_dependencies(back_circle_layer ${dep_pkgs})

# Installing plugins
install(
    TARGETS line_layer traversability_layer rolling_layer back_circle_layer
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION lib/${PROJECT_NAME}
)
