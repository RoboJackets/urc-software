## Resources
- Intro, use with Gazebo: https://www.youtube.com/watch?v=4QKsDf1c4hc
- Hardware after Simulation: https://www.youtube.com/watch?v=4VVrTCnxvSw

## Input
- Command Velocity

### ros2_control Component
Consists of three main components:
- Diff Drive Controller
- Controller Manager (connects the controllers and hardware-abstraction sides of the ros2_control framewor)
- Hardware Interface (are used by ROS control in conjunction with one of the available ROS controllers to send (hardware_interface::RobotHW::write) commands to the hardware and receive (hardware_interface::RobotHW::read) states from the robot's resources (joints, sensors, actuators))
<br></br>
**Diagram:**

![ROS2_Control_Diagram](https://control.ros.org/master/_images/components_architecture.png "ROS2 Control Diagram")

- Diff Drive controller converts command velocities into req. motor velocities 
- Hardware interface converts abstract wheel velocity into motor hardware commands
- Controller manager links these two together
- Joint state broadcaster uses encoder position state from hardware interface to publish to /joint_states to the robot state publisher (update wheel positions)
- Resource manager is just the bridge between the controller manager and the hardware interface.

### Action Steps
- We want to use our own hardware interface (can use a common one)
- Install packages
    `sudo apt install ros-humble-ros2-control ros-humble-ros2-controllers ros-humble-gazebo-ros2-control`

### XACRO Configuration
- We need to have two different plugins, one for the real robot and another for gazebo


# Instructions for Starting ROS2 Control (for now, requires commenting out the arm version)
1. Start the simulation with `ros2 launch urc_gazebo simulation.launch.py`
2. (Optional) Check the available hardware interfaces with `ros2 control list_hardware_interfaces` (will allow you to see the fake hardware interfaces provided by ROS2 Control to be used on the simulation rover)
3. Start the controller manager for diff_cont: `ros2 run controller_manager spawner diff_cont` to connect between the fake simulation hardware and the controls (keyboard and controller)
4. Start the controller manager for joint_broad: `ros2 run controller_manager spawner joint_broad` (doing the same for the joint broadcaster instead of the diff drive controller)
5. Start the teleop_twist_keyboard node and remap topics: `ros2 run teleop_twist_keyboard teleop_twist_keyboard  --ros-args -r /cmd_vel:=/diff_cont/cmd_vel_unstamped` (should allow you to publish twist messages - angle and velocity - to diff_cont/cmd_vel_unstamped).
6. (Optional) If you want to confirm that messages are being correctly published to `/diff_cont/cmd_vel_unstamped`, then run `ros2 topic echo /diff_cont/cmd_vel_unstamped`
7. Press keys on the keyboard WITHIN the terminal that you started `teleop_twist_keyboard` in order to control the rover in Gazebo

# Using a Joystick
- Use the same set of instructions, until and including step 4.
- Run `sudo modprobe xpad` for controller setup.
- Run `ros2 launch teleop_twist_joy teleop-launch.py joy_config:='xbox'` to get the controller listener running.
- Then, run `ros2 run teleop_twist_joy teleop_node --ros-args -r  /cmd_vel:=/diff_cont/cmd_vel_unstamped` to convert /joy messages to /cmd_vel and remap to the proper topic
- Use the controller bumpers to move the rover
**We need better controls than this, we need to redo the controller listener.**

