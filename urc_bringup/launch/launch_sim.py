import os
from xacro import process_file
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.substitutions import PathJoinSubstitution
from launch.actions import (DeclareLaunchArgument, IncludeLaunchDescription, SetEnvironmentVariable)
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch import LaunchDescription


def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_bringup = get_package_share_directory("urc_bringup")
    path_urc_platform = get_package_share_directory("urc_platform")
    path_urc_localization = get_package_share_directory("urc_localization")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")

    xacro_file = os.path.join(path_urc_hw_description, "urdf/simplified_swerve", "simplified_swerve.urdf.xacro")
    robot_description = process_file(xacro_file, mappings = {"use_sim": "true"}).toxml()
    controller_config = os.path.join(path_urc_bringup, "config", "controller_config.yaml")
    twist_mux_config = os.path.join(path_urc_platform, "config", "twist_mux.yaml")



    sim_world = DeclareLaunchArgument(
        "sim_world",
        default_value = os.path.join(path_urc_hw_description, "world", "world.sdf"),
        description = "Path to the Gazebo world file"
    )

    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py"))
    )

    enable_color = SetEnvironmentVariable(name = "RCUTILS_COLORIZED_OUTPUT", value = "1")

    spawn_robot_args_str = ("-entity walli -x 0 -y 0 -z 10 -R 0 -P 0 -Y 0 -topic robot_description")
    spawn_robot = Node(package = "gazebo_ros", executable = "spawn_entity.py", arguments = spawn_robot_args_str.split(" "))
    
    robot_state_publisher_node = Node(
        package = "robot_state_publisher",
        executable = "robot_state_publisher",
        name = "robot_state_publisher",
        parameters = [
            {"use_sim_time": True, "robot_description": robot_description}
        ],
        output = "screen",
    )

    joint_state_broadcaster_node = Node(
        package = "controller_manager",
        executable = "spawner",
        arguments = ["-p", controller_config, "joint_state_broadcaster"],
    )

    load_drivetrain_controller = Node(
        package = "controller_manager",
        executable = "spawner",
        arguments = ["-p", controller_config, "rover_drivetrain_controller"],
    )

    twist_mux_node = Node(
        package = "urc_platform",
        executable = "urc_platform_TwistMux"
    )

    sim_gps_handler_node = Node(
        package = "urc_platform",
        executable = "urc_platform_SimGpsHandler",
    )

    imu_ned2enu_node = Node(
        package = "urc_platform",
        executable = "urc_platform_ImuNED2ENU",
    )

    joystick_driver_node = Node(
        package = "urc_platform",
        executable = "urc_platform_JoystickDriver",
        output = "screen",
        parameters = [
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_bringup"),
                    "config/",
                    "controller_config.yaml",
                ]
            )
        ]
    )

    return LaunchDescription([
        #Gazebo, robot spawning
        gz_sim,
        spawn_robot,
        enable_color,

        #Control
        robot_state_publisher_node,
        joint_state_broadcaster_node,
        load_drivetrain_controller,
        twist_mux_node,

        sim_gps_handler_node,
        imu_ned2enu_node,

        joystick_driver_node])






    