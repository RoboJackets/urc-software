# URC Perception

`urc_perception` converts terrain point clouds into the rolling traversability
grid map used by path planning and trajectory following.

## Mapping pipeline

`TraversabilityMapping`:

1. Transforms the input cloud into the `map` frame and crops it to the cache
   window plus `crop_margin_m`.
2. Extracts an elevation grid and applies the configured Grid Map filter chain.
3. Computes slope, roughness and step height, scores each cell against the
   rover's limits, and inflates lethal cells by the rover footprint.
4. Merges the result into a rolling cache centered on the latest odometry pose.

With the default configuration, the node consumes the SLAM map
(`/slam/map_points`) and `/slam/odometry`, then publishes `/costmap` as
`grid_map_msgs/msg/GridMap`. Navigation consumes its
`traversability_inflated` layer.

## Cost contract

- Cost runs from 0 (easy) to 1 (lethal). `TraversabilityCostFilter` takes the
  worst of slope ÷ `max_slope_rad`, roughness ÷ `max_roughness_m` and
  step height ÷ `max_step_height_m`, capped at 1. Step height is the height
  change to a neighboring cell beyond what the local slope explains.
- `FootprintInflationFilter` makes every cell within `inscribed_radius_m` of a
  lethal cell lethal, then decays cost below lethal out to
  `inflation_radius_m`.
- NaN means the cell has not been observed. Unknown cells are never reported
  as 0.
- The roughness and step limits are provisional and should be set from what
  the rover can actually climb. At 0.25 m resolution, a step near the limit is
  hard to tell apart from a slope near the limit.

## Configuration

- [`config/traversability_params.yaml`](config/traversability_params.yaml)
  defines topics, frames, cache geometry, cropping, rover limits, and the Grid
  Map filter chain.
- [`config/pcl_grid_map_params.yaml`](config/pcl_grid_map_params.yaml) controls
  elevation-grid extraction. It is tuned for the 0.2 m voxel SLAM map and is
  read once at startup.
- [`filter_plugins.xml`](filter_plugins.xml) exports
  `urcPerception/TraversabilityCostFilter` and
  `urcPerception/FootprintInflationFilter`.

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
