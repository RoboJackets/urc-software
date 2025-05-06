"""
@file    bringup_simulation.launch.py
@brief   Launch file for the URC robot simulation.
@details This launch file is used to start the simulation of the URC robot in Gazebo.
"""
import os
from xacro import process_file
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch.event_handlers import OnProcessStart, OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import (
    IncludeLaunchDescription,
    SetEnvironmentVariable,
    RegisterEventHandler,
)


def generate_launch_description():
    """
    Launch the simulation with the URC robot.
    """

    # Get the path to the package directories
    pkg_gz_sim    = get_package_share_directory("ros_gz_sim")
    pkg_urc_bringup = get_package_share_directory("urc_bringup")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")
    pkg_path_planning = get_package_share_directory("path_planning")
    pkg_trajectory_following = get_package_share_directory("trajectory_following")
    pkg_urc_localization = get_package_share_directory("urc_localization")
    pkg_urc_hw_description = get_package_share_directory("urc_hw_description")

    # Get the path to the URDF and world files
    xacro_file = os.path.join(pkg_urc_hw_description, "urdf/walli.xacro")
    world_path = os.path.join(pkg_urc_gazebo, "urdf/worlds", "urc_world.world")
    controller_config_file_dir = os.path.join(
        pkg_urc_bringup, "config", "ros2_control_walli.yaml"
    )

    # Check if the files exist
    assert os.path.exists(xacro_file), f"URDF path doesnt exist in {xacro_file}"
    assert os.path.exists(world_path), f"World path doesnt exist in {world_path}"

    # Load the URDF file and process it with xacro
    robot_desc = process_file(xacro_file, mappings={"use_simulation": "true"}).toxml()

    use_world_path = True

    gazebo_launch = IncludeLaunchDescription(
      PythonLaunchDescriptionSource(
        os.path.join(pkg_gz_sim, "launch", "gz_sim.launch.py"),
      ),
      launch_arguments={
        "gz_args": f"-r -v4 {' '.join([world_path] if use_world_path else [])}",
        "use_sim_time":"true"
      }.items(),
    )

    bt_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_bringup, "launch", "bt.launch.py")
        )
    )

    path_planning_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_path_planning, "launch", "planning.launch.py")
        )
    )

    trajectory_following_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                pkg_trajectory_following,
                "launch",
                "trajectory_following.launch.py",
            )
        )
    )

    ekf_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_localization, "launch", "ekf.launch.py")
        )
    )

    enable_color = SetEnvironmentVariable(name="RCUTILS_COLORIZED_OUTPUT", value="1")

    spawn_robot = Node(
      package="ros_gz_sim",
      executable="create",
      arguments=[
        "-name",  "walli",
        "-topic", "robot_description"
      ],
      output="screen",
    )

    rosbridge_server_node = Node(
        package="rosbridge_server",
        name="rosbridge_server",
        executable="rosbridge_websocket.py",
        parameters=[{"port": 9090}],
    )

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        parameters=[
            {"use_sim_time": True, "robot_description": robot_desc},
        ],
        output="screen",
    )

    joint_state_broadcaster_node = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "joint_state_broadcaster"],
    )

    drivetrain_controller_node = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "rover_drivetrain_controller"],
    )

    twist_mux_node = Node(
        package="urc_platform",
        executable="urc_platform_TwistMux",
        name="twist_mux",
    )

    sim_gps_handler_node = Node(
        package="urc_platform",
        executable="urc_platform_SimGpsHandler",
        name="sim_gps_handler",
    )


    elevation_mapping_node = Node(
        package="urc_perception",
        executable="urc_perception_ElevationMapping",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_perception"),
                    "config",
                    "mapping_params.yaml",
                ]
            )
        ],
    )

    driver_joy_node = Node(
        package="joy",
        executable="joy_node",
        remappings=(
            ("/joy", "/driver/joy"),
            ("/joy/set_feedback", "/driver/joy/set_feedback"),
        ),
    )

    joystick_driver_node = Node(
        name="joy_drive",
        package="urc_platform",
        executable="urc_platform_JoystickDriver",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_bringup"),
                    "config/",
                    "controller_config.yaml",
                ]
            )
        ],
        remappings=[
            ("/joystick_driver/joy", "/driver/joy"),
        ],
    )

    return LaunchDescription(
        [
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=spawn_robot,
                    on_exit=[
                        joint_state_broadcaster_node,
                        drivetrain_controller_node,
                        elevation_mapping_node,
                        driver_joy_node,
                        joystick_driver_node,
                    ],
                )
            ),
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=drivetrain_controller_node,
                    on_exit=[twist_mux_node],
                )
            ),
            RegisterEventHandler(
                event_handler=OnProcessStart(
                    target_action=elevation_mapping_node,
                    on_start=[
                        path_planning_launch,
                        trajectory_following_launch,
                        bt_launch,
                    ],
                )
            ),
            enable_color,
            gazebo_launch,
            sim_gps_handler_node,
            robot_state_publisher_node,
            spawn_robot,
            ekf_launch,
            rosbridge_server_node,
        ]
    )
