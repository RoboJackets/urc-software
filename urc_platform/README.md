# URC Platform

`urc_platform` provides the rover's input and platform-adapter nodes. Its ROS 2
components translate joystick, velocity, GPS, and IMU data and publish the
software heartbeat.

## Components

| Executable | Responsibility |
| --- | --- |
| `urc_platform_JoystickDriver` | Converts `sensor_msgs/msg/Joy` input to scaled `TwistStamped` teleoperation commands |
| `urc_platform_TwistMux` | Selects teleoperation or autonomous `TwistStamped` commands and forwards them to the drivetrain controller |
| `urc_platform_SimGpsHandler` | Republishes simulated GPS fixes with position covariance |
| `urc_platform_ImuNED2ENU` | Converts IMU orientation, angular velocity, and acceleration from NED to ENU coordinates |
| `urc_platform_HeartbeatPublisher` | Publishes timestamped heartbeat messages at a configured interval |

All five executables are also registered as composable ROS 2 components.

## Usage

The base-station launch starts the joystick driver together with the ROS joystick
node:

```bash
ros2 launch urc_bringup base_station.launch.py
```

Components can also be run individually, for example:

```bash
ros2 run urc_platform urc_platform_JoystickDriver
```

This package does not install its own launch files. System composition belongs in
`urc_bringup`.

## Operational contracts

- Joystick axes, velocity limits, and input/output topics are parameters.
- `TwistMux` starts enabled in teleoperation mode. Disabling it publishes one
  zero-velocity command; mode values must be `teleop` or `autonomous`.
- `HeartbeatPublisher` requires `heartbeatInterval` in milliseconds.
- Topic defaults are defined by each component. Use `ros2 param describe` for
  the complete parameter interface.

The `config/` directory contains controller, upstream twist-mux, and VectorNav
settings. Higher-level system compositions load the relevant configuration.
