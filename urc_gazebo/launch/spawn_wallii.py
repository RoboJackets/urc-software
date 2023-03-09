from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
from xacro import process_file


def generate_launch_description():
    xacro_file = os.path.join(get_package_share_directory('urc_gazebo'), 'urdf/', 'arm_urdf.urdf')
    assert os.path.exists(xacro_file), "wallii.xacro doesnt exist in "+str(xacro_file)

    robot_description_config = process_file(xacro_file)
    robot_desc = robot_description_config.toxml()

    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'wallii', '-topic', '/robot_description']
    )
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[
            {"robot_description": robot_desc}],
        output='screen'
       )
    return LaunchDescription([
        robot_state_publisher,
        spawn_robot
    ])
