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
| `Waypoint` | Latitude and longitude for a navigation target |

## Service and Action

| Interface | Purpose |
| --- | --- |
| `GeneratePlan` service | Requests a path between start and goal poses and returns a `nav_msgs/Path` with a success or failure code |
| `AstronautFollow` action | Runs the astronaut-follow sub-mission from gesture recognition through follow behavior |
| `ExecuteAutonomousMission` action | Navigates to a waypoint and optionally performs a YOLO or ArUco search while retaining mission context across replans |
| `NavigateToWaypoint` action | Follows a supplied path or plans to a goal, with optional final-heading enforcement and progress feedback |
| `RecognizeFollowGesture` action | Arms camera-based follow-gesture recognition and returns the confirmed astronaut detection |

## Astronaut-follow contract

`AstronautFollow` is the activation boundary for the astronaut-follow
sub-mission. Sending a goal arms follow-gesture recognition for the requested
timeout. A zero timeout delegates timeout selection to the action server's
configuration. Implementations use `astronaut_follow` as the default action
name.

Feedback distinguishes waiting for a confirmed gesture, gesture confirmation,
behavior startup, active following, and temporary target loss. The matching-frame
counts expose temporal confirmation progress without making the classifier's
thresholds part of the action request.

A successful result means the complete sub-mission finished. Recognition
timeout, perception failure, following-behavior failure, and cancellation have
separate result codes. Once a gesture has been confirmed,
`has_astronaut_detection` is true and `astronaut_detection` identifies the
confirmed image-space target, even if a later behavior fails.

`RecognizeFollowGesture` is the narrower perception contract used by the
sub-mission coordinator. Its feedback exposes image availability, processed
frames, temporal-confirmation progress, confidence, and inference latency. It
does not command rover motion.

Once an action server is implemented, inspect its connections and stream its
feedback during a bounded recognition attempt with:

```bash
ros2 action info astronaut_follow
ros2 action send_goal --feedback astronaut_follow \
  urc_msgs/action/AstronautFollow \
  "{recognition_timeout: {sec: 30, nanosec: 0}}"
```

## Autonomous mission contract

`ExecuteAutonomousMission` is the mission-level interface consumed by the
navigation coordinator. Its `search_mode` has these behaviors:

| Search mode | Behavior after reaching the initial waypoint |
| --- | --- |
| `SEARCH_NONE` | Complete without starting a search |
| `SEARCH_YOLO` | Spiral-search until the requested object is detected, then return its bounding box |
| `SEARCH_ARUCO_1` | Search for ArUco 1 using its 5-10 m detection profile, then navigate to a safe goal within 2 m of the marker |
| `SEARCH_ARUCO_2` | Search for ArUco 2 using its 10-20 m detection profile, then navigate to a safe goal within 2 m of the marker |

Requests supply a `waypoint`; an omitted/default `search_mode` is
`SEARCH_NONE` (0), preserving ordinary A* navigation without search. A blank
search selection means NONE, not a blank waypoint or a string value. The
coordinator must reject unsupported modes before starting navigation; a rejected
ROS action goal has no result. Runtime enforcement is part of ROB-42.

Feedback reports the mission state, distance to the current navigation goal in
meters, and that navigation leg's replan count. A successful result uses
`SUCCESS`: NONE has no detection payload, YOLO returns `bounding_box`, and ArUco
returns `aruco_pose` after the approach succeeds. Read each payload only when its
`has_*` flag is true; pose frames and timestamps come from their headers.

Accepted missions return one terminal result. Failures use `INVALID_REQUEST`
for invalid request data found after acceptance, `NAVIGATION_FAILED` for initial
navigation failure, `SEARCH_FAILED` for search errors, `TARGET_NOT_FOUND` for a
search ending without a target, or `APPROACH_FAILED` for ArUco approach failure.
Cancellation uses `CANCELED`; `message` provides diagnostic detail.

The coordinator owns the mission action and retains its waypoint and search mode
for the action's entire lifetime. `NavigateToWaypoint` owns each individual
navigation leg and may call `GeneratePlan` repeatedly when it needs to replan.
Neither `NavigateToWaypoint` nor `GeneratePlan` interprets the mission search
mode.

An ArUco approach is a second internal `NavigateToWaypoint` goal within the
original mission. It does not create another mission or start another spiral
search.

The definitions under `msg/`, `srv/`, and `action/` are authoritative for field
types, constants, and result codes. Inspect an installed interface with:

```bash
ros2 interface show urc_msgs/action/NavigateToWaypoint
ros2 interface show urc_msgs/action/AstronautFollow
ros2 interface show urc_msgs/action/RecognizeFollowGesture
ros2 interface show urc_msgs/action/ExecuteAutonomousMission
ros2 interface show urc_msgs/msg/DetectionBoundingBox
```

Changes to these files affect every producer and consumer. Rebuild the workspace
and update all dependent packages when an interface changes.
