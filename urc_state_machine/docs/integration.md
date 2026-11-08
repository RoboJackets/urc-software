# Mission inputs and integration

The [mission flow](../README.md) shows how these interfaces meet at the
coordinator. The [code guide](code_guide.md) traces their callbacks and functions. The coordinator is started by
`ros2 launch urc_bringup autonomy.launch.py` along with the planner, follower,
traversability mapper, and Grid Map visualization. That launch does not supply
camera images, astronaut tracking, gesture/remote commands, localization, or
the TF tree. The ArUco detector has its own launch below. A complete mission
needs the relevant inputs running with timestamps from the same ROS clock.

| Mission | Required live inputs beyond autonomy launch |
| --- | --- |
| Route | Map-to-rover TF, traversability, camera/ArUco input, and spiral generator for fallback; detection/search may be disabled with `aruco_refinement=false` |
| Astronaut | `/astronaut/pose`, `/command`, map-to-rover TF, traversability data; simulated tool completion for an end-to-end test |

The action goal's initial waypoint must be in `map`. `/waypoint` is a separate
standalone GPS input with UTM conversion; it is not a mission action goal.

## Optional ArUco refinement

Route goals use exact target coordinates converted to the map frame. With default settings, coordinate arrival without a detection triggers spiral
search; detection is required before reporting route success. With `aruco_refinement=true`, fresh transformed
observations within `aruco_association_radius` (default 1 m) of that target may
refine the approach. The coordinator uses proximity rather than a requested ID;
place/validate targets accordingly. `aruco_standoff` defaults to 0.5 m, while
`route_arrival_radius` defaults to 1 m. Refined goals remain inside that waypoint
radius. Disable refinement for coordinate-only navigation.

