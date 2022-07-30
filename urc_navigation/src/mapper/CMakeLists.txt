# Traversability layer plugin
add_library(traversability_layer
    traversability_layer/traversability_layer.cpp
    traversability_layer/traversability_layer.hpp
    traversability_layer/traversability_layer_config.cpp
    traversability_layer/traversability_layer_config.hpp
    map_config/map_config.cpp
    map_config/map_config.hpp
    gridmap_layer/gridmap_layer.cpp
    gridmap_layer/gridmap_layer.hpp
)
ament_export_libraries(traversability_layer)
target_link_libraries(traversability_layer ${AMENT_LIBRARIES})

# Rolling layer plugin
add_library(rolling_layer
    rolling_layer/rolling_layer.cpp
    rolling_layer/rolling_layer.hpp
    rolling_layer/rolling_layer_config.cpp
    rolling_layer/rolling_layer_config.hpp
)
ament_export_libraries(rolling_layer)
target_link_libraries(rolling_layer ${AMENT_LIBRARIES})

# Unrolling layer plugin
add_library(unrolling_layer
    unrolling_layer.cpp
    unrolling_layer.hpp
    unrolling_layer_config.cpp
    unrolling_layer.hpp
)
ament_export_libraries(rolling_layer)
target_link_libraries(unrolling_layer ${AMENT_LIBRARIES})

# Back circle plugin
add_library(back_circle_layer
	back_circle_layer.cpp
    back_circle_layer.hpp
)
ament_export_libraries(back_circle_layer)
target_link_libraries(back_circle_layer ${AMENT_LIBRARIES})

# Installing plugins
install(
    TARGETS line_layer traversability_layer rolling_layer back_circle_layer
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION lib/${PROJECT_NAME}
)
