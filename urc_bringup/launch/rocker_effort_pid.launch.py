from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    left_joint = DeclareLaunchArgument(
        "left_joint_name", default_value="L_Rocker_Joint"
    )
    right_joint = DeclareLaunchArgument(
        "right_joint_name", default_value="R_Rocker_Joint"
    )
    cmd_topic = DeclareLaunchArgument(
        "command_topic", default_value="/rocker_effort_controller/commands"
    )
    js_topic = DeclareLaunchArgument(
        "joint_state_topic", default_value="/joint_states"
    )
    spin_topic = DeclareLaunchArgument(
        "spin_effort_topic", default_value="/rocker/spin_effort"
    )
    kp = DeclareLaunchArgument("kp", default_value="200.0")
    ki = DeclareLaunchArgument("ki", default_value="0.0")
    kd = DeclareLaunchArgument("kd", default_value="5.0")
    effort_limit = DeclareLaunchArgument("effort_limit", default_value="1200.0")

    node = Node(
        package="urc_bringup",
        executable="urc_bringup_RockerEffortPid",
        name="rocker_effort_pid",
        output="screen",
        parameters=[
            {
                "left_joint_name": LaunchConfiguration("left_joint_name"),
                "right_joint_name": LaunchConfiguration("right_joint_name"),
                "command_topic": LaunchConfiguration("command_topic"),
                "joint_state_topic": LaunchConfiguration("joint_state_topic"),
                "spin_effort_topic": LaunchConfiguration("spin_effort_topic"),
                "kp": LaunchConfiguration("kp"),
                "ki": LaunchConfiguration("ki"),
                "kd": LaunchConfiguration("kd"),
                "effort_limit": LaunchConfiguration("effort_limit"),
            }
        ],
    )

    return LaunchDescription(
        [
            left_joint,
            right_joint,
            cmd_topic,
            js_topic,
            spin_topic,
            kp,
            ki,
            kd,
            effort_limit,
            node,
        ]
    )

