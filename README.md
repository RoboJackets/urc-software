# urc-software [![CI Status Badge](https://github.com/RoboJackets/urc-software/actions/workflows/ci.yml/badge.svg)](https://github.com/RoboJackets/urc-software/actions)

Welcome to the RoboJackets/RoboNav software repo for the [University Rover Challenge](https://urc.marssociety.org/) (URC)! This document will give you a brief description of the repo's layout and an overview of the repo.

[![Software Lead](https://img.shields.io/badge/Software%20Lead-David%20Calderon-green?color=EEB211&logo=data:image/png;base64,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)](https://github.com/a-stickan)

## Directory Structure

- **.github**
  _CI pipeline and PR/issue templates_
- **cmake**
  _CMake files to aid with building_
- **documents**
  _Research, design, and documentation_
- **external**
  _Where all our submodules are located_
- **urc_analysis**
  _Nodes used for scientific analysis_
- **urc_arm_moveit_config**
  _Moveit config folder for rover arm_
- **urc_bringup**
  _Location of the universal launch file + heartbeat node_
- **urc_control** *deprecated*
  _Controller manager node and controllers bring up_
- **urc_controllers**
  _ros2-control controllers_
- **urc_gazebo**
  _Helper nodes used for simulation purposes_
- **urc_hw**
  _ros2-control hardware interface_
- **urc_hw_description**
  _URDF description for the rover_
- **urc_manipulation**
  _Collection of nodes used for the robotic arm_
- **urc_nanopb**
  _nanopb related files and settings_
- **urc_msgs**
  _Custom ROS messages used in various packages_
- **urc_platform**
  _Manages our nanopb protocol buffers_
- **urc_nav2**
  _Launch scripts and configs for Nav2 packages_
- **urc_navigation**
  _Collection of nodes that form our navigation stack_
- **urc_perception**
  _Collection of nodes that form our perception stack_
- **urc_platform**
  _Nodes that are platform specific and used to communicate with the hardware, ie. IMU, joystick and motor controller_
- **urc_util**
  _A collection of utility nodes and classes_

## Installation Instructions
**Essential** <br />
You will need to be using Ubuntu 22.04 to run ROS2. This can be accomplished with any of the following methods:

- [Ubuntu 22.04: Native Installation or WSL (Windows/Linux)](documents/installation/ubuntu_installation.md) **Strongly recommended!**
- [NoVNC Docker Installation Instructions (Mac/Windows/Linux)](documents/installation/docker_installation.md) **Less viable, use for Apple Silicon**

**Specific Features**
- [XBox Controller Setup](documents/installation/controller_setup.md)
- [Depth Camera Setup](documents/installation/camera_setup.md)
- [ROS2 Control Gazebo Setup](documents/installation/ros2_control.md)
- [Radio Communication Between Rover and Ground Station](documents/installation/radio_setup.md)


## Helpful Resources
- [Useful Commands: ROS2 Commands, Git Commands](documents/helpers/useful_commands.md)
- [Design Presentation Requirements](documents/design/README.md)
- [Drone Repository](https://github.com/RoboJackets/urc-drone)
- [Firmware Repository](https://github.com/RoboJackets/urc-firmware/tree/master)


## Team-Related Links
* [Slack](https://robojackets.slack.com/)
* [Google Drive](https://drive.google.com/drive/folders/1qZ3fwFvTRdvCWRLjbE44AmqxUnaBq8FP?usp=drive_link)  
* [Software Training](https://github.com/RoboJackets/software-training-old)  

## External Documentation and Background Reading
* [ROS2 Humble Documentation](https://docs.ros.org/en/humble/index.html)  
* [MoveIt2 Documentation](https://moveit.picknik.ai/main/index.html)  
* [Nav2 Documentation](https://navigation.ros.org/)  
* [ROS2 Control Documentation](https://control.ros.org/master/index.html)  

## Common Issues
#### NanoPB Not Building 
Fix (will only build after the last time):
```
colcon build --symlink-install ; chmod +x build/urc_nanopb/nanopb/generator/protoc-gen-nanopb
colcon build --symlink-install ; chmod +x build/urc_nanopb/nanopb/generator/nanopb_generator.py
colcon build --symlink-install
```