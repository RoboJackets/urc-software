# urc_bt

## Overview

The `urc_bt` package provides a **behavior tree orchestrator** for the rover’s autonomy system.  
It leverages [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP) and [behavior_tree_ros2](https://github.com/BehaviorTree/BehaviorTree.ROS2) to manage high-level decision-making.

This system enables runtime loading, reloading, and hot-swapping of behavior trees from configuration files or text, while exposing services to control execution.

This system includes the following modules:

### BehaviorTreeOrchestrator Node
- Central component that manages behavior tree lifecycle.  
- Handles plugin registration, tree initialization, and tick execution.  
- Exposes ROS 2 services to update, reload, start, and stop the tree.  

---

## Features
- **Dynamic Tree Loading**: Load trees from file (`.xml`) or text at runtime.  
- **Hot-Swapping**: Swap behavior trees without restarting the node.  
- **Plugin Registration**: Supports both normal and ROS-aware BT plugins.  
- **Execution Control**: Services to start, stop, and reload trees.  
- **Tick Rate Control**: Configurable tree ticking frequency.  

---
## Package Structure

```
├── CMakeLists.txt
├── include
│   └── urc_bt
│       └── bt_orchestrator.hpp
├── package.xml
├── README.md
└── src
    └── bt_orchestrator.cpp
```

---

## Components

### BehaviorTreeOrchestrator (`bt_orchestrator.hpp/cpp`)

**Description**  
Main ROS 2 node responsible for orchestrating behavior tree execution.

**Key Functionality**
- Loads plugins from provided directories.  
- Builds trees from file or string.  
- Manages ticking in a loop with user-defined frequency.  
- Provides services to update/reload/start/stop execution.  

---

### `bt_orchestrator` | Node

#### Services

- **`~/update_tree`** (`urc_msgs/srv/UpdateBehaviorTree`)  
  **Request:**  
  - `use_dir (bool)` – Load from file (`true`) or raw text (`false`).  
  - `tree_dir (string)` – Path to tree file (if `use_dir=true`).  
  - `tree_content (string)` – XML content of tree (if `use_dir=false`).  

  **Response:**  
  - `success (bool)` – Whether the new tree was successfully loaded.  

- **`~/reload`** (`std_srvs/srv/Trigger`)  
  Reloads the last behavior tree from its saved file path.  

- **`~/start_bt`** (`std_srvs/srv/Trigger`)  
  Starts ticking the behavior tree.  

- **`~/stop_bt`** (`std_srvs/srv/Trigger`)  
  Stops ticking the behavior tree.  

---

#### Parameters

- `normal_node_lib_dirs (list<string>)` – Paths to BT plugin libraries.  
- `ros_node_lib_dirs (list<string>)` – Paths to ROS-aware BT plugin libraries.  
- `tree_file_dir (string)` – Path to the initial behavior tree XML file.  
- `tick_rate (int)` – Frequency of ticking loop (Hz). **Default:** 100.  
- `start_bridge (bool)` – Whether to enable ROS bridge plugins. **Default:** `true`.  

