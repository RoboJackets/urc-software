from launch import LaunchDescription
from launch.substitutions import (
    Command,
    FindExecutable,
    PathJoinSubstitution,
)
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from launch_ros.parameter_descriptions import ParameterValue  # ADDED THIS LINE


def generate_launch_description():
    
    # Declare arguments
    declared_arguments = []

    # Build the URDF with command line xacro.
    # We also pass parameters for the system_interface here.
    robot_description_content = Command(
        [
            PathJoinSubstitution([FindExecutable(name="xacro")]),
            " ",
            PathJoinSubstitution(
                [
                    FindPackageShare("cartesian_controller_simulation"),
                    "urdf",
                    "arm_mujoco.urdf.xacro",
                ]
            ),
            " ",
            "mujoco_model:=",
            PathJoinSubstitution(
                [
                    FindPackageShare("cartesian_controller_simulation"),
                    "etc",
                    "arm2.xml",
                ]
            ),
        ]
    )
    
    # CHANGED THIS LINE:
    robot_description = {
        "robot_description": ParameterValue(robot_description_content, value_type=str)
    }

    # Controller configuration
    robot_controllers = PathJoinSubstitution(
        [
            FindPackageShare("cartesian_controller_simulation"),
            "config",
            "controller_manager_arm.yaml",
        ]
    )
    
    # RViz configuration
    rviz_config_file = PathJoinSubstitution(
        [FindPackageShare("cartesian_controller_simulation"), "etc", "arm_robot.rviz"]
    )

    # Nodes
    control_node = Node(
        package="controller_manager",
        executable="ros2_control_node",
        parameters=[robot_description, robot_controllers],
        output="both",
        remappings=[
            ("~/robot_description", "/robot_description"),
            ("motion_control_handle/target_frame", "target_frame"),
            ("cartesian_motion_controller/target_frame", "target_frame"),
        ],
    )

    # Convenience function for easy spawner construction
    def controller_spawner(name, *args):
        return Node(
            package="controller_manager",
            executable="spawner",
            output="screen",
            arguments=[name] + [a for a in args],
        )

    
   # Active controllers
    active_list = [
        "joint_state_broadcaster",
    ]
    active_spawners = [controller_spawner(controller) for controller in active_list]

    # Inactive controllers
    inactive_list = [
        "cartesian_motion_controller",
        "motion_control_handle",
        "joint_trajectory_controller",
        "invalid_cartesian_compliance_controller",
        "invalid_cartesian_force_controller",
    ]
    state = "--inactive"
    inactive_spawners = [
        controller_spawner(controller, state) for controller in inactive_list
    ]

    # TF tree
    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="both",
        parameters=[robot_description],
    )

    # Visualization
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

    # Nodes to start
    nodes = (
        [control_node, robot_state_publisher, rviz]
        + active_spawners
        + inactive_spawners
    )

    return LaunchDescription(declared_arguments + nodes)