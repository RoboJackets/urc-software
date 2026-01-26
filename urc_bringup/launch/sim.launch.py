import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, RegisterEventHandler, TimerAction
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, Command, PathJoinSubstitution
from launch_ros.descriptions import ParameterValue
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node


def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")
    path_urc_bringup = get_package_share_directory("urc_bringup")
    path_urc_localization = get_package_share_directory("urc_localization")

    controller_config_file_dir = os.path.join(path_urc_bringup, "config", "test_controllers.yaml")

    sim_world_arg = DeclareLaunchArgument(
        "world",
        default_value="marsyard2020.sdf",
        description="Name of the world file (not full path)",
    )

    walli_xacro = DeclareLaunchArgument(
        "walli_xacro",
        default_value=os.path.join(
            path_urc_hw_description,
            "urdf/simplified_swerve",
            "simplified_swerve.urdf.xacro",
        ),
        description="Path to xacro file",
    )

    bridge_yaml = DeclareLaunchArgument(
        "bridge_yaml",
        default_value=os.path.join(path_urc_bringup, "config", "sim_config.yaml"),
        description="bridge YAML config",
    )

    spawn_rocker_effort = DeclareLaunchArgument(
        "spawn_rocker_effort_controller",
        default_value="true",
        description="Spawn rocker effort controller (Option B)",
    )

    world_filename = LaunchConfiguration("world")
    walli_xacro_config = LaunchConfiguration("walli_xacro")

    world_path = PathJoinSubstitution([path_urc_hw_description, "world", world_filename])

    robot_urdf_file = ParameterValue(
        Command(["xacro ", walli_xacro_config, " use_sim:=", "true"]),
        value_type=str,
    )

    # Start Gazebo and immediately run the simulation (-r)
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py")),
        launch_arguments={"gz_args": ["-r ", world_path]}.items(),
    )

    bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        name="ros_gz_bridge",
        output="screen",
        parameters=[{"config_file": LaunchConfiguration("bridge_yaml")}],
    )

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        parameters=[{"robot_description": robot_urdf_file}],
        output="screen",
    )

    covariances_on_imu = Node(
        package="urc_localization",
        executable="urc_localization_CovariancesOnImu",
        name="covariances_on_imu",
        parameters=[
            {
                "imu_input_topic": "/imu/data_raw",
                "imu_output_topic": "/imu/fused",
            }
        ],
        output="screen",
    )

    scan_to_point_cloud = Node(
        package="urc_localization",
        executable="urc_localization_ScanToPointCloud",
        name="scan_to_point_cloud",
        parameters=[
            {
                "scan_input_topic": "/scan",
                "point_cloud_output_topic": "/point_cloud",
                "target_frame": "base_link",
            }
        ],
        output="screen",
    )

    rover_pose_bridge = Node(
        package="urc_bringup",
        executable="urc_bringup_RoverPoseBridge",
        name="rover_pose_bridge",
        parameters=[
            {
                "tf_topic": "/ground_truth_pose",
                "rover_pos_topic": "/rover_ground_truth",
                "use_sim_time": True,
            }
        ],
        output="screen",
    )

    spawn = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-name", "walli",
            "-x", "-20",
            "-y", "-15",
            "-z", "1.5",
            "-R", "0",
            "-P", "0",
            "-Y", "0",
            "-topic", "robot_description",
        ],
    )

    # --- Controller Spawners ---
    load_joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "joint_state_broadcaster",
            "--param-file", controller_config_file_dir,
            "--controller-manager-timeout", "120",
        ],
        output="screen",
    )

    load_swerve_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "swerve_controller",
            "--param-file", controller_config_file_dir,
            "--controller-manager-timeout", "120",
        ],
        output="screen",
    )

    load_rocker_effort_controller = Node(
        package="controller_manager",
        executable="spawner",
        condition=IfCondition(LaunchConfiguration("spawn_rocker_effort_controller")),
        arguments=[
            "rocker_effort_controller",
            "--param-file", controller_config_file_dir,
            "--controller-manager-timeout", "120",
        ],
        output="screen",
    )

    # IMPORTANT:
    # Using TimerAction chaining is more reliable than OnProcessExit on the spawner nodes,
    # because spawners exit quickly and your previous event target was not the TimerAction.
    delayed_load_jsb = TimerAction(period=5.0, actions=[load_joint_state_broadcaster])
    delayed_load_swerve = TimerAction(period=7.0, actions=[load_swerve_controller])
    delayed_load_rocker = TimerAction(period=9.0, actions=[load_rocker_effort_controller])

    return LaunchDescription(
        [
            sim_world_arg,
            walli_xacro,
            bridge_yaml,
            spawn_rocker_effort,

            gz_sim,
            bridge,
            robot_state_publisher_node,
            covariances_on_imu,
            scan_to_point_cloud,
            rover_pose_bridge,
            spawn,

            # After robot spawn, start controller spawners on a fixed schedule
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=spawn,
                    on_exit=[delayed_load_jsb, delayed_load_swerve, delayed_load_rocker],
                )
            ),
        ]
    )
