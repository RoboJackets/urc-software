#!/usr/bin/env bash
set -euo pipefail

export USER="${USER_NAME:-ros}"
export HOME="${HOME:-/home/${USER}}"
export DISPLAY="${VNC_DISPLAY:-:1}"

vnc_directory="${HOME}/.vnc"
mkdir -p "${vnc_directory}"
chmod 700 "${vnc_directory}"

if [[ -z "${VNC_PASSWORD:-}" ]]; then
    echo "VNC_PASSWORD must not be empty." >&2
    exit 1
fi

if [[ ${#VNC_PASSWORD} -gt 8 ]]; then
    echo "TigerVNC only uses the first 8 characters of VNC_PASSWORD." >&2
fi

printf '%s\n' "${VNC_PASSWORD}" | vncpasswd -f > "${vnc_directory}/passwd"
chmod 600 "${vnc_directory}/passwd"

cat > "${vnc_directory}/xstartup" <<'EOF'
#!/usr/bin/env bash
unset SESSION_MANAGER
unset DBUS_SESSION_BUS_ADDRESS
export XKL_XMODMAP_DISABLE=1
export QT_X11_NO_MITSHM=1
export LIBGL_ALWAYS_SOFTWARE=1

xsetroot -solid '#263238'
exec dbus-launch --exit-with-session startxfce4
EOF
chmod +x "${vnc_directory}/xstartup"

vncserver -kill "${DISPLAY}" >/dev/null 2>&1 || true
rm -f "/tmp/.X${DISPLAY#:}-lock" "/tmp/.X11-unix/X${DISPLAY#:}"

cleanup() {
    vncserver -kill "${DISPLAY}" >/dev/null 2>&1 || true
}
trap cleanup EXIT INT TERM

vncserver "${DISPLAY}" \
    -geometry "${VNC_GEOMETRY:-1280x800}" \
    -depth "${VNC_DEPTH:-24}" \
    -localhost no \
    -SecurityTypes VncAuth \
    -AlwaysShared

log_file="${vnc_directory}/$(hostname)${DISPLAY}.log"
echo "TigerVNC is running on ${DISPLAY} (TCP port 5901)."
echo "ROS 2 Humble is sourced in new terminals."

touch "${log_file}"
tail -F "${log_file}" &
wait $!
