#!/bin/bash

# Check if Git is installed
if ! command -v git &> /dev/null; then
    echo "Git is not installed. Please install Git and try again."
    exit 1
fi

# Set the repository URLs
rover_url="https://github.com/RoboJackets/urc-rover.git"
drone_url="https://github.com/RoboJackets/urc-firmware.git"

# Set the target directories for cloning
rover_dir="rover_ws/src"
drone_dir="drone_ws/src"

# Clone the rover repository
if ! git clone "$rover_url" "$rover_dir"; then
    echo "Failed to clone urc-rover"
    exit 1
fi

# Clone the drone repository
if ! git clone "$drone_url" "$drone_dir"; then
    echo "Failed to clone urc-drone"
    exit 1
fi

# Check if Docker is installed
if ! command -v docker &> /dev/null; then
    echo "Docker is not installed. Please install Docker and try again."
    exit 1
fi

# Set up image name + tag
image_name="tiryoh/ros2-desktop-vnc"
image_tag="humble"

# Get NoVNC container from DockerHub
docker pull "$image_name:$image_tag"

# Set up container name + location
container_name="urc_container"
mount_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Check if a container with the same name already exists
existing_container=$(docker ps -aq --filter name="$container_name")
if [[ -n "$existing_container" ]]; then
    echo "A container with the name $container_name already exists. Please choose a different name."
    exit 1
fi

# Run the container and mount
docker run -d --name "$container_name" -v "$mount_dir:/mount" "$image_name:$image_tag"
