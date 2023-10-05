# Camera Setup Documentation
For now, we are using an Intel RealSense D435 as our depth camera.

### Installation Steps 
(from https://github.com/IntelRealSense/realsense-ros):
1. [Download Intel RealSense SDK](https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md#installing-the-packages)
2. Install ROS2 wrapper with `sudo apt install ros-humble-realsense2-*`

### Usage
- Launch the launch node: `ros2 launch realsense2_camera rs_launch.py`
- Can also use parameters such as: `ros2 launch realsense2_camera rs_launch.py depth_module.profile:=1280x720x30 pointcloud.enable:=true`

### Extra Details
- Check the documentation at https://github.com/IntelRealSense/realsense-ros if more information is required, and update the documentation here if that information will be used by other members.