# URC Navigation Common

`urc_nav_common` exports shared C++ accessors for
`grid_map_msgs/msg/GridMap`. It has no ROS nodes or launch files.

`grid_map_utils::GridMapUtils` is used by path planning and trajectory following
to select a map layer, convert world coordinates to cell indices, and read a
cell cost.

## Consumer setup

Declare `urc_nav_common` as a package dependency, link it with
`ament_target_dependencies`, and include:

```cpp
#include <urc_nav_common/grid_map_utils.hpp>
```

A consumer must set both the current map and layer before querying it:

```cpp
grid_map_utils::GridMapUtils grid_map;
grid_map.setLayer("traversability_inflated");
grid_map.setMap(message);

float cost = 0.0F;
if (grid_map.tryGetCellCost(x, y, cost)) {
  // Use the selected layer's cost at the world position.
}
```

## Contract

- Query methods return `false` for a missing layer, invalid dimensions or
  resolution, out-of-bounds coordinates, or an invalid data index.
- `setMap` stores a copy of the message.
- Coordinate conversion assumes an axis-aligned map whose pose is its center and
  whose layer data is row-major. It does not apply map-pose rotation or Grid Map
  circular-buffer offsets.
