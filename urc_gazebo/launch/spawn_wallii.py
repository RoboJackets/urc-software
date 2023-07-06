from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess, RegisterEventHandler
from launch.event_handlers import (OnProcessStart, OnProcessExit)
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import Command, LaunchConfiguration, TextSubstitution
import os
from xacro import process_file
from tempfile import NamedTemporaryFile

#Wallii_ArmV3
#wallii.xacro
def generate_launch_description():
    urdf_path = 'urdf/wallii.xacro'
    xacro_file = os.path.join(get_package_share_directory('urc_gazebo'), urdf_path)
    assert os.path.exists(xacro_file), "urdf path doesnt exist in "+str(xacro_file)
    
    with open(xacro_file, "r") as file:
    	urdf_content = file.read()
    
    robot_description_config = process_file(xacro_file)
    robot_desc = robot_description_config.toxml()
   
    # Explanation for this convoluted logic/text replacement:
    # To load files in ros2, nodes like the ones used in moveit2 need to use paths relative to a package 
    # they are located in. However, the spawn_entity.py script needs the absolute file path to load
    # model files, which causes issues when trying to load the two together. Thus, this text replacement
    # gets rid of that issue by processing the xacro/urdf file and adding the absolute file path as a
    # replacement string for the relative path that nodes within moveit2 use.
    # If there is a more elegant way to solve this issue, please bring it up and try to implement it
    # in your workspace. Elegant methods would NOT involve directly modifying the source code of
    # either the moveit robot model loader or spawn_entity.py...
   
    replacement_pattern = "package://urc_gazebo"
    new_pattern = get_package_share_directory('urc_gazebo')
    
    robot_desc = robot_desc.replace(replacement_pattern, new_pattern)
    
    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'wallii', '-x', '0', '-y', '0', '-z', '0.3', '-topic', '/robot_description']
    )
    
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[
            {"robot_description": robot_desc}],
        output='screen'
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

    gorilla_grip = ExecuteProcess(
    	cmd=['ros2','control', 'load_controller', '--set-state',
    		'active', 'gripper_controller'],
    	output='screen'
    )
    
    return LaunchDescription([
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
