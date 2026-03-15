import os
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    RegisterEventHandler,
)
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import (
    Command,
    FindExecutable,
    LaunchConfiguration,
    PathJoinSubstitution,
)
from launch_ros.descriptions import ParameterValue
from launch_ros.parameter_descriptions import ParameterValue as RosParameterValue
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_bringup = get_package_share_directory("urc_bringup")

    controller_config_file_dir = os.path.join(
        get_package_share_directory("cartesian_controller_simulation"),
        "config",
        "controller_manager_arm.yaml"
    )

    sim_world_arg = DeclareLaunchArgument(
        "world",
        default_value="marsyard2020.sdf",
        description="Name of the world file (not full path)",
    )

    bridge_yaml = DeclareLaunchArgument(
        "bridge_yaml",
        default_value=os.path.join(path_urc_bringup, "config", "sim_config.yaml"),
        description="bridge YAML config",
    )

    # --- Arm URDF from cartesian_controller_simulation ---
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [
                    FindPackageShare("cartesian_controller_simulation"),
                    "urdf",
                    "arm_gazebo.urdf.xacro",
                ]
            ),
        ]
    )

    robot_description = {
        "robot_description": RosParameterValue(
            robot_description_content, value_type=str
        )
    }

    # --- Gazebo sim ---
    path_urc_hw_description = get_package_share_directory("urc_hw_description")
    world_filename = LaunchConfiguration("world")
    world_path = PathJoinSubstitution(
        [path_urc_hw_description, "world", world_filename]
    )

    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py")
        ),
        launch_arguments={"gz_args": [world_path, " -r"]}.items(),
    )

    bridge = Node(
        package="ros_gz_bridge",
        executable="parameter_bridge",
        name="ros_gz_bridge",
        output="screen",
        parameters=[{"config_file": LaunchConfiguration("bridge_yaml")}],
    )

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        parameters=[robot_description],
        output="screen",
    )

    # --- Spawn arm in Gazebo ---
    spawn = Node(
        package="ros_gz_sim",
        executable="create",
        output="screen",
        arguments=[
            "-name", "arm",
            "-x", "-20",
            "-y", "-15",
            "-z", "1.5",
            "-R", "0",
            "-P", "0",
            "-Y", "0",
            "-topic", "robot_description",
        ],
    )

    # --- RViz ---
    rviz_config = PathJoinSubstitution(
        [FindPackageShare("cartesian_controller_simulation"), "etc", "arm_robot.rviz"]
    )
    rviz = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="log",
        arguments=["-d", rviz_config],
    )

    # --- Controller Spawners ---
    def controller_spawner(name, *args):
        return Node(
            package="controller_manager",
            executable="spawner",
            output="screen",
            arguments=[name, "--param-file", controller_config_file_dir]
            + [a for a in args],
        )

    load_joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        output="screen",
        arguments=["joint_state_broadcaster"],
    )

    load_cartesian_motion_controller = Node(
    package="controller_manager",
    executable="spawner",
    output="screen",
    arguments=["cartesian_motion_controller", "--param-file", controller_config_file_dir],
    remappings=[
        ("/cartesian_motion_controller/target_frame", "/motion_control_handle/target_frame")
    ],
)

   # Inactive cartesian controllers
    
    inactive_list = [
        "motion_control_handle",
        "joint_trajectory_controller",
    ]

    inactive_spawners = [
        controller_spawner(controller, "--inactive") for controller in inactive_list
    ]

    relay = Node(
        package="topic_tools",
        executable="relay",
        name="target_frame_relay",
        arguments=[
            "/motion_control_handle/target_frame",
            "/cartesian_motion_controller/target_frame"
        ],
        output="screen",
    )


    return LaunchDescription(
        [
            sim_world_arg,
            bridge_yaml,
            gz_sim,
            bridge,
            robot_state_publisher_node,
            rviz,
            relay,
            spawn,
            # Start joint_state_broadcaster AFTER robot spawn
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=spawn,
                    on_exit=[load_joint_state_broadcaster],
                )
            ),
            # Start cartesian controllers AFTER joint_state_broadcaster
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=load_joint_state_broadcaster,
                    on_exit=inactive_spawners + [load_cartesian_motion_controller],
                )
            ),
        ]
    )