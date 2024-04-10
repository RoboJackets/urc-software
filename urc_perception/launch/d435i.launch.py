from launch import LaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch.actions import IncludeLaunchDescription, GroupAction
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import SetRemap, Node, SetParameter
from launch.launch_description_sources import PythonLaunchDescriptionSource


def generate_launch_description():
    realsense = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [
                PathJoinSubstitution(
                    [FindPackageShare("realsense2_camera"), "launch", "rs_launch.py"]
                )
            ],
        ),
        launch_arguments={
            "unite_imu_method": "2",
            "enable_accel": "true",
            "enable_gyro": "true",
        }.items(),
    )

    imu_fusion = Node(
        package="imu_complementary_filter", executable="complementary_filter_node"
    )

    return LaunchDescription(
        [
            GroupAction(
                [
                    SetRemap(src="/camera/imu", dst="/imu/data_raw"),
                    realsense,
                ]
            ),
            GroupAction(
                [
                    SetParameter(name="publish_tf", value="true"),
                    imu_fusion,
                ]
            ),
        ]
    )
