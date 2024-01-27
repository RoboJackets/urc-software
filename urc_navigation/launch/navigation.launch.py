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

    pkg_urc_navigation = get_package_share_directory('urc_navigation')
    pkg_hw_description = get_package_share_directory('urc_hw_description')
    nav2_bringup = os.path.join(get_package_share_directory('nav2_bringup'))
    slam_toolbox = os.path.join(get_package_share_directory('slam_toolbox'))
    
    # Process the URDF xacro file
    xacro_file = os.path.join(pkg_hw_description,'urdf/simplified_model/','simplified_model.xacro')
    urdf = xacro.process_file(xacro_file)

    launch_localization = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_navigation, "launch", "localization.launch.py")
        )
    )

    # Load SLAM parameters from yaml file and add node to launch description
    # slam_params_file = os.path.join(pkg_pathfinder,'params', 'mapper_params_online_async.yaml')
    # slam = IncludeLaunchDescription(
    #             PythonLaunchDescriptionSource([os.path.join(slam_toolbox,'launch','online_async_launch.py')]), 
    #             launch_arguments={'slam_params_file': slam_params_file}.items()
    # )

    # Load nav2 parameters from yaml file and add nav2 bringup to launch description
    nav2_params_file = os.path.join(pkg_urc_navigation, 'config/', 'nav2_params.yaml')
    nav2 = IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    [os.path.join(nav2_bringup,'launch','navigation_launch.py')]
                ),
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

    
        

    # Launch everything!
    return LaunchDescription([
        # slam,
        # delayed_nav2_launch,
        launch_localization
        # delayed_rviz2_launch,
        # frontier_explore_node # Uncomment this line to enable the explore_lite node to start mapping the environment
    ])