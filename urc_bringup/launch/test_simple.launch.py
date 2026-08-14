#!/usr/bin/env python3
"""
Simplified test launch - loads pre-generated URDF instead of running xacro at launch time
"""

import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")
    path_urc_bringup = get_package_share_directory("urc_bringup")

    # Setup paths
    urc_bringup_model_dir = os.path.join(path_urc_bringup, "models")
    urc_hw_model_dir = os.path.join(path_urc_hw_description, "models")
    urc_hw_world_dir = os.path.join(path_urc_hw_description, "world")

    gazebo_resource_path = os.pathsep.join([
        urc_bringup_model_dir,
        urc_hw_model_dir,
        urc_hw_world_dir,
        os.environ.get("GZ_SIM_RESOURCE_PATH", ""),
    ])

    world_path = os.path.join(urc_hw_world_dir, "marsyard2020.sdf")

    # Set environment variables
    set_gz_resource_path = SetEnvironmentVariable(
        name="GZ_SIM_RESOURCE_PATH",
        value=gazebo_resource_path,
    )

    set_ign_resource_path = SetEnvironmentVariable(
        name="IGN_GAZEBO_RESOURCE_PATH",
        value=gazebo_resource_path,
    )

    # Load pre-generated URDF
    urdf_file = os.path.join(path_urc_hw_description, "urdf/simplified_swerve/simplified_swerve.urdf")
    
    # If pre-generated not available, fall back to xacro generated version
    if not os.path.exists(urdf_file):
        # Try to find xacro version
        xacro_file = os.path.join(path_urc_hw_description, "urdf/simplified_swerve/simplified_swerve.urdf.xacro")
        if os.path.exists(xacro_file):
            urdf_file = xacro_file
    
    # Read URDF content
    try:
        with open(urdf_file, 'r') as f:
            robot_urdf_content = f.read()
    except FileNotFoundError:
        raise RuntimeError(f"Could not find URDF file at {urdf_file}")

    # Gazebo
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py")),
        launch_arguments={"gz_args": ["-s -r ", world_path]}.items(),
    )

    # Robot state publisher
    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        parameters=[{
            "robot_description": robot_urdf_content,
            "use_sim_time": True,
        }],
        output="screen",
    )

    # Bridge
    bridge_config_file = os.path.join(path_urc_bringup, "config", "sim_config.yaml")
    bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        arguments=[
            "--ros-args",
            "-p", f"config_file:={bridge_config_file}",
        ],
        output="screen",
    )

    # ArUco detector
    aruco_detector_node = Node(
        package="urc_bringup",
        executable="aruco_detector.py",
        name="aruco_detector",
        output="screen",
        parameters=[{"marker_size": 0.05}],
    )

    # Spawn robot
    spawn_robot = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-name", "walli",
            "-x", "0",
            "-y", "0",
            "-z", "2.0",
            "-topic", "robot_description",
        ],
    )

    # Spawn ArUco tag
    aruco_sdf_path = os.path.join(path_urc_bringup, "models", "aruco_tag_0", "model.sdf")
    spawn_aruco_tag = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-name", "aruco_tag_0",
            "-x", "4.0",
            "-y", "0.0",
            "-z", "0.2",
            "-R", "0.0",
            "-P", "0.0",
            "-Y", "0.0",
            "-file", aruco_sdf_path,
        ],
    )

    return LaunchDescription([
        set_gz_resource_path,
        set_ign_resource_path,
        gz_sim,
        robot_state_publisher_node,
        bridge,
        spawn_robot,
        spawn_aruco_tag,
        aruco_detector_node,
    ])
