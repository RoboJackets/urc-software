# urc_orchestrator

## Overview

The `urc_orchestrator` package provides the rover’s navigation orchestration layer, integrating GPS, IMU, and waypoint commands to manage rover localization, navigation state, and velocity control.

This node is responsible for:

- Converting raw GPS offsets into metric and costmap poses.
- Tracking rover heading using IMU orientation.
- Managing navigation states (e.g., `NoGPS`, `NoWaypoint`, `Navigating`, `Goal`).
- Publishing velocity commands for basic waypoint following using a **pure pursuit** controller.

### 1. Pose Offset Publishing
- Computes rover offsets relative to the base GPS position.  
- Publishes **metric poses** and **costmap poses** for use in navigation.  

### 2. Navigation State Management
- Determines the current navigation state (`NoGPS`, `NoWaypoint`, `Navigating`, `Goal`).  
- Publishes state updates for external monitoring.  

### 3. Pure Pursuit Controller
- Computes velocity commands based on rover heading and waypoint offsets.  
- Supports basic orientation correction and forward motion.  

---

## Features

- **GPS Integration**: Converts latitude/longitude into metric offsets.  
- **IMU Tracking**: Uses yaw from IMU to track rover heading.  
- **Navigation State Machine**: Determines navigation mode based on GPS and waypoint availability.  
- **Pure Pursuit Control**: Publishes velocity commands (`cmd_vel`) for autonomous waypoint following.  

---

## Package Structure

```
├── CMakeLists.txt
├── include
│   └── orchestrator.hpp
├── launch
│   └── navigation.launch.py
├── package.xml
└── src
    └── orchestrator.cpp
```

### Components

#### Orchestrator (`orchestrator.hpp` / `orchestrator.cpp`)
- Core node handling navigation orchestration.  
- Subscribes to GPS, IMU, base reset, and waypoint topics.  
- Publishes metric and costmap poses, navigation status, and velocity commands.  
- Implements pure pursuit waypoint tracking.  

---

## Node: `orchestrator`

### Subscriptions
- **`/imu/data`** (`sensor_msgs/msg/Imu`)  
  IMU orientation data for yaw estimation.  

- **`/fix`** (`sensor_msgs/msg/NavSatFix`)  
  GPS fix providing rover latitude and longitude.  

- **`/waypoint`** (`urc_msgs/msg/Waypoint`)  
  Waypoint command with target latitude and longitude.  

- **`/set_base`** (`std_msgs/msg/Bool`)  
  Signal to reset the GPS base reference.  

---

### Publishers
- **`/current_navigation_state`** (`urc_msgs/msg/NavigationStatus`)  
  Publishes the current navigation state (`NoGPS`, `NoWaypoint`, `Navigating`, `Goal`).  

- **`/rover_drivetrain_controller/cmd_vel`** (`geometry_msgs/msg/TwistStamped`)  
  Velocity command for drivetrain control.  

- **`/pose/metric`** (`geometry_msgs/msg/Pose`)  
  Rover’s metric pose offset relative to base.  

- **`/pose/costmap`** (`geometry_msgs/msg/Pose`)  
  Rover’s costmap pose for planning and mapping.  

---

## Parameters
- **`purePursuitEnabled`** (`bool`) – Enables/disables pure pursuit controller.  
- **`maxDelta`** (`double`) – Maximum allowed offset delta (used in pursuit control).  


## Launch

Start the Orchestrator node with:

```bash
ros2 launch urc_orchestrator navigation.launch.py
```
