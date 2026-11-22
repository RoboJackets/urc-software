import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node


def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")

    world_path = os.path.join(path_urc_hw_description, "world", "empty_world.sdf")

    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py")
        ),
        launch_arguments={
            "gz_args": ["-r ", world_path],
        }.items(),
    )

    aruco_node = Node(
        package="aruco_ros",
        executable="marker_publisher",
        name="aruco_marker_publisher",
        output="screen",
        parameters=[
            {
                "image_is_rectified": False,
                "marker_size": 0.05,
                "reference_frame": "camera_link",
                "camera_frame": "camera_link",
            }
        ],
        remappings=[
            ("/camera_info", "/camera/camera_info"),
            ("/image", "/camera/image_raw"),
        ],
    )

    return LaunchDescription([gz_sim, aruco_node])
