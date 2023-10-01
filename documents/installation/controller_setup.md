1. Set Up the XBox Driver
```
sudo apt install xboxdrv
```
- Restart your computer
```
sudo modprobe xpad
```

2. Launching the correct node
```
ros2 launch teleop_twist_joy teleop-launch.py joy_config:='xbox'
```