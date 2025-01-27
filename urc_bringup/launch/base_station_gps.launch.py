import os
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch import LaunchDescription


def generate_launch_description():
    pkg_urc_localization = get_package_share_directory("urc_localization")
    pkg_ublox_gps = get_package_share_directory("ublox_gps")

    base_station_gps_config = os.path.join(
        pkg_urc_localization, "config", "base_station_gps.yaml"
    )

    temp_gps_config = os.path.join(pkg_ublox_gps, "config", "zed_f9p.yaml")

    base_station_gps_node = Node(
        package="ublox_gps",
        executable="ublox_gps_node",
        name="ublox_gps_node_base_station",
        output="screen",
        parameters=[
            # temp_gps_config,
            base_station_gps_config,
            # {"sv_in": {"reset": True, "min_dur": 60, "acc_lim": 3.0}},
        ],
    )

    return LaunchDescription([base_station_gps_node])
