# Required Packages

Package manifests are the source of truth for repository dependencies. Use
`rosdep` instead of maintaining or installing a separate manual list of ROS
packages.

After installing ROS 2 Humble, install the dependency-management and build
tools:

```bash
sudo apt update
sudo apt install python3-rosdep python3-colcon-common-extensions
```

Initialize `rosdep` once on a new system, then install dependencies from the
workspace root:

```bash
sudo rosdep init  # Skip this line if rosdep is already initialized.
rosdep update
cd rover_ws
rosdep install --from-paths src --ignore-src -r -y
```

Run the `rosdep install` command again after pulling changes that modify a
`package.xml`. Docker users should run it inside the development container.

The SLAM package requires the GTSAM development library (`ros-humble-gtsam`).
A CMake error about missing `GTSAMConfig.cmake` means this dependency is absent
or its installation prefix is not sourced. On the supported Humble setup:

```bash
sudo apt update
sudo apt install ros-humble-gtsam
source /opt/ros/humble/setup.bash
```

Keep `grid_map_visualization` installed for the autonomy launch even though it
is not a compile-time dependency of the perception library.
