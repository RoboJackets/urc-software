from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.actions import ExecuteProcess, RegisterEventHandler
from launch_ros.actions import Node
from launch.event_handlers import OnProcessExit
from ament_index_python.packages import get_package_share_directory
import os
from xacro import process_file


def generate_launch_description():
    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")
    pkg_urc_bringup = get_package_share_directory("urc_bringup")
    controller_config_file_dir = os.path.join(
        pkg_urc_bringup,
        'config', 'controller_config.yaml'
    )
    world_path = os.path.join(pkg_urc_gazebo, "urdf/worlds/urc_world.world")
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    'config', 'controller_config.yaml'

    xacro_file = os.path.join(
        get_package_share_directory('urc_hw_description'),
        "urdf/walli.xacro"
    )
    assert os.path.exists(
        xacro_file), "urdf path doesnt exist in " + str(xacro_file)

    robot_description_config = process_file(xacro_file)
    robot_desc = robot_description_config.toxml()

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gazebo.launch.py'),
        ),
        launch_arguments={"world": world_path}.items()
    )
    enable_color = SetEnvironmentVariable(
        name="RCUTILS_COLORIZED_OUTPUT",
        value="1"
    )

    aruco_detector = Node(
        package='urc_perception',
        executable='urc_perception_ArucoDetector',
        output='screen',
        parameters=[
                PathJoinSubstitution([FindPackageShare('urc_perception'), 'config',
                                     'aruco_detector_params.yaml'])
        ],
        remappings=[
            ("/aruco_detector/aruco_detection", "/aruco_detection")
        ]
    )

    aruco_location = Node(
        package='urc_perception',
        executable='urc_perception_ArucoLocation',
        output='screen',
        remappings=[
                ("/aruco_location/aruco_location", "/aruco_location")
        ]
    )

    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'walli', '-x', '0', '-y', '0', '-z', '0.3',
                   '-topic', '/robot_description']
    )

    load_robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[
            {"use_sim_time": use_sim_time},
            {"robot_description": robot_desc}
        ],
        output='screen'
    )

    robot_localization_node = Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_filter_node',
        output='screen',
        parameters=[
            os.path.join(
                pkg_urc_gazebo, 'config/ekf.yaml'),
            {'use_sim_time': LaunchConfiguration('use_sim_time')}
        ]
    )

    load_joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            '-p', controller_config_file_dir,
            'joint_state_broadcaster'
        ],
    )

    load_drivetrain_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=[
            'rover_drivetrain_controller'
        ],
    )

    return LaunchDescription([
        RegisterEventHandler(
            event_handler=OnProcessExit(
                target_action=spawn_robot,
                on_exit=[
                    load_joint_state_broadcaster,
                    load_drivetrain_controller,
                    #  load_rover_drivetrain_controller,
                    # robot_localization_node,
                    aruco_detector,
                    aruco_location,
                ],
            )
        ),
        enable_color,
        gazebo,
        load_robot_state_publisher,
        spawn_robot
    ])
