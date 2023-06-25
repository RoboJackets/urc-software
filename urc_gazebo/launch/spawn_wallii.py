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

    # ros2_control using real hardware
    #Is this necessary or is this redundant?
    #ros2_controllers_path = os.path.join(
    #    get_package_share_directory("urc_arm_moveit_config"),
    #    "config",
    #    "ros2_controllers.yaml",
    #)
    #ros2_control_node = Node(
    #    package="controller_manager",
    #    executable="ros2_control_node",
    #    parameters=[moveit_config.robot_description, ros2_controllers_path],
    #    output="screen",
    #)
    
    load_joint_state_controller = ExecuteProcess(
    	cmd=['ros2', 'control', 'load_controller', '--set-state', 'active',
    		'joint_state_broadcaster'],
    	output='screen'
    )
    
    load_joint_trajectory_controller = ExecuteProcess(
    	cmd=['ros2','control', 'load_controller', '--set-state',
    		'active', 'joint_trajectory_controller'],
    	output='screen'
    )

    gorilla_grip = ExecuteProcess(
    	cmd=['ros2','control', 'load_controller', '--set-state',
    		'active', 'gripper_controller'],
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
        #ros2_control_node,
    	RegisterEventHandler(
    		event_handler=OnProcessExit(
    			target_action=spawn_robot,
    			on_exit=[load_joint_state_controller],
    		)
    	),
    	RegisterEventHandler(
    		event_handler=OnProcessExit(
    			target_action=load_joint_state_controller,
    			on_exit=[load_joint_trajectory_controller],
    		)
    	),
    	RegisterEventHandler(
    		event_handler=OnProcessExit(
    			target_action=load_joint_state_controller,
    			on_exit=[gorilla_grip],
    		)
    	),
    	
        robot_state_publisher,
        spawn_robot,
        
    ])
