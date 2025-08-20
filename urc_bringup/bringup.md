# urc_bringup
## Overview

The `urc_bringup` package provides core bringup functionality for the URC robotics platform, including hardware initialization, robot state publishing, telemetry, and teleoperation integration.

This system includes the following modules:

### Heartbeat Publisher

- Publishes periodic heartbeat messages to indicate system liveliness.  
- Outputs a `std_msgs/msg/Header` message with a timestamp on the `/heartbeat` topic.

### Robot Bringup

- Initializes the robot hardware, controller manager, and sensor interfaces.  
- Launches drivers for GPS, IMU, and other onboard sensors.

### Teleoperation

- Integrates joystick input for manual robot control.  
- Remaps topics and parameters for controlling drivetrain and actuators.

### Behavior Tree Orchestration

- Runs high-level behavior nodes for autonomous operations.  
- Uses XML-based behavior tree definitions to load node libraries and execute strategies.

---

## Features

- **Heartbeat Monitoring**: Continuously publishes system heartbeat messages.  
- **Robot Initialization**: Sets up controllers, robot state publisher, and hardware interfaces.  
- **Sensor Integration**: Supports GPS, IMU, and other sensors for localization and navigation.  
- **Teleoperation**: Joystick-based control with configurable parameters.  
- **Behavior Execution**: Runs behavior trees for autonomous mission planning.  
- **ROS 2 Launch Support**: Multiple launch files for base station, bringup, teleop, and testing scenarios.


## Package Structure

```
├── CMakeLists.txt
├── config
│   ├── controller_config.yaml
│   ├── heartbeat_publisher.yaml
│   ├── nmea_serial_driver.yaml
│   ├── ros2_control_leo.yaml
│   ├── ros2_control_simple.yaml
│   ├── ros2_control_walli.yaml
│   ├── servo_config.yaml
│   └── vectornav_imu.yaml
├── include
│   └── heartbeat_publisher.hpp
├── launch
│   ├── base_station.launch.py
│   ├── bringup.launch.py
│   ├── bringup_simulation.launch.py
│   ├── bt.launch.py
│   ├── heartbeat_publisher.launch.py
│   ├── teleop.launch.py
│   └── test_status_light.launch.py
├── package.xml
├── rviz
│   └── urdf_config.rviz
├── src
│   └── heartbeat_publisher.cpp
└── strategies
    ├── bt_test.xml
    ├── status_light.xml
    ├── test_strategy.xml
    └── urc_strategies.btproj
```
## Components

### Heartbeat Publisher

- **HeartbeatPublisher (`heartbeat_publisher.hpp/cpp`)**
  - Publishes heartbeat messages on a configurable interval.  
  - **Inputs**: None  
  - **Outputs**: `/heartbeat` (`std_msgs/msg/Header`)  

### Robot Bringup

- **bringup.launch.py**
  - Launches the complete robot bringup sequence including controllers, sensors, and state publishers.  
  - **Outputs**: Initialized hardware and active ROS 2 nodes for telemetry and control.  

### Teleoperation

- **teleop.launch.py**
  - Launches joystick driver nodes and remaps topics for teleoperation control.  
  - **Inputs**: Joystick hardware messages on `/driver/joy`  
  - **Outputs**: Twist commands on `/cmd_vel`  

### Behavior Tree Orchestration

- **bt.launch.py**
  - Launches behavior tree orchestrator node with specified node libraries and strategy XML file.  
  - **Outputs**: Autonomous behavior execution through ROS 2 action nodes.  

---

## HeartbeatPublisher | Node

### Publishers

- `/heartbeat` (`std_msgs/msg/Header`)  
  Publishes a timestamped message at a configurable interval to indicate system is alive.  


### Parameters

- `heartbeatInterval` (`int`) – Interval in milliseconds between heartbeat messages.

## Launch

Start the Heartbeat Publisher with:
```bash
ros2 launch urc_bringup heartbeat_publisher.launch.py
```

Start the full robot bringup with:
```bash
ros2 launch urc_bringup bringup.launch.py
```

Start the base station setup with:
```bash
ros2 launch urc_bringup base_station.launch.py
```

Start teleoperation nodes with:
```bash
ros2 launch urc_bringup teleop.launch.py
```

Start the behavior tree orchestrator with:
```bash
ros2 launch urc_bringup bt.launch.py
```

Start the status light test with:
```bash
ros2 launch urc_bringup test_status_light.launch.py
```
