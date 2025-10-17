import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from xacro import process_file

def generate_launch_description():
    path_ros_gazebo_sim = get_package_share_directory("ros_gz_sim")
    path_urc_hw_description = get_package_share_directory("urc_hw_description")

    sim_world_arg = DeclareLaunchArgument(
        "world",
        default_value = os.path.join(path_urc_hw_description, "world", "leo_world.sdf"),
        description = "Path to gz world file"
    )

    walli_xacro = DeclareLaunchArgument(
        "walli_xacro",
        default_value = os.path.join(path_urc_hw_description, "urdf", "walli.xacro"),
        description = "Path to xacro file"
    )


    world = LaunchConfiguration("world")
    xacro = LaunchConfiguration("walli_xacro")

    robot_urdf_file = process_file(
        os.path.join(path_urc_hw_description, "urdf", "walli.xacro"),
        mappings = {"use_simulation": "true"}
    ).toxml()


    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(path_ros_gazebo_sim, "launch", "gz_sim.launch.py")
        ),
        launch_arguments = {"gz_args": world}.items()
   )

    urdf_path = os.path.join(path_urc_hw_description, "urdf", "walli.urdf")


    spawn = Node(
        package = "ros_gz_sim",
        executable = "create",
        output = "screen",
        arguments = [
            "-name", "walli",
            "-x", "0", "-y", "0", "-z", "0.5",
            "-R", "0", "-P", "0", "-Y", "0",
            "-file", urdf_path,
        ],
   )

    return LaunchDescription([
        sim_world_arg, gz_sim, spawn,
    ])