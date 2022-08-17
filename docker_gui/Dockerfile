FROM ros:humble-ros-base
LABEL maintainer="vivekmhatre7686@gmail.com"

# Setup apt to be happy with no console input
ARG DEBIAN_FRONTEND=noninteractive

# setup apt tools and other goodies we want
RUN apt-get update --fix-missing && apt-get -y install \
    apt-utils \
    git \
    software-properties-common \
    ssh \
    python3-pip \
    libeigen3-dev \
    && apt-get clean

# Initialize colcon workspace
RUN mkdir -p /colcon_ws
WORKDIR /colcon_ws
RUN mkdir -p src

# Set up VNC server
RUN apt-get update && apt-get install -y x11vnc xvfb terminator && apt-get clean
RUN mkdir ~/.vnc
RUN x11vnc -storepasswd 1234 ~/.vnc/passwd

EXPOSE 8080 5900
RUN apt-get install -y novnc websockify wget

COPY entrypoint.sh /entrypoint.sh
RUN sed -i -e 's/\r$//' /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]