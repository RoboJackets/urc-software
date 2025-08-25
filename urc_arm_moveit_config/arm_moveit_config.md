# urc_arm_moveit_config

## Overview

The `urc_arm_moveit_config` package provides **MoveIt configuration and launch files** for controlling and simulating the Walli robotic arm.  
It integrates the arm model with MoveIt’s planning pipeline, visualization tools, and control interfaces, enabling motion planning, execution, and testing in both simulation and real hardware.

This package primarily wraps the standard `moveit_configs_utils` utilities to provide ready-to-use launch files for different MoveIt components.

This system includes the following modules:

1. **Move Group Interface**
   - Launches the main `move_group` node for planning and execution.
   - Provides interfaces for planners, controllers, and execution pipelines.

2. **Visualization & Setup Tools**
   - Includes RViz with MoveIt plugins for visualization.
   - Provides the MoveIt Setup Assistant for reconfiguring the arm model.
   - Enables static transforms for virtual joints.

---

## Features

- **Motion Planning**: Plan collision-free trajectories for the Walli arm.  
- **Move Group Integration**: Provides the central planning and execution node.  
- **Visualization**: RViz integration for interactive motion planning.  
- **Controller Management**: Spawn and manage controllers via launch files.  
- **Setup Assistant**: Configure and modify MoveIt settings for the Walli arm.  
- **Database Support**: Warehouse DB integration for storing planning scenes and states.  

---

## Package Structure
```
├── CMakeLists.txt
├── config
│   ├── initial_positions.yaml
│   ├── joint_limits.yaml
│   ├── kinematics.yaml
│   ├── moveit_controllers.yaml
│   ├── moveit.rviz
│   ├── pilz_cartesian_limits.yaml
│   ├── ros2_controllers.yaml
│   ├── walli.ros2_control.xacro
│   ├── walli.srdf
│   └── walli.urdf.xacro
├── launch
│   ├── demo.launch.py
│   ├── move_group.launch.py
│   ├── moveit_rviz.launch.py
│   ├── rsp.launch.py
│   ├── setup_assistant.launch.py
│   ├── spawn_controllers.launch.py
│   ├── static_virtual_joint_tfs.launch.py
│   └── warehouse_db.launch.py
└── package.xml
```


## Components

### Move Group Launch

- **File**: `move_group.launch.py`  
- **Description**: Starts the main MoveIt `move_group` node, which handles planning, execution, and the planning scene.  
- **Outputs**: Motion planning services, execution actions, and TF updates.  

### Controller Spawning

- **File**: `spawn_controllers.launch.py`  
- **Description**: Spawns controllers required to execute trajectories on the Walli arm.  
- **Inputs**: Controller configuration.  
- **Outputs**: Controller manager topics and services.  

### Demo Launch

- **File**: `demo_launch.py`  
- **Description**: Starts a MoveIt demo environment with the Walli arm.  
- **Outputs**: MoveIt demo node and RViz with planning capabilities.  

### RViz Visualization

- **File**: `moveit_rviz.launch.py`  
- **Description**: Launches RViz preconfigured with MoveIt’s planning and motion execution plugins.  

### Robot State Publisher

- **File**: `rsp.launch.py`  
- **Description**: Runs the robot state publisher with the Walli arm description for TF broadcasting.  

### Setup Assistant

- **File**: `setup_assistant.launch.py`  
- **Description**: Opens the MoveIt Setup Assistant, allowing reconfiguration of planning groups, controllers, and SRDF.  

### Static Virtual Joint TFs

- **File**: `static_virtual_joint_tfs.launch.py`  
- **Description**: Publishes static transforms for virtual joints (e.g., world ↔ base link).  

### Warehouse Database

- **File**: `warehouse_db.launch.py`  
- **Description**: Runs the MoveIt warehouse database (MongoDB) for saving and loading planning scenes and robot states.  

---
## Launch

Start MoveIt with the Walli arm:

```bash
ros2 launch urc_arm_moveit_config move_group.launch.py
```

Run a demo with RViz:
```bash
ros2 launch urc_arm_moveit_config demo_launch.py
```

Start the MoveIt Setup Assistant:
```bash
ros2 launch urc_arm_moveit_config setup_assistant.launch.py
```

Enable controllers:
```bash
ros2 launch urc_arm_moveit_config spawn_controllers.launch.py
```

Start Warehouse DB:
```bash
ros2 launch urc_arm_moveit_config warehouse_db.launch.py
```
