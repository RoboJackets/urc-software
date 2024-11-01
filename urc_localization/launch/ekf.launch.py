from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
import launch_ros.actions
import os
from launch.actions import (
    RegisterEventHandler
)
from launch.event_handlers import OnProcessStart


def generate_launch_description():
    
    ekf = launch_ros.actions.Node(
                package="robot_localization",
                executable="navsat_transform_node",
                name="navsat_transform_node",
                output="screen",
                parameters=[
                    os.path.join(
                        get_package_share_directory("robot_localization"),
                        "params",
                        "navsat_transform.yaml",
                    )
                ],
                remappings=[
                    ("gps/fix", "/gps/data"),
                    ("/imu", "/imu/data"),
                ],
            )

    navsat = launch_ros.actions.Node(
                package="robot_localization",
                executable="ekf_node",
                name="ekf_filter_node",
                output="screen",
                parameters=[
                    os.path.join(
                        get_package_share_directory("robot_localization"),
                        "config",
                        "ekf.yaml",
                    )
                ],
            )
    
    return LaunchDescription(
        [
          RegisterEventHandler(
              event_handler = OnProcessStart(
                    target_action = navsat,
                    on_start=[ekf]

              )
          ),
          #ekf,
          navsat  
            
        ]
    )
