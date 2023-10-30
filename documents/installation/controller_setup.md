# Controller Setup Documentation
- We are using an XBox Series S/X controller as our main controller.

### Setup
Install the controller's driver: `sudo apt install xboxdrv` and restart computer

### Usage
1. Run `sudo modprobe xpad`
Do this every time, if it doesn't show up on the ros2 launch in the next step. Add it it to ~/.bashrc if you want it to happen automatically.
2. Launching the node with `ros2 launch teleop_twist_joy teleop-launch.py joy_config:='xbox'`
3. Use `ros2 topic echo /joy` to get the output of the controller