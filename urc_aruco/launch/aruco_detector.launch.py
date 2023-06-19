from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    aruco_detector_node = Node(
            package='urc_aruco',
            executable='urc_aruco_ArucoDetector',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_aruco'), 'config',
                                     'aruco_detector_params.yaml'])
            ],
            remappings=[
                ("/aruco_detector/aruco_detection", "/aruco_detection")
            ]
        )

    aruco_location_node = Node(
            package='urc_aruco',
            executable='urc_aruco_ArucoLocation',
            output='screen',
            # No parameters exist for this node, so we do not need to use it.
            # parameters=[
            #    PathJoinSubstitution([FindPackageShare('urc_aruco'), 'config',
            #                         'aruco_location_params.yaml'])
            # ],
            remappings=[
                ("/aruco_location/aruco_location", "/aruco_location")
            ]
            )

    return LaunchDescription([
        aruco_detector_node,
        aruco_location_node
    ])
