# syntax=docker/dockerfile:1
# Reproducible build environment shared by CI and local development.
# Build from the repository root: docker build -f docker/Dockerfile --target ci .
ARG ROS_IMAGE=ros:humble-ros-base

# Reduces the workspace to its package manifests so that the dependency layer
# below is invalidated only when a dependency declaration changes.
FROM ${ROS_IMAGE} AS manifests
COPY . /src
RUN mkdir /manifests \
 && cd /src \
 && find . -name package.xml -not -path './.git/*' -exec cp --parents {} /manifests \;

FROM ${ROS_IMAGE} AS lint
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      git \
      ros-humble-ament-cmake-lint-cmake \
      ros-humble-ament-cmake-uncrustify \
      ros-humble-ament-cmake-xmllint \
      ros-humble-ament-cmake-flake8 \
 && rm -rf /var/lib/apt/lists/*

FROM ${ROS_IMAGE} AS ci
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      ccache \
      git \
      python3-colcon-common-extensions \
      python3-rosdep \
 && rm -rf /var/lib/apt/lists/*
COPY --from=manifests /manifests /tmp/manifests
RUN apt-get update \
 && rosdep update \
 && rosdep install --from-paths /tmp/manifests --ignore-src --skip-keys nanopb -y \
 && rm -rf /var/lib/apt/lists/* /tmp/manifests
ENV CCACHE_DIR=/ccache \
    CCACHE_MAXSIZE=1G
WORKDIR /ws
