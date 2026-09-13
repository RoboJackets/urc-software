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

The xacro defines the rover links, rocker and swerve joints, sensor frames, and
`ros2_control` interfaces. With `use_sim:=true`, it selects
`gz_ros2_control/GazeboSimSystem`; otherwise it selects
`urc_hw/RoverDrivetrain`.

Joint names, frame names, limits, dimensions, and units are shared contracts
with controllers, localization, and launch files. Update those consumers with
any model change.

## Simulation Assets

- `world/` contains the empty and Mars Yard Gazebo worlds.
- `models/` contains the installed rover and terrain meshes.
- `rviz/display.rviz` is the default visualization configuration.
- Sensor xacros define the simulated lidar, IMU, and GPS.

Use `ros2 launch urc_bringup sim.launch.py` for the composed rover simulation.
