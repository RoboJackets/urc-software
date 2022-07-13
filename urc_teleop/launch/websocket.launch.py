import launch
import launch_ros.actions

def generate_launch_description():
    rosbridge_server_node = launch_ros.actions.Node(
        package="rosbridge_server",
        name="rosbridge",
        executable="rosbridge_websocket.py",
        parameters=[
            {"port" : 8080}
        ]
    )

    return launch.LaunchDescription([
        rosbridge_server_node
    ])