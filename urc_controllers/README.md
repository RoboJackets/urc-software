# URC Controllers

`urc_controllers` provides rover-specific `ros2_control` plugins and standalone
nodes for the rocker suspension.

## Components

| Component | Type | Public behavior |
| --- | --- | --- |
| `urc_controllers/SwerveDriveController` | Controller plugin | Converts `/cmd_vel` (`Twist`) into wheel velocity and swivel position commands; publishes `/odom` |
| `urc_controllers/BMSBroadcaster` | Controller plugin | Reads battery hardware state interfaces and publishes `state_battery` (`BatteryInfo`) |
| `urc_controllers/StatusLightController` | Controller plugin | Converts `/command/status_light` into status-light hardware commands |
| `RockerTfBroadcaster` | ROS component | Averages the rocker joint positions and publishes `/rocker/pitch_raw` |
| `RockerEffortPid` | ROS component | Converts rocker pitch error into paired effort commands |

The controller plugins are loaded by `controller_manager`; they are not run as
standalone executables. Their plugin names are defined in
`urc_controllers.xml`.

## Configuration

- `urc_platform/config/controller_config.yaml` configures the hardware BMS and
  status-light controllers.
- `urc_bringup/config/test_controllers.yaml` configures the simulated swerve and
  rocker-effort controllers.
- The swerve controller requires `module_x`, `module_y`, and `wheel_radius`, plus
  velocity and position interfaces for the `FL`, `FR`, `BL`, and `BR` modules.

Start the standalone rocker PID through bringup:

```bash
ros2 launch urc_bringup rocker_effort_pid.launch.py
```

Its gains, pitch target, integral clamp, minimum effort, and output effort limit
are ROS parameters. The effort limit is the final saturation applied to both
rocker commands.
