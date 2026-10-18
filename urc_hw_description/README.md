# URC Hardware Description

`urc_hw_description` owns the rover model and its visualization and simulation
assets. The primary model is the simplified swerve-drive xacro at
`urdf/simplified_swerve/simplified_swerve.urdf.xacro`.

## Visualizing the Rover

After building and sourcing the workspace, open the model with the joint-state
GUI and RViz:

```bash
ros2 launch urc_hw_description display.launch.py
```

The launch file accepts `urdf_file`, `use_sim`, and `rviz_config_file`
overrides. Use `ros2 launch urc_hw_description display.launch.py --show-args`
for their current defaults.

## Model Contracts

The xacro defines the rover links, rocker and swerve joints, sensor frames, the
rear status light link (`status_light_link`), and `ros2_control` interfaces.
With `use_sim:=true`, it selects `gz_ros2_control/GazeboSimSystem`; otherwise
it selects `urc_hw/RoverDrivetrain`.

Joint names, frame names, limits, dimensions, and units are shared contracts
with controllers, localization, and launch files. Update those consumers with
any model change.

## Simulation Assets

- `world/` contains the empty and Mars Yard Gazebo worlds.
- `models/` contains the installed rover and terrain meshes.
- `rviz/display.rviz` is the default visualization configuration.
- Sensor xacros define the simulated lidar, IMU, and GPS.
- `urdf/simplified_swerve/simplified_swerve_status_light.xacro` defines the
  rear status light; the `SimStatusLight` node sets its color in simulation.

Use `ros2 launch urc_bringup sim.launch.py` for the composed rover simulation.

## SimStatusLight | Node

Executable: `urc_hw_description_SimStatusLight`, also registered as a
composable ROS 2 component. `sim.launch.py` starts it with the simulation.

The URC autonomy rules require a rear status light: red for autonomous
operation, blue for teleoperation, and flashing green on arrival at a target.
On the rover, `urc_controllers/StatusLightController` drives the physical light
from the same topic.

### Subscriptions

- `/command/status_light` (`urc_msgs/msg/StatusLightCommand`)
  Color (`BLUE`, `GREEN`, `RED`) and state (`OFF`, `ON`, `BLINK`) to show.

### Gazebo services called

- `/world/<world_name>/visual_config` (`ignition.msgs.Visual`)
  Recolors `status_light_link_visual`.

### Parameters

- `command_topic` (`string`) - Status light command topic.
- `world_name` (`string`) - Gazebo world name. Must match the loaded world:
  `leo_marsyard` for `marsyard2020.sdf`, `leo_empty` for `empty_world.sdf`.
- `link_name` (`string`) - Link that owns the status light visual.
- `visual_name` (`string`) - Status light visual to recolor.
- `refresh_period_ms` (`int`) - Blink half-period. The color is re-sent every
  period, so the light recovers if Gazebo starts after the node.

Defaults are in `config/sim_status_light.yaml`. To check the light while the
simulation runs, publish a command, for example flashing green:

```bash
ros2 topic pub --once /command/status_light urc_msgs/msg/StatusLightCommand "{color: 1, state: 2}"
```
