import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    IncludeLaunchDescription,
)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder

moveit_config = MoveItConfigsBuilder(
    "walli_arm_v2_block", package_name="walli_arm_v2_block_moveit_config"
).to_moveit_configs()
urc_arm_dir = get_package_share_directory("urc_arm")
controller_config_file_dir = os.path.join(
    urc_arm_dir, "config", "controller_config.yaml"
)


def generate_launch_description():
    # mujoco simulator
    mjsim = Node(
        package="urc_arm_py",
        executable="arm_sim_mj",
        parameters=[controller_config_file_dir],
    )
    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[controller_config_file_dir],
        output="both",
        remappings=[("~/robot_description", "/robot_description")],
    )
    rsp_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        respawn=True,
        output="screen",
        parameters=[
            moveit_config.robot_description,
            {
                "publish_frequency": 100.0,
            },
        ],
        remappings=[("/joint_states", "/arm_joint_states")],
    )
    spawn_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["arm_position_controller"],
        output="screen",
    )
    qp_controller = Node(
        package="urc_arm_py",
        executable="arm_qp_control",
        parameters=[controller_config_file_dir],
        output="screen",
    )

    return LaunchDescription(
        [rsp_node, control_node, mjsim, spawn_controller, qp_controller]
    )
