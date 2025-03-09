import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    IncludeLaunchDescription,
    SetEnvironmentVariable
)
from launch_ros.actions import Node


urc_arm_dir = get_package_share_directory("urc_arm_py")
arm_models_dir = get_package_share_directory("urc_arm_models")
robot_description_dir = os.path.join(
    arm_models_dir, "urdf", "walli_arm_v2_block_mjcf", "robot.urdf"
)
with open(robot_description_dir, 'r+') as urdf_file:
    robot_description = urdf_file.read()
controller_config_file_dir = os.path.join(
    urc_arm_dir, "config", "controller_config.yaml"
)


def generate_launch_description():
    qp_controller = Node(
        package="urc_arm_py",
        executable="arm_qp_control",
        name="qp_ctrl",
        parameters=[controller_config_file_dir],
        output="screen",
    )

    rsp_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        respawn=True,
        output="screen",
        parameters=[
            {
                "robot_description": robot_description,
                "publish_frequency": 100.0,
            },
        ]
    )

    foxglove_bridge = Node(
        package="foxglove_bridge",
        executable="foxglove_bridge",
        output="log"
    )

    return LaunchDescription(
        [
            rsp_node,
            qp_controller,
            foxglove_bridge
        ]
    )
