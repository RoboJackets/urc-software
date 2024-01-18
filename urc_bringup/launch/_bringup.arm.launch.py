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


def generate_launch_description():
    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")
    pkg_urc_bringup = get_package_share_directory("urc_bringup")

    hardware_config_file_dir = os.path.join(
        pkg_urc_bringup, 'config', 'hardware_config.yaml')
    with open(hardware_config_file_dir) as f:
        hardware_config = yaml.safe_load(f)
    use_simulation = hardware_config['hardware_config']['use_simulation']

    srdf_file = os.path.join(
        get_package_share_directory('urc_hw_description'),
        "urdf/walli.srdf"
    )
    with open(srdf_file, 'r') as f:
        semantic_content = f.read()

    controller_config_file_dir = os.path.join(
        pkg_urc_bringup,
        'config', 'controller_config.yaml'
    )

    xacro_file = os.path.join(
        get_package_share_directory('urc_hw_description'),
        "urdf/walli.xacro"
    )
    assert os.path.exists(
        xacro_file), "urdf path doesnt exist in " + str(xacro_file)
    robot_description_config = process_file(xacro_file)
    robot_desc = robot_description_config.toxml()

    moveit_config = MoveItConfigsBuilder(package_name="urc_hw_description", robot_name="walli").robot_description(
        file_path="urdf/walli.xacro"
    ).robot_description_semantic(
        file_path="config/walli.srdf"
    ).trajectory_execution(
        file_path="config/moveit_controllers.yaml"
    ).joint_limits(
        file_path="config/joint_limits.yaml"
    ).robot_description(
        file_path=xacro_file
    ).to_moveit_configs()

    moveit_config_str = moveit_config.to_dict()

    run_move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[
            moveit_config_str,
            {
                'robot_description_semantic': semantic_content,
            }
        ]
    )

    return LaunchDescription([
        run_move_group_node
    ])
