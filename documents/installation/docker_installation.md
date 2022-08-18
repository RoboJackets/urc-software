# Docker Installation

Doing a Docker installation is a good method for setting up the repository on any operating system
that isn't Ubuntu 22.04 LTS. It is a lighter-weight and faster alternative than installing a Virtual Machine.
In addition, you can run GUI applications like Gazebo using the VNC server.

Although compiling code in a Docker container is not as fast as compiling it on Ubuntu 22.04 natively, it is not slow by any means. If you use an IDE with Docker support (such as VS Code with the recommended extensions), writing code will be no different than doing it natively on Ubuntu 22.04. 

## 1. Install Docker

[Windows Instructions](https://docs.docker.com/desktop/windows/install/)

[Mac Instructions](https://docs.docker.com/desktop/mac/install/)

[Ubuntu Instructions](https://docs.docker.com/engine/install/ubuntu/)

To check that everything installed OK, you should be able to open the command line and type:
```bash
docker
```

## 2. Install VS Code (Highly Recommended)

You do not have to use VS Code. However, VS Code has very nice extensions for using Docker containers.

[Download VS Code here](https://code.visualstudio.com/Download)

### 2a. Install VS Code Extensions

Search for and install the following extensions in VS Code

* Docker
* ROS
* Remote - Containers

## 3. Install Git

[Install Git using the instructions here](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)


## 4. Create Docker Image

```bash
git clone https://github.com/RoboJackets/urc-software.git
```

Navigate to the directory `docker_gui` and run:
```bash
docker build -t robojackets/urc-baseimage .
```

Run the command as a superuser if you get permission errors.

## 5. Create Docker Container

To create a Docker container from the newly created image `robojackets/urc-baseimage`, run

```bash
docker container create -i -t -p=8080:8080 --name=urc_software_container robojackets/urc-baseimage
```

## 6. Launch Docker Container

You can launch your newly created Docker container using the command line or VS Code.

### 6a. Launch Docker Container Using VS Code

First, make sure that you have the `Remote - Containers` extension installed.

Once you have it, click on the Remote Explorer tab. You should see the container you made in the "containers" tab. 

To launch the container in VS Code, either 
* right click the container and select `Attach to Container`.
* hover over the container and click on the folder with a plus.

### 6b. Launch Docker Container Using Command Line

To run the Docker container in the command line, run

```bash
docker start -i -p=8080:8080 urc_software_container
```

If you want to open another terminal if the Docker container is still running, run

```bash
docker attach urc_software_container
```

## 7. Finish Setup

In its current state, the Docker container is not quite ready for building the `urc-software` codebase. 

### Re-clone `urc-software` in `/colcon_ws/src`

```bash
cd /colcon_ws/src
rm -rf urc-software
git clone https://github.com/RoboJackets/urc-software.git --recursive
```

### bashrc Setup

```bash
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> ~/.bashrc
echo "source /usr/share/gazebo/setup.sh" >> ~/.bashrc
source ~/.bashrc
```

### Update ROS Dependencies
```bash
cd /colcon_ws
sudo apt-get update
rosdep update
rosdep install --from-paths src --ignore-src -r -y
```
### Build

``` bash
source ~/.bashrc
cd /colcon_ws
colcon build
```

## 8. Closing the Container

Once you are done with the conatiner, be sure to close the Docker container. Otherwise, the 
Docker container will take up a big chunk of memory on your computer.

Important Note: DO NOT delete the Docker container! The container saves its current state, so all of your
work is also preserved inside the container as well! Only delete the container if you somehow mess up your
environment. Then, you can just create a new container from the `robojackets/urc-baseimage` image.

### 8a. Close Docker Conatiner Using VS Code

Closing the VS Code window does not stop the Docker container. To stop the Docker container, you can either:
* go to the `Remote Explorer` tab, right click the active Docker container, and hit `Stop Container`.
* go to the `Docker` tab, and toggle the green arrow on the active container.

### 8b. Close Docker Container Using Command Line

Close the Docker container using

```bash
docker stop urc_software_container
```

## 9. Using the GUI

To use the GUI, open your web browser and enter: 
```
http://localhost:8080/vnc.html
```

You should get a webpage for noVNC. Click `Connect` and enter the password, `1234`.

After this, you should see a Terminator window. You can launch GUI applications from this window. For example, try launching `gazebo`.