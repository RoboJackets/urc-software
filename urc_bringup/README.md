# URC Bringup

`urc_bringup` composes rover subsystems into launchable ROS 2 configurations.
The nodes it starts are implemented and configured by their owning packages.

## Launching

| Command | Purpose |
| --- | --- |
| `ros2 launch urc_bringup sim.launch.py` | Rover simulation with localization and controllers |
| `ros2 launch urc_bringup autonomy.launch.py` | Planning, trajectory following, navigation coordination, and traversability mapping |
| `ros2 launch urc_bringup base_station.launch.py` | Joystick control and base-station GNSS |
| `ros2 launch urc_bringup rocker_effort_pid.launch.py` | Standalone rocker effort PID |

There is currently no single launch file for complete physical-rover bringup.
The base-station launch requires `ublox_dgnss` and the configured receiver.

## Simulation

The default simulation uses `marsyard2020.sdf`. Enable the autonomous navigation
stack when needed:

```bash
ros2 launch urc_bringup sim.launch.py autonomy:=true
```

The simulation activates the rocker effort controller, publishes mean rocker
angle from joint states, and starts the effort PID after its controller activates.
Set `spawn_rocker_effort_controller:=false` to disable the complete rocker loop.
Simulation gains and topics are in `config/rocker_control.yaml`.

Use `ros2 launch urc_bringup sim.launch.py --show-args` for the complete set of
world, robot, controller, and simulation options.

## Configuration

- `config/sim_config.yaml` defines the Gazebo-to-ROS bridges for clock, laser,
  IMU, GPS, point-cloud, and ground-truth data.
- `config/test_controllers.yaml` configures the controllers loaded by the
  simulation.
