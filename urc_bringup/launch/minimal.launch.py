#!/usr/bin/env python3
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    test_node = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=["-name", "test", "-x", "0"],
    )
    
    return LaunchDescription([test_node])
