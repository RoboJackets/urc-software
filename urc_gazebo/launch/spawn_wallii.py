from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess, RegisterEventHandler
from launch.event_handlers import (OnProcessStart, OnProcessExit)
from ament_index_python.packages import get_package_share_directory
import os
from xacro import process_file
from moveit_configs_utils import MoveItConfigsBuilder

#Wallii_ArmV2
#robot_arm_urdf
def generate_launch_description():
    xacro_file = os.path.join(get_package_share_directory('urc_gazebo'), 'urdf/', 'WalliiArmV3.urdf')
    assert os.path.exists(xacro_file), "wallii.xacro doesnt exist in "+str(xacro_file)

    robot_description_config = process_file(xacro_file)
    robot_desc = robot_description_config.toxml()
    
    arm_moveit_pkg_path = get_package_share_directory("urc_arm_moveit_config")
    
    moveit_config = (
        MoveItConfigsBuilder("urc_arm")
        .robot_description(file_path="config/WalliiArmV3.urdf.xacro")
        .trajectory_execution(file_path="config/moveit_controllers.yaml")
        .robot_description_kinematics(file_path="config/kinematics.yaml")
        .to_moveit_configs()
    )

    # Get parameters for the Servo node
    servo_yaml = os.path.join(arm_moveit_pkg_path, "/config/WalliiArmV3_simulated_config.yaml")
    servo_params = {"wallii_servo": servo_yaml}
    
    
    # ros2_control using real hardware
    #Is this necessary or is this redundant?
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
    
    load_joint_state_controller = ExecuteProcess(
    	cmd=['ros2', 'control', 'load_controller', '--set-state', 'active',
    		'joint_state_broadcaster'],
    	output='screen'
    )
    
    load_joint_trajectory_controller = ExecuteProcess(
    	cmd=['ros2','control', 'load_controller', '--set-state',
    		'active', 'arm_controller'],
    	output='screen'
    )

    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'wallii', '-topic', '/robot_description']
    )
    
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[
            {"robot_description": robot_desc}],
        output='screen'
       )

    return LaunchDescription([
        RegisterEventHandler(
    		event_handler=OnProcessExit(
    			target_action=spawn_robot,
    			on_exit=[ros2_control_node],
    		)
    	),
    	RegisterEventHandler(
    		event_handler=OnProcessExit(
    			target_action=spawn_robot,
    			on_exit=[load_joint_state_controller],
    		)
    	),
    	RegisterEventHandler(
    		event_handler=OnProcessExit(
    			target_action=spawn_robot,
    			on_exit=[load_joint_trajectory_controller],
    		)
    	),
    	
        robot_state_publisher,
        spawn_robot,
        
    ])
