# from http.server import executable <----- commented out for flake8
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import yaml


def generate_launch_description():

    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")

    # todo: make this a launch parameter
    world_path = os.path.join(pkg_urc_gazebo, "urdf/worlds/flat_world.world")

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gazebo.launch.py'),
        ),
        launch_arguments={"world": world_path}.items()
    )

    wallii = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_gazebo, "launch", "spawn_wallii.py")
        )
    )

    parameters_file_path = os.path.join(get_package_share_directory(
        'urc_gazebo'), 'config', 'urc_gazebo_params.yaml')
    with open(parameters_file_path, 'r') as file:
        scan_to_pointcloud_params = yaml.safe_load(file)['scan_to_pointcloud']['ros_parameters']

    scan_to_pointcloud = Node(
            package='urc_gazebo',
            executable='urc_gazebo_ScanToPointCloud',
            output='screen',
            parameters=[
                scan_to_pointcloud_params
            ],
            remappings=[
                ("/scan_to_pointcloud/pc2", "/pc2"),
                ("/scan_to_pointcloud/scan", "/scan")
            ]
        )

    control = Node(
            package='urc_gazebo',
            executable='urc_gazebo_Control',
            output='screen',
            parameters=[
                parameters_file_path
            ],
            remappings=[
                ("/control/right_wheel_shock_controller/command",
                    "/right_wheel_shock_controller/command"),
                ("/control/left_wheel_shock_controller/command",
                    "/left_wheel_shock_controller/command"),

                ("/control/right_wheel_effort_controller/command",
                    "/right_wheel_effort_controller/command"),
                ("/control/left_wheel_effort_controller/command",
                    "/left_wheel_effort_controller/command"),

                ("/control/robot_enabled", "/robot_enabled"),
                ("/control/encoders", "/encoders"),
                ("/control/motors", "/motors"),
                ("/control/joint_states", "/joint_states")
            ]
        )

    # magnetometer = Node(
    #            package='urc_gazebo',
    #            executable='urc_gazebo_Magnetometer',
    #            output='screen',
    #            parameters=[
    #               parameters_file_path
    #            ]
    #        )

    # ground_truth = Node(
    #        package='urc_gazebo',
    #        executable='urc_gazebo_GroundTruth',
    #        output='screen',
    #        parameters=[
    #            parameters_file_path
    #        ]
    #    )

    # sim_color_detector = Node(
    #        package='urc_gazebo',
    #        executable='urc_gazebo_SimColorDetector',
    #        output='screen',
    #        parameters=[
    #            parameters_file_path
    #        ]
    #    )

    return LaunchDescription([
        gazebo,
        wallii,
        scan_to_pointcloud,
        control
        # magnetometer
        # ground_truth
        # sim_color_detector
    ])
