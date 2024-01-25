import os
import xacro

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch.actions import (IncludeLaunchDescription, DeclareLaunchArgument, EmitEvent, ExecuteProcess,
                            LogInfo, RegisterEventHandler, TimerAction)
from launch.conditions import IfCondition
from launch.event_handlers import (OnExecutionComplete, OnProcessExit,
                                OnProcessIO, OnProcessStart, OnShutdown)
from launch.events import Shutdown
from launch.substitutions import (EnvironmentVariable, FindExecutable,
                                LaunchConfiguration, LocalSubstitution,
                                PythonExpression)


def generate_launch_description():

    pkg_pathfinder = get_package_share_directory('urc_navigation')
    pkg_hw_description = get_package_share_directory('urc_hw_description')
    nav2_bringup = os.path.join(get_package_share_directory('nav2_bringup'))
    slam_toolbox = os.path.join(get_package_share_directory('slam_toolbox'))
    
    # Process the URDF xacro file
    xacro_file = os.path.join(pkg_hw_description,'urdf/simplified_model/','simplified_model.xacro')
    urdf = xacro.process_file(xacro_file)
    
    # Include the robot_state_publisher to publish transforms
    rsp_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        output='screen',
        parameters=[{'robot_description': urdf.toxml()}]
    )

    # Include the Gazebo launch file, provided by the gazebo_ros package
    # world = os.path.join(pkg_pathfinder, 'world/', 'world.sdf') 
    #  # Gazebo launch
    # start_gazebo = ExecuteProcess(
    #     cmd=[
    #         'gazebo',
    #         "--verbose",
    #         "-s",
    #         "libgazebo_ros_init.so",
    #         "-s",
    #         "libgazebo_ros_factory.so",
    #         world,
    #     ],
    #     output="screen",
    # )

    # Run the spawner node from the gazebo_ros package to spawn the robot in the simulation
    spawn_entity_node = Node(
                package='gazebo_ros', 
                executable='spawn_entity.py',
                output='screen',
                arguments=['-topic', 'robot_description',   # The the robot description is published by the rsp node on the /robot_description topic
                           '-entity', 'pathfinder'],        # The name of the entity to spawn (doesn't matter if you only have one robot)
    )

    # Load SLAM parameters from yaml file and add node to launch description
    # slam_params_file = os.path.join(pkg_pathfinder,'params', 'mapper_params_online_async.yaml')
    # slam = IncludeLaunchDescription(
    #             PythonLaunchDescriptionSource([os.path.join(slam_toolbox,'launch','online_async_launch.py')]), 
    #             launch_arguments={'slam_params_file': slam_params_file}.items()
    # )

    # Load nav2 parameters from yaml file and add nav2 bringup to launch description
    nav2_params_file = os.path.join(pkg_pathfinder, 'config/', 'nav2_params.yaml')
    nav2 = IncludeLaunchDescription(
                PythonLaunchDescriptionSource([os.path.join(nav2_bringup,'launch','navigation_launch.py')]),
                launch_arguments={'params_file': nav2_params_file}.items()
    )

    # Delay the launch of nav2 by 5 seconds to give the SLAM node time to initialize and publish the map
    delayed_nav2_launch = TimerAction(
                period=8.0,
                actions=[nav2])

    # Load explore_lite parameters from yaml file and add node to launch description
    # explore_params_file = os.path.join(pkg_pathfinder, 'params', 'explore_params.yaml')
    # frontier_explore_node = Node(
    #             package='explore_lite',
    #             executable='explore',
    #             output='screen',
    #             parameters=[explore_params_file]
    # )

    # Launch RViz to vizualize the robot and the map in real time
    # rviz_config_file = os.path.join(pkg_pathfinder, 'rviz', 'view_nav2_slam.rviz')
    # rviz2_node = Node(
    #             package='rviz2',
    #             executable='rviz2',
    #             output="screen",
    #             arguments=[
    #                 '-d', rviz_config_file,
    #             ],
    # )
    
    # delayed_rviz2_launch = TimerAction(
    #             period=10.0,
    #             actions=[rviz2_node])

    

    # Launch everything!
    return LaunchDescription([
        DeclareLaunchArgument(
          'use_sim_time',
          default_value='true',
          description='Use simulation/Gazebo clock'
        ),
        rsp_node,
        # start_gazebo,
        # RegisterEventHandler(
        #     OnProcessStart(
        #         target_action=start_gazebo,
        #         on_start=[
        #             LogInfo(msg='Starting Gazebo & spawning robot...'),
        #             TimerAction(
        #                 period=5.0,
        #                 actions=[spawn_entity_node],
        #             ),
        #         ]
        #     )
        # ),
        # RegisterEventHandler(
        #     OnProcessExit(
        #         target_action=spawn_entity_node,
        #         on_exit=[
        #             LogInfo(msg='Robot spawned, starting SLAM...'),
        #             slam
        #         ]
        #     )
        # ),
        delayed_nav2_launch,
        # delayed_rviz2_launch,
        # frontier_explore_node # Uncomment this line to enable the explore_lite node to start mapping the environment
    ])