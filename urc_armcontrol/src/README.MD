## This urc_armcontrol package contains the logic for controlling the Robonav arm
**Untested on docker, works for wsl / bare metal Ubuntu installation.**

### Instructions to get set up:

Install Mujuco 3.0.0 to /home/[user] (preferred) or /root directory using wget:
```
    cd /home/[user]
    wget https://github.com/google-deepmind/mujoco/releases/download/3.0.0/mujoco-3.0.0-linux-x86_64.tar.gz
```

NOTE: This is a link to the mujuco releases <https://github.com/google-deepmind/mujoco/releases>

Extract from tar:
```
    tar -xzvf mujoco-3.0.0-linux-x86_64.tar.gz
```

Copy install and bin files to /usr/local:
```
    sudo cp -r mujoco-3.0.0/include/mujoco /usr/local/include/
    sudo cp -P mujoco-3.0.0/lib/libmujoco.so* /usr/local/lib/
    sudo ldconfig
```

If using WSL 22.04, to connect xbox series x controller follow these steps (powershell):
```
    winget install --interactive --exact dorssel.usbipd-win

    usbipd list # Find the BUSID of the xbox controller

    usbipd bind --busid [INSERT BUSID OF CONTROLLER]

    usbipd attach --wsl --busid [INSERT BUSID OF CONTROLLER] 
    # You must re-attach the controller every time you plug it in. If the controller isn't working, try this first.
```

If you encounter this warning when trying to run the xbox arm controller:  
**[WARN] [1782072228.213256607] [xbox_arm_controller]: Gamepad error: The user (that this program is being run as) does not have permission to access the input events, check groups and permissions, for example, on Debian, the user needs to be in the input group.**  

Run this command to add your user to the input group:
```
    sudo usermod -a -G input $USER
    sudo reboot
    # Run "usbipd attach --wsl --busid [INSERT BUSID OF CONTROLLER]" again in powershell, if you're using wsl.
```
  
Command to launch simulation from rover_ws:
```
    ros2 launch cartesian_controller_simulation arm_simulation.launch.py
```

Commands to launch arm controller scripts (the first directory may change depending on what your workspace is named):
```
    python3 [workspace-name]/src/urc_armcontrol/src/cartesian_motion_controller/scripts/keyboard_arm_control.py
```
```
    python3 [workspace-name]/src/urc_armcontrol/src/cartesian_motion_controller/scripts/xbox_arm_control.py
```

Command to switch controllers:
```
    ros2 control switch_controllers --activate [name-of-controller]
    # Ex: ros2 control switch_controllers --activate cartesian_motion_controller
```

**IMPORTANT**  
If an error is displayed while trying to launch the simulation regarding numpy needing to be less than 2.0, one possible fix is to downgrade numpy using the following command:
```
    pip install 'numpy<2'  
```