from http.server import executable
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import xacro


def generate_launch_description():
    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")

    world_path = os.path.join(pkg_urc_gazebo, "urdf/worlds/flat_world.world")

    xacro_file = os.path.join(get_package_share_directory('urc_gazebo'),'urdf/','wallii.xacro')
    assert os.path.exists(xacro_file), "wallii.xacro doesnt exist in "+str(xacro_file)

    robot_description_config = xacro.process_file(xacro_file)
    robot_desc = robot_description_config.toxml()

    spawn_robot = Node(
    	package = 'gazebo_ros',
        executable = 'spawn_entity.py',
        arguments = ['-entity', 'wallii', '-topic', '/robot_description']
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

