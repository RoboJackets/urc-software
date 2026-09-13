# URC State Machine

`urc_state_machine` coordinates high-level waypoint requests with the trajectory
follower. It does not generate paths or command drivetrain velocity directly.

## Navigation flow

`urc_state_machine_NavCoordinator` accepts either:

- a map-frame `geometry_msgs/msg/PoseStamped` on `/nav/waypoint`, or
- a latitude/longitude `urc_msgs/msg/Waypoint` on `/waypoint`.

GPS waypoints are converted to UTM and transformed from `utm` into `map`. The
coordinator then sends a goal-based `NavigateToWaypoint` action request. The
trajectory follower calls the A* planning service, follows the returned path,
and reports feedback and completion to the coordinator.

```text
waypoint -> NavCoordinator -> NavigateToWaypoint -> GeneratePlan -> path following
```

## State and failure behavior

The coordinator publishes `IDLE`, `WAITING_FOR_SERVER`, `SENDING_GOAL`,
`TRACKING_GOAL`, `SUCCEEDED`, `FAILED`, or `CANCELED` on
`nav_coordinator_state`, together with its latest error classification.

By default, a new waypoint cancels the active follower goal before being sent.
Missing UTM-to-map transforms, an unavailable follower action server, rejected
goals, planning failures, and follower failures transition the coordinator to
`FAILED`.

## Usage

The coordinator is started as part of the autonomy stack:

```bash
ros2 launch urc_bringup autonomy.launch.py
```

It is also available as the `urc_state_machine_NavCoordinator` executable and a
composable ROS 2 component. This package has no standalone launch file.

The input topics, follower action name, replacement-goal behavior, and map/UTM
frame names are parameters. Pose waypoints must already use coordinates accepted
by the follower and planner; only GPS waypoints are transformed by the
coordinator.
