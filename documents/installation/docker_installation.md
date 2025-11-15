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

## 4. Obtain Docker Image

You can either pull the image from Dockerhub or build the image manually using a Dockerfile.
**Pulling from Dockerhub is faster, easier, and less error-prone**. However, if you want to
edit the Dockerfile for some reason, do the manual build instructions.

- ### Pull From Dockerhub (Recommended!)

```bash
docker pull robojackets/urc-gui-baseimage
```

- ### [Manually Build Docker Image](manual_docker_image.md)

## 5. Create directory to mount container

The docker container is essentially a self-contained instance of Ubuntu 22.04, but can access some files on your system in a limited way. We use this so the container can see the repositories you clone locally, that way both local development and containerized testing can be done without any delays.

**You can place this directory wherever you want**, I recommend `/home` for Mac/Linux and `C:\Users\[Username]\` for Windows

```bash
mkdir urc_container
```

## 6. [Download our installation script](../../setup.sh)

Our installation script will

- Clone all necessary repos
- Automatically setup your desktop NoVNC environment

## 7. Move the script into your `urc_container` directory

## 8. Run the script

**If on Windows, you will need to use Git Bash to run the following commands!**

Run this command only if you are on Mac/Linux

```bash
chmod +x setup.sh
```

```bash
./setup.sh
```

## 9. Access your new container

For beginners to Docker:

- Go to `localhost:6060` in your web browser of choice

Recommended way:

- Open up VS Code
- Click on the whale Docker icon on your left
- Right click the currently running container (Should be called tiryoh/ros2)
- Select open in browser

![Picture of where to head in VS Code](../pictures/docker_tab.png)

## 10. Head to your mounted directory

Open terminator in the desktop (this is the recommended terminal for commands in your container)

![You can find terminator in the bottom left corner here](../pictures/terminator_location.png)

In terminator, run

```bash
cd urc_container
```

## 11. Get necessary packages

First, it's always a good idea to check for updates. Nothing will happen if you just created the image. However, if you decide to re-create the container a while after you made the initial image, you will need to update those packages.

```bash
sudo apt update
sudo apt upgrade
```

```bash
cd /rover_ws
rosdep update && rosdep install --from-paths src --ignore-src -r -y
```

## 12. Build the repo!

Now, it's time for the moment of truth!

```bash
colcon build
```

## 13. Developing using the Docker NoVNC container

1. Work on your code in `urc_container` locally to avoid input lag
2. When ready to test, you can build and run your code in the container just like on native Ubuntu!

## 14. Closing/Starting the Container

Once you are done with the conatiner, be sure to close the Docker container. Otherwise, the
Docker container will take up a big chunk of memory on your computer.

- ### Using VS Code
  - Go to the Docker tab in VS Code
  - Right click the container (it has a green arrow next to it if already running)
  - Press stop/start

  ![Picture of where to head in VSCode](../pictures/docker_tab.png)

- ### Using the install script
  - Go to where you placed `urc_container` locally
  - Run `./setup.sh stop` to stop
  - Run `./setup.sh start` to start up again

# Faster, but untested docker method

The below steps are for a faster docker container. However, there are a few caveats: running graphical

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

The first time, you will have to navigate to the `docker` folder (located inside `rover_ws/src/docker`) and run the following command:

```bash
docker compose up
```

You can open another terminal and run `docker exec -it ros_desktop bash` to access the container. For subsequent launches, it is recommended to use VS Code to connect to the container and develop inside the container.

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
