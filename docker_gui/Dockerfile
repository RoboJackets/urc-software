FROM tiryoh/ros2-desktop-vnc:humble
LABEL maintainer="aidan.stickan@gmail.com"

# Setup apt to be happy with no console input
ARG DEBIAN_FRONTEND=noninteractive

# Initialize colcon workspace
RUN mkdir -p /urc
WORKDIR /urc
RUN mkdir -p /rover_colcon/src
RUN mkdir -p /drone_colcon/src
WORKDIR /rover_colcon
RUN mkdir -p src

# Clone rover repo
WORKDIR /rover_colcon/src
RUN git clone https://github.com/RoboJackets/urc-software.git . --recursive

# Clone drone repo
WORKDIR /drone_colcon/src
RUN git clone https://github.com/RoboJackets/urc-drone.git . --recursive

# Setup bashrc
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc \
    && echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> ~/.bashrc \
    && echo "source /usr/share/gazebo/setup.sh" >> ~/.bashrc
