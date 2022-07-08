# Docker Installation

## 1. Install docker

[Windows Instructions](https://docs.docker.com/desktop/windows/install/)

[Mac Instructions](https://docs.docker.com/desktop/mac/install/)

[Ubuntu Instructions](https://docs.docker.com/engine/install/ubuntu/)

## 2. Create the Docker image

```bash
sudo docker build -t <image name> https://github.com/RoboJackets/urc-software.git
```

## 3. Run Docker image

```bash
sudo docker run -i -t <image name>
```

