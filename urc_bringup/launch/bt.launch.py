import os
from pathlib import Path
from launch import LaunchDescription
from launch.actions import SetEnvironmentVariable
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    pkg_urc_bringup = get_package_share_directory("urc_bringup")
    path_urc_bt_nodes = os.path.join(
        Path(
            get_package_share_directory("urc_bt_nodes")
        ).parent.parent.absolute(),
        "lib",
        "liburc_bt_nodes.so"
    )
    bt_file_name = "bt_test.xml"

    enable_color = SetEnvironmentVariable(
        name="RCUTILS_COLORIZED_OUTPUT",
        value="1"
    )

    orchestor = Node(
        package="urc_bt",
        executable="urc_bt_orchestor",
        parameters=[{
            "node_lib_dirs": [path_urc_bt_nodes],
            "tree_file_dir": os.path.join(
                pkg_urc_bringup,
                "strategies",
                bt_file_name
            ),
            "tick_rate": 1
        }]
    )

    return LaunchDescription([
        enable_color,
        orchestor
    ])
