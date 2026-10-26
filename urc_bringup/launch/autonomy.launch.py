import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    pkg_urc_perception = get_package_share_directory("urc_perception")
    pkg_trajectory_following = get_package_share_directory("urc_trajectory_following")
    pkg_path_planning = get_package_share_directory("urc_path_planning")

    traversability_config = os.path.join(
        pkg_urc_perception, "config", "traversability_params.yaml"
    )
    trajectory_config = os.path.join(
        pkg_trajectory_following, "config", "pure_pursuit_config.yaml"
    )
    planner_config = os.path.join(pkg_path_planning, "config", "planner_params.yaml")

    use_sim_time_arg = DeclareLaunchArgument(
        "use_sim_time",
        default_value="false",
        description="Use the simulation clock (set by sim.launch.py)",
    )
    trajectory_controller_arg = DeclareLaunchArgument(
        "trajectory_controller",
        default_value="pure_pursuit",
        description="Path-following controller: pure_pursuit or lqr",
    )
    controller = {"trajectory_controller": LaunchConfiguration("trajectory_controller")}
    sim_time = {
        "use_sim_time": ParameterValue(LaunchConfiguration("use_sim_time"), value_type=bool)
    }

    state_machine_node = Node(
        package="urc_state_machine",
        executable="urc_state_machine_NavCoordinator",
        name="nav_coordinator",
        parameters=[sim_time],
        output="screen",
    )

    path_planning_node = Node(
        package="urc_path_planning",
        executable="urc_path_planning_PlannerServer",
        name="planner_server",
        parameters=[planner_config, sim_time],
        output="screen",
    )

    trajectory_following_node = Node(
        package="urc_trajectory_following",
        executable="urc_trajectory_following_FollowerActionServer",
        name="follower_action_server",
        parameters=[trajectory_config, sim_time, controller],
        output="screen",
    )

    traversability_mapping_node = Node(
        package="urc_perception",
        executable="urc_perception_TraversabilityMapping",
        name="traversability_mapping",
        parameters=[traversability_config, sim_time],
        output="screen",
    )

    grid_map_visualization_node = Node(
        package="grid_map_visualization",
        executable="grid_map_visualization",
        name="grid_map_visualization",
        output="screen",
        parameters=[traversability_config, sim_time],
    )

    return LaunchDescription(
        [
            use_sim_time_arg,
            trajectory_controller_arg,
            state_machine_node,
            path_planning_node,
            trajectory_following_node,
            traversability_mapping_node,
            grid_map_visualization_node
        ]
    )
