from http.server import executable
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():

    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")


    

    # todo: make this a launch parameter
    world_path = os.path.join(pkg_urc_gazebo, "urdf/worlds/flat_world.world")

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

    control = Node(
            package='urc_gazebo',
            executable='urc_gazebo_Control',
            output='screen',
            parameters=[
                parameters_file_path
            ]
        )

    magnetometer = Node(
                package='urc_gazebo',
                executable='urc_gazebo_Magnetometer',
                output='screen',
                parameters=[
                   parameters_file_path
                ]
            )
    ground_truth = Node(
            package='urc_gazebo',
            executable='urc_gazebo_GroundTruth',
            output='screen',
            parameters=[
                parameters_file_path
            ]
        )

    sim_color_detector = Node(
            package='urc_gazebo',
            executable='urc_gazebo_SimColorDetector',
            output='screen',
            parameters=[
                parameters_file_path
            ]
        )
        
    return LaunchDescription([
        gazebo,
        scan_to_pointcloud
        #control
        #magnetometer
        #ground_truth
        #sim_color_detector  
    ])
