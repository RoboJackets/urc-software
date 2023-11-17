# URC Control

This is the central bring-up package for the whole ros2_control system used in URC. The related packages are:

- **urc_hw**: contains hardware resource managers, hardware interfaces, and utilities.
- **urc_hw_description**: provides .urdf and .xacro files that describes the hardware on the rover.
- **urc_controllers**: contains all the controllers for communicating with the hardware interfaces.
- **urc_control**: contains a node to start the control manager, initialize all the hardware interfaces, and finally start the publishers & subscribers for receiving and sending control signals.

## Usage

Simply type in command line:

```
ros2 launch urc_control bringup.launch.py
```

Everything will go live.
