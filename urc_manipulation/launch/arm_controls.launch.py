import os
import yaml
from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode
import xacro
from moveit_configs_utils import MoveItConfigsBuilder

#Note: Joint Trajectory controllers are initialized in simulation.launch.py
# The same goes for the Joint State Broadcaster.

def generate_launch_description():
    # Launch as much as possible in components
    container = ComposableNodeContainer(
        name="urc_manipulation_container",
        namespace="/",
        package="rclcpp_components",
        executable="component_container_mt",
        composable_node_descriptions=[
            # Example of launching Servo as a node component
            # Assuming ROS2 intraprocess communications works well, this is a more efficient way.
            # ComposableNode(
            #     package="moveit_servo",
            #     plugin="moveit_servo::ServoServer",
            #     name="servo_server",
            #     parameters=[
            #         servo_params,
            #         moveit_config.robot_description,
            #         moveit_config.robot_description_semantic,
            #     ],
            # ),
            ComposableNode(
                package="tf2_ros",
                plugin="tf2_ros::StaticTransformBroadcasterNode",
                name="static_tf2_broadcaster",
                #check if child frame id and base link are correct
                parameters=[{"child_frame_id": "/claw", "frame_id": "/base_link"}],
            ),
            ComposableNode(
                package="urc_manipulation",
                plugin="joy_to_servo_pub::JoyToServoPub",
                name="controller_to_servo_node",
            ),
            ComposableNode(
                package="joy",
                plugin="joy::Joy",
                name="joy_node",
            ),
        ],
        output="screen",
    )
    
    #Standalone arm control node. Could be necessary if servo runs on different PC
    arm_controls_node = Node(
            package='urc_manipulation',
            executable='urc_manipulation_JoyToServoPub',
            output='screen',
            parameters=[
                PathJoinSubstitution([FindPackageShare('urc_manipulation'), 'config',
                                     'joy_to_servo_pub_params.yaml'])
            ],
            remappings=[]
        )

    return LaunchDescription([
        arm_controls_node,
        container
    ])
