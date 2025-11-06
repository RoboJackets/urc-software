# urc-software [![CI Status Badge](https://github.com/RoboJackets/urc-software/actions/workflows/ci.yml/badge.svg)](https://github.com/RoboJackets/urc-software/actions)

Welcome to the RoboJackets/RoboNav software repo for the [University Rover Challenge](https://urc.marssociety.org/) (URC)! This document will give you a brief description of the repo's layout and an overview of the repo.

[![Static Badge](https://img.shields.io/badge/Software_Lead-Mrinal_Jain-EAAA00)](https://github.com/mrinalTheCoder)

## Directory Structure

- **.github**
  _CI pipeline and PR/issue templates_
- **cmake**
  _CMake files to aid with building_
- **documents**
  _Research, design, and documentation_
- **external**
  _Where all our submodules are located_
- **urc_arm_moveit_config**
  _Moveit config folder for rover arm_
- **urc_bringup**
  _Location of the universal launch file + heartbeat node_
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
- **urc_navigation**
  _Collection of nodes that form our navigation stack_
- **urc_perception**
  _Collection of nodes that form our perception stack_
- **urc_platform**
  _Nodes that are platform specific and used to communicate with the hardware, ie. IMU, joystick and motor controller_

## Installation Instructions

**Essential** <br />
You will need to be using Ubuntu 22.04 to run ROS2. This can be accomplished with any of the following methods:

- [Ubuntu 22.04: Native Installation or WSL (Windows/Linux)](documents/installation/ubuntu_installation.md) **Strongly recommended!**
- [Docker Installation Instructions (Mac/Windows/Linux)](documents/installation/docker_installation.md) **Less viable, use for Apple Silicon**

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

- [Slack](https://robojackets.slack.com/)
- [Google Drive](https://drive.google.com/drive/folders/1qZ3fwFvTRdvCWRLjbE44AmqxUnaBq8FP?usp=drive_link)
- [Software Training](https://github.com/RoboJackets/software-training-old)

## External Documentation and Background Reading

- [ROS2 Humble Documentation](https://docs.ros.org/en/humble/index.html)
- [MoveIt2 Documentation](https://moveit.picknik.ai/main/index.html)
- [Nav2 Documentation](https://navigation.ros.org/)
- [ROS2 Control Documentation](https://control.ros.org/master/index.html)

## Common Issues

#### NanoPB Not Building

Fix (will only build after the last time):

```
colcon build --symlink-install ; chmod +x build/urc_nanopb/nanopb/generator/protoc-gen-nanopb
colcon build --symlink-install ; chmod +x build/urc_nanopb/nanopb/generator/nanopb_generator.py
colcon build --symlink-install
```
Can also try downgrading/installing protobuf (described in error message):
```
pip install protoc==3.20
```
