#!/bin/bash 

# Note: You should run this script in your colcon workspace folder... if you're in the src folder, it will go up a directory to the workspace

# Become root so we don't have to add sudo to everything
if [ $UID -ne 0 ]; then
	echo "-- Becoming root"
	# Executes the current script as user 0 (sudo)
	exec sudo $0 $@
fi

echo "Adding ROS2 keys..."
apt install software-properties-common

add-apt-repository universe

# Add the ROS GPG key
apt update && apt install curl gnupg lsb-release
curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null

echo "Updating and upgrading system packages..."
apt update
apt upgrade

echo "Installing ROS2..."
apt install ros-humble-desktop-full

apt install python3-colcon-common-extensions

for line in /opt/ros/humble/setup.bash /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash /usr/share/gazebo/setup.sh 
do
		if  grep $line ~/.bashrc 
then
		echo $line already added to ~./bashrc
else
		echo $line >> ~/.bashrc
		fi
done

source /opt/ros/humble/setup.bash
# If you have an error when running colcon build or rosdep:
# - Search the apt repository for the appropriate ROS package (usually ros-humble-package-name, using em dashes)
# - If it exists, install it
# - Run the script again
# - Repeat as neccessary

colcon build --symlink-install

# This script will initialize and run rosdep if in the correct directory
apt install python3-rosdep
if ($pwd | grep "src"); then
		source ../../install/setup.bash
else
		source ./install/setup.bash 
fi
if !(ls /etc/ros/rosdep | grep "sources"); then 
		rosdep init
fi
rosdep update
rosdep install --from-paths ../../src --ignore-src -r -y -v
