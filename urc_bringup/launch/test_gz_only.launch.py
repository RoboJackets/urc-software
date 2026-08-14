#!/usr/bin/env python3
import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")

    world_path = os.path.join(path_urc_hw_description, "world", "marsyard2020.sdf")
    
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py")),
        launch_arguments={"gz_args": ["-s -r ", world_path]}.items(),
    )
    
    return LaunchDescription([gz_sim])
