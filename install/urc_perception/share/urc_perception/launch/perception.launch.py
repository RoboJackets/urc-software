from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import SetRemap
from launch_ros.substitutions import FindPackageShare
from launch.actions import IncludeLaunchDescription, GroupAction
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    aruco = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [
                PathJoinSubstitution(
                    [
                        FindPackageShare("aruco_ros"),
                        "launch",
                        "marker_publisher.launch.py",
                    ]
                )
            ]
        ),
    )

    realsense = GroupAction(
        actions=[
            SetRemap(src="/camera/depth/color/points", dst="/depth_camera/points"),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    [
                        PathJoinSubstitution(
                            [
                                FindPackageShare("realsense2_camera"),
                                "launch",
                                "rs_launch.py",
                            ]
                        )
                    ]
                ),
                launch_arguments={"pointcloud.enable": "True"}.items(),
            ),
        ]
    )

    return LaunchDescription(
        [
            realsense,
            aruco,
        ]
    )
