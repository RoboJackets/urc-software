# URC Hardware Interfaces

`urc_hw` connects `ros2_control` to rover hardware over UDP using nanopb
messages. These plugins are loaded through a robot's `<ros2_control>`
description rather than launched as standalone nodes.

## Plugins

| Plugin | Type | Hardware contract |
| --- | --- | --- |
| `urc_hw/RoverDrivetrain` | System | Sends left and right wheel velocity commands and receives wheel-speed feedback |
| `urc_hw/StatusLight` | System | Exposes `color` and `state` command interfaces for the rover status light |
| `urc_hw/BatteryManagement` | Sensor | Receives battery telemetry and exposes voltage, charge, current, and temperature state interfaces |

Only plugins listed in `urc_hw.xml` are exported for runtime use. The current
physical-rover xacro selects `urc_hw/RoverDrivetrain`; simulation uses
`gz_ros2_control/GazeboSimSystem` instead.

## Configuration

Hardware parameters belong in the `<hardware>` section of the robot
description:

- `RoverDrivetrain` requires `udp_address`, `udp_self_address`, and `udp_port`.
- `StatusLight` requires `udp_address` and `udp_port`.
- `BatteryManagement` requires `udp_self_address` and `udp_self_port`.

The active drivetrain integration is defined in
`urc_hw_description/urdf/simplified_swerve/simplified_swerve_ros2_control.xacro`.
Its command and state interfaces must match the controllers loaded by
`controller_manager`.

Do not activate these plugins against physical hardware until the target
address, port, firmware protocol, and controller limits have been verified.
