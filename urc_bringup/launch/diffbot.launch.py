from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.actions import SetEnvironmentVariable
from launch.actions import DeclareLaunchArgument
from launch.actions import RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.substitutions import LaunchConfiguration, Command, FindExecutable
from launch.substitutions import PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os
import yaml

def generate_launch_description():

    # Package Imports
    pkg_urc_bringup = FindPackageShare(
        "urc_bringup").find("urc_bringup")
    pkg_urc_navigation = FindPackageShare(
        "urc_navigation").find("urc_navigation")
    pkg_urc_hw_description = FindPackageShare(
        "urc_hw_description").find("urc_hw_description")
    pkg_urc_platform = FindPackageShare(
        "urc_platform").find("urc_platform")

    # Configurations
    world_path = os.path.join(pkg_urc_hw_description, "world/world.sdf")

    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [FindPackageShare("urc_hw_description"), "urdf", "diffbot", "robot.urdf.xacro"]
            ),
        ]
    )

    hardware_config_filepath = os.path.join(
        pkg_urc_bringup, 'config', 'hardware_config.yaml')
    with open(hardware_config_filepath) as f:
        hardware_config = yaml.safe_load(f)

    use_simulation = hardware_config['hardware_config']['use_simulation']

    robot_controllers_config = os.path.join(
        pkg_urc_bringup, 'config', 'ros2_control_diffbot.yaml'
    )

    default_rviz_config_path = os.path.join(
        pkg_urc_bringup, 'rviz', 'urdf_config.rviz'
    )

    enable_color = SetEnvironmentVariable(
        name="RCUTILS_COLORIZED_OUTPUT",
        value="1"
    )

    # Other Launch Scripts Pulled In
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [PathJoinSubstitution([FindPackageShare(
                "gazebo_ros"), "launch", "gazebo.launch.py"])]
        ),
        launch_arguments={"verbose": "false", "world": world_path}.items()
    )

    launch_navigation = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_navigation, "launch", "navigation.launch.py")
        )
    )

    # Nodes
    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[robot_controllers_config],
        output="both",
    )

    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'robot',
                   '-topic', 'robot_description'],
        output='screen'
    )

    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{"robot_description": robot_description_content}],
        output='screen'
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
        arguments=["joint_broad"],
    )

    load_drivetrain_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=['diff_cont'],
    )

    joystick_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [
                FindPackageShare("urc_platform"),
                "/launch/diffbot_joy.launch.py"
            ]
        )
    )

    twist_mux_params = os.path.join(pkg_urc_bringup,'config','twist_mux.yaml')
    twist_mux = Node(
            package="twist_mux",
            executable="twist_mux",
            parameters=[twist_mux_params, {'use_sim_time': True}],
            remappings=[('/cmd_vel_out','/diff_cont/cmd_vel_unstamped')]
        )

    # Final Launch Description With or Without Simulation Mode
    if use_simulation:
        return LaunchDescription([
                DeclareLaunchArgument(
                name='rvizconfig',
                default_value=default_rviz_config_path,
                description='Absolute path to rviz config file'
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
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=spawn_robot,
                    on_exit=[
                        load_joint_state_broadcaster,
                        load_drivetrain_controller,
                        rviz_node,
                        joystick_launch,
                        twist_mux
                    ],
                ),
            ),
            gazebo,
            robot_state_publisher_node,
            spawn_robot,
        ])
        # return LaunchDescription([
        #     DeclareLaunchArgument(
        #         name='rvizconfig',
        #         default_value=default_rviz_config_path,
        #         description='Absolute path to rviz config file'
        #     ),
        #     DeclareLaunchArgument(
        #         name='use_sim_time',
        #         default_value='True',
        #         description='Flag to enable use_sim_time'
        #     ),
        #     DeclareLaunchArgument(
        #         name='gui',
        #         default_value='True',
        #         description='Flag to enable joint_state_publisher_gui'
        #     ),
        #     enable_color,
        #     gazebo,
        #     robot_state_publisher_node,
        #     spawn_robot,
        #     load_joint_state_broadcaster,
        #     load_drivetrain_controller,
        #     rviz_node,
        #     joystick_launch,
        #     twist_mux,
        # ])
    else:
        return LaunchDescription([
            robot_state_publisher_node,
            control_node,
            load_joint_state_broadcaster,
            load_drivetrain_controller,
            joystick_launch
        ])
