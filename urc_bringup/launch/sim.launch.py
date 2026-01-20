import os
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    RegisterEventHandler,
)
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, Command, PathJoinSubstitution
from launch_ros.descriptions import ParameterValue
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node


def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")
    path_urc_bringup = get_package_share_directory("urc_bringup")
    path_urc_localization = get_package_share_directory("urc_localization")

    controller_config_file_dir = os.path.join(
        path_urc_bringup, "config", "test_controllers.yaml"
    )

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

    world_filename = LaunchConfiguration("world")
    walli_xacro_config = LaunchConfiguration("walli_xacro")

    world_path = PathJoinSubstitution(
        [path_urc_hw_description, "world", world_filename]
    )

    robot_urdf_file = ParameterValue(
        Command(
            [
                "xacro ",
                walli_xacro_config,
                " use_sim:=",
                "true",
            ]
        ),
        value_type=str,
    )

    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py")
        ),
        launch_arguments={"gz_args": world_path}.items(),
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
            "-name",
            "walli",
            "-x",
            "0", # "-20",
            "-y",
            "0", # "-15",
            "-z",
            "1.5",
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

    # --- Controller Spawners ---
    load_joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "joint_state_broadcaster",
            "--param-file",
            controller_config_file_dir,
        ],
    )

    load_swerve_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            "swerve_controller",
            "--param-file",
            controller_config_file_dir,
        ],
    )

    follower_action_server_node = Node(
        package="trajectory_following",
        executable="trajectory_following_FollowerActionServer",
        name="follower_action_server",
        output="screen",
        parameters=[
            {"use_sim_time": True}
        ],
    )

    return LaunchDescription(
        [
            sim_world_arg,
            walli_xacro,
            bridge_yaml,
            gz_sim,
            bridge,
            robot_state_publisher_node,
            covariances_on_imu,
            rover_pose_bridge,
            spawn,
            follower_action_server_node,
            # Start joint_state_broadcaster AFTER robot spawn
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=spawn,
                    on_exit=[load_joint_state_broadcaster],
                )
            ),
            # Start swerve controller AFTER joint_state_broadcaster
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=load_joint_state_broadcaster,
                    on_exit=[load_swerve_controller],
                )
            ),
        ]
    )
