# urc_platform

## Overview

The `urc_platform` package provides software nodes for interfacing with vehicle control and simulation systems. It includes joystick input handling, simulated GPS data processing, and twist command multiplexing for teleoperation.

This system includes the following modules:

1. **Joystick Driver**  
   - Interfaces with a joystick and converts input into velocity commands.  
   - Publishes `TwistStamped` messages for drivetrain control.

2. **Simulated GPS Handler**  
   - Processes GPS data in simulation.  
   - Adjusts covariance values and republishes GPS messages.

3. **Twist Multiplexer**  
   - Combines multiple velocity command inputs into a single output command.  
   - Ensures safe teleoperation by prioritizing sources.

---

## Features

- **Joystick Teleoperation**: Convert joystick input to linear and angular velocity commands.
- **Twist Multiplexing**: Switch between autonomous and teleop control safely.
- **Simulated GPS Handling**: Provides reliable GPS messages for simulation or testing.
- **Parameter Configurable**: Velocity limits, axis selection, topic names, and inversion can be adjusted via launch files or YAML.

---

## Package Structure

```bash
├── CMakeLists.txt
├── config
│   └── twist_mux.yaml
├── include
│   ├── joystick_driver.hpp
│   ├── preprocessing.hpp
│   ├── sim_gps_handler.hpp
│   └── twist_mux.hpp
├── launch
│   ├── joy_drive.launch.py
│   ├── joystick.launch.py
│   └── src.code-workspace
├── package.xml
├── README.md
├── src
│   ├── joystick_driver.cpp
│   ├── sim_gps_handler.cpp
│   └── twist_mux.cpp
└── test
    ├── CMakeLists.txt
    └── launch_tests
        ├── CMakeLists.txt
        ├── joystick_driver_test.py
        └── motor_controller_test.py
```

## Components

### Joystick Driver

**Files:** `joystick_driver.hpp` / `joystick_driver.cpp`

- Converts joystick input to `geometry_msgs::msg::TwistStamped`.
- Scales linear and angular velocities according to parameters.
- Supports axis inversion and custom mapping.
- Publishes commands to `/cmd_vel_teleop` by default.

### Simulated GPS Handler

**Files:** `sim_gps_handler.hpp` / `sim_gps_handler.cpp`

- Receives raw GPS data (`sensor_msgs::msg::NavSatFix`).
- Updates covariance to minimal values for simulation/testing.
- Republishes messages to a configurable output topic.

### Twist Multiplexer

**Files:** `twist_mux.hpp` / `twist_mux.cpp`

- Subscribes to multiple `TwistStamped` sources (autonomous and teleop).
- Publishes selected command based on mode and enabled topics.
- Ensures safe operation by zeroing commands when disabled.

### Preprocessing

**Files:** `preprocessing.hpp`

- Helper functions for scaling, clamping, and inverting joystick input values.

---

## Nodes

### JoystickDriver | Node

**Subscriptions:**

- `/driver/joy` (`sensor_msgs/msg/Joy`) — joystick input.

**Publishers:**

- `/cmd_vel_teleop` (`geometry_msgs/msg/TwistStamped`) — teleop velocity commands.

**Parameters:**

- `max_linear_velocity` (double) – Maximum linear speed.
- `max_angular_velocity` (double) – Maximum angular speed.
- `driver_velocity_x_axis` (int) – Joystick axis for linear velocity.
- `driver_velocity_z_axis` (int) – Joystick axis for angular velocity.
- `driver_left_invert` (bool) – Invert linear axis.
- `driver_right_invert` (bool) – Invert angular axis.
- `drivetrain_topic` (string) – Output topic for velocity commands.

### SimGpsHandler | Node

**Subscriptions:**

- `/gps/data_raw` (`sensor_msgs/msg/NavSatFix`) — raw GPS messages.

**Publishers:**

- `/gps/data` (`sensor_msgs/msg/NavSatFix`) — processed GPS messages.

### TwistMux | Node

**Subscriptions:**

- `/cmd_vel_autonomous` (`geometry_msgs/msg/TwistStamped`) — autonomous commands.
- `/cmd_vel_teleop` (`geometry_msgs/msg/TwistStamped`) — teleop commands.
- `/cmd_vel_enabled` (`std_msgs/msg/Bool`) — enable/disable control.
- `/cmd_vel_mode` (`std_msgs/msg/String`) — selects autonomous or teleop.

**Publishers:**

- `/rover_drivetrain_controller/cmd_vel` (`geometry_msgs/msg/TwistStamped`) — selected velocity commands.

---

## Launching the Package

Start Joystick Teleop

```bash
ros2 launch urc_platform joystick.launch.py
```


Start JoyDrtive Node

```bash
ros2 launch urc_platform joy_drive.launch.py
```

