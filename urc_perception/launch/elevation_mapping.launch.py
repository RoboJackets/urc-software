import launch
import launch_ros.actions
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():

    elevation_mapping_node = launch_ros.actions.Node(
        package="elevation_mapping",
        name="elevation_mapping",
        executable="elevation_mapping",
        output="screen",
        parameters=[
            PathJoinSubstitution([FindPackageShare('urc_perception'),
                                 'config', 'multiclass_segmentation_params.yaml'])
        ]
    )

    return launch.LaunchDescription([
        elevation_mapping_node
    ])