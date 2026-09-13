# ROS 2 Control Integration

The rover uses ROS 2 control to connect velocity commands to either Gazebo or
physical hardware. The URDF defines the available command and state interfaces;
controllers claim those interfaces through `controller_manager`.

## Simulation control path

```text
/cmd_vel (Twist)
  -> urc_controllers/SwerveDriveController
  -> wheel velocity and swivel position interfaces
  -> gz_ros2_control/GazeboSimSystem
  -> simulated rover
```

The swerve controller also publishes `/odom`. A joint-state broadcaster publishes
the model state, while the rocker effort controller and `RockerEffortPid` manage
the suspension effort loop.

Start the supported simulation configuration with:

```bash
ros2 launch urc_bringup sim.launch.py
```

The launch generates the rover description with `use_sim:=true`, starts Gazebo,
and loads these controllers from
[`urc_bringup/config/test_controllers.yaml`](../../urc_bringup/config/test_controllers.yaml):

- `joint_state_broadcaster`
- `swerve_controller`
- `rocker_effort_controller` by default

Inspect the running control system with:

```bash
ros2 control list_controllers
ros2 control list_hardware_interfaces
ros2 topic echo /odom
```

The swerve geometry parameters and controller types belong in the controller
YAML. Joint names, interface types, limits, and hardware selection belong in
[`simplified_swerve_ros2_control.xacro`](../../urc_hw_description/urdf/simplified_swerve/simplified_swerve_ros2_control.xacro).

## Simulation and physical hardware

The rover xacro selects its hardware backend through `use_sim`:

| Mode | Hardware plugin |
| --- | --- |
| `use_sim:=true` | `gz_ros2_control/GazeboSimSystem` |
| `use_sim:=false` | `urc_hw/RoverDrivetrain` |

Only the simulation path currently has a complete bringup launch. The physical
plugin communicates with firmware over UDP and requires verified addresses,
ports, and matching Nanopb firmware.

The current physical selection is not ready to activate unchanged: the swerve
xacro exposes per-corner wheel and swivel interfaces, while
`RoverDrivetrain` exports left/right wheel interfaces and requires UDP hardware
parameters that the xacro does not provide. Reconcile those contracts and add a
physical controller-manager launch before attempting hardware activation.

See the [`urc_controllers` guide](../../urc_controllers/README.md),
[`urc_hw` guide](../../urc_hw/README.md), and
[`urc_hw_description` guide](../../urc_hw_description/README.md) for package-level
contracts.
