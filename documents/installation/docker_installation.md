# Docker Installation

Doing a Docker installation is a good method for setting up the repository on any operating system
that isn't Ubuntu 22.04 LTS. It is a lighter-weight and faster alternative than installing a Virtual Machine. However, this is not a good method if you need to use rviz or gazebo. 

## 1. Install Docker

[Windows Instructions](https://docs.docker.com/desktop/windows/install/)

[Mac Instructions](https://docs.docker.com/desktop/mac/install/)

[Ubuntu Instructions](https://docs.docker.com/engine/install/ubuntu/)

## 2. Install VSCode (Highly Recommended)

You do not have to use VSCode. However, VSCode has very nice extensions for using Docker containers.

### 2a. Install VSCode

[Download VSCode here](https://code.visualstudio.com/Download)

### 2b. Install VSCode Extensions

Search for and install the following extensions in VSCode

* Docker
* ROS
* Remote - Containers

## 3. Download Docker Image

Next, you need to get the Docker image for our repository. You can either manually build the Docker image or you can download the Docker image from Dockerhub.

### 3a. Download Image from Dockerhub

We only have an ```amd64``` version on our Dockerhub. If your architecture does not match, then use the manual installation method.

```bash
docker pull robojackets/urc-baseimage
```

### 3b. Manually Build Image

To do the manual installation, you need to download the Dockerfile in the `urc-software` repository. If you have `git` installed, you can just clone the whole repository:
```bash
git clone https://github.com/RoboJackets/urc-software.git
cd urc-software
```
If you don't have `git` or don't want to download the whole repository, you can just save [this](https://raw.githubusercontent.com/RoboJackets/urc-software/master/Dockerfile) as `Dockerfile` on your computer.

Once you are in the same directory as our Dockerfile, run:
```bash
docker build -t robojackets/urc-baseimage .
```

## 4. Create Docker Container

To create a Docker container from the newly created image `robojackets/urc-baseimage`, run

```bash
docker container create -i -t --name=urc_software_container robojackets/urc-baseimage
```

## 5. Launch Docker Container

You can launch your newly created Docker container using the command line or VSCode.

### 5a. Launch Docker Conatiner Using VSCode

First, make sure that you have the `Remote - Containers` extension installed.

Once you have it, click on the Remote Explorer tab. You should see the container you made in the "containers" tab. 

To launch the container in VSCode, right click the container and select `Attach to Container`. This will open VSCode in the Docker container.

## 6. Finish Setup

In its current state, the Docker container is not quite ready for building the `urc-software` codebase. 

### Re-clone `urc-software` in `/colcon_ws/src`

```bash
cd /colcon_ws/src
rm -rf urc-software
git clone https://github.com/RoboJackets/urc-software.git --recursive
```
### Update ROS Dependencies
```bash
cd /colcon_ws
source /opt/ros/humble/setup.bash
sudo apt-get update
rosdep update
rosdep install --from-paths src --ignore-src -r -y
```
### Build

``` bash
cd /colcon_ws
colcon build
```