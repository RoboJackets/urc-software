# urc_arm

## Overview

The `urc_arm` package provides control, command, and feedback interfaces for the rover’s robotic arm.  
It handles motion control, claw manipulation, and sensor feedback for precise arm operations.

This system includes the following modules:

1. **Arm Control**  
   - Handles joint commands and claw operations.  
   - Key features: Effort control, claw actuation, and motion setpoints.  

2. **Arm Feedback**  
   - Publishes encoder and position feedback from arm joints.  
   - Key features: Encoder ticks, joint state feedback, and synchronization with drivetrain.  

---

## Features

- **Effort Control**: Send torque/effort commands to arm joints.  
- **Claw Manipulation**: Open/close or set claw velocity for grasping.  
- **Position Feedback**: Access encoder ticks and joint positions.  
- **Integration**: Works alongside drivetrain and science modules for mission tasks.  

---

## Package Structure
```
├── CMakeLists.txt
├── include
│   └── urc_arm
│       └── arm_rt.hpp
├── model
│   └── meshes
│       ├── collision
│       │   ├── base_link_collision.STL
│       │   ├── bicep_collision.STL
│       │   ├── claw_collision.STL
│       │   ├── elbow_collision.STL
│       │   ├── finger.obj
│       │   ├── hand.obj
│       │   ├── leftbogie_collision.STL
│       │   ├── left_center_wheel_collision.STL
│       │   ├── left_front_wheel_collision.STL
│       │   ├── leftgripper_collision.STL
│       │   ├── left_rear_wheel_collision.STL
│       │   ├── leftrocker_collision.STL
│       │   ├── link0.obj
│       │   ├── link1.obj
│       │   ├── link2.obj
│       │   ├── link3.obj
│       │   ├── link4.obj
│       │   ├── link5.obj
│       │   ├── link6.mtl
│       │   ├── link6.obj
│       │   ├── link7.obj
│       │   ├── rightbogie_collision.STL
│       │   ├── right_center_wheel_collision.STL
│       │   ├── right_front_wheel_collision.STL
│       │   ├── rightgripper_collision.STL
│       │   ├── right_rear_wheel_collision.STL
│       │   ├── rightrocker_collision.STL
│       │   ├── shoulder_collision.STL
│       │   ├── spine_collision.STL
│       │   └── wrist_collision.STL
│       ├── old
│       │   ├── base_link_collision.STL
│       │   ├── base_link.STL
│       │   ├── bicep_collision.STL
│       │   ├── bicep.STL
│       │   ├── claw_collision.STL
│       │   ├── claw.STL
│       │   ├── elbow_collision.STL
│       │   ├── elbow.STL
│       │   ├── forearm_collision.STL
│       │   ├── forearm.STL
│       │   ├── leftgripper_collision.STL
│       │   ├── leftgripper.STL
│       │   ├── rightgripper_collision.STL
│       │   ├── rightgripper.STL
│       │   ├── shoulder_collision.STL
│       │   ├── shoulder.STL
│       │   ├── wrist_collision.STL
│       │   └── wrist.STL
│       ├── visual
│       │   ├── base_link.STL
│       │   ├── bicep.STL
│       │   ├── claw.STL
│       │   ├── colors.png
│       │   ├── elbow.STL
│       │   ├── finger.mtl
│       │   ├── finger.obj
│       │   ├── hand.mtl
│       │   ├── hand.obj
│       │   ├── leftbogie.STL
│       │   ├── left_center_wheel.STL
│       │   ├── left_front_wheel.STL
│       │   ├── leftgripper.STL
│       │   ├── left_rear_wheel.STL
│       │   ├── leftrocker.STL
│       │   ├── link1.mtl
│       │   ├── link1.obj
│       │   ├── link2.mtl
│       │   ├── link2.obj
│       │   ├── link3.mtl
│       │   ├── link3.obj
│       │   ├── link4.mtl
│       │   ├── link4.obj
│       │   ├── link5.mtl
│       │   ├── link5.obj
│       │   ├── link6.mtl
│       │   ├── link6.obj
│       │   ├── rightbogie.STL
│       │   ├── right_center_wheel.STL
│       │   ├── right_front_wheel.STL
│       │   ├── rightgripper.STL
│       │   ├── right_rear_wheel.STL
│       │   ├── rightrocker.STL
│       │   ├── shoulder.STL
│       │   ├── spine.STL
│       │   ├── visualShapeBench.json_0.json
│       │   └── wrist.STL
│       └── walli_arm.urdf
├── package.xml
├── scripts
│   └── test_arm.ipynb
├── src
│   └── arm_rt.cpp
└── urc_arm
    └── __init__.py
```
---

## Components

### Arm Control

- **arm_controller (`.hpp/cpp`)**  
  - Sends control commands to the robotic arm joints and claw.  
  - **Inputs**: Command messages (effort, velocity, claw requests).  
  - **Outputs**: Forwarded motor commands for execution.  

### Arm Feedback

- **arm_feedback (`.hpp/cpp`)**  
  - Collects encoder ticks and joint positions.  
  - **Inputs**: Hardware encoder data.  
  - **Outputs**: ROS 2 messages with joint feedback.  

---

## arm_rt_pinocchio | Node

### Subscriptions
- `/urc/arm/effort_request` (`urc_proto/ArmEffortRequest`)  
  Receives effort commands for arm joints.  

- `/urc/arm/claw_request` (`urc_proto/ArmClawRequest`)  
  Receives claw velocity or open/close commands.  

### Publishers
- `/urc/arm/encoders` (`urc_proto/ArmEncodersMessage`)  
  Publishes encoder ticks for shoulder, elbow, and wrist joints.  

- `/urc/arm/position_feedback` (`urc_proto/ArmPositionFeedback`)  
  Publishes joint position feedback for closed-loop control.  


### Parameters
- `arm_joint_limits` (`list[float]`) – Defines joint angle/effort limits.  
- `update_rate` (`double`) – Frequency of arm feedback publishing.  

---

## Launch

Start the arm control node with:

```bash
ros2 launch urc_arm arm_control.launch.py
```
