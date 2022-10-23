# Manual Docker Image Creation

## 1. Clone URC software

```bash
git clone https://github.com/RoboJackets/urc-software.git
```

Navigate to the directory `docker_gui` and run:
```bash
docker build -t robojackets/urc-gui-baseimage .
```

If on an M1 Mac, enable x64 emulation by adding the `--platform linux/amd64` argument. Otherwise, some apt packages will be unavailable.
```bash
docker build --platform linux/amd64 -t robojackets/urc-gui-baseimage .
```

## 2. Create Docker Volume

Create a Docker volume that will hold the `urc-software` repository. The Docker volume will store your data seperately from the container itself. As a result, you can delete the container without losing your changes.

```bash
docker volume create urc_software_volume
```

## 3. Create Docker Container

To create a Docker container from the newly created image `robojackets/urc-baseimage`, run

```bash
docker container create -i -t -p=8080:8080 -v=urc_software_volume:/colcon_ws/src --name=urc_software_container robojackets/urc-gui-baseimage
```

If on an M1 Mac, again add the platform argument.
```bash
docker container create --platform linux/amd64 -i -t -p=8080:8080 -v=urc_software_volume:/colcon_ws/src --name=urc_software_container robojackets/urc-gui-baseimage
```