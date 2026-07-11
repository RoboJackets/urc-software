## This urc_armcontrol package contains the logic for controlling the Robonav arm, this README includes instructions for setting up and running the code on your machine.
**Doesn't work on docker, works for wsl / bare metal Ubuntu installation.**

### Instructions to get set up:

Install Mujuco 3.0.0 to /home/[user] (preferred) or /root directory using wget:
```
cd /home/[user]
wget https://github.com/google-deepmind/mujoco/releases/download/3.0.0/mujoco-3.0.0-linux-x86_64.tar.gz
```

**This is a link to the mujuco releases <https://github.com/google-deepmind/mujoco/releases>**

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

## If using WSL Ubuntu 22.04, follow these steps to connect an xbox series x controller:

In **(powershell)**:
```
winget install --interactive --exact dorssel.usbipd-win

usbipd list # Find the BUSID of the xbox controller

usbipd bind --busid [INSERT BUSID OF CONTROLLER]

usbipd attach --wsl --busid [INSERT BUSID OF CONTROLLER] 
# You must re-attach the controller every time you plug it in. If the controller isn't working, try this first.
```

### By default, wsl doesn't with the drivers needed by the xbox controller. Follow these steps to install the proper drivers:

Install the tools for compiling the linux kernel from source:
```
sudo apt update && sudo apt install -y build-essential flex bison libssl-dev \ libelf-dev libncurses-dev bc dwarves python3
```
Find the version of wsl you're using and clone the kernel for your version of ubuntu, you can do this in $HOME:
```
uname -r
# That command prints something like: [version-number]-microsoft-standard-WSL2
# Example version number:  6.6.114.1

# Paste your [version-number] into this git clone command
git clone --depth 1 -b linux-msft-wsl-[version-number] \
https://github.com/microsoft/WSL2-Linux-Kernel.git
```
Open the configuration menu:
```
cd WSL2-Linux-Kernel 
cp Microsoft/config-wsl .config 
make menuconfig
```
After opening the configuration menu follow these steps.  
Go to Device Drivers → Input device support:  
Press "Y" or <\*> for:  
* Event interface
* Joystick interface
* Joysticks/Gamepads
* Joysticks/Gamepads->Xbox gamepad support (This is inside of Joysticks/Gamepads)

Go to Device Drivers → USB support → USB/IP support:  
Press "Y" or <\*> for:  
* USB/IP support
* VHCI hcd (USB/IP)

Go to Device Drivers → LED support:  
Press "Y" or <\*> for:  
* LED class support

**The menu might say that a configuration depends on another feature, press "?" key to see which configurations have a "M" modular configuration or aren't configured at all, and select "Y" for those configurations as well.**

Save as ".config".

Run these commands in wsl:
```
make -j$(nproc)
sudo make modules_install
cp arch/x86/boot/bzImage /mnt/c/Users/[name-of-your-windows-user]/bzImage
```

In **powershell** run these commands in your HOME directory:
```
notepad C:\Users\[name-of-your-windows-user]\.wslconfig
```
Paste this into .wslconfig **still in powershell**:
```
[wsl2] 
kernel=C:\\Users\\[name-of-your-windows-user]\\bzImage
```

In wsl:
```
wsl --shutdown
```

You should be done with installing the necessary drivers for the xbox controller. Run these commands to make sure everything is working. This information may also be useful for non-wsl users. 

### Test that everything works:

In powershell make sure the controller is attached:
```
usbipd list
```
In wsl make sure the xbox controller is listed in lsusb and that /dev/input exists (it shouldn't say "No such file or directory"):
```
lsusb
ls /dev/input
```

Run this command in wsl to add your user to the input group ():
```
sudo usermod -a -G input $USER
sudo reboot
```
Run "usbipd attach --wsl --busid [INSERT BUSID OF CONTROLLER]" again in powershell, if you're using wsl.

## Launch commands:
**Make sure you CTRL+C out of both the launch sim and the controller script before launching again.**
  
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

Command to switch controllers manually (use 'ros2 control list_controllers' to list available controllers):  
```
ros2 control switch_controllers --activate [name-of-controller]
```
**Manually switching controllers may confict with the logic in the xbox_arm_control.py script and cause unintended behavior, switching controllers with the xbox controller should be done by pressing (dpad_down + y) simultaneously.**

Command to check currently active controllers (joint_state_broadcaster should **always** be active):
```
ros2 control list_controllers
```

**If you encounter this warning when trying to run the xbox arm controller, run the command to add your user to the input group in ubuntu/wsl (also mentioned above):**  
[WARN] [1782072228.213256607] [xbox_arm_controller]: Gamepad error: The user (that this program is being run as) does not have permission to access the input events, check groups and permissions, for example, on Debian, the user needs to be in the input group. 
```
sudo usermod -a -G input $USER
sudo reboot
```
or unplug/replug the controller and attach in powershell again.

**If an error is displayed while trying to launch the simulation regarding numpy needing to be less than 2.0, one possible fix is to downgrade numpy using the following command:**
```
pip install 'numpy<2'  
```