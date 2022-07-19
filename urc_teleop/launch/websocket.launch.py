import launch
import launch_ros.actions


def generate_launch_description():

    # Initializes the websocket
    rosbridge_server_node = launch_ros.actions.Node(
        package="rosbridge_server",
        name="rosbridge_server",
        executable="rosbridge_websocket.py",
        parameters=[
            {"port": 9090}
        ]
    )

    # Adds /rosapi/topics_and_raw_types to ROS2 (required for Foxglove Studio)
    ros_api_node = launch_ros.actions.Node(
        package="rosapi",
        name="rosapi",
        executable="rosapi_node",
        parameters=[]
    )

    return launch.LaunchDescription([
        rosbridge_server_node,
        ros_api_node
    ])
