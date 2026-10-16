from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    pitch_topic = DeclareLaunchArgument(
        "pitch_topic", default_value="/rocker/pitch_raw"
    )
    cmd_topic = DeclareLaunchArgument(
        "command_topic", default_value="/rocker_effort_controller/commands"
    )
    kp = DeclareLaunchArgument("kp", default_value="200.0")
    ki = DeclareLaunchArgument("ki", default_value="0.0")
    kd = DeclareLaunchArgument("kd", default_value="5.0")
    effort_limit = DeclareLaunchArgument("effort_limit", default_value="1200.0")

    node = Node(
        package="urc_controllers",
        executable="urc_controllers_RockerEffortPid",
        name="rocker_effort_pid",
        output="screen",
        parameters=[
            {
                "pitch_topic": LaunchConfiguration("pitch_topic"),
                "command_topic": LaunchConfiguration("command_topic"),
                "kp": LaunchConfiguration("kp"),
                "ki": LaunchConfiguration("ki"),
                "kd": LaunchConfiguration("kd"),
                "effort_limit": LaunchConfiguration("effort_limit"),
            }
        ],
    )

    return LaunchDescription(
        [
            pitch_topic,
            cmd_topic,
            kp,
            ki,
            kd,
            effort_limit,
            node,
        ]
    )
