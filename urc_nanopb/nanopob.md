# urc_nanopb

## Overview

The `urc_nanopb` package provides **Protocol Buffers (Nanopb) message definitions** for rover communication between ROS 2 nodes and microcontrollers.

This system includes the following modules:

1. **Arm & Drivetrain Messages**  
   - Defines encoder, setpoint, and feedback messages for rover arms and drivetrain.  
   - Supports structured, serialized communication with microcontrollers.  

2. **Sensor & Status Messages**  
   - Encodes IMU, battery, and status light messages.  
   - Facilitates efficient monitoring and control of rover subsystems.  

---

## Features

- **Nanopb Serialization**: Lightweight C structs for microcontroller-friendly messaging.  
- **Cross-Module Communication**: Standardized messages for drivetrain, arm, sensors, and lights.  
- **Timestamped Data**: Most messages include timestamps for synchronization.  
- **Flexible Message Types**: Supports optional and required fields, as well as `oneof` payloads for multiplexed messages.  

---

## Package Structure

```
├── CMakeLists.txt
├── package.xml
├── proto
│   └── urc.proto
└── README.md
```

---

## Components

### Arm & Drivetrain Messages

- **ArmEncodersMessage (`urc.proto`)**  
  Reports encoder ticks for shoulder, elbow, and wrist joints.  
  **Inputs:** Hardware encoders  
  **Outputs:** Serialized Nanopb message  

- **DriveEncodersMessage (`urc.proto`)**  
  Reports left/right drivetrain speeds and timestamp.  
  **Inputs:** Motor controllers  
  **Outputs:** Serialized Nanopb message  

- **DrivetrainRequest / DrivetrainResponse (`urc.proto`)**  
  Send motor setpoints and receive speed, current, and position feedback.  
  **Inputs:** Desired motor commands  
  **Outputs:** Feedback from motors  

- **ArmClawRequest / ArmEffortRequest / ArmPositionFeedback (`urc.proto`)**  
  Send effort or claw velocity commands and receive joint position feedback.  

### Sensor & Status Messages

- **IMUMessage (`urc.proto`)**  
  Provides orientation (quaternion), linear acceleration, and angular velocity.  
  Used for rover heading and motion tracking.  

- **BatteryMessage (`urc.proto`)**  
  Reports main voltage, individual cell voltages, charge percentage, and discharge current.  

- **StatusLightMessage / NewStatusLightCommand (`urc.proto`)**  
  Control RGB LEDs on the rover with optional blinking.  

- **SetpointMessage (`urc.proto`)**  
  Drive setpoints for left and right wheels; alternative to full drivetrain messages.  

- **ScienceModuleCommand / ScienceMotorRequest (`urc.proto`)**  
  Commands to rotate turntables, move leadscrews, or drill.  

- **TeensyMessage (`urc.proto`)**  
  Multiplexed message type combining setpoints and status light commands using `oneof`.  

### Nodes

This package does not include runtime ROS 2 nodes.  
It is a message definition library. Nodes using this package will include the generated `.h` and `.c` files for communication with microcontrollers.  
