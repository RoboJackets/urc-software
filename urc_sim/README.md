# URC Sim

`urc_sim` contains simulation-only nodes that connect ROS 2 interfaces to Gazebo.
It is the only package that links against the Gazebo transport libraries
(Fortress: `ignition-transport11`, `ignition-msgs8`), so rover packages stay free
of simulator dependencies.

## Components

| Executable | Responsibility |
| --- | --- |
| `urc_sim_SimStatusLight` | Shows `/command/status_light` on the simulated rover's rear status light |

The executable is also registered as a composable ROS 2 component.

## SimStatusLight | Node

The URC autonomy rules require a rear status light: red for autonomous
operation, blue for teleoperation, and flashing green on arrival at a target.
On the rover, `urc_controllers/StatusLightController` drives the physical light
from the same topic.

### Subscriptions

- `/command/status_light` (`urc_msgs/msg/StatusLightCommand`)
  Color (`BLUE`, `GREEN`, `RED`) and state (`OFF`, `ON`, `BLINK`) to show.

### Gazebo services called

- `/world/<world_name>/visual_config` (`ignition.msgs.Visual`)
  Recolors `status_light_link_visual`, the light defined in
  `urc_hw_description`.

### Parameters

- `command_topic` (`string`) - Status light command topic.
- `world_name` (`string`) - Gazebo world name. Must match the loaded world:
  `leo_marsyard` for `marsyard2020.sdf`, `leo_empty` for `empty_world.sdf`.
- `link_name` (`string`) - Link that owns the status light visual.
- `visual_name` (`string`) - Status light visual to recolor.
- `refresh_period_ms` (`int`) - Blink half-period. The color is re-sent every
  period, so the light recovers if Gazebo starts after the node.

Defaults are in `config/sim_status_light.yaml`.

## Launch

`sim.launch.py` starts the node with the simulation:

```bash
ros2 launch urc_bringup sim.launch.py
```

To check the light, publish a command, for example flashing green:

```bash
ros2 topic pub --once /command/status_light urc_msgs/msg/StatusLightCommand "{color: 1, state: 2}"
```
