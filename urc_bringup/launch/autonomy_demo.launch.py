import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    bringup_share = get_package_share_directory("urc_bringup")
    slam_share = get_package_share_directory("urc_slam")

    rviz_arg = DeclareLaunchArgument(
        "rviz", default_value="true", description="Open RViz with the demo layout"
    )

    simulation = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(bringup_share, "launch", "sim.launch.py")),
        launch_arguments={"autonomy": "true"}.items(),
    )
    # Scoped so SLAM's rviz:=false neither opens nor overrides the demo's RViz
    slam = GroupAction([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(slam_share, "launch", "slam.launch.py")),
            launch_arguments={"rviz": "false"}.items(),
        )
    ])
    mission = Node(
        package="urc_state_machine",
        executable="urc_state_machine_WaypointMission",
        name="waypoint_mission",
        output="screen",
        parameters=[os.path.join(bringup_share, "config", "autonomy_demo.yaml")],
    )
    rviz = Node(
        package="rviz2",
        executable="rviz2",
        name="autonomy_demo_rviz",
        arguments=["-d", os.path.join(bringup_share, "rviz", "autonomy_demo.rviz")],
        parameters=[{"use_sim_time": True}],
        condition=IfCondition(LaunchConfiguration("rviz")),
    )

    return LaunchDescription([rviz_arg, simulation, slam, mission, rviz])
