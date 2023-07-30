from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess, RegisterEventHandler, DeclareLaunchArgument
from launch.event_handlers import OnProcessExit
from ament_index_python.packages import get_package_share_directory
import os
from xacro import process_file
import launch
import launch_ros
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    urdf_path = 'urdf/walli.xacro'
    xacro_file = os.path.join(get_package_share_directory('urc_gazebo'), urdf_path)
    assert os.path.exists(xacro_file), "urdf path doesnt exist in "+str(xacro_file)
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')

    pkg_share = launch_ros.substitutions.FindPackageShare(package='urc_gazebo').find('urc_gazebo')
    default_model_path = os.path.join(pkg_share, 'urdf/walli.xacro')
    default_rviz_config_path = os.path.join(pkg_share, 'config/rviz_config.rviz')

    robot_description_config = process_file(xacro_file)
    robot_desc = robot_description_config.toxml()

    # Explanation for this convoluted logic/text replacement:
    # To load files in ros2, nodes like the ones used in moveit2
    # need to use paths relative to a package they are located in.
    # However, the spawn_entity.py script needs the absolute file
    # path to load model files, which causes issues when trying to
    # load the two together. Thus, this text replacement gets rid
    # of that issue by processing the xacro/urdf file and adding
    # the absolute file path as a replacement string for the
    # relative path that nodes within moveit2 use.

    # If there is a more elegant way to solve this issue, please
    # bring it up and try to implement it in your workspace.
    # Elegant methods would NOT involve directly modifying the
    # source code of either the moveit robot model loader or spawn_entity.py...

    replacement_pattern = "package://urc_gazebo"
    new_pattern = get_package_share_directory('urc_gazebo')
    robot_desc = robot_desc.replace(replacement_pattern, new_pattern)

    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=['-entity', 'walli', '-x', '0', '-y', '0', '-z', '0.3',
                   '-topic', '/robot_description']
    )
    robot_state_publisher_node = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[
            {"robot_description": robot_desc},
            {"use_sim_time": use_sim_time}
        ],
        output='screen'
    )
    joint_state_publisher_node = Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
        name='joint_state_publisher',
        condition=launch.conditions.UnlessCondition(LaunchConfiguration('gui')),
        parameters=[{"use_sim_time": use_sim_time}]
    )
    joint_state_publisher_gui_node = Node(
        package='joint_state_publisher_gui',
        executable='joint_state_publisher_gui',
        name='joint_state_publisher_gui',
        condition=launch.conditions.IfCondition(LaunchConfiguration('gui')),
        parameters=[{"use_sim_time": use_sim_time}]
    )
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        output='screen',
        arguments=['-d', LaunchConfiguration('rvizconfig')],
        parameters=[{"use_sim_time": use_sim_time}]
    )
    robot_localization_node = launch_ros.actions.Node(
        package='robot_localization',
        executable='ekf_node',
        name='ekf_filter_node',
        output='screen',
        parameters=[os.path.join(pkg_share, 'config/ekf.yaml'),
                    {'use_sim_time': LaunchConfiguration('use_sim_time')}
                    ]
    )

    load_joint_state_controller = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state', 'active',
             'joint_state_broadcaster'],
        output='screen'
    )

    load_joint_trajectory_controller = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state',
             'active', 'arm_controller'],
        output='screen'
    )

    gorilla_grip = ExecuteProcess(
        cmd=['ros2', 'control', 'load_controller', '--set-state',
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


        DeclareLaunchArgument(name='gui',
                              default_value='True',
                              description='Flag to enable joint_state_publisher_gui'),
        DeclareLaunchArgument(name='model',
                              default_value=default_model_path,
                              description='Absolute path to robot urdf file'),
        DeclareLaunchArgument(name='rvizconfig',
                              default_value=default_rviz_config_path,
                              description='Absolute path to rviz config file'),
        DeclareLaunchArgument(name='use_sim_time',
                              default_value='True',
                              description='Flag to enable use_sim_time'),
        robot_state_publisher_node,
        joint_state_publisher_node,
        joint_state_publisher_gui_node,
        rviz_node,
        robot_localization_node,
        spawn_robot,
    ])
