# Docker Installation

The repository's [`setup.sh`](../../setup.sh) script creates the supported
development container. It uses `tiryoh/ros2-desktop-vnc:humble`, names the
container `urc_container`, exposes the NoVNC desktop on port 6060, and mounts the
host project directory at `/home/ubuntu/urc_container`.

## Prerequisites

Install [Docker Desktop](https://docs.docker.com/desktop/) on macOS or Windows,
or [Docker Engine](https://docs.docker.com/engine/install/ubuntu/) on Ubuntu.
Install Git as well. On Linux, configure Docker so your user can run it without
`sudo`.

## Create the project directory

The setup script manages both rover and drone workspaces. Create their parent
directories, then clone the rover repository:

```bash
mkdir -p urc_container/rover_ws urc_container/drone_ws
git clone --recurse-submodules \
  https://github.com/RoboJackets/urc-software.git \
  urc_container/rover_ws/src
cd urc_container
```

## Start the container

Run the setup script from `urc_container` so that directory becomes the mounted
project root:

```bash
chmod +x rover_ws/src/setup.sh
./rover_ws/src/setup.sh start
```

On first use, the script:

- clones the drone repository into `drone_ws/src`
- pulls the ROS 2 Humble NoVNC image
- creates and starts `urc_container`
- installs the container dependencies maintained by the script

Open [http://localhost:6060](http://localhost:6060) for the browser desktop, or
open a shell directly:

```bash
docker exec -it urc_container bash
```

## Build inside the container

From the container shell:

```bash
cd /home/ubuntu/urc_container/rover_ws
source /opt/ros/humble/setup.bash
rosdep update
rosdep install --from-paths src --ignore-src -r -y
colcon build --symlink-install
source install/setup.bash
```

The source tree is shared with the host, while `build/`, `install/`, and `log/`
are created in the mounted workspace.

## Stop and restart

Run these commands from the host `urc_container` directory:

```bash
./rover_ws/src/setup.sh stop
./rover_ws/src/setup.sh start
```

If the container configuration or mount location must change, update `setup.sh`
and recreate the container deliberately; restarting an existing container does
not apply new `docker run` options.
