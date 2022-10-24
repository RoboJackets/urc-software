# Manual Docker Image Creation

First, clone the `urc-software` repository.

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

Once the Docker image has built, you can refer to the Docker installation instructions.