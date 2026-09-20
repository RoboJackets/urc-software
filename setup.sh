#!/usr/bin/env bash
set -euo pipefail

repository_directory="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
compose_file="${repository_directory}/docker/docker-compose.yml"
project_name="urc-software"
command="${1:-start}"

require_docker() {
    if ! command -v docker >/dev/null 2>&1; then
        echo "Docker is not installed or is not on PATH." >&2
        exit 1
    fi

    if ! docker compose version >/dev/null 2>&1; then
        echo "Docker Compose is unavailable. Install Docker Desktop or the Docker Compose plugin." >&2
        exit 1
    fi
}

compose() {
    docker compose --project-name "${project_name}" --file "${compose_file}" "$@"
}

start_container() {
    require_docker

    if [[ "$(uname -s)" == "Linux" ]]; then
        export USER_UID="${USER_UID:-$(id -u)}"
        export USER_GID="${USER_GID:-$(id -g)}"
    fi

    echo "Building and starting the URC TigerVNC development container..."
    compose up --build --detach

    echo
    echo "Container is running."
    echo "TigerVNC address: localhost:${VNC_HOST_PORT:-5901}"
    echo "TigerVNC password: ${VNC_PASSWORD:-ros}"
    echo "Open Terminal Emulator in the desktop to work in /workspace/rover_ws."
    echo "Run '$0 shell' for a host-terminal shell in the container."
}

case "${command}" in
    start)
        start_container
        ;;
    stop)
        require_docker
        compose down
        ;;
    restart)
        require_docker
        compose down
        start_container
        ;;
    shell)
        require_docker
        compose exec urc-development bash
        ;;
    logs)
        require_docker
        compose logs --follow
        ;;
    help|-h|--help)
        echo "Usage: $0 [start|stop|restart|shell|logs|help]"
        ;;
    *)
        echo "Unrecognized command: ${command}" >&2
        echo "Usage: $0 [start|stop|restart|shell|logs|help]" >&2
        exit 1
        ;;
esac
