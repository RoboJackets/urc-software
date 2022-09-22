# Installation Guide

## 1. Make sure you are running Ubuntu 22.04!

## 2. Create a folder to contain the urc-software repo
```bash
cd <path to where you want to keep the project>
```
```bash
mkdir -p colcon-urc/src
```

## 3. Clone the urc-software git repository 
```bash
cd colcon-urc/src
```
```bash
git clone https://github.com/RoboJackets/urc-software.git --recursive
```
## 4. Run the automated install script
This will install ROS2 and its associated system packages, including initializing rosdep and building our workspace.

```bash
cd urc-software/
./install_script.sh
```
### Getting errors when running colcon build?
If you have an error when running colcon build or rosdep:
- Search the apt repository for the appropriate ROS package (usually ros-humble-package-name, using em dashes, with the package name being the package that caused an ament_cmake error) using `apt search ros-humble-package-name` or `apt search package-name`
- Add the package to the list of apt packages to install in the install_script.sh script (line 32)
- Run the install script with the new packaged added or manually install the package using `apt install ros-humble-package-name`
- Run colcon build using `colcon build --symlink-install`
- Repeat as neccessary until build succeeds
