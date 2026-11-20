# URC Interfaces

`urc_msgs` defines the custom ROS 2 interfaces shared across rover packages. It
contains no runtime nodes.

## Messages

| Interface | Purpose |
| --- | --- |
| `BatteryInfo` | Battery voltage, charge, current, temperature, and per-cell telemetry |
| `DetectionBoundingBox` | Timestamped YOLO detection, confidence, image size, and pixel bounds |
| `GridLocation` | Unsigned grid-cell coordinates |
| `OrientationPoses` | Header and named pose collection |
| `RoverPoses` | Header and named rover-pose collection |
| `StatusLightCommand` | Status-light color and off/on/blink state |
| `AstronautCommand` | Timestamped gesture/remote task command or operator abort/resume |
| `ArucoDetection` | Marker ID and stamped pose from one observation |
| `Waypoint` | Latitude and longitude for a navigation target |

## Service and Action

| Interface | Purpose |
| --- | --- |
| `GenerateSpiralSearch` service | Returns a traversability-routed spiral path; compatible with spiral-search PR #342 |
| `GeneratePlan` service | Requests a path between start and goal poses and returns a `nav_msgs/Path` with a success or failure code |
| `ExecuteAutonomousMission` action | Navigates to a target waypoint with optional ArUco refinement |
| `ExecuteAstronautMission` action | Runs rendezvous, follow, stay, fetch, come, and give |
| `NavigateToWaypoint` action | Follows a supplied path or plans to a goal, with optional final-heading enforcement and progress feedback |

## Mission contracts

`ExecuteAutonomousMission` accepts a target map waypoint. Arrival requires the
rover to be within the configured waypoint radius (1 m by default). Fresh ArUco observations near the waypoint refine the approach and check
distance to the post. With default coordinator settings, arrival without a fresh
detection triggers a bounded spiral-search fallback. Disable `aruco_refinement`
for coordinate-only completion. The result includes the last associated observation when
`has_aruco_pose=true`; that pose may be older than the final arrival measurement.

`ExecuteAstronautMission` accepts the initial rendezvous waypoint. Subsequent
FOLLOW/STAY/FETCH/COME/GIVE phases belong to that action and use tracked astronaut
positions. Feedback explicitly reports whether arm completion is simulated.

Both actions return a terminal error code and diagnostic message. Operational
failures pause the active action for teleoperation and an explicit resume;
ROS action cancellation is terminal. Invalid/busy
requests are rejected before execution and have no action result. Definitions in
`action/` are authoritative. See the [mission documentation](../urc_state_machine/README.md)
for transition conditions, result handling, and integration requirements.

`AstronautCommand` includes a timestamp, command enum, and source enum. FOLLOW
accepts GESTURE or REMOTE as a fallback; the other commands require REMOTE.
REMOTE means the astronaut's device, rather than a C2 operator intervention.
ABORT and RESUME accept REMOTE or OPERATOR. ABORT preserves the interrupted task
for teleoperation; RESUME retries it after input and navigation readiness checks.
Repeating FOLLOW from GESTURE or REMOTE also resumes interrupted following;
FETCH/COME/GIVE can resume their own task from REMOTE. Rebuild command producers
after adding the ABORT/RESUME commands and OPERATOR source constants.
`ArucoDetection` bundles a
marker ID with its timestamped pose, preventing mismatched ID/pose observations.

**Migration:** `ExecuteAutonomousMission.search_mode`, SEARCH_NONE/YOLO modes,
and its unused bounding-box result were removed. The intermediate `marker_id`
route field and fixed ID constants were also removed. Use a target `waypoint` for routes,
`ExecuteAstronautMission` for astronaut assistance, and direct waypoint inputs
for standalone navigation. Rebuild all producers and consumers after interface
changes. `NavigateToWaypoint` and `GeneratePlan` remain unchanged.
