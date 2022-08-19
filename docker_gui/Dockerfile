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
    python3-colcon-common-extensions \
    python3-rosdep \
    && apt-get clean

# Initialize colcon workspace
RUN mkdir -p /colcon_ws
WORKDIR /colcon_ws
RUN mkdir -p src

# Clone git repo
WORKDIR /colcon_ws/src
RUN rm -rf urc-software
RUN git clone https://github.com/RoboJackets/urc-software.git --recursive

# Install our ROS dependecies
WORKDIR /colcon_ws
RUN rosdep update
RUN apt-get update --fix-missing
RUN rosdep install --from-paths src --ignore-src -r -y

# Setup bashrc
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc \
    && echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> ~/.bashrc \
    && echo "source /usr/share/gazebo/setup.sh" >> ~/.bashrc

# Set up VNC server
RUN apt-get update && apt-get install -y x11vnc xvfb terminator && apt-get clean
RUN mkdir ~/.vnc
RUN x11vnc -storepasswd urc-2023 ~/.vnc/passwd

EXPOSE 8080 5900
RUN apt-get install -y novnc websockify wget

COPY entrypoint.sh /entrypoint.sh
RUN sed -i -e 's/\r$//' /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]