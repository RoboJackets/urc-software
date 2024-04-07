import os
from xacro import process_file
import yaml
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.actions import SetEnvironmentVariable, RegisterEventHandler
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory


def load_yaml(package_name, file_path):
    package_path = get_package_share_directory(package_name)
    absolute_file_path = os.path.join(package_path, file_path)

    try:
        with open(absolute_file_path, "r") as file:
            return yaml.safe_load(file)
    except EnvironmentError:  # parent of IOError, OSError *and* WindowsError
        return None


def generate_launch_description():
    pkg_gazebo_ros = get_package_share_directory("gazebo_ros")
    pkg_urc_gazebo = get_package_share_directory("urc_gazebo")
    pkg_urc_bringup = get_package_share_directory("urc_bringup")
    pkg_nmea_navsat_driver = FindPackageShare("nmea_navsat_driver").find(
        "nmea_navsat_driver"
    )

    hardware_config_file_dir = os.path.join(
        pkg_urc_bringup, "config", "hardware_config.yaml"
    )
    with open(hardware_config_file_dir) as f:
        hardware_config = yaml.safe_load(f)
    use_simulation = hardware_config["hardware_config"]["use_simulation"]

    controller_config_file_dir = os.path.join(
        pkg_urc_bringup, "config", "ros2_control_walli.yaml"
    )
    world_path = os.path.join(pkg_urc_gazebo, "urdf/worlds/urc_world.world")
    use_sim_time = LaunchConfiguration("use_sim_time", default="true")

    xacro_file = os.path.join(
        get_package_share_directory("urc_hw_description"), "urdf/walli.xacro"
    )
    assert os.path.exists(xacro_file), "urdf path doesnt exist in " + str(xacro_file)
    robot_description_config = process_file(xacro_file)
    robot_desc = robot_description_config.toxml()

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, "launch", "gazebo.launch.py"),
        ),
        launch_arguments={"use_sim_time": "true", "world": world_path}.items(),
    )
    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[controller_config_file_dir, {"robot_description": robot_desc}],
        output="both",
    )
    enable_color = SetEnvironmentVariable(name="RCUTILS_COLORIZED_OUTPUT", value="1")

    spawn_robot = Node(
        package="gazebo_ros",
        executable="spawn_entity.py",
        arguments=[
            "-entity",
            "walli",
            "-x",
            "0",
            "-y",
            "0",
            "-z",
            "5",
            "-R",
            "0",
            "-P",
            "0",
            "-Y",
            "0",
            "-topic",
            "robot_description",
        ],
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

    load_arm_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "arm_controller"],
    )

    load_gripper_controller_left = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "gripper_controller_left"],
    )

    load_gripper_controller_right = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "gripper_controller_right"],
    )

    load_drivetrain_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "rover_drivetrain_controller"],
    )

    teleop_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [FindPackageShare("urc_bringup"), "/launch/teleop.launch.py"]
        )
    )

    launch_gps = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                pkg_nmea_navsat_driver, "launch", "nmea_serial_driver.launch.py"
            )
        )
    )

    rosbridge_server_node = Node(
        package="rosbridge_server",
        name="rosbridge_server",
        executable="rosbridge_websocket.py",
        parameters=[{"port": 9090}],
    )

    joint_state_publisher_gui_node = Node(
        package="joint_state_publisher_gui",
        executable="joint_state_publisher_gui",
        name="joint_state_publisher_gui",
        parameters=[{"use_sim_time": use_sim_time}],
    )

    if use_simulation:
        return LaunchDescription(
            [
                RegisterEventHandler(
                    event_handler=OnProcessExit(
                        target_action=spawn_robot,
                        on_exit=[
                            load_joint_state_broadcaster,
                            # load_arm_controller,
                            # load_gripper_controller_left,
                            # load_gripper_controller_right,
                            load_drivetrain_controller,
                            teleop_launch,
                        ],
                    )
                ),
                enable_color,
                gazebo,
                load_robot_state_publisher,
                spawn_robot,
            ]
        )
    else:
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
                load_robot_state_publisher,
                control_node,
                load_joint_state_broadcaster,
                load_drivetrain_controller,
                load_gripper_controller_left,
                load_gripper_controller_right,
                teleop_launch,
                launch_gps,
                rosbridge_server_node,
            ]
        )
