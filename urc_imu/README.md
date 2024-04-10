# URC IMU
This node is responsible for transmitting serial IMU messages over the ROS2 network.

[config/imu_serial_driver.yaml](config/imu_serial_driver.yaml) defines the configuration for the serial driver.  
[launch/imu_serial_driver.launch.py](launch/imu_serial_driver.launch.py) is the launch file for the serial driver node.  
[src/driver.py](src/driver.py) defines the main serial driver.  
[src/parser.py](src/parser.py) helps to driver by parsing serial information.  
[src/nodes/imu_serial_driver.py](src/nodes/imu_serial_driver.py) is the source of the rospy serial driver node.  