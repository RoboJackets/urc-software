from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration, Command
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os
import yaml
import launch_ros
import launch


def generate_launch_description():

    pkg_urc_bringup = FindPackageShare("urc_bringup").find("urc_bringup")
    pkg_urc_navigation = FindPackageShare("urc_navigation").find("urc_navigation")

    world_path = os.path.join(pkg_urc_bringup, 'world/world.sdf')
    default_model_path = os.path.join(get_package_share_directory('urc_hw_description'), "urdf/robot.xacro")

    hardware_config_file_dir = os.path.join(pkg_urc_bringup, 'config', 'hardware_config.yaml')
    with open(hardware_config_file_dir) as f:
        hardware_config = yaml.safe_load(f)
    use_simulation = hardware_config['hardware_config']['use_simulation']

    controller_config_file_dir = os.path.join(
        pkg_urc_bringup, 'config', 'ros2_control_walli.yaml'
    )

    default_rviz_config_path = os.path.join(
        pkg_urc_bringup, 'rviz/urdf_config.rviz'
    )

    # gazebo = IncludeLaunchDescription(
    #     PythonLaunchDescriptionSource(
    #         os.path.join(pkg_gazebo_ros, 'launch', 'gazebo.launch.py'),
    #     ),
    #     launch_arguments={"world": world_path}.items()
    # )

    navigation_nodes = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_navigation, "launch", "navigation.launch.py")
        )
    )

    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[controller_config_file_dir],
        output="both",
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
                PathJoinSubstitution([
                    FindPackageShare('urc_perception'),
                    'config', 'aruco_detector_params.yaml'])
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
        arguments=['-entity', 'walli',
                   '-x', '0', '-y', '0', '-z', '0.4',
                   '-R', '0', '-P', '0', '-Y', '0',
                   '-topic', '/robot_description'],
        output='screen'
    )
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[
            # {"use_sim_time": LaunchConfiguration('use_sim_time')},
            {"robot_description": Command(
                ['xacro ', LaunchConfiguration('model')])}],
        output='screen'
    )
    joint_state_publisher_node = launch_ros.actions.Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        condition=launch.conditions.UnlessCondition(LaunchConfiguration('gui'))
    )
    joint_state_publisher_gui_node = launch_ros.actions.Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        condition=launch.conditions.IfCondition(LaunchConfiguration('gui'))
    )

    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', LaunchConfiguration('rvizconfig')],
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

    joystick_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [
                FindPackageShare("urc_platform"),
                "/launch/joystick.launch.py"
            ]
        )
    )
    if use_simulation:
        print("USING SIMULATION MODE")
        return LaunchDescription([
            DeclareLaunchArgument(
                name='rvizconfig',
                default_value=default_rviz_config_path,
                description='Absolute path to rviz config file'
            ),
            DeclareLaunchArgument(
                name='model',
                default_value=default_model_path,
                description='Absolute path to robot urdf file'
            ),
            DeclareLaunchArgument(
                name='use_sim_time',
                default_value='True',
                description='Flag to enable use_sim_time'
            ),
            DeclareLaunchArgument(
                name='gui',
                default_value='True',
                description='Flag to enable joint_state_publisher_gui'
            ),
            ExecuteProcess(cmd=[
                'gazebo', '--verbose', '-s',
                'libgazebo_ros_init.so', '-s',
                'libgazebo_ros_factory.so', world_path
                ],
                output='screen'
            ),

            enable_color,
            # gazebo,
            robot_state_publisher_node,
            joint_state_publisher_node,
            joint_state_publisher_gui_node,
            load_drivetrain_controller,
            spawn_robot,
            rviz_node,
            navigation_nodes
        ])
    else:
        return LaunchDescription([
            robot_state_publisher_node,
            control_node,
            load_joint_state_broadcaster,
            load_drivetrain_controller,
            aruco_detector,
            aruco_location,
            joystick_launch
        ])