The generator from [PR #342](https://github.com/RoboJackets/urc-software/pull/342)
serves `urc_msgs/srv/GenerateSpiralSearch` on `/generate_spiral_search`. Start its
server separately after installing that implementation. The coordinator requests
the target waypoint as center and `spiral_search_radius` (default 5 m), leaving
spacing overrides at server defaults. Service wait, generation, and following
share `search_timeout` (default 180 s). Missing/invalid paths stop and pause;
there is no unplanned velocity fallback. The generator must set
`traversability_checked=true`. Responses must contain 2–2000 valid map-frame poses.

The detector in `urc_perception/scripts/aruco_detector.py` publishes the paired
mission observation and also provides `/aruco/poses`, `/aruco/ids`,
`/aruco/pose`, and optional `/aruco/image_debug` for other consumers:

```text
/aruco/detections : urc_msgs/msg/ArucoDetection
  marker_id       : int32
  pose            : geometry_msgs/PoseStamped
```

The ID and pose come from the same detection. The coordinator deliberately does
not pair `/aruco/ids` with `/aruco/poses`: IDs lack timestamps, and independent
subscriptions cannot prove they came from the same image.

Run the detector with:

```bash
ros2 launch urc_perception aruco_detector.launch.py
```

Its YAML selects DICT_4X4_50 and all marker IDs. The inherited 0.05 m marker size
is a simulation default: set `marker_size` to the measured physical printed
marker size before trusting distances. The camera image header must identify the
optical frame used by OpenCV (x right, y down, z forward); TF must connect that
frame to `map`. The observation keeps the image timestamp.

This dedicated launch does not start a camera or replace the older perception
launch. Avoid starting competing detector publishers on the same outputs. Existing
6x6 simulation tags require a matching detector config; they are not detected by
the URC 4x4 configuration.

## Astronaut input contracts

| Topic | Type | Required producer behavior |
| --- | --- | --- |
| `/command` | `urc_msgs/AstronautCommand` | Timestamp each new command; FOLLOW accepts GESTURE or REMOTE, other task commands require REMOTE; ABORT/RESUME accept REMOTE or OPERATOR |
| `/astronaut/pose` | `geometry_msgs/PoseStamped` | Track the selected astronaut consistently, with valid pose, frame, and capture timestamp |

REMOTE commands originate from the astronaut's device. OPERATOR identifies C2
ABORT/RESUME intervention. Gesture publishers should emit a new timestamped FOLLOW
event when the gesture is recognized again, rather than continuously replaying a
previous recognition.

Gesture recognition, person tracking, and remote command producers are external
to this package. They must publish these message types with recent timestamps.

Commands use reliable, volatile QoS with a bounded queue. Old commands are never
replayed to a new mission; timestamps at or before the last accepted command or
mission start are discarded. Perception subscriptions use sensor-data QoS and
reject stale, future-dated, out-of-order, or untransformable observations.

Map goals require finite positions and unit quaternions. Perception pose transforms
use the observation timestamp without waiting inside a callback. Robot localization
comes from fresh `map → base_link` TF. An initial GNSS mission location must first
be converted to a map waypoint; `/waypoint` retains the existing UTM conversion
path for standalone navigation.

## Navigation and state output

Both mission actions use the single `NavigateToWaypoint` client. The planner and
follower action contracts are unchanged. Mission state is published on
`nav_coordinator_state` as `std_msgs/String` with reliable, transient-local QoS.
Action feedback gives the same state plus mission-specific progress. The state
publisher retains the last terminal state until another request starts.

## Rear status light

The coordinator publishes `urc_msgs/StatusLightCommand` on `/command/status_light`,
shared by the hardware controller and Gazebo light. Autonomous operation is solid
red. Confirmed route/standalone waypoint completion and astronaut arrivals in
WAIT_FOLLOW, WAIT_STAY, and WAIT_GIVE flash green. Starting another phase clears
the arrival indication; completing FETCH or GIVE alone does not indicate arrival.

`/drive_mode` is the mux's reliable, transient-local `std_msgs/String` output
(`teleop`, `autonomous`, or `disabled`). The coordinator requests mode changes
through `/cmd_vel_mode` and waits for autonomous feedback before starting a phase.
Leaving autonomy pauses an active mission and clears its arrival indication.
The status light follows confirmed mux mode.

Commands are refreshed periodically for consumers that start later. Configure
`status_light_topic`, `drive_mode_topic`, and `status_light_refresh_period` in
`mission.yaml`. Run one status-light command publisher; manual light commands
will be replaced by the coordinator's next update.

The navigation client serializes cancel/replace requests and coalesces rapid target
updates. It never treats distance feedback or a cancellation result as goal success.
Direct waypoint topic requests are ignored during either mission.

## Abort, teleoperation, and resume

```bash
ros2 service call /abort_mission std_srvs/srv/Trigger '{}'
ros2 service call /resume_mission std_srvs/srv/Trigger '{}'
```

Abort requests STOPPING → PAUSED. The mission action stays active, retaining its
task and ownership. After the follower finishes cancellation, the coordinator
requests teleoperation through `/cmd_vel_mode`; the mux reports it on
`/drive_mode`. The abort service response only acknowledges the request. No autonomous return is initiated by abort.

A fresh FOLLOW gesture or remote FOLLOW resumes interrupted following, including
WAIT_FOLLOW/WAIT_STAY. Remote FETCH, COME, and GIVE resume only the corresponding
interrupted task or its preceding command wait. ABORT and RESUME are also available
on `/command`; generic RESUME or the resume service retries the saved phase for
any mission kind, including initial navigation and route missions. Commands sent
before PAUSED or during STOPPING/RESUMING are not queued for later execution.

Resume requires teleop mode, idle/available navigation, fresh rover localization,
and fresh target data when the phase requires it. RESUMING requests autonomous
mode, waits for mux feedback, and rechecks inputs before restarting the saved
phase with a fresh timeout and retry budget. Marker approaches are recomputed
after teleoperation.
Missing inputs reject the resume; reissue the command after inputs recover.
Paused missions have no phase deadline.

Operational failures also stop and enter PAUSED with their reason. ROS action
cancellation remains terminal: it releases the mission after stopping and requests
teleop; it cannot be resumed by a gesture. Use `/abort_mission` for resumable aborts.

The autonomy launch loads `urc_bringup/config/autonomy_drive.yaml` to override the
follower output to stamped `/cmd_vel_autonomous`. The mux selects that input or
stamped `/cmd_vel_teleop` and publishes `geometry_msgs/Twist` on `/cmd_vel`.
Standalone follower defaults are unchanged. Route teleop commands through the mux;
other publishers on `/cmd_vel` bypass arbitration. Mode changes publish zero and
reject commands stamped before the change. A 0.5-second command timeout stops
output when the selected producer stops updating. `/cmd_vel_enabled=false`
disables output and clears autonomous selection; re-enabling starts in teleop.

For simulation, use `use_sim_time:=true` with the autonomy launch; the simulation
launch passes this automatically. All velocity, sensor, and command producers must
share that clock. Real arm actions remain a future integration and must join the cancellation
barrier when added.
