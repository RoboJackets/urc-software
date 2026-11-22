# URC Path Planning

`urc_path_planning` provides the rover's global A* planner and exposes it through
the `urc_msgs/srv/GeneratePlan` service.

## Planning versus following

These interfaces serve different parts of navigation:

| Interface | Responsibility |
| --- | --- |
| `GeneratePlan` service | Runs A* once and returns a waypoint path; it does not move the rover |
| `NavigateToWaypoint` action | Follows a supplied path, or requests an A* path for a goal and then follows it |

`NavigateToWaypoint` is implemented by `urc_trajectory_following`. The navigation
coordinator sends goal-based action requests, so the follower calls this
package's planning service before commanding motion.

## Planner server

`urc_path_planning_PlannerServer` is also registered as a composable ROS 2
component. Its parameters are in
[`config/planner_params.yaml`](config/planner_params.yaml). It uses these fixed
interfaces:

| Interface | Type | Purpose |
| --- | --- | --- |
| `/costmap` subscription | `grid_map_msgs/msg/GridMap` | Latest traversability map |
| `plan` service | `urc_msgs/srv/GeneratePlan` | Start and goal poses in; path and result code out |
| `/path` publisher | `nav_msgs/msg/Path` | Successful plans for visualization |

The planner reads the `costmap_layer` (default `traversability_inflated`) and
searches an eight-connected grid. Each move is weighted by its distance and the
destination cell's cost. Cells at or above `lethal_cost` are never entered.
Unobserved (NaN) cells cost `unknown_cost`, so known ground is preferred but
unseen ground is not forbidden.

## Usage

The normal entry point is the full autonomy stack:

```bash
ros2 launch urc_bringup autonomy.launch.py
```

To start only the planner server:

```bash
ros2 launch urc_path_planning planning.launch.py
```

The standalone launch requires a compatible `/costmap` publisher before plan
requests can succeed.

## Planning contract

- Request poses and the costmap must use `map` coordinates. The server does not
  transform request frames and publishes paths in `map`.
- The start must lie inside a valid costmap containing the
  `traversability_inflated` layer.
- When a goal lies outside the rolling costmap, A* plans to the map boundary and
  appends a straight segment to the requested goal. Terrain beyond the costmap
  is not validated.
- Invalid maps, out-of-bounds starts, goals in lethal cells, and failed
  searches return `GeneratePlan::FAILURE`. A clipped goal on the map boundary
  can also land in a lethal cell.
