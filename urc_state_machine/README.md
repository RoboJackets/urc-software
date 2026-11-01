# Mission coordinator

`NavCoordinator` runs one route mission, astronaut mission, or standalone waypoint
at a time. It decides what the rover should do next. The follower handles driving,
and the planner computes paths.

## How the system fits together

```text
Mission action goal → NavCoordinator → NavigateToWaypoint → Follower → cmd_vel
                                                           ↓
                                                   GeneratePlan / A*

Commands, astronaut poses, marker detections, and rover TF → NavCoordinator
NavCoordinator → mission feedback, state topic, and final action result
```

One mission can contain several navigation goals. The mission action remains
active until the whole sequence succeeds or is canceled. Operational failures and
explicit aborts pause the action for a teleop intervention and later retry.

## Mission sequences

**Route:** navigate to the supplied target waypoint. A fresh nearby ArUco pose
can refine the approach and confirm arrival. If the follower reaches the coordinate
without a fresh detection, stop and request a spiral-search path. Follow it until
a marker is found, then stop search motion before approaching the marker.
Search failure, exhaustion, or timeout pauses the mission. Marker IDs are not
specified in route goals. Setting `aruco_refinement=false` retains coordinate-only
completion without search.

Spiral generation uses `/generate_spiral_search` from
[PR #342](https://github.com/RoboJackets/urc-software/pull/342). Its server must be
installed and running separately; this branch adds the client integration, not a
second generator. Radius and timeout are configured in `config/mission.yaml`.

**Astronaut:** drive to the rendezvous waypoint → gesture or remote FOLLOW → follow the
tracked person → wait when they stop nearby → remote STAY → FETCH → grasp
confirmation → COME → return within 3 m → GIVE → release confirmation → succeed.
Fetch and give currently support simulated completion only.

## Where to read next

- [Coordinator design](docs/code_guide.md): ownership, execution, and integration boundaries.
- [States and recovery](docs/state_machine.md): exact transition conditions and differences from the architecture drawing.
- [Inputs and integration](docs/integration.md): topics, frames, and external nodes needed to run missions.

## Running

```bash
ros2 launch urc_bringup autonomy.launch.py
```

This starts the coordinator, drive mux, planner, follower, traversability mapper, and Grid
Map visualization. Sensor sources, localization, and astronaut input publishers
must be running separately. Settings live in [config/mission.yaml](config/mission.yaml).

To exercise fetch/give without an arm, add `tool_placeholder_success:=true`.
The default is `false`, which pauses those phases explicitly with `TOOL_FAILED`.

Send route goals to `/execute_autonomous_mission` using
`urc_msgs/action/ExecuteAutonomousMission` with the target map `waypoint`. Send astronaut goals to `/execute_astronaut_mission` using
`urc_msgs/action/ExecuteAstronautMission` with the initial map `waypoint`.
Standalone navigation uses `/nav/waypoint` (map pose) or `/waypoint` (GPS).

The coordinator drives the rear status light: red for autonomous operation, blue
for teleoperation, and flashing green at confirmed navigation arrivals. See
[light and drive-mode integration](docs/integration.md#rear-status-light) for the
mode input and configuration.

The route action accepts only `waypoint`; clients using `search_mode` or
`marker_id` must be updated and rebuilt. Convert supplied GNSS coordinates to
the configured map frame before sending an action goal. `route_arrival_radius`
replaces `aruco_arrival_radius`. `search_timeout` bounds the complete fallback,
including service availability, path generation, and following.

Phase limits are configured separately for navigation, search, tools, following,
and command waits. Following and command waits have no deadline by default;
STAYING always waits for a command or cancellation. Custom configurations using
`phase_timeout` must migrate to the [separate limits](docs/state_machine.md#phase-deadlines).

Use `/abort_mission` (`std_srvs/Trigger`) to stop and hand control to teleop while
preserving the current task. Repeating the task's command resumes it; interrupted
following accepts a fresh FOLLOW gesture or remote command. `/resume_mission`
(`std_srvs/Trigger`) retries the saved phase, including route navigation. Resume
waits for valid inputs and confirmed autonomous mux mode. Abort never
initiates a return to the astronaut. See [abort and resume](docs/integration.md#abort-teleoperation-and-resume).
