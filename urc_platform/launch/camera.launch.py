from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    # this node should produce both a uncompressed and compressed version of the image
    # pub topics:
    # ~<camera_name>/image_raw
    # ~<camera_name>/image_raw/compressed
    camera_node = Node(
            package='usb_cam',
            executable='usb_cam_node',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_platform'), 'config',
                                     'camera.yaml'])
            ]
        )

    return LaunchDescription([
        camera_node
    ])
