# urc_localization

## Overview

The `urc_localization` package provides configuration and launch files for rover state estimation using the **Extended Kalman Filter (EKF)** from the `robot_localization` package.  

It fuses IMU, odometry, and (optionally) GPS inputs to estimate the rover’s position, orientation, and velocity in a consistent world frame.  

This system includes the following modules:

1. **EKF Configuration**  
   - YAML configuration defining sensor inputs, noise models, and state estimation parameters.  
   - **Key features**: Flexible tuning for rover-specific sensors.  

2. **EKF Launch**  
   - Launch file for starting the `ekf_node` with the provided configuration.  
   - **Key features**: Quick deployment of localization with minimal setup.  

---

## Features

- **Sensor Fusion**: Combines IMU, odometry, and GPS into a unified state estimate.  
- **EKF Tuning**: Parameters can be adjusted to account for rover-specific dynamics.  
- **ROS 2 Integration**: Built on top of `robot_localization`’s `ekf_node`.  
- **Launch Support**: Simple launch file to start the EKF with provided config.  


## Package Structure

```
├── CMakeLists.txt
├── config
│   └── ekf.yaml
├── launch
│   └── ekf.launch.py
└── package.xml
```


## Components

### EKF Configuration

- **ekf.yaml**  
  - Defines state estimation parameters for the rover.  
  - **Inputs**: IMU, odometry, and optional GPS topics.  
  - **Outputs**: Filtered state estimate (`/odometry/filtered`, `/tf`).  

### EKF Launch

- **ekf.launch.py**  
  - Starts the `robot_localization/ekf_node` with the parameters in `ekf.yaml`.  
  - Provides a ready-to-use entry point for rover localization.  

---

## ekf_node | Node

*(from `robot_localization`)*  

### Subscriptions
- `/imu/data` (`sensor_msgs/Imu`) – Raw IMU orientation, angular velocity, and acceleration.  
- `/odom/wheel` (`nav_msgs/Odometry`) – Odometry from wheel encoders.  
- `/gps/fix` (`sensor_msgs/NavSatFix`) – (Optional) GPS position fix.  

### Publishers
- `/odometry/filtered` (`nav_msgs/Odometry`) – EKF-fused odometry.  
- `/tf` (`tf2_msgs/TFMessage`) – Transform tree updates for rover pose.  

### Parameters (from `ekf.yaml`)
- `frequency` (`double`) – Filter update rate in Hz.  
- `sensor_timeout` (`double`) – Timeout for dropping sensor data.  
- `two_d_mode` (`bool`) – Restrict estimation to planar (x, y, yaw) if true.  
- `odom0`, `imu0`, `gps0` (`string`) – Input topics for each sensor.  
- `odom0_config`, `imu0_config`, `gps0_config` (`array<bool>`) – Which variables from each sensor to fuse.  

---

## Launch

Start the localization system with:

```bash
ros2 launch urc_localization ekf.launch.py
```
