from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node, SetRemap
from launch_ros.substitutions import FindPackageShare
 

def generate_launch_description():

    use_yolo = LaunchConfiguration("use_yolo")
    yolo_model = LaunchConfiguration("yolo_model")
    yolo_image_topic = LaunchConfiguration("yolo_image_topic")

    args = [
        DeclareLaunchArgument("use_yolo", default_value="true"),
        DeclareLaunchArgument("yolo_model", default_value=""),
        DeclareLaunchArgument("yolo_image_topic", default_value="/camera/color/image_raw")
    ]

    aruco = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [
                PathJoinSubstitution(
                    [
                        FindPackageShare("aruco_ros"),
                        "launch",
                        "marker_publisher.launch.py",
                    ]
                )
            ]
        ),
    )

    realsense = GroupAction(
        actions=[
            SetRemap(src="/camera/depth/color/points", dst="/depth_camera/points"),
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(
                    [
                        PathJoinSubstitution(
                            [
                                FindPackageShare("realsense2_camera"),
                                "launch",
                                "rs_launch.py",
                            ]
                        )
                    ]
                ),
                launch_arguments={"pointcloud.enable": "True"}.items(),
            ),
        ]
    )

    yolo = Node(
        package="urc_perception",
        executable="yolo_detector_node.py",
        name="yolo_detector",
        output="screen",
        condition=IfCondition(use_yolo),

        parameters=[{
            "model": yolo_model,
            "image_topic": yolo_image_topic,
            "detections_topic": "/yolo/detections",
            "annotated_topic": "/yolo/annotated",
            "publish_annotated": True,
            "confidence_threshold": 0.40,
            "iou_threshold": 0.45,
            "image_size": 640,
            "max_detections": 50,
            "device": "0",
            "half": True,
        }],
    )

    return LaunchDescription(
        [
            realsense,
            aruco,
            yolo
        ]
    )
