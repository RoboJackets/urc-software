# Docker Installation

Doing a Docker installation is a good method for setting up the repository on any operating system
that isn't Ubuntu 22.04 LTS. It is a lighter-weight and faster alternative than installing a Virtual Machine.
In addition, you can run GUI applications like Gazebo using the VNC server.

Although compiling code in a Docker container is not as fast as compiling it on Ubuntu 22.04 natively, it is not slow by any means. If you use an IDE with Docker support (such as VSCode with the recommended extensions), writing code will be no different than doing it natively on Ubuntu 22.04. 

## 1. Install Docker

[Windows Instructions](https://docs.docker.com/desktop/windows/install/)

[Mac Instructions](https://docs.docker.com/desktop/mac/install/)

[Ubuntu Instructions](https://docs.docker.com/engine/install/ubuntu/)

### NOTE
* If you are on Linux, add yourself to the `docker` group. Being a member of the `docker` group allows you to run `docker` without `sudo`.
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

## 5. Create Docker Volume

Create a Docker volume that will hold the `urc-software` repository. The Docker volume will store your data seperately from the container itself. As a result, you can delete the container without losing your changes.

```bash
docker volume create urc_software_volume
```

## 6. Create Docker Container

To create a Docker container from the newly created image `robojackets/urc-baseimage`, run

```bash
docker container create -i -t -p=8080:8080 -v=urc_software_volume:/colcon_ws/src --name=urc_software_container robojackets/urc-baseimage
```

## 7. Launch Docker Container

You can launch your newly created Docker container using the command line or VS Code.

### 7a. Launch Docker Container Using VS Code

First, double check you have the `Docker` extension installed.

Once you have it, click on the Docker tab on the left of the editor. You should see the container you made in the "containers" tab. 

To launch the container in VS Code, right click it and select `Start`.

### 7b. Launch Docker Container Using Command Line

To run the Docker container in the command line, run

```bash
docker start -i urc_software_container
```

If you want to open another terminal if the Docker container is still running, run

```bash
docker attach urc_software_container
```

## 8. Build!

First, it's always a good idea to check for updates. Nothing will happen if you just created the image. However, if you decide to re-create the container a while after you made the initial image, you will need to update those packages.

```bash
sudo apt update
sudo apt upgrade
cd /colcon_ws
rosdep update
```

Now, its time for the moment of truth!

``` bash
cd /colcon_ws
colcon build
```

## 9. Closing the Container

Once you are done with the conatiner, be sure to close the Docker container. Otherwise, the 
Docker container will take up a big chunk of memory on your computer.

Note: Deleting the Docker container is not a big deal, since
* Your work is stored in a volume, which is seperate from the container.
* All of the required pacakges were installed in the image creation step.
However, the container remembers its state, so its a good idea to reuse the same container unless you mess up your environment.

### 9a. Close Docker Conatiner Using VS Code

Closing the VS Code window does not stop the Docker container. To stop the Docker container, you can either:
* go to the `Docker` tab, and toggle the green arrow on the active container.
* go to the `Remote Explorer` tab, right click the active Docker container, and hit `Stop Container`.

### 9b. Close Docker Container Using Command Line

Close the Docker container using

```bash
docker stop urc_software_container
```

## 10. Using the GUI

To use the GUI, open your web browser and enter: 
```
http://localhost:8080/vnc.html
```

You should get a webpage for noVNC. Click `Connect` and enter the password, `urc-2023`.

After this, you should see a terminal window. You can launch GUI applications from this window. For example, try launching `gazebo` or `rviz2`.

## 11. Deleting the Docker Container

If your development environment gets messed up, you can delete the development environment with:
```bash
docker stop urc_software_container
docker rm urc_software_container
```
You can also delete the container in the `Remote Explorer` tab or the `Docker` tab by right clicking on the container and removing it.