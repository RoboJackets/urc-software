# Docker Installation

Doing a Docker installation is a great method for setting up the repository on any operating system
that isn't Ubuntu 22.04. It is a faster and more lightweight alternative to a traditional Virtual Machine.
In addition, you can still run GUI applications like Gazebo using the NoVNC desktop environment.

## 1. Install Docker

[Windows Instructions](https://docs.docker.com/desktop/windows/install/)

[Mac Instructions](https://docs.docker.com/desktop/mac/install/)

[Ubuntu Instructions](https://docs.docker.com/engine/install/ubuntu/)

### NOTE

- If you are on Linux, add yourself to the `docker` group. Being a member of the `docker` group allows you to run `docker` without `sudo`.

```bash
sudo groupadd docker
sudo usermod -aG docker $USER
```

After you complete the installation, **restart your computer**!

To check that everything installed OK, you should be able to open the command line and type:

```bash
docker
```

## 2. Install VS Code (Highly Recommended)

You do not have to use VS Code. However, VS Code has very nice extensions for using Docker containers.

[Download VS Code here](https://code.visualstudio.com/Download)

### 2a. Install VS Code Extensions

Search for and install the following extensions in VS Code

- Docker
- DevContainers
- ROS
- C/C++
- CMake

## 3. Install Git

[Install Git using the instructions here](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)

## 4. Clone the Repository

Open a terminal (or Git Bash on Windows), create a folder where you want the repository to be located, navigate to that folder, and run:

```bash
mkdir rover_ws
cd rover_ws && git clone https://github.com/RoboJackets/urc-software src
```

## 5. Pull the docker image

```bash
docker pull osrf/ros:humble-desktop
```

## 6. Run the docker container

Navigate to the `docker` folder (located inside `rover_ws/src/docker`) and run the following command:

```bash
docker compose up
```

You can open another terminal and run `docker exec -it ros_desktop bash` to access the container. it is recommended to use VS Code to connect to the container and develop inside the container.

## 7. Connect to container using VS Code (Highly Recommended)

Open VS Code, press `F1`, and select `Dev Containers: Attach to Running Container...`. Then select the container named `ros_desktop`.
You should now be conneceted to the container and can open the folder `/home/rover_ws` to start working on the code.

## 8. Modify container `.bashrc`

To make sure that ROS is sourced every time you open a new terminal in the container, run the following command _inside the docker container_:

```bash
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
```

## 9. Install dependencies and build the code

Run the following commands _inside the docker container_:

```
sudo apt update
rosdep update
cd /home/rover_ws
rosdep install --from-paths src --ignore-src -r -y
colcon build --symlink-install
```
