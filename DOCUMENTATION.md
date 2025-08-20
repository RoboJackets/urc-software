# RoboNav Package Documentation

Welcome to the centralized documentation for the **RoboNav software stack**. This directory contains detailed documentation for each package in the system to aid development, onboarding, and debugging.

## Installation

Full Installation Instructions  [URC Software README](../README.md).

## Package Documentation

### Core System & Utilities
- [README.md](README.md) – You’re currently reading this overview file.  
- [bringup.md](bringup.md) – Universal launch files and system bringup instructions.  
- [orchestrator.md](orchestrator.md) – System orchestration node managing overall robot behavior.  
- [msgs.md](msgs.md) – Custom ROS2 messages shared across packages.  
- [nanopb.md](nanopb.md) – NanoPB protocol buffers configuration and usage.  
- [util.md](util.md) – Utility scripts and helper nodes for development and deployment.  

### Hardware & Simulation
- [hw.md](hw.md) – ROS2 control hardware interface implementation.  
- [hw_description.md](hw_description.md) – URDF and hardware description files for the rover.  
- [controllers.md](controllers.md) – ROS2 control controllers for hardware interfaces.  
- [platform.md](platform.md) – Platform-specific hardware communication nodes.  
- [gazebo.md](gazebo.md) – Simulation configuration and Gazebo integration.  

### Robotic Arm Control
- [arm.md](arm.md) – Nodes for controlling the robotic arm.  
- [arm_moveit_config.md](arm_moveit_config.md) – MoveIt configuration package for arm planning and control.  
- [walli_arm.md](walli_arm.md) – Walli-specific robotic arm MoveIt configuration.  

### Autonomy & Perception
- [bt.md](bt.md) – Behavior tree core package for task execution.  
- [bt_nodes.md](bt_nodes.md) – Custom behavior tree nodes for autonomy.  
- [navigation.md](navigation.md) – Navigation stack, including Nav2 configuration and nodes.  
- [perception.md](perception.md) – Perception stack, including computer vision and detection nodes.  

---

## How to Use These Documents

Each markdown file follows a standardized structure to provide comprehensive information about the package:

1. **Overview**  
   A high-level description of the package, its purpose, and the system modules it includes.

2. **Features**  
   Key functionalities and capabilities of the package.

3. **Package Structure**  
   Details of the folder and file organization within the package.

4. **Components**  
   Descriptions of modules and their components, including inputs, outputs, and key functionality.

5. **Nodes**  
   Information about ROS 2 nodes (if applicable), including:
   - Subscriptions  
   - Publishers  
   - Services  
   - Actions  
   - Parameters  

6. **Launch Instructions**  
   How to start nodes or modules using ROS 2 launch files.

---

## Helpful Links

- [URC Software Repository](https://github.com/RoboJackets/urc-software)
- [ROS2 Documentation](https://docs.ros.org/en/humble/index.html)
- [MoveIt2 Documentation](https://moveit.picknik.ai/main/index.html)
- [Nav2 Documentation](https://navigation.ros.org/)

_Last updated: 2025-08-19_

