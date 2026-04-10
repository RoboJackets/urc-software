import os
from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():
    pkg_urc_perception = get_package_share_directory("urc_perception")
    pkg_trajectory_following = get_package_share_directory("trajectory_following")

    traversability_config = os.path.join(pkg_urc_perception, "config", "traversability_params.yaml")
    trajectory_config = os.path.join(pkg_trajectory_following, "config", "pure_pursuit.yaml")

    state_machine_node = Node(
        package="nav_testing",
        executable="nav_testing_NavCoordinator",
        name="nav_coordinator",
        output="screen",
    )

    path_planning_node = Node(
        package="path_planning",
        executable="path_planning_PlannerServer",
        name="planner_server",
        output="screen",
    )

    trajectory_following_node = Node(
        package="trajectory_following",
        executable="trajectory_following_FollowerActionServer",
        name="follower_action_server",
        parameters=[trajectory_config],
        output="screen",
    )

    traversability_mapping_node = Node(
        package="urc_perception",
        executable="urc_perception_TraversabilityMapping",
        name="traversability_mapping",
        parameters=[traversability_config],
        output="screen",
    )

    grid_map_visualization_node = Node(
        package="grid_map_visualization",
        executable="grid_map_visualization",
        name="grid_map_visualization",
        output="screen",
        parameters=[traversability_config],
    )

    return LaunchDescription(
        [
            state_machine_node,
            path_planning_node,
            trajectory_following_node,
            traversability_mapping_node,
            grid_map_visualization_node
        ]
    )
