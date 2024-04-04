from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():

    aruco_detector_node = Node(
        package="urc_perception",
        executable="urc_perception_ArucoDetector",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_perception"),
                    "config",
                    "aruco_detector_params.yaml",
                ]
            )
        ],
        remappings=[("/aruco_detector/aruco_detection", "/aruco_detection")],
    )

    aruco_location_node = Node(
        package="urc_perception",
        executable="urc_perception_ArucoLocation",
        output="screen",
        remappings=[("/aruco_location/aruco_location", "/aruco_location")],
    )

    depth_laserscan_node = Node(
        package="urc_perception",
        executable="urc_perception_DepthLaserScan",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_perception"),
                    "config",
                    "depth_laserscan_params.yaml",
                ]
            )
        ],
        remappings=[],
    )

    costmap_generator_node = Node(
        package="urc_perception",
        executable="urc_perception_CostmapGenerator",
        output="screen",
        parameters=[],
        remappings=[],
    )

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

    realsense = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [
                PathJoinSubstitution(
                    [FindPackageShare("realsense2_camera"), "launch", "rs_launch.py"]
                )
            ]
        ),
    )

    return LaunchDescription(
        [
            aruco_detector_node,
            aruco_location_node,
            depth_laserscan_node,
            costmap_generator_node,
            realsense,
            aruco,
        ]
    )
