## Resources
- Intro, use with Gazebo: https://www.youtube.com/watch?v=4QKsDf1c4hc
- Hardware after Simulation: https://www.youtube.com/watch?v=4VVrTCnxvSw

## Input
- Command Velocity

### ros2_control Component
Consists of three main components:
- Diff Drive Controller
- Controller Manager
- Hardware Interface

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


