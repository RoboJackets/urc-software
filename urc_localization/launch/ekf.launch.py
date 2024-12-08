from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
import launch_ros.actions
import os
from launch.actions import (
    RegisterEventHandler
)
from launch.event_handlers import OnProcessStart


def generate_launch_description():
    
    ekf_map = launch_ros.actions.Node(
                package="robot_localization",
                executable="ekf_node",
                name="ekf_filter_node_map",
                output="screen",
                parameters=[
                    os.path.join(
                        get_package_share_directory("urc_localization"),
                        "config",
                        "ekf.yaml",
                    )
                ],
                remappings=[
                    ("/odometry/filtered","/odometry/filtered_map")
                ],
            )
    
    ekf_odom = launch_ros.actions.Node(
                package="robot_localization",
                executable="ekf_node",
                name="ekf_filter_node_odom",
                output="screen",
                parameters=[
                    os.path.join(
                        get_package_share_directory("urc_localization"),
                        "config",
                        "ekf.yaml",
                    )
                ],
                remappings=[
                    
                    ("/odometry/filtered","odometry/filtered_twist")
                ],
            )

    navsat = launch_ros.actions.Node(
                package="robot_localization",
                executable="navsat_transform_node",
                name="navsat_transform",
                output="screen",
                parameters=[
                    os.path.join(
                        get_package_share_directory("urc_localization"),
                        "config",
                        "ekf.yaml",
                    )
                ],
                remappings=[
                    ("/imu","/imu/data"),
                    ("/odometry/filtered","/odometry/filtered_map"),
                    ("/gps/fix","/gps/data")
                ]
            )
    
    return LaunchDescription(
        [
          RegisterEventHandler(
              event_handler = OnProcessStart(
                    target_action = navsat,
                    on_start=[ekf_map,ekf_odom]

              )
          ),
          #ekf,
          navsat  
            
        ]
    )
