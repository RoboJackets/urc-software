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
    pkg_urc_bringup = get_package_share_directory("urc_bringup")
    pkg_imu_driver = FindPackageShare(
        "imu_driver").find("imu_driver")

    hardware_config_file_dir = os.path.join(
        pkg_urc_bringup, "config", "hardware_config.yaml"
    )
    with open(hardware_config_file_dir) as f:
        hardware_config = yaml.safe_load(f)
    use_simulation = hardware_config["hardware_config"]["use_simulation"]

    controller_config_file_dir = os.path.join(
        pkg_urc_bringup, "config", "controller_config.yaml"
    )
    nmea_config_file = os.path.join(
        get_package_share_directory("urc_bringup"),
        "config",
        "nmea_serial_driver.yaml",
    )
    # world_path = os.path.join(pkg_urc_gazebo, "urdf/worlds/urc_world.world")
    use_sim_time = LaunchConfiguration("use_sim_time", default="true")

    xacro_file = os.path.join(
        get_package_share_directory("urc_hw_description"), "urdf/walli.xacro"
    )
    robot_description_config = process_file(xacro_file)
    robot_desc = robot_description_config.toxml()

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, "launch", "gazebo.launch.py"),
        ),
        launch_arguments={"use_sim_time": "true"}.items(),
        # launch_arguments={"world": world_path}.items()
    )
    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[controller_config_file_dir,
                    {"robot_description": robot_desc}],
        output="both",
    )
    enable_color = SetEnvironmentVariable(
        name="RCUTILS_COLORIZED_OUTPUT", value="1")

    aruco_detector = Node(
        package="urc_perception",
        executable="urc_perception_ArucoDetector",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_perception"),
                    "config",
                    "aruco_detector_params.yaml",
                ]
            )
        ],
        remappings=[("/aruco_detector/aruco_detection", "/aruco_detection")],
    )

    aruco_location = Node(
        package="urc_perception",
        executable="urc_perception_ArucoLocation",
        output="screen",
        remappings=[("/aruco_location/aruco_location", "/aruco_location")],
    )

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
            "0.4",
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
        arguments=["-p", controller_config_file_dir,
                   "joint_state_broadcaster"],
    )

    load_arm_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir, "arm_controller"],
    )

    load_gripper_controller_left = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir,
                   "gripper_controller_left"],
    )

    load_gripper_controller_right = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["-p", controller_config_file_dir,
                   "gripper_controller_right"],
    )

    load_drivetrain_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["rover_drivetrain_controller"],
    )

    teleop_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [FindPackageShare("urc_bringup"), "/launch/teleop.launch.py"]
        )
    )
    launch_gps = Node(
        package="nmea_navsat_driver",
        executable="nmea_serial_driver",
        output="screen",
        parameters=[nmea_config_file],
    )

    launch_imu = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_imu_driver, "launch",
                         "imu_serial_driver.launch.py")
        )
    )

    rosbridge_server_node = Node(
        package="rosbridge_server",
        name="rosbridge_server",
        executable="rosbridge_websocket.py",
        parameters=[{"port": 9090}],
    )

    bt_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_urc_bringup, "launch", "bt.launch.py")
        )
    )

    odom_frame_node = Node(
      package="urc_tf",
      executable="urc_tf_WorldFrameBroadcaster",
      output='screen'
    )

    if use_simulation:
        return LaunchDescription(
            [
                RegisterEventHandler(
                    event_handler=OnProcessExit(
                        target_action=spawn_robot,
                        on_exit=[
                            load_joint_state_broadcaster,
                            load_arm_controller,
                            load_gripper_controller_left,
                            load_gripper_controller_right,
                            load_drivetrain_controller,
                            aruco_detector,
                            aruco_location,
                            teleop_launch,
                            bt_launch,
                        ],
                    )
                ),
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
                aruco_detector,
                aruco_location,
                teleop_launch,
                launch_gps,
                launch_imu,
                odom_frame_node,
                rosbridge_server_node
            ])
