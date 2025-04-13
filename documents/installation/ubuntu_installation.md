# Installation Guide

## 1. Make sure you are running Ubuntu 22.04!

## 2. Install ROS2

```bash
sudo apt install software-properties-common
```
```bash
sudo add-apt-repository universe
```
```bash
sudo apt update && sudo apt install curl gnupg lsb-release
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
```
```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```
```bash
sudo apt update
```
```bash
sudo apt upgrade
```
```bash
sudo apt install ros-humble-desktop-full
```

## 3. Install Colcon
   
```bash
sudo apt install python3-colcon-common-extensions
```

## 4. bashrc Setup

```bash
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
```
```bash
echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> ~/.bashrc
```
```bash
echo "source /usr/share/gazebo/setup.sh" >> ~/.bashrc
```
```bash
source ~/.bashrc
```

## 5. Create URC environment 

```bash
cd <path to where you want to keep the project>
```
```bash
mkdir urc && cd urc
```
Both the rover and the drone projects will live in the `/urc` directory. The install process for both projects is very similar and detailed below. 

---
## Rover
### 1. Create rover colcon environment

```bash
mkdir -p rover-colcon/src
```

### 2. Clone the rover repository into the rover-colcon environment
```bash
cd rover-colcon
git clone https://github.com/RoboJackets/urc-software.git src --recursive
```

### 3. Install and run rosdep
 Make sure to call the `rosdep install` command from the colcon workspace directory (`/rover-colcon`)!
```bash
sudo apt install python3-rosdep
sudo rosdep init
rosdep update
rosdep install --from-paths src --ignore-src -r -y
```
### 4. Build your rover workspace
Any time you call `colcon build`, make sure you are in the colcon directory (`/rover-colcon`)!
```bash
colcon build --symlink-install
```

### 5. Source the rover environment

```bash
. install/setup.bash
```

---
## Recap
You should now have a file structure that looks like 
```
 urc
 └── rover-colcon
     ├── build
     ├── install
     ├── log
     └── src
         └── urc-software
```
