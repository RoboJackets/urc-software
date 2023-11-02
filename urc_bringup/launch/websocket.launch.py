from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    rosbridge_server_node = Node(
        package="rosbridge_server",
        name="rosbridge_server",
        executable="rosbridge_websocket.py",
        parameters=[{
            "port" : 9090
        }]
    )

    return LaunchDescription([rosbridge_server_node])

