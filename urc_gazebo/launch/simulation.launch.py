# from http.server import executable <----- commented out for flake8
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os
import xacro


def generate_launch_description():

    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")

    # todo: make this a launch parameter
    world_path = os.path.join(pkg_urc_gazebo, "urdf/worlds/flat_world.world")
	
    xacro_file = os.path.join(get_package_share_directory('urc_gazebo'),'urdf/','08-macroed.urdf.xacro')
    assert os.path.exists(xacro_file), "08-macroed.urdf.xacro doesnt exist in "+str(xacro_file)

    robot_description_config = xacro.process_file(xacro_file)
    robot_desc = robot_description_config.toxml()
    
    #print(robot_desc)

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gazebo.launch.py'),
        ),
        launch_arguments={"world": world_path}.items()
    )

    parameters_file_path = os.path.join(get_package_share_directory(
        'urc_gazebo'), 'config', 'urc_gazebo_params.yaml')

    scan_to_pointcloud = Node(
            package='urc_gazebo',
            executable='urc_gazebo_ScanToPointCloud',
            output='screen',
            parameters=[
                parameters_file_path
            ]
        )
        
    spawn_robot = Node(
    	    package='urc_gazebo',
    	    executable='spawn_wallii.py',
    	    arguments=[robot_desc],
    	    output='screen'
    
        )
    #robot_state_publisher = Node(
    #	    package='robot_state_publisher',
    #	    executable='robot_state_publisher',
    #       name='robot_state_publisher',
    #	    parameters=[
    #	    	{"robot_description": robot_desc}],
    #	    output='screen'
    #    )

    # control = Node(
    #        package='urc_gazebo',
    #        executable='urc_gazebo_Control',
    #        output='screen',
    #        parameters=[
    #            parameters_file_path
    #        ]
    #    )

    # magnetometer = Node(
    #            package='urc_gazebo',
    #            executable='urc_gazebo_Magnetometer',
    #            output='screen',
    #            parameters=[
    #               parameters_file_path
    #            ]
    #        )

    # ground_truth = Node(
    #        package='urc_gazebo',
    #        executable='urc_gazebo_GroundTruth',
    #        output='screen',
    #        parameters=[
    #            parameters_file_path
    #        ]
    #    )

    # sim_color_detector = Node(
    #        package='urc_gazebo',
    #        executable='urc_gazebo_SimColorDetector',
    #        output='screen',
    #        parameters=[
    #            parameters_file_path
    #        ]
    #    )

    return LaunchDescription([
        gazebo,
        scan_to_pointcloud,
        spawn_robot,
        #robot_state_publisher
        # control
        # magnetometer
        # ground_truth
        # sim_color_detector
    ])
