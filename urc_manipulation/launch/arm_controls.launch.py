import os

from launch import LaunchDescription

from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node

from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

from moveit_configs_utils import MoveItConfigsBuilder

# Note: Joint Trajectory controllers are initialized in simulation.launch.py
# The same goes for the Joint State Broadcaster.


def generate_launch_description():
    arm_moveit_pkg_path = get_package_share_directory("urc_arm_moveit_config")

    moveit_config = (
        MoveItConfigsBuilder("urc_arm")
        .robot_description(file_path="config/walli_arm.urdf.xacro")
        .robot_description_semantic(file_path="config/walli_arm.srdf")
        .trajectory_execution(file_path="config/moveit_controllers.yaml")
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .planning_scene_monitor(
            publish_robot_description=True, publish_robot_description_semantic=True
        )
        .planning_pipelines(pipelines=["ompl"])
        .to_moveit_configs()
    )

    # Get parameters for the Servo node
    servo_yaml = os.path.join(
        arm_moveit_pkg_path, "/config/walli_arm_simulated_config.yaml"
    )
    servo_params = {"moveit_servo": servo_yaml}

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
                # check if child frame id and base link are correct
                parameters=[
                    {"child_frame_id": "/leftgripper", "frame_id": "/arm_base_link"}
                ],
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

    # Standalone arm control node. Could be necessary if servo runs on different PC
    arm_controls_node = Node(
        package="urc_manipulation",
        executable="servo_node_main",
        output="screen",
        parameters=[
            servo_params,
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
        ],
    )

    return LaunchDescription([arm_controls_node, container])
