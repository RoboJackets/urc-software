from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():

    aruco = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [PathJoinSubstitution([FindPackageShare(
                "aruco_ros"), "launch", "marker_publisher.launch.py"])]
        ),
    )

    realsense = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [PathJoinSubstitution([FindPackageShare(
                "realsense2_camera"), "launch", "rs_launch.py"])]
        ),
    )

    return LaunchDescription([
        realsense,
        aruco
    ])