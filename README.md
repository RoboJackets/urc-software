# URC Rover Software

[![CI](https://github.com/RoboJackets/urc-software/actions/workflows/ci.yml/badge.svg)](https://github.com/RoboJackets/urc-software/actions/workflows/ci.yml)

This repository contains the RoboJackets University Rover Challenge ROS 2
software stack. It targets ROS 2 Humble on Ubuntu 22.04 and uses C++17, Python
launch files, `ament_cmake`, and `colcon`.

## Quick start

Create a workspace and clone the repository with its submodules:

```bash
mkdir -p rover_ws
git clone --recurse-submodules https://github.com/RoboJackets/urc-software.git rover_ws/src
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

## Core package layout

The core packages follow the standard ROS 2 layout: public C++ headers live in
`include/<package>/`, implementations live in `src/`, runtime parameters live in
`config/`, and launch composition lives in `launch/`. The trees below omit the
`CMakeLists.txt`, `package.xml`, and `README.md` present at each package root.

### Bringup and autonomy

`urc_bringup` remains the entry point for composing the rover stack. It does not
own general-purpose controller, localization, or platform node implementations.

```text
urc_bringup/
├── config/
│   ├── sim_config.yaml
│   └── test_controllers.yaml
└── launch/
    ├── autonomy.launch.py
    ├── base_station.launch.py
    ├── rocker_effort_pid.launch.py
    └── sim.launch.py

urc_perception/
├── config/
│   ├── pcl_grid_map_params.yaml
│   └── traversability_params.yaml
├── include/urc_perception/
│   ├── gaussian_filter.hpp
│   └── traversability_mapping.hpp
├── launch/
│   ├── d435i.launch.py
│   ├── mapping.launch.py
│   └── perception.launch.py
└── src/
    ├── gaussian_filter.cpp
    └── traversability_mapping.cpp

urc_nav_common/
├── include/urc_nav_common/grid_map_utils.hpp
└── src/grid_map_utils.cpp

urc_path_planning/
├── include/urc_path_planning/
│   ├── astar.hpp
│   └── planner_server.hpp
├── launch/planning.launch.py
└── src/
    ├── astar.cpp
    └── planner_server.cpp

urc_state_machine/
├── include/urc_state_machine/nav_coordinator.hpp
└── src/nav_coordinator.cpp

urc_trajectory_following/
├── config/pure_pursuit_config.yaml
├── include/urc_trajectory_following/
│   ├── follower_action_server.hpp
│   ├── geometry_util.hpp
│   ├── trajectory_controller.hpp
│   ├── trajectory_factory.hpp
│   └── pure_pursuit/pure_pursuit.hpp
├── launch/trajectory_following.launch.py
└── src/
    ├── follower_action_server.cpp
    ├── geometry_util.cpp
    ├── trajectory_factory.cpp
    └── pure_pursuit/pure_pursuit.cpp
```

Run the complete simulation through `urc_bringup`:

```bash
ros2 launch urc_bringup sim.launch.py
ros2 launch urc_bringup sim.launch.py autonomy:=true
```

Run only the autonomy nodes when localization, sensors, TF, and rover control
are already available:

```bash
ros2 launch urc_bringup autonomy.launch.py
```

There is currently no single launch file for complete physical-rover bringup.

### Hardware, localization, and platform integration

```text
urc_controllers/
├── include/urc_controllers/
│   ├── bms_broadcaster.hpp
│   ├── rocker_effort_pid.hpp
│   ├── rocker_tf_broadcaster.hpp
│   ├── status_light_controller.hpp
│   └── swerve_drive_controller.hpp
└── src/
    ├── bms_broadcaster.cpp
    ├── rocker_effort_pid.cpp
    ├── rocker_tf_broadcaster.cpp
    ├── status_light_controller.cpp
    └── swerve_drive_controller.cpp

urc_hw/
├── include/urc_hw/
│   ├── hardware/serial.hpp
│   ├── hardware_interface_types.hpp
│   └── hardware_interfaces/
│       ├── arm_control.hpp
│       ├── battery_management.hpp
│       ├── rover_drivetrain.hpp
│       ├── science_module.hpp
│       ├── status_light.hpp
│       └── test_hardware.hpp
└── src/
    ├── hardware/serial.cpp
    └── hardware_interfaces/
        ├── arm_control.cpp
        ├── battery_management.cpp
        ├── rover_drivetrain.cpp
        ├── science_module.cpp
        ├── status_light.cpp
        └── test_hardware.cpp

urc_localization/
├── config/ekf_redemption.yaml
├── include/urc_localization/
│   ├── covariances_on_gps.hpp
│   ├── covariances_on_imu.hpp
│   ├── gps_imu_localizer.hpp
│   └── ground_truth.hpp
├── launch/ekf.launch.py
└── src/
    ├── covariances_on_gps.cpp
    ├── covariances_on_imu.cpp
    ├── gps_imu_localizer.cpp
    └── ground_truth.cpp

urc_platform/
├── config/
│   ├── controller_config.yaml
│   ├── twist_mux.yaml
│   └── vectornav_imu.yaml
├── include/urc_platform/
│   ├── heartbeat_publisher.hpp
│   ├── imu_ned2enu.hpp
│   ├── joystick_driver.hpp
│   ├── preprocessing.hpp
│   ├── sim_gps_handler.hpp
│   └── twist_mux.hpp
└── src/
    ├── heartbeat_publisher.cpp
    ├── imu_ned2enu.cpp
    ├── joystick_driver.cpp
    ├── sim_gps_handler.cpp
    └── twist_mux.cpp
```

### Rover description and shared interfaces

```text
urc_hw_description/
├── config/joint_limits.yaml
├── launch/display.launch.py
├── meshes/
├── models/
├── rviz/display.rviz
├── urdf/simplified_swerve/
└── world/

urc_msgs/
├── action/NavigateToWaypoint.action
├── msg/
│   ├── BatteryInfo.msg
│   ├── GridLocation.msg
│   ├── OrientationPoses.msg
│   ├── RoverPoses.msg
│   ├── StatusLightCommand.msg
│   └── Waypoint.msg
└── srv/GeneratePlan.srv

urc_nanopb/
└── proto/urc.proto
```

### Package moves in this refactor

| Previous location | New location |
| --- | --- |
| `urc_navigation/grid_map_utils` | `urc_nav_common` |
| `urc_navigation/path_planning` | `urc_path_planning` |
| `urc_navigation/nav_testing` | `urc_state_machine` |
| `urc_navigation/trajectory_following` | `urc_trajectory_following` |
| `urc_perception/src/GaussianFilter.cpp` | `urc_perception/src/gaussian_filter.cpp` |
| `urc_perception/include/GaussianFilter.hpp` | `urc_perception/include/urc_perception/gaussian_filter.hpp` |
| `urc_bringup/src/rocker_effort_pid.cpp` | `urc_controllers/src/rocker_effort_pid.cpp` |
| `urc_bringup/src/rocker_tf_broadcaster.cpp` | `urc_controllers/src/rocker_tf_broadcaster.cpp` |
| `urc_bringup/src/ground_truth.cpp` | `urc_localization/src/ground_truth.cpp` |
| `urc_bringup/src/heartbeat_publisher.cpp` | `urc_platform/src/heartbeat_publisher.cpp` |

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
