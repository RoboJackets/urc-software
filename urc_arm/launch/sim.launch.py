import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    RegisterEventHandler,
    SetEnvironmentVariable,
)
from launch.conditions import IfCondition
from launch.event_handlers import OnProcessExit, OnProcessStart
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launch_utils import (
    DeclareBooleanLaunchArg,
    add_debuggable_node,
)
from srdfdom.srdf import SRDF

moveit_config = MoveItConfigsBuilder(
    "walli_arm_v2_block", package_name="walli_arm_v2_block_moveit_config"
).to_moveit_configs()


def generate_launch_description():
    # gazebo simulator & ros2 controllers
    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, "launch", "gazebo.launch.py"),
        ),
        launch_arguments={"use_sim_time": "true"}.items(),  # "world": world_path
    )
    robot_state_publisher_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            str(moveit_config.package_path / "launch/rsp.launch.py")
        ),
    )
    movegroup_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            str(moveit_config.package_path / "launch/move_group.launch.py")
        ),
    )

    spawn_robot = Node(
        package="gazebo_ros",
        executable="spawn_entity.py",
        arguments=[
            "-entity",
            "walli_arm_v2_block",
            "-x",
            "0",
            "-y",
            "0",
            "-z",
            "0",
            "-R",
            "0",
            "-P",
            "0",
            "-Y",
            "0",
            "-topic",
            "robot_description",
        ],
    )

    spawn_controller = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            str(moveit_config.package_path / "launch/spawn_controllers.launch.py")
        ),
    )

    return LaunchDescription(
        [
            # RegisterEventHandler(
            #     event_handler=OnProcessExit(
            #         target_action=spawn_robot,
            #         on_exit=[spawn_controller],
            #     )
            # ),
            robot_state_publisher_launch,
            # movegroup_launch,
            gazebo,
            # spawn_robot,
        ]
    )
