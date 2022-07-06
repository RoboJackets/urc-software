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

COPY . /colcon_ws/src/urc-software

# Install all ROS dependencies that can automatically be installed
WORKDIR /colcon_ws/src/urc-software
#RUN /bin/bash -c /colcon_ws/src/urc-software/install_dependencies.sh