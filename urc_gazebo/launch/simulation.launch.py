from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():

    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")
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

    control = Node(
            package='urc_gazebo',
            executable='urc_gazebo_Control',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_gazebo'), 'config',
                                     'control_params.yaml'])
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

    ground_truth = Node(
           package='urc_gazebo',
           executable='urc_gazebo_GroundTruth',
           output='screen'
       )
       
    monkey = Node(
           package='urc_gazebo',
           executable='urc_gazebo_Monkey',
           output='screen'
       )

    # sim_color_detector = Node(
    #        package='urc_gazebo',
    #        executable='urc_gazebo_SimColorDetector',
    #        output='screen',
    #        parameters=[
    #            PathJoinSubstitution([FindPackageShare('urc_gazebo'), 'config',
    #                                 'sim_color_detector_params.yaml'])
    #        ]
    #    )

    return LaunchDescription([
        gazebo,
        wallii,
        control,
        ground_truth,
        monkey
        # sim_color_detector
    ])
