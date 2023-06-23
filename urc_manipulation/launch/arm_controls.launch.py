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
    arm_moveit_pkg_path = get_package_share_directory("urc_arm_moveit_config")
    
    moveit_config = (
        MoveItConfigsBuilder("urc_arm")
        .robot_description(file_path="config/WalliiArmV3.urdf.xacro")
        .to_moveit_configs()
    )

    # Get parameters for the Servo node
    servo_yaml = os.path.join(arm_moveit_pkg_path, "/config/WalliiArmV3_simulated_config.yaml")
    servo_params = {"wallii_servo": servo_yaml}
    
    
    #TODO Check if this ros2 control node is necessary
    # ros2_control using FakeSystem as hardware
    ros2_controllers_path = os.path.join(
        get_package_share_directory("urc_arm_moveit_config"),
        "config",
        "ros2_controllers.yaml",
    )
    ros2_control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[moveit_config.robot_description, ros2_controllers_path],
        output="screen",
    )

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
            #replace with urc manipulation arm control node
            ComposableNode(
                package="urc_manipulation",
                plugin="urc_manipulation::JoyToServoPub",
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
        ros2_control_node,
        arm_controls_node,
        container
    ])
