import launch
import launch_ros.actions
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():

    multiclass_segmentation_node = launch_ros.actions.Node(
        package="urc_perception",
        name="multiclass_segmentation",
        executable="multiclass_segmentation.py",
        output="screen",
        parameters=[
            PathJoinSubstitution([FindPackageShare('urc_perception'), 'config',
                                     'multiclass_segmentation_params.yaml'])
        ]
    )

    return launch.LaunchDescription([
        multiclass_segmentation_node
    ])
