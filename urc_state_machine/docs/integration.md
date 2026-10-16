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
| Route | Camera image and camera info, ArUco detector, map-to-camera and map-to-rover TF, traversability data |
| Astronaut | `/astronaut/pose`, `/command`, map-to-rover TF, traversability data; simulated tool completion for an end-to-end test |

The action goal's initial waypoint must be in `map`. `/waypoint` is a separate
standalone GPS input with UTM conversion; it is not a mission action goal.

## ArUco observation

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
| `/command` | `urc_msgs/AstronautCommand` | Timestamp each new command; FOLLOW accepts GESTURE or REMOTE, all other commands require REMOTE |
| `/astronaut/pose` | `geometry_msgs/PoseStamped` | Track the selected astronaut consistently, with valid pose, frame, and capture timestamp |

REMOTE commands must originate from the astronaut's device. Operator intervention
is separate from normal astronaut commands; mission action cancellation is available.

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

The navigation client serializes cancel/replace requests and coalesces rapid target
updates. It never treats distance feedback or a cancellation result as goal success.
Direct waypoint topic requests are ignored during either mission.
