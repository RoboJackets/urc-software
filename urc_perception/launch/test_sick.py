from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    sick_node = Node(
        package = "sick_scan_xd",
        executable = "sick_generic_caller",
        parameters = [
            {
                "hostname": "192.168.1.10",
                "scanner_type": "sick_multiscan",
                "publish_frame_id": "lidar_link",
                "tf_base_frame_id": "lidar_link",
                "publish_laserscan_segment_topic": "scan_segment",
                "publish_laserscan_fullframe_topic": "scan_fullframe",
                "custom_pointclouds": "cloud_unstructured_fullframe",
                "verbose_level": 0,
                "cloud_unstructured_fullframe": (
                    "coordinateNotation=0 updateMethod=0 echos=0,1,2 "
                    "layers=1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 "
                    "reflectors=0,1 infringed=0,1 rangeFilter=0.05,999,1 "
                    "topic=/scan/points frameid=lidar_link publish=1"
                )
            }
        ],
        output = "screen",
    )

    return LaunchDescription([
        sick_node,
    ])

