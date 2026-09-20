FROM osrf/ros:humble-desktop

ARG USER_NAME=ros
ARG USER_UID=1000
ARG USER_GID=1000

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8
ENV ROS_DISTRO=humble
ENV USER_NAME=${USER_NAME}
ENV HOME=/home/${USER_NAME}
ENV DISPLAY=:1
ENV VNC_DISPLAY=:1
ENV VNC_GEOMETRY=1280x800
ENV VNC_DEPTH=24
ENV QT_X11_NO_MITSHM=1
ENV LIBGL_ALWAYS_SOFTWARE=1

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN apt-get update \
    && apt-get install -y --no-install-recommends software-properties-common \
    && add-apt-repository universe \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
      bash-completion \
      build-essential \
      dbus-x11 \
      git \
      less \
      locales \
      nano \
      python3-colcon-common-extensions \
      python3-rosdep \
      python3-vcstool \
      ros-dev-tools \
      sudo \
      tigervnc-common \
      tigervnc-standalone-server \
      tigervnc-tools \
      tmux \
      x11-xserver-utils \
      xauth \
      xfce4 \
      xfce4-goodies \
      xfonts-base \
      xterm \
    && locale-gen en_US en_US.UTF-8 \
    && update-locale LANG=en_US.UTF-8 LC_ALL=en_US.UTF-8 \
    && rm -rf /var/lib/apt/lists/*

RUN rosdep init 2>/dev/null || true \
    && rosdep update

COPY . /tmp/urc-package-manifests

RUN apt-get update \
    && rosdep install \
      --from-paths /tmp/urc-package-manifests \
      --ignore-src \
      --skip-keys nanopb \
      --rosdistro humble \
      -r -y \
    && rm -rf /tmp/urc-package-manifests /var/lib/apt/lists/*

RUN existing_group="$(getent group "${USER_GID}" | cut -d: -f1 || true)" \
    && if [[ -z "${existing_group}" ]]; then \
         groupadd --gid "${USER_GID}" "${USER_NAME}"; \
         existing_group="${USER_NAME}"; \
       fi \
    && useradd \
      --uid "${USER_UID}" \
      --gid "${existing_group}" \
      --create-home \
      --shell /bin/bash \
      "${USER_NAME}" \
    && echo "${USER_NAME} ALL=(ALL) NOPASSWD:ALL" > "/etc/sudoers.d/${USER_NAME}" \
    && chmod 0440 "/etc/sudoers.d/${USER_NAME}" \
    && mkdir -p \
      /workspace/rover_ws/src \
      /workspace/rover_ws/build \
      /workspace/rover_ws/install \
      /workspace/rover_ws/log \
      "${HOME}/.vnc" \
    && chown -R "${USER_UID}:${USER_GID}" /workspace "${HOME}"

COPY docker/start-vnc.sh /usr/local/bin/start-vnc.sh
RUN chmod +x /usr/local/bin/start-vnc.sh

USER ${USER_NAME}
WORKDIR /workspace/rover_ws

RUN echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> "${HOME}/.bashrc" \
    && echo 'if [[ -f /workspace/rover_ws/install/setup.bash ]]; then source /workspace/rover_ws/install/setup.bash; fi' >> "${HOME}/.bashrc" \
    && echo 'export QT_X11_NO_MITSHM=1' >> "${HOME}/.bashrc" \
    && echo 'export LIBGL_ALWAYS_SOFTWARE=1' >> "${HOME}/.bashrc"

EXPOSE 5901

CMD ["/usr/local/bin/start-vnc.sh"]
