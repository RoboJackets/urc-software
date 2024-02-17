from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder
import os


def generate_launch_description():
    xacro_file = os.path.join(
        get_package_share_directory('urc_hw_description'),
        "urdf/walli.xacro"
    )
    assert os.path.exists(
        xacro_file), "urdf path doesnt exist in " + str(xacro_file)

    moveit_config = MoveItConfigsBuilder(package_name="urc_hw_description",
                                         robot_name="walli").robot_description(
        file_path="urdf/walli.xacro"
    ).robot_description_semantic(
        file_path="config/walli.srdf"
    ).trajectory_execution(
        file_path="config/moveit_controllers.yaml"
    ).joint_limits(
        file_path="config/joint_limits.yaml"
    ).robot_description(
        file_path=xacro_file
    ).pilz_cartesian_limits(
        file_path="config/pilz_cartesian_limits.yaml"
    ).planning_pipelines(
        pipelines=["ompl"]
    ).to_moveit_configs()

    run_move_group_node = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[
            moveit_config.to_dict(),
            {
                "publish_robot_description_semantic": True,
                "publish_planning_scene": True
            }
        ]
    )

    return LaunchDescription([
        run_move_group_node
    ])
