from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable, TimerAction
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import ExecuteProcess, RegisterEventHandler
from launch_ros.actions import Node
from launch.event_handlers import OnProcessExit
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launch_utils import (
    add_debuggable_node,
    DeclareBooleanLaunchArg,
)

import os
import yaml
from xacro import process_file


def load_yaml(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)

    try:
        with open(absolute_file_path, 'r') as file:
            return yaml.safe_load(file)
    except EnvironmentError:  # parent of IOError, OSError *and* WindowsError where available
        return None


def generate_launch_description():
    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")
    pkg_urc_bringup = get_package_share_directory("urc_bringup")

    servo_yaml = load_yaml("urc_bringup", "config/servo_config.yaml")
    servo_params = {"moveit_servo": servo_yaml}

    run_servo_node = Node(
        package="urc_manipulation",
        executable="urc_manipulation_ArmRT",
        output="screen",
        parameters=[
            servo_params
        ]
    )

    return LaunchDescription([
        run_servo_node
    ])
