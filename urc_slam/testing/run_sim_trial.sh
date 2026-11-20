#!/usr/bin/env bash
# Runs one end-to-end SLAM trial in simulation:
# fresh sim -> SLAM + navsat_transform (+ optional RViz) -> route_trial.py and
# odom_drift_benchmark.py -> summary -> shutdown of everything it started.
#
# Usage: run_sim_trial.sh [--rviz] [--override params.yaml] [label]
# Logs go to ./slam_trial_logs/<label>/. Source the workspace before running.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RVIZ=false
OVERRIDE=""
LABEL="trial"
while [[ $# -gt 0 ]]; do
  case "$1" in
    --rviz) RVIZ=true; shift ;;
    --override) OVERRIDE="$(realpath "$2")"; shift 2 ;;
    -h|--help) sed -n '2,8p' "$0"; exit 0 ;;
    *) LABEL="$1"; shift ;;
  esac
done

SLAM_SHARE="$(ros2 pkg prefix urc_slam)/share/urc_slam"
PARAMS="$SLAM_SHARE/config/slam_params.yaml"
LOG_DIR="$PWD/slam_trial_logs/$LABEL"
mkdir -p "$LOG_DIR"

# Each component runs in its own process group so cleanup stops exactly what
# this script started, including Gazebo's child processes
GROUPS_STARTED=()
start_group() {
  local log="$1"; shift
  setsid "$@" > "$log" 2>&1 &
  GROUPS_STARTED+=("$!")
}
cleanup() {
  for group in "${GROUPS_STARTED[@]}"; do kill -INT -- "-$group" 2>/dev/null || true; done
  sleep 5
  for group in "${GROUPS_STARTED[@]}"; do kill -KILL -- "-$group" 2>/dev/null || true; done
}
trap cleanup EXIT

echo "Starting simulation (logs in $LOG_DIR)"
start_group "$LOG_DIR/sim.log" ros2 launch urc_bringup sim.launch.py autonomy:=false
timeout 120 bash -c 'until ros2 topic list 2>/dev/null | grep -q "^/scan/points$"; do sleep 2; done'
sleep 8

SLAM_PARAMS=(--params-file "$PARAMS")
[[ -n "$OVERRIDE" ]] && SLAM_PARAMS+=(--params-file "$OVERRIDE")
start_group "$LOG_DIR/slam.log" ros2 run urc_slam SlamNode --ros-args -r __node:=slam_node \
  "${SLAM_PARAMS[@]}" --log-level slam_node:=debug
start_group "$LOG_DIR/navsat.log" ros2 run robot_localization navsat_transform_node --ros-args \
  -r __node:=slam_navsat_transform --params-file "$PARAMS" \
  -r gps/fix:=/gps/covariances -r imu:=/imu/fused \
  -r odometry/filtered:=/slam/odometry -r odometry/gps:=/slam/gps_odometry
if [[ "$RVIZ" == true ]]; then
  start_group "$LOG_DIR/rviz.log" ros2 run rviz2 rviz2 -d "$SLAM_SHARE/rviz/slam.rviz" \
    --ros-args -p use_sim_time:=true
fi
sleep 5

echo "=== trial $LABEL${OVERRIDE:+ (override $(basename "$OVERRIDE"))}"
python3 "$SCRIPT_DIR/odom_drift_benchmark.py" > "$LOG_DIR/drift.log" 2>&1 &
BENCHMARK_PID=$!
python3 "$SCRIPT_DIR/route_trial.py" 2>&1 | tee "$LOG_DIR/route.log" | grep -v RTPS || true
kill -USR1 "$BENCHMARK_PID" 2>/dev/null || true
wait "$BENCHMARK_PID" || true

echo "--- odometry drift between keyframes"
grep -v RTPS "$LOG_DIR/drift.log" || true
echo "--- SLAM warnings"
grep -o "\[slam_node\]: .*" "$LOG_DIR/slam.log" | grep -v "registration accepted\|Keyframe [0-9]" \
  | sed -E 's/[0-9]+\.[0-9]+/N/g' | sort | uniq -c | sort -rn | head -8 || true
