# urc_slam testing

Simulation tools for measuring SLAM accuracy against ground truth. They're run
from source and not installed, and they need the `marsyard2020` simulation from
`urc_bringup`.

| Tool | What it does |
|---|---|
| `run_sim_trial.sh` | One command for a full trial: fresh sim, SLAM, route, benchmark, summary and shutdown |
| `route_trial.py` | Drives the test route closed-loop on ground truth and reports SLAM error after each leg |
| `odom_drift_benchmark.py` | Measures how far `/slam/odometry` drifts between keyframes and the correction jump at each keyframe |

## Full trial

```bash
cd ~/rover_ws && source install/setup.bash
src/urc_slam/testing/run_sim_trial.sh --rviz my_trial
```

- **Parameter overrides:** to compare a parameter change without editing the
  installed config, add `--override file.yaml`. The file contains only the
  parameters being changed, under `slam_node: ros__parameters:`.
- **Logs:** written to `./slam_trial_logs/<label>/` (sim, SLAM at debug level,
  navsat, route and drift).
- **Duration:** a trial takes about 3–4 minutes of wall time.
- **Cleanup:** the script stops only the processes it started. Don't run it while another
  simulation is up, because both would publish on the same topics.

## Against an already running sim and SLAM

```bash
python3 src/urc_slam/testing/odom_drift_benchmark.py > drift.log &
python3 src/urc_slam/testing/route_trial.py
kill -USR1 %1; wait; cat drift.log
```

## The route

1. 10 s at rest
2. reverse 3 m
3. sideways 1.5 m
4. a 3 m forward arc turning about 105°
5. sideways back 1.5 m

Each leg ends on distance measured from ground truth, so the route is the same
regardless of the simulator's speed. It avoids the slope in +x of the spawn
point and turning in place, where the sim rover tends to flip.

## Reading the output

- **Leg errors:** each one is the horizontal distance between SLAM's
  displacement from its start and ground truth's displacement from its start.
  `z error` is the same comparison for height.
- **Drift since last keyframe:** the error that builds up in odometry between
  `optimize()` calls.
- **Correction jump:** how far odometry snaps when the next keyframe is
  optimized. This matters most for trajectory following.

Reference results with the shipped defaults are in `../SLAM_CHANGES.md`
(Validation): horizontal RMS 0.09–0.17 m, height RMS 0.04 m, and correction
jumps at keyframes of at most 0.21 m.
