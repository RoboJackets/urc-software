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
active until the whole sequence succeeds, fails, or is canceled.

Inside the coordinator, the normal flow is:

```text
Event → transitionOn() → changeState()
                              ↓
Timer → updateMission() → updateCurrentState() → current state's function
                                                   ↓
                                     Start once, then check progress
                                                   ↓
                                             Next event
```

The constructor in `src/nav_coordinator.cpp` sets up the timer and subscriptions.
ROS calls them when the timer fires or a message arrives. The methods spread
across `src/ros/` and `src/missions/` all belong to the same `NavCoordinator`
object. `NavigationClient` and `AstronautTracking` are components it owns.

## Mission sequences

**Route:** drive to the supplied waypoint → wait for marker 1 or 2 → calculate
an approach → drive toward the marker → verify distance within 1 m → succeed.
Search motion is a placeholder for the incoming spiral-search node. Without a
matching detection, the search phase times out.

**Astronaut:** drive to the rendezvous waypoint → gesture or remote FOLLOW → follow the
tracked person → wait when they stop nearby → remote STAY → FETCH → grasp
confirmation → COME → return within 3 m → GIVE → release confirmation → succeed.
Fetch and give currently support simulated completion only.

## Where to read next

- [Files and functions](docs/code_guide.md): every package file, what its functions do, and example call flows.
- [States and recovery](docs/state_machine.md): exact transition conditions and differences from the architecture drawing.
- [Inputs and integration](docs/integration.md): topics, frames, and external nodes needed to run missions.

## Running

```bash
ros2 launch urc_bringup autonomy.launch.py
```

This starts the coordinator, planner, follower, traversability mapper, and Grid
Map visualization. Sensor sources, localization, and astronaut input publishers
must be running separately. Settings live in [config/mission.yaml](config/mission.yaml).

To exercise fetch/give without an arm, add `tool_placeholder_success:=true`.
The default is `false`, which fails those phases explicitly with `TOOL_FAILED`.

Send route goals to `/execute_autonomous_mission` using
`urc_msgs/action/ExecuteAutonomousMission` with a map `waypoint` and `marker_id`
1 or 2. Send astronaut goals to `/execute_astronaut_mission` using
`urc_msgs/action/ExecuteAstronautMission` with the initial map `waypoint`.
Standalone navigation uses `/nav/waypoint` (map pose) or `/waypoint` (GPS).

The route action uses `marker_id`; clients using the old `search_mode` interface
must be rebuilt. Use standalone waypoints for travel without marker detection.
