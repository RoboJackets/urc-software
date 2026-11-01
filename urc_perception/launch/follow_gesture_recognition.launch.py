from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    model_path = LaunchConfiguration("model_path")
    image_topic = LaunchConfiguration("image_topic")
    action_name = LaunchConfiguration("action_name")
    config_file = PathJoinSubstitution(
        [
            FindPackageShare("urc_perception"),
            "config",
            "follow_gesture_recognition.yaml",
        ]
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "model_path",
                description="Absolute path to the YOLO pose ONNX model",
            ),
            DeclareLaunchArgument(
                "image_topic",
                default_value="/camera/camera/color/image_raw",
                description="RealSense color image topic",
            ),
            DeclareLaunchArgument(
                "action_name",
                default_value="recognize_follow_gesture",
                description="Follow-gesture recognition action name",
            ),
            DeclareLaunchArgument(
                "use_sim_time",
                default_value="false",
                description="Use the same ROS clock as the camera and mission coordinator",
            ),
            Node(
                package="urc_perception",
                executable="follow_gesture_recognition",
                name="follow_gesture_recognition",
                output="screen",
                additional_env={"YOLO_AUTOINSTALL": "false"},
                parameters=[
                    config_file,
                    {
                        "model_path": model_path,
                        "image_topic": image_topic,
                        "action_name": action_name,
                        "use_sim_time": ParameterValue(
                            LaunchConfiguration("use_sim_time"), value_type=bool
                        ),
                    },
                ],
            ),
        ]
    )
