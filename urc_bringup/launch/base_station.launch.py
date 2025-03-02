import os
from xacro import process_file
from launch import LaunchDescription
from launch.actions import (
    IncludeLaunchDescription,
    SetEnvironmentVariable,
    RegisterEventHandler,
)
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch.event_handlers import OnProcessExit, OnProcessStart
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    joystick_launch = PathJoinSubstitution([
        FindPackageShare('urc_platform'),
        'launch', 
        'joystick.launch.py',
    ])

    joy_drive_launch = PathJoinSubstitution([
        FindPackageShare('urc_platform'),
        'launch', 
        'joy_drive.launch.py',
    ])

    base_station_gps_launch = PathJoinSubstitution([
        Fid
    ])