from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
# from launch.substitutions import PathJoinSubstitution
# from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource
# from launch_ros.actions import Node
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

    drone = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_gazebo, "launch", "spawn_drone.py")
        )
    )

    return LaunchDescription([
        gazebo,
        drone,
    ])
