import os
import xacro

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


# Get the robot description
urdf_path = os.path.join(get_package_share_directory(
    'urc_hw_description'), 'urdf', 'wallii.urdf')
urdf_doc = xacro.parse(open(urdf_path, 'r'))
xacro.process_doc(urdf_doc)
robot_description = urdf_doc.toxml()

robot_controller_config = os.path.join(get_package_share_directory(
    'urc_hw_description'), 'config', 'urc_hw_config.yaml')
control_node = Node(
    package="controller_manager",
    executable="ros2_control_node",
    parameters=[{'robot_description': robot_description},
                robot_controller_config],
    remappings=[
    ],
    output="both",
)

imu_broadcaster_spawner = Node(
    package="controller_manager",
    executable="spawner",
    arguments=["imu_state_broadcaster",
               "--controller-manager", "/controller_manager"]
)

rover_drivetrain_controller = Node(
    package="controller_manager",
    executable="spawner",
    arguments=["rover_drivetrain_controller",
               "--controller-manager", "/controller_manager"]
)

bms_broadcaster_spawner = Node(
    package="controller_manager",
    executable="spawner",
    arguments=["bms_broadcaster",
               "--controller-manager", "/controller_manager"]
)

status_light_controller = Node(
    package="controller_manager",
    executable="spawner",
    arguments=["status_light_controller",
               "--controller-manager", "/controller_manager"]
)


joystick_launch = IncludeLaunchDescription(
    PythonLaunchDescriptionSource(
        [
            FindPackageShare("urc_platform"),
            "/launch/joystick.launch.py"
        ]
    )
)


def generate_launch_description():
    # Get the launch configuration
    return LaunchDescription([
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='false',
            description='Use simulation (Gazebo) clock if true'),
        control_node,
        rover_drivetrain_controller,
        # imu_broadcaster_spawner,
        bms_broadcaster_spawner,
        status_light_controller,

        joystick_launch
    ])
