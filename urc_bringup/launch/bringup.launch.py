import os
from xacro import process_file
import yaml
from launch import LaunchDescription
from launch.actions import GroupAction, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node, SetRemap
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource


def load_yaml(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)

    try:
        with open(absolute_file_path, "r") as file:
            return yaml.safe_load(file)
    except EnvironmentError:  # parent of IOError, OSError *and* WindowsError
        return None


def generate_launch_description():
    pkg_urc_bringup = get_package_share_directory("urc_bringup")
    pkg_urc_platform = get_package_share_directory("urc_platform")
    pkg_urc_localization = get_package_share_directory("urc_localization")

    pkg_ublox_dgnss = get_package_share_directory("ublox_dgnss")

    controller_config_file_dir = os.path.join(
        pkg_urc_bringup, "config", "controller_config.yaml"
    )
    twist_mux_config = os.path.join(pkg_urc_platform, "config", "twist_mux.yaml")
    use_sim_time = LaunchConfiguration("use_sim_time", default="true")

    xacro_file = os.path.join(
        get_package_share_directory("urc_hw_description"), "urdf/walli.xacro"
    )
    assert os.path.exists(xacro_file), "urdf path doesnt exist in " + str(xacro_file)
    robot_description_config = process_file(
        xacro_file, mappings={"use_simulation": "false"}
    )
    robot_desc = robot_description_config.toxml()

    heartbeat_node = Node(
        package="urc_bringup",
        executable="urc_bringup_HeartbeatPublisher",
        parameters=[{"heartbeatInterval": 1000}],
    )

    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[controller_config_file_dir, {"robot_description": robot_desc}],
        output="both",
    )

    load_robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        parameters=[
            {"use_sim_time": use_sim_time, "robot_description": robot_desc},
        ],
        output="screen",
    )

    load_joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "joint_state_broadcaster"],
    )

    load_drivetrain_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["rover_drivetrain_controller"],
    )

    load_status_light_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "status_light_controller"],
    )

    twist_mux_node = Node(
        package="urc_platform",
        executable="urc_platform_TwistMux",
        name="twist_mux",
        parameters=[twist_mux_config],
    )

    launch_gps = GroupAction(
        actions=[
            SetRemap(src="/rover/fix", dst="/gps/data"),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    os.path.join(
                        pkg_ublox_dgnss, "launch", "ublox_fb+r_rover.launch.py"
                    )
                ),
                launch_arguments={"device_serial_string": "rover"}.items(),
            ),
        ]
    )

    vectornav_node = Node(
        package="vectornav",
        executable="vectornav",
        output="screen",
        parameters=[os.path.join(pkg_urc_bringup, "config", "vectornav_imu.yaml")],
        remappings=[("/vectornav/imu", "/imu/data")],
    )

    vectornav_sensor_msg_node = Node(
        package="vectornav",
        executable="vn_sensor_msgs",
        output="screen",
        parameters=[os.path.join(pkg_urc_bringup, "config", "vectornav_imu.yaml")],
        remappings=[("/vectornav/imu", "/imu/data")],
    )

    launch_ekf = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_localization, "launch", "ekf.launch.py")
        )
    )

    rosbridge_server_node = Node(
        package="rosbridge_server",
        name="rosbridge_server",
        executable="rosbridge_websocket.py",
        parameters=[{"port": 9090}],
    )

    return LaunchDescription(
        [
            IncludeLaunchDescription(
                XMLLaunchDescriptionSource(
                    [
                        FindPackageShare("foxglove_bridge"),
                        "/launch",
                        "/foxglove_bridge_launch.xml",
                    ]
                ),
                launch_arguments={"port": "8765"}.items(),
            ),
            control_node,
            load_robot_state_publisher,
            load_joint_state_broadcaster,
            load_drivetrain_controller,
            load_status_light_controller,
            twist_mux_node,
            launch_gps,
            rosbridge_server_node,
            launch_ekf,
            vectornav_node,
            vectornav_sensor_msg_node,
            heartbeat_node,
        ]
    )
