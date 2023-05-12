FROM tiryoh/ros2-desktop-vnc:humble
LABEL maintainer="aidan.stickan@gmail.com"

# Setup apt to be happy with no console input
ARG DEBIAN_FRONTEND=noninteractive

# Initialize colcon workspace
RUN mkdir -p /home/ubuntu/urc
WORKDIR /ubuntu/home/urc
RUN mkdir -p /home/ubuntu/urc/rover_colcon/src
RUN mkdir -p /home/ubuntu/urc/drone_colcon/src
WORKDIR /home/ubuntu/urc/rover_colcon
RUN mkdir -p src

# Clone rover repo
WORKDIR /home/ubuntu/urc/rover_colcon/src
RUN git clone https://github.com/RoboJackets/urc-software.git . --recursive

# Clone drone repo
WORKDIR /home/ubuntu/urc/drone_colcon/src
RUN git clone https://github.com/RoboJackets/urc-drone.git . --recursive

# Setup bashrc
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc \
    && echo "source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash" >> ~/.bashrc \
    && echo "source /usr/share/gazebo/setup.sh" >> ~/.bashrc
