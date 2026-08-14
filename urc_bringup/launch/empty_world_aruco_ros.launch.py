import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, LaunchConfiguration, TextSubstitution
from launch_ros.actions import Node
from launch_ros.descriptions import ParameterValue


def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")
    path_urc_bringup = get_package_share_directory("urc_bringup")

    world_path = os.path.join(path_urc_hw_description, "world", "empty_world.sdf")
    
    # Path to robot URDF xacro file
    walli_xacro = os.path.join(
        path_urc_hw_description,
        "urdf/simplified_swerve",
        "simplified_swerve.urdf.xacro",
    )
    
    # Bridge YAML config
    bridge_yaml = os.path.join(path_urc_bringup, "config", "sim_config.yaml")

    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(path_ros_gz_sim, "launch", "gz_sim.launch.py")
        ),
        launch_arguments={
            "gz_args": ["-r ", world_path],
        }.items(),
    )

    # Robot description from xacro
    robot_urdf_file = ParameterValue(
        Command(["xacro ", walli_xacro, " use_sim:=true"]),
        value_type=str,
    )

    # Publish robot state from URDF
    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        parameters=[{"robot_description": robot_urdf_file}],
        output="screen",
    )

    # Spawn robot into Gazebo
    spawn = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-name", "walli",
            "-x", "0",
            "-y", "0",
            "-z", "2.0",
            "-R", "0",
            "-P", "0",
            "-Y", "0",
            "-topic", "robot_description",
        ],
    )

    # ROS-Gazebo bridge
    bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        name="ros_gz_bridge",
        output="screen",
        parameters=[{"config_file": bridge_yaml}],
    )

    aruco_node = Node(
        package="aruco_ros",
        executable="marker_publisher",
        name="aruco_marker_publisher",
        output="screen",
        parameters=[
            {
                "image_is_rectified": False,
                "marker_size": 0.05,
                "reference_frame": "camera_link",
                "camera_frame": "camera_link",
            }
        ],
        remappings=[
            ("/camera_info", "/camera/camera_info"),
            ("/image", "/camera/image_raw"),
        ],
    )

    return LaunchDescription([gz_sim, robot_state_publisher_node, spawn, bridge, aruco_node])
