# URC Perception

`urc_perception` converts terrain point clouds into the rolling traversability
grid map used by path planning and trajectory following.

## Mapping pipeline

`TraversabilityMapping`:

1. Filters non-finite points and points outside the configured sensor radius.
2. Transforms the cloud into the `map` frame.
3. Extracts an elevation grid and applies the configured Grid Map filter chain.
4. Computes slope and roughness, combines them into traversability cost, and
   inflates that cost with the package's Gaussian filter plugin.
5. Merges the result into a rolling cache centered on the latest odometry pose.

With the default configuration, the node consumes `/scan/points` and
`/odometry/filtered_global`, then publishes `/costmap` as
`grid_map_msgs/msg/GridMap`. Navigation consumes its
`traversability_inflated` layer.

## Configuration

- [`config/traversability_params.yaml`](config/traversability_params.yaml)
  defines topics, frames, cache geometry, point filtering, and the Grid Map
  filter chain.
- [`config/pcl_grid_map_params.yaml`](config/pcl_grid_map_params.yaml) controls
  point-cloud preprocessing and elevation-grid extraction.
- [`filter_plugins.xml`](filter_plugins.xml) exports
  `urcPerception/GaussianFilter` for use in Grid Map filter chains.

## Usage

Start the complete autonomy stack, including mapping and Grid Map visualization:

```bash
ros2 launch urc_bringup autonomy.launch.py
```

Start only the traversability mapper:

```bash
ros2 launch urc_perception mapping.launch.py
```

The standalone mapping launch does not start a point-cloud source, localization,
or the required TF tree. Incoming clouds are skipped when their sensor frame
cannot be transformed into `map`. Tune the map resolution, cache size, filter
radii, and cost calculation together with their navigation consumers.
