## Rosbridge

Rosbridge allows for communication between ROS2 and non-ROS programs by creating a WebSocket connection that can convert between ROS messages and JSON objects. We use this to remotely publish and subscribe to topics for our teleoperation.

Launch the ROS2 WebSocket with `ros2 launch urc_teleop websocket.launch.py`


## Remote Vision

1. [Install Foxglove Studio here](https://foxglove.dev/download)

2. Launch the ROS2 WebSocket

3. Select open connection

4. Choose *Rosbridge (ROS 1 & 2)* and enter in the WebSocket URL


## Remote Operation

1. Launch the ROS2 WebSocket

2. `cd src/urc_software/urc_teleop/gui`

3. Start a http server with `python3 -m http.server`

4. Navigate to `http://127.0.0.1:8000` in a browser

5. Connect the controller first, then the joystick