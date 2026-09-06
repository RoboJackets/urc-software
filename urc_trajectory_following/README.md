# URC Trajectory Following

`urc_trajectory_following` owns the `NavigateToWaypoint` action that turns a
planned path into rover velocity commands. The current controller implementation
is [Pure Pursuit](src/pure_pursuit/README.md).

## Action behavior

`urc_trajectory_following_FollowerActionServer` accepts two request forms:

| Goal fields | Behavior |
| --- | --- |
| `has_goal: true` | Gets the current rover pose from TF, calls the `GeneratePlan` A* service, and follows the returned path |
| `has_path: true` | Follows the supplied non-empty `nav_msgs/Path` without initial planning |

If both flags are set, the goal-based planning path takes precedence. A request
with neither flag is rejected.

During execution, the server publishes distance, planning state, and replan count
as action feedback. It checks the controller's tracking point against the
configured costmap layer and requests a new A* path when the cost exceeds the
lethal threshold.

## Runtime contracts

- The action name is `navigate_to_waypoint`; the planning service is `plan`.
- The server requires the configured map-to-base TF throughout execution.
- `/costmap` must contain the configured layer, normally
  `traversability_inflated`. A missing or unreadable cost is currently treated as
  zero and therefore does not trigger replanning.
- Velocity output may be `Twist` or `TwistStamped`, selected by
  `cmd_vel_stamped`; its topic is configured by `cmd_vel_topic`.
- Cancellation, completion, and handled planning failures publish a final
  zero-velocity command.
- Goal heading is enforced when requested by the action or enabled in the node
  configuration.

## Usage

The normal entry point is the complete autonomy stack:

```bash
ros2 launch urc_bringup autonomy.launch.py
```

To start only the follower with its installed configuration:

```bash
ros2 launch urc_trajectory_following trajectory_following.launch.py
```

The standalone launch still requires TF and, for goal-based requests, the
planner and traversability map. Runtime settings live in
[`config/pure_pursuit_config.yaml`](config/pure_pursuit_config.yaml). Although
the controller is selected through `TrajectoryFactory`, `pure_pursuit` is the
only supported selection today.
