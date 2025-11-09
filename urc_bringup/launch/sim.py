import os
from tempfile import NamedTemporaryFile
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, Command
from launch_ros.descriptions import ParameterValue
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from xacro import process_file

def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")
    path_urc_bringup = get_package_share_directory("urc_bringup")

    sim_world_arg = DeclareLaunchArgument(
        "world",
        default_value = os.path.join(path_urc_hw_description, "world", "leo_world.sdf"),
        description = "Path to gz world file"
    )

    walli_xacro = DeclareLaunchArgument(
        "walli_xacro",
        default_value = os.path.join(path_urc_hw_description, "urdf/simplified_swerve", "simplified_swerve.urdf.xacro"),
        description = "Path to xacro file"
    )

    bridge_yaml = DeclareLaunchArgument(
        "bridge_yaml",
        default_value = os.path.join(path_urc_bringup, "config", "sim_config.yaml"),
        description = "bridge YAML config"
    )

    world = LaunchConfiguration("world")
    walli_xacro_config = LaunchConfiguration("walli_xacro")

    '''
    robot_urdf_file = process_file(
        ParameterValue(walli_xacro_config, value_type = str),
        mappings = {"use_sim": "true"}
    ).toxml()
    '''
    robot_urdf_file = ParameterValue(
        Command(
            [
                "xacro ",
                walli_xacro_config,
                " use_sim:=",
                "true",
            ]
        ),
        value_type=str,
    )



    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py")
        ),
        launch_arguments = {"gz_args": world}.items()
   )

    bridge = Node(
        package = "ros_gz_bridge",
        executable = "parameter_bridge",
        name = "ros_gz_bridge",
        output = "screen",
        parameters = [{"config_file": LaunchConfiguration("bridge_yaml")}]
    )

    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        parameters=[
            {
                "robot_description": robot_urdf_file
            }
        ],
        output="screen",
    )

    orientation_pose_bridge = Node(
        package="urc_bringup",
        executable="urc_bringup_OrientationPoseBridge",
        name="orientation_pose_bridge",
        parameters=[
            {
                "tf_topic": "/tf",
                "orientation_topic": "/orientation",
            }
        ],
        output="screen",
    )

    spawn = Node(
        package = "ros_gz_sim",
        executable = "create",
        output = "screen",
        arguments = [
            "-name", "walli",
            "-x", "0", "-y", "0", "-z", "0.5",
            "-R", "1.57", "-P", "0", "-Y", "1.57",
            "-topic", "robot_description"
        ],
   )


    return LaunchDescription([
        sim_world_arg, walli_xacro, gz_sim, spawn, bridge_yaml, bridge, robot_state_publisher_node, orientation_pose_bridge
    ])
