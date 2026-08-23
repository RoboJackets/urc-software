# URC Rover Software

[![CI](https://github.com/RoboJackets/urc-rover/actions/workflows/ci.yml/badge.svg)](https://github.com/RoboJackets/urc-rover/actions/workflows/ci.yml)

This repository contains the RoboJackets University Rover Challenge ROS 2
software stack. It targets ROS 2 Humble on Ubuntu 22.04 and uses C++17, Python
launch files, `ament_cmake`, and `colcon`.

## Quick start

Create a workspace and clone the repository with its submodules:

```bash
mkdir -p rover_ws
git clone --recurse-submodules https://github.com/RoboJackets/urc-rover.git rover_ws/src
cd rover_ws
```

Install dependencies and build from the workspace root:

```bash
source /opt/ros/humble/setup.bash
rosdep update
rosdep install --from-paths src --ignore-src -r -y
colcon build --symlink-install
source install/setup.bash
```

Start the rover simulation:

```bash
ros2 launch urc_bringup sim.launch.py
```

Enable the autonomy stack when needed:

```bash
ros2 launch urc_bringup sim.launch.py autonomy:=true
```

There is currently no single launch file for complete physical-rover bringup.

## Repository map

- [`urc_bringup`](urc_bringup/README.md) composes simulation, autonomy,
  base-station, and rocker-control launches.
- [`urc_hw`](urc_hw/README.md),
  [`urc_controllers`](urc_controllers/README.md), and
  [`urc_hw_description`](urc_hw_description/README.md) own hardware access,
  ROS 2 control, and the rover model.
- [`urc_localization`](urc_localization/README.md),
  [`urc_perception`](urc_perception/README.md),
  [`urc_path_planning`](urc_path_planning/README.md),
  [`urc_state_machine`](urc_state_machine/README.md), and
  [`urc_trajectory_following`](urc_trajectory_following/README.md) form the
  autonomy stack.
- [`urc_platform`](urc_platform/README.md), [`urc_msgs`](urc_msgs/README.md),
  [`urc_nanopb`](urc_nanopb/README.md), and
  [`urc_nav_common`](urc_nav_common/README.md) provide platform adapters and
  shared interfaces.
- `external` contains vendored submodules and should not be modified as normal
  first-party code.

## Setup and development

- [Native Ubuntu installation](documents/installation/ubuntu_installation.md)
- [Docker installation](documents/installation/docker_installation.md)
- [Navigation architecture](documents/navigation.md)
- [ROS 2 control integration](documents/installation/ros2_control.md)
- [Useful development commands](documents/helpers/useful_commands.md)
- [Common troubleshooting issues](documents/helpers/common_issues.md)

Run build and test commands from `rover_ws`, not `rover_ws/src`:

```bash
colcon build --packages-up-to <package_name> --symlink-install
colcon test --packages-select <package_name>
colcon test-result --verbose
```

Source `install/setup.bash` again after rebuilding. Package manifests are the
source of truth for dependencies; use `rosdep` rather than maintaining a manual
package list.
