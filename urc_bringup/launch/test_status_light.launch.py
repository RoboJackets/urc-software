import os
from xacro import process_file
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.actions import IncludeLaunchDescription, RegisterEventHandler
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.event_handlers import OnProcessExit


def generate_launch_description():
    pkg_urc_bringup = get_package_share_directory("urc_bringup")

    controller_config_file_dir = os.path.join(
        pkg_urc_bringup, "config", "controller_config.yaml"
    )
    xacro_file = os.path.join(
        get_package_share_directory("urc_hw_description"), "urdf/walli.xacro"
    )
    assert os.path.exists(xacro_file), "urdf path doesnt exist in " + str(xacro_file)
    robot_description_config = process_file(
        xacro_file, mappings={"use_simulation": "false"}
    )
    robot_desc = robot_description_config.toxml()

    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[controller_config_file_dir, {"robot_description": robot_desc}],
        output="both",
    )

    load_status_light_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "status_light_controller"],
    )

    bt_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_bringup, "launch", "bt.launch.py")
        )
    )

    return LaunchDescription(
        [
            control_node,
            load_status_light_controller,
            RegisterEventHandler(
                event_handler=OnProcessExit(
                    target_action=load_status_light_controller,
                    on_exit=[bt_launch],
                )
            ),
        ]
    )
