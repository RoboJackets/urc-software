# urc_gazebo

## Overview

The `urc_gazebo` package provides simulation support for the URC robotics platform, including robot control, sensor emulation, ground truth publishing, laser scan processing, and integration with Gazebo.  

This system includes the following modules:

1. **Control**
   - Implements PID-based wheel control for simulated robot drivetrains.  
   - Publishes wheel velocities, efforts, and enabled status.  
   - Subscribes to desired velocity commands and joint state feedback.  

2. **Ground Truth**
   - Provides odometry and pose information for the robot in simulation.  
   - Publishes accurate position data and optionally simulates sensor noise.  

3. **Scan to PointCloud**
   - Converts laser scan messages into point clouds.  
   - Publishes `sensor_msgs/msg/PointCloud2` for downstream processing.  

---

## Features

- **PID Control**: Configurable PID control for left and right wheels.  
- **Ground Truth Odometry**: Accurate robot position and orientation for simulation.  
- **Laser Scan Conversion**: Transform laser scans into point clouds.  
- **ROS 2 Parameter Support**: Configurable via `urc_gazebo_params.yaml`.  
- **Gazebo Integration**: Launch simulation including robot spawn, controllers, and robot state publisher.  

---

## Package Structure

```
├── CMakeLists.txt
├── config
│   └── urc_gazebo_params.yaml
├── include
│   ├── control.hpp
│   ├── ground_truth.hpp
│   └── scan_to_pointcloud.hpp
├── launch
│   └── simulation.launch.py
├── package.xml
└── urdf
    ├── gazebo.material
    ├── models
    │   ├── aruco_visual_marker_0
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   └── aruco_visual_marker_0_marker.material
    │   │   │   └── textures
    │   │   │       ├── 4x4_1000-0.svg
    │   │   │       ├── aruco_mark_0(old).png
    │   │   │       ├── aruco_mark_0.png
    │   │   │       └── aruco_mark_0.svg
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_0_pad
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   ├── aruco_visual_marker_0_marker.material
    │   │   │   │   └── aruco_visual_marker_0_num.material
    │   │   │   └── textures
    │   │   │       ├── 4x4_1000-0.svg
    │   │   │       ├── aruco_mark_0_num.png
    │   │   │       ├── aruco_mark_0_num.svg
    │   │   │       ├── aruco_mark_0(old).png
    │   │   │       ├── aruco_mark_0.png
    │   │   │       └── aruco_mark_0.svg
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_1
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   └── aruco_visual_marker_1_marker.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_1(old).png
    │   │   │       └── aruco_mark_1.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_1_pad
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   ├── aruco_visual_marker_1_marker.material
    │   │   │   │   └── aruco_visual_marker_1_num.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_1_num.png
    │   │   │       ├── aruco_mark_1_num.svg
    │   │   │       ├── aruco_mark_1(old).png
    │   │   │       └── aruco_mark_1.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_2
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   └── aruco_visual_marker_2_marker.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_2(old).png
    │   │   │       └── aruco_mark_2.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_2_pad
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   ├── aruco_visual_marker_2_marker.material
    │   │   │   │   └── aruco_visual_marker_2_num.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_2_num.png
    │   │   │       ├── aruco_mark_2_num.svg
    │   │   │       ├── aruco_mark_2(old).png
    │   │   │       └── aruco_mark_2.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_3
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   └── aruco_visual_marker_3_marker.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_3(old).png
    │   │   │       └── aruco_mark_3.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_3_pad
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   ├── aruco_visual_marker_3_marker.material
    │   │   │   │   └── aruco_visual_marker_3_num.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_3_num.png
    │   │   │       ├── aruco_mark_3_num.svg
    │   │   │       ├── aruco_mark_3(old).png
    │   │   │       └── aruco_mark_3.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_4
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   └── aruco_visual_marker_4_marker.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_4(old).png
    │   │   │       └── aruco_mark_4.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_4_pad
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   ├── aruco_visual_marker_4_marker.material
    │   │   │   │   └── aruco_visual_marker_4_num.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_4_num.png
    │   │   │       ├── aruco_mark_4_num.svg
    │   │   │       ├── aruco_mark_4(old).png
    │   │   │       └── aruco_mark_4.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_5
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   └── aruco_visual_marker_5_marker.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_5(old).png
    │   │   │       └── aruco_mark_5.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── aruco_visual_marker_5_pad
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   ├── aruco_visual_marker_5_marker.material
    │   │   │   │   └── aruco_visual_marker_5_num.material
    │   │   │   └── textures
    │   │   │       ├── aruco_mark_5_num.png
    │   │   │       ├── aruco_mark_5_num.svg
    │   │   │       ├── aruco_mark_5(old).png
    │   │   │       └── aruco_mark_5.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── barrel
    │   │   ├── meshes
    │   │   │   ├── barrel.dae
    │   │   │   └── Barrel.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── desert_surface
    │   │   ├── materials
    │   │   │   ├── scripts
    │   │   │   │   └── desert.material
    │   │   │   └── textures
    │   │   │       └── mars_texture.jpg
    │   │   ├── model.config
    │   │   └── model.sdf
    │   ├── marsyard2022_terrain
    │   │   ├── dem
    │   │   │   ├── marsyard2022_terrain_hm.tif
    │   │   │   └── marsyard2022_terrain_texture.png
    │   │   ├── model.config
    │   │   └── model.sdf
    │   └── sun
    │       ├── model.config
    │       └── model.sdf
    └── worlds
        ├── nav2_world.sdf
        └── urc_world.world
```

## Components

### Control

- **Control (`control.hpp/cpp`)**
  - Implements PID-based wheel control for left and right motors.  
  - **Inputs**: `/speed_cmd` (`urc_msgs/msg/VelocityPair`), `/joint_states` (`sensor_msgs/msg/JointState`)  
  - **Outputs**: Wheel velocities (`/wheel_speed`), efforts (`/left_wheel_effort`, `/right_wheel_effort`), shocks, enabled flag (`/enabled`)  
  - **Key Parameters**: `speed_P_left`, `speed_P_right`, `speed_I_left`, `speed_I_right`, `speed_D_left`, `speed_D_right`, `wheel_radius`, `max_effort`, `rate_var`  

### Ground Truth

- **GroundTruth (`groundtruth.hpp/cpp`)**
  - Publishes accurate odometry and robot pose, optionally simulating sensor noise.  
  - **Inputs**: `/ground_truth_odom`, `/estimate_odom` (`nav_msgs/msg/Odometry`)  
  - **Outputs**: `/ground_truth` (`nav_msgs/msg/Odometry`)  
  - **Key Parameters**: `x_noise_std_dev`, `y_noise_std_dev`, `z_noise_std_dev`, `roll_noise_std_dev`, `pitch_noise_std_dev`, `yaw_noise_std_dev`, `utm_enabled`  

### Scan to PointCloud

- **ScanToPointCloud (`scan_to_pointcloud.hpp/cpp`)**
  - Converts `LaserScan` messages into `PointCloud2`.  
  - **Inputs**: `/scan` (`sensor_msgs/msg/LaserScan`)  
  - **Outputs**: `/pointcloud` (`sensor_msgs/msg/PointCloud2`)  
  - **Key Parameters**: `min_dist`, `neighbor_dist`  

---

## Nodes

### Control | Node

#### Subscriptions
- `/speed_cmd` (`urc_msgs/msg/VelocityPair`) – Desired wheel velocities  
- `/joint_states` (`sensor_msgs/msg/JointState`) – Measured wheel joint states  

#### Publishers
- `/wheel_speed` (`urc_msgs/msg/VelocityPair`) – Current wheel velocities  
- `/left_wheel_effort` (`std_msgs/msg/Float64`) – Left wheel PID effort  
- `/right_wheel_effort` (`std_msgs/msg/Float64`) – Right wheel PID effort  
- `/enabled` (`std_msgs/msg/Bool`) – Indicates controller is active  

#### Parameters
- `speed_P_left`, `speed_P_right` (`double`) – Proportional PID gains  
- `speed_I_left`, `speed_I_right` (`double`) – Integral PID gains  
- `speed_D_left`, `speed_D_right` (`double`) – Derivative PID gains  
- `wheel_radius` (`double`) – Wheel radius for speed calculations  
- `max_effort` (`double`) – Maximum allowed actuator effort  
- `rate_var` (`double`) – Loop rate in Hz  

---

### GroundTruth | Node

#### Subscriptions
- `/ground_truth_odom` (`nav_msgs/msg/Odometry`) – Input odometry from simulation  
- `/estimate_odom` (`nav_msgs/msg/Odometry`) – Optional estimated odometry  

#### Publishers
- `/ground_truth` (`nav_msgs/msg/Odometry`) – Published ground truth pose  

#### Parameters
- `x_noise_std_dev`, `y_noise_std_dev`, `z_noise_std_dev` (`double`) – Noise for position  
- `roll_noise_std_dev`, `pitch_noise_std_dev`, `yaw_noise_std_dev` (`double`) – Noise for orientation  
- `utm_enabled` (`bool`) – Enable UTM coordinate conversion  

---

### ScanToPointCloud | Node

#### Subscriptions
- `/scan` (`sensor_msgs/msg/LaserScan`) – Input laser scan  

#### Publishers
- `/pointcloud` (`sensor_msgs/msg/PointCloud2`) – Output point cloud  

#### Parameters
- `min_dist` (`double`) – Minimum distance to include a point  
- `neighbor_dist` (`double`) – Neighbor distance for filtering points  

---

## Launch

Start the Gazebo simulation with:

```bash
ros2 launch urc_gazebo simulation.launch.py
```

