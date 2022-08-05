# URC Nav2 Plugins

This package is a collection of custom node plugins for Nav2. Plugins allow us to heavily customize
our Nav2 stack, and tune it more to our specific use case.

[You can see the plugins being integrated into the Nav2 stack here](../urc_navigation/config/)

## Costmap 2D Plugins

- #### **Rolling Layer**
  - Transfers data from global costmap to local costmap

- #### **Traversability Layer**
  - Performs occupancy grid mapping, using GridMap as the backing data structure
  - GridMap is currently used as a submodule, [you can find it here](../external/grid_map/)