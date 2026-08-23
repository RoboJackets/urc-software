# URC Interfaces

`urc_msgs` defines the custom ROS 2 interfaces shared across rover packages. It
contains no runtime nodes.

## Messages

| Interface | Purpose |
| --- | --- |
| `BatteryInfo` | Battery voltage, charge, current, temperature, and per-cell telemetry |
| `GridLocation` | Unsigned grid-cell coordinates |
| `OrientationPoses` | Header and named pose collection |
| `RoverPoses` | Header and named rover-pose collection |
| `StatusLightCommand` | Status-light color and off/on/blink state |
| `Waypoint` | Latitude and longitude for a navigation target |

## Service and Action

| Interface | Purpose |
| --- | --- |
| `GeneratePlan` service | Requests a path between start and goal poses and returns a `nav_msgs/Path` with a success or failure code |
| `NavigateToWaypoint` action | Follows a supplied path or plans to a goal, with optional final-heading enforcement and progress feedback |

The definitions under `msg/`, `srv/`, and `action/` are authoritative for field
types, constants, and result codes. Inspect an installed interface with:

```bash
ros2 interface show urc_msgs/action/NavigateToWaypoint
```

Changes to these files affect every producer and consumer. Rebuild the workspace
and update all dependent packages when an interface changes.
