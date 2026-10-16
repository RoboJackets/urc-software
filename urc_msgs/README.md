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
| `AstronautCommand` | Timestamped gesture/remote mission command |
| `ArucoDetection` | Marker ID and stamped pose from one observation |
| `Waypoint` | Latitude and longitude for a navigation target |

## Service and Action

| Interface | Purpose |
| --- | --- |
| `GeneratePlan` service | Requests a path between start and goal poses and returns a `nav_msgs/Path` with a success or failure code |
| `ExecuteAutonomousMission` action | Navigates to a search area and approaches marker 1 or 2 |
| `ExecuteAstronautMission` action | Runs rendezvous, follow, stay, fetch, come, and give |
| `NavigateToWaypoint` action | Follows a supplied path or plans to a goal, with optional final-heading enforcement and progress feedback |

## Mission contracts

`ExecuteAutonomousMission` accepts a map waypoint and `marker_id` (1 or 2).
It navigates to the search area, searches for that marker, approaches it, and
verifies arrival within the configured radius (1 m by default). A successful
result includes `aruco_pose` with `has_aruco_pose=true`.

`ExecuteAstronautMission` accepts the initial rendezvous waypoint. Subsequent
FOLLOW/STAY/FETCH/COME/GIVE phases belong to that action and use tracked astronaut
positions. Feedback explicitly reports whether arm completion is simulated.

Both actions return a terminal error code and diagnostic message. Invalid/busy
requests are rejected before execution and have no action result. Definitions in
`action/` are authoritative. See the [mission documentation](../urc_state_machine/README.md)
for transition conditions, result handling, and integration requirements.

`AstronautCommand` includes a timestamp, command enum, and source enum. FOLLOW
requires GESTURE; the other commands require REMOTE. `ArucoDetection` bundles a
marker ID with its timestamped pose, preventing mismatched ID/pose observations.

**Migration:** `ExecuteAutonomousMission.search_mode`, SEARCH_NONE/YOLO modes,
and its unused bounding-box result were removed. Use `marker_id` for routes,
`ExecuteAstronautMission` for astronaut assistance, and direct waypoint inputs
for standalone navigation. Rebuild all producers and consumers after interface
changes. `NavigateToWaypoint` and `GeneratePlan` remain unchanged.
