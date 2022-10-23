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

## 4. Obtain Docker Image

You can either pull the image from Dockerhub or build the image manually using a Dockerfile. 
**Pulling from Dockerhub is faster, easier, and less error-prone**. However, if you want to 
edit the Dockerfile for some reason, do the manual build instructions.

-   ### Pull From Dockerhub (Recommended!)

```bash
docker pull robojackets/urc-gui-baseimage
```

-   ### [Manually Build Docker Image](manual_docker_image.md)


## 5. Launch Docker Container

You can launch your newly created Docker container using the command line or VS Code.

-   ### Launch Docker Container Using VS Code

First, double check you have the `Docker` extension installed.

Once you have it, click on the Docker tab on the left of the editor. You should see the container you made in the "containers" tab. 

To launch the container in VS Code, right click it and select `Start`.

-   ### Launch Docker Container Using Command Line

To run the Docker container in the command line, run

```bash
docker start -i urc_software_container
```

If you want to open another terminal if the Docker container is still running, run

```bash
docker attach urc_software_container
```

## 6. Build!

First, it's always a good idea to check for updates. Nothing will happen if you just created the image. However, if you decide to re-create the container a while after you made the initial image, you will need to update those packages.

```bash
sudo apt update
sudo apt upgrade
cd /colcon_ws
rosdep update
```

Now, it's time for the moment of truth!

``` bash
cd /colcon_ws
colcon build
```

## 7. Closing the Container

Once you are done with the conatiner, be sure to close the Docker container. Otherwise, the 
Docker container will take up a big chunk of memory on your computer.

Note: Deleting the Docker container is not a big deal, since
* Your work is stored in a volume, which is seperate from the container.
* All of the required pacakges were installed in the image creation step.
However, the container remembers its state, so its a good idea to reuse the same container unless you mess up your environment.

-   ### Close Docker Conatiner Using VS Code

Closing the VS Code window does not stop the Docker container. To stop the Docker container, you can either:
* go to the `Docker` tab, and toggle the green arrow on the active container.
* go to the `Remote Explorer` tab, right click the active Docker container, and hit `Stop Container`.

-   ### Close Docker Container Using Command Line

Close the Docker container using

```bash
docker stop urc_software_container
```

## 8. Container Password

People outside your LAN should not be able to connect to your VNC server unless the port is being forwarded 
and the network firewall is disabled. If you want to change the default password, open the Dockerfile and change the line

```bash
RUN x11vnc -storepasswd urc-2023 ~/.vnc/passwd
```

by replacing the default password, `urc-2023`.

## 9. Using the GUI

To use the GUI, open your web browser and enter: 
```
http://localhost:8080/vnc.html
```

You should get a webpage for noVNC. Click `Connect` and enter the password, `urc-2023`.

After this, you should see a terminal window. You can launch GUI applications from this window. For example, try launching `gazebo` or `rviz2`.

## Troubleshooting

If something isn't working correctly with your Docker container, the best solution 
is to delete your old stuff and restart from step 4. To do this, you should
remove the Docker container, Docker image, and Docker volume.

### Deleting the Docker Container

If your development environment gets messed up, you can delete the development environment with:
```bash
docker stop urc_software_container
docker rm urc_software_container
```
You can also delete the container in the `Remote Explorer` tab or the `Docker` tab by right clicking on the container and removing it.

### Deleting the Docker Image

If something isn't working correctly from a container freshly minted from the `urc-gui-baseimage`, something
is probably wrong with your Docker image. To delete `urc-gui-baseimage`, run

```bash
docker image rm robojackets/urc-gui-baseimage
```

### Deleting the Docker Volume

If you are deleting your Docker image due to systemic issues, you should probably remove the Docker volume as
well. However, **all of your previous work is stored inside this volume! If you delete it, your changes will be gone!**
Make sure to push your changes to Github before deleting the volume!

```bash
docker volume rm urc_software_volume
```
