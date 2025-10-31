from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution, Command
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch_ros.descriptions import ParameterValue


def generate_launch_description():
    # Get the launch directory
    pkg_urc_hw_desc = get_package_share_directory("urc_hw_description")

    # Declare launch arguments
    urdf_file_arg = DeclareLaunchArgument(
        "urdf_file",
        default_value="simplified_swerve/simplified_swerve.urdf.xacro",
        description="Path to the URDF file",
    )

    use_sim_arg = DeclareLaunchArgument(
        "use_sim",
        default_value="false",
        description="Whether to use simulation-specific features",
    )

    use_ros2_control_arg = DeclareLaunchArgument(
        "use_ros2_control",
        default_value="true",
        description="Whether to include ROS2 control interfaces",
    )

    rviz_config_file_arg = DeclareLaunchArgument(
        "rviz_config_file",
        default_value=PathJoinSubstitution(
            [FindPackageShare("urc_hw_description"), "rviz", "display.rviz"]
        ),
        description="Path to the RViz config file",
    )

    # Get launch configurations
    rviz_config_file = LaunchConfiguration("rviz_config_file")
    use_sim = LaunchConfiguration("use_sim")
    use_ros2_control = LaunchConfiguration("use_ros2_control")

    # Robot state publisher node
    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        parameters=[
            {
                "robot_description": ParameterValue(
                    Command(
                        [
                            "xacro ",
                            PathJoinSubstitution(
                                [
                                    pkg_urc_hw_desc,
                                    "urdf",
                                    LaunchConfiguration("urdf_file"),
                                ]
                            ),
                            " use_sim:=",
                            use_sim,
                            " use_ros2_control:=",
                            use_ros2_control,
                        ]
                    ),
                    value_type=str,
                )
            }
        ],
        output="screen",
    )

    # Joint state publisher node
    joint_state_publisher_node = Node(
        package="joint_state_publisher",
        executable="joint_state_publisher",
        name="joint_state_publisher",
        output="screen",
        parameters=[{"use_sim_time": False}],
    )

    # Joint state publisher GUI node
    joint_state_publisher_gui_node = Node(
        package="joint_state_publisher_gui",
        executable="joint_state_publisher_gui",
        name="joint_state_publisher_gui",
        output="screen",
        parameters=[{"use_sim_time": False}],
    )

    # RViz node
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="screen",
        arguments=["-d", rviz_config_file],
        parameters=[{"use_sim_time": False}],
    )

    return LaunchDescription(
        [
            urdf_file_arg,
            use_sim_arg,
            use_ros2_control_arg,
            rviz_config_file_arg,
            robot_state_publisher_node,
            joint_state_publisher_node,
            joint_state_publisher_gui_node,
            rviz_node,
        ]
    )
