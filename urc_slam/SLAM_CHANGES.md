# urc_slam changes

Changes to the LiDAR-inertial SLAM pipeline made on `feat/new-costmap`, on top of
commit `94a58ca`. Everything was built in `/home/rover_ws` and tested in the
`marsyard2020` simulation against `/ground_truth/odom`.

## Integration with the wheel odometry branch

The merged node retains planar wheel pose and body-velocity factors alongside
the per-scan registration and timestamp-aligned IMU windows described below.
Wheel measurements use the new keyframe map's timestamps and the backend's
staged optimization API. Wheel corrections invalidate the map and rebuild the
path without replaying old odometry or TF timestamps. Wheel and rock sources are
included in the package library so the retained regression executables link.
The rock pipeline remains disconnected from runtime scan processing.

## Root causes found

These explained most of the "LiDAR registration did not converge" and drift
problems.

| Problem | Evidence | Fix |
|---|---|---|
| Package built without optimization | `CMAKE_BUILD_TYPE` was empty, so GICP and Eigen templates compiled at `-O0`. Registration took 1.3–6.5 s for ~800 points. | Default to `RelWithDebInfo`. Registration now takes 16–40 ms. |
| Seconds-long callbacks starved the IMU | Odometry stalled entirely. IMU messages were dropped, and predictions reached hundreds of meters. | Fixed by the build type, plus a deeper IMU subscription queue. |
| GPS was never used | `slam.launch.py` fed navsat_transform the raw `/gps` topic, whose covariance is all zeros, so every fix failed validation. This was also true before these changes. | Launch now uses `/gps/covariances` (launch argument `gps_fix_topic`). |
| LiDAR clouds echoed ~35× | `/scan/points` in the sim bridge had no `direction`, so it was bridged both ways. One run saw 665 clouds with only 19 unique stamps. | `direction: GZ_TO_ROS` in `urc_bringup/config/sim_config.yaml` (see "Changes outside urc_slam"). |
| Identity starting orientation | The rover spawns pitched about −5°, so gravity leaked into the IMU prediction as fake acceleration. | Initialize roll and pitch from the IMU (commit `94a58ca`), now including the IMU mounting rotation. |
| Odometry drifted between keyframes | Between keyframes, odometry was IMU-only, with up to 0.85 m drift and 0.85 m correction jumps. | Every scan is now registered (see "Per-scan registration"). |
| The IMU factor overrode the LiDAR | A debug log of LiDAR-measured vs optimized keyframe motion showed differences up to 0.96 m. The Huber loss on the LiDAR factor down-weighted the LiDAR whenever the vibration-corrupted IMU disagreed with it, while the IMU factor kept full weight. | LiDAR factor is plain Gaussian. Differences are now a median of 0.02–0.04 m and a max of 0.08–0.23 m. |
| The fitness gate rejected good alignments | Every rejection in sparse parts of the route had fitness 0.30–0.44 m² with 85–100 % inliers, just over the 0.3 m² cutoff. Three rejections in a row added an IMU-only keyframe, which drifted. That's why drift always appeared at the same spot. Genuinely wrong alignments had about 40 % inliers. | Gate is now fitness ≤ 0.5 m² and inliers ≥ 0.8. Since then, no rejections and no IMU-only keyframes. |

## Behavior changes

### Per-scan registration

- **Every scan is registered.** Each LiDAR scan is now registered with GICP against a local submap. Odometry for that scan is the latest keyframe pose composed with the measured relative motion.
- **IMU fallback.** The IMU prediction is used only for a scan whose registration fails.
- **Keyframe gate uses the LiDAR pose.** The gate (0.5 m, 10° or `keyframe.maximum_interval_s`) is evaluated on the LiDAR-measured pose instead of the IMU prediction. A keyframe reuses that scan's registration result.
- **The factor graph is unchanged.** It still contains one IMU factor and one LiDAR factor per keyframe.

### Registration

- **Local submap target.** The target is a voxel-downsampled union of the last `registration.submap_keyframes` keyframes, instead of only the previous scan.
- **Initial guesses.** The IMU prediction is tried first, then identity. One GICP instance is reused, so point covariances are computed once.
- **Acceptance.** A registration is accepted when the inlier mean squared distance is at most `maximum_fitness_score_m2` and the inlier fraction is at least `minimum_inlier_fraction`. Inliers are points within the correspondence distance. Before, scoring counted every point, including newly visible terrain.
- **Recovery.** After `registration.maximum_consecutive_failures` failed scans, an IMU-only keyframe is added, so SLAM keeps advancing instead of stalling.
- **Logging.** Rejections log the timing, fitness, inlier fraction and the IMU guess, throttled to once per second. Accepted registrations log the same at debug level.
- **Keyframe debug log.** At debug level, each keyframe logs the LiDAR-measured motion next to the optimized motion. A large difference means the IMU factor is overriding the LiDAR.

### IMU handling

- **Buffered integration.** IMU samples are buffered (`ImuBuffer`), and each integration window starts and ends exactly at scan stamps. The sample that straddles a scan stamp is split.
- **Ordering and gaps.**
  - Out-of-order or duplicate IMU samples are dropped.
  - Scans whose stamp isn't newer than the last processed scan are skipped.
  - Scans the IMU hasn't reached yet are skipped until it does.
  - Gaps larger than `imu.maximum_gap_s` are integrated and logged, instead of being dropped silently.
- **IMU extrinsics.** The IMU pose in `base_link` is looked up from TF and passed to GTSAM as `body_P_sensor`.
- **Initial orientation.** Roll and pitch come from the IMU orientation, rotated into `base_link`; yaw is 0.
- **Settled start.** Initialization waits until that orientation has stayed within 0.05 rad for 1 s, so a rover still dropping in at spawn isn't sampled mid-motion. The rover can genuinely spawn pitched by up to about −0.6 rad, before the suspension levels it, and that case initializes and tracks correctly.

### Factor graph

- **LiDAR factor.** The LiDAR between-factor is plain Gaussian, with sigmas of 0.05 rad and 0.1 m (were 0.2 and 0.2). A Huber loss here was tried and removed; see "Root causes found".
- **Robust GPS factor.** The GPS factor uses a Huber loss on the message covariance.
- **Bias random walk.** The bias random-walk noise scales with √(window length) instead of being fixed per keyframe.
- **Keyframe rotation distance.** Uses `Rot3::Logmap(...).norm()` instead of `rpy().norm()`.
- **Time-based keyframes.** A keyframe is also forced after `keyframe.maximum_interval_s`, which keeps velocity constrained when the rover is stationary.
- **Marginal covariances.** After every `optimize()`, the backend computes the latest pose and velocity marginal covariances and publishes them.

### GPS

- **Matcher component.** Validation and matching moved into `GpsKeyframeMatcher`. Matching uses a binary search over keyframe stamps instead of a linear scan.
- **Duplicate fixes.** navsat_transform republishes each fix at 10 Hz. The duplicates are now ignored silently instead of logged as rejections.
- **Matching tolerance.** It is now 0.25 s, half the GPS period. Each fix is shifted to its keyframe's time using that keyframe's estimated velocity, so the wider window doesn't add position error.
- **Effect of a GPS correction.** It updates the path immediately and re-projects the map on the next map tick. It no longer republishes odometry or TF with an old stamp, which used to cause repeated and backwards TF stamps.

### Map and outputs

- **Map storage.** `KeyframeMap` stores keyframe clouds in `base_link` and keeps the published map voxel-downsampled (`map.voxel_size_m`). Clouds are now transformed with the real LiDAR extrinsic from TF instead of identity.
- **Map publishing.** The map is published from a timer (`map.publish_period_s`) only when it changed. It is fully re-projected only after a GPS correction.
- **Odometry covariance.** Odometry carries the pose covariance in the map frame (ROS order) and twist covariance in `base_link`. Angular velocity isn't estimated, so it is marked unknown with variance 1e6.
- **Path.** Keyframe poses are appended to the path, which is rebuilt after GPS corrections. Before, it was resized with empty poses.
- **TF output.** `publish_tf` (default `true`) controls the `map → base_link` TF. Turn it off if another node, such as the EKF, parents `base_link`.

## Changes outside urc_slam

These were made to fix the simulation and enable fair benchmarking, with approval.

- **`urc_bringup/config/sim_config.yaml`:** `/scan/points` is bridged `GZ_TO_ROS` only, which removes the ~35× cloud echo.
- **`urc_localization/src/ground_truth.cpp`:**
  - **Full 3D pose.** `/ground_truth/odom` now publishes the full pose. It used to hard-code z = 0 and drop roll and pitch.
  - **Missing frame.** A TF message without the rover's frame is now skipped. Before, it dereferenced an end iterator, which is undefined behaviour.
  - **New `relative_to_first_pose` parameter** (default `false`). It publishes the pose relative to the start using SLAM's `map` convention: origin at the start, start heading along +x, absolute roll and pitch. The origin is latched only after the pose has been still for 1 s, because the rover spawns at z = 2 m and drops.
- **`urc_bringup/launch/sim.launch.py`:** sets `relative_to_first_pose: true`, so ground truth and SLAM overlay in RViz.

Nothing else in the workspace subscribes to `/ground_truth/odom`.

## Code structure

`slam_node.cpp` (541 lines, everything in one class) was split into focused
components. Headers moved to `include/urc_slam/`.

| File | Responsibility |
|---|---|
| `slam_node` | ROS wiring and orchestration (single-threaded executor contract documented) |
| `slam_backend` | iSAM2 factor graph, IMU preintegration, covariances |
| `lidar_frontend` | Preprocessing, GICP, alignment scoring |
| `imu_buffer` | Stamp-aligned IMU integration windows |
| `gps_keyframe_matcher` | GPS validation and keyframe association |
| `keyframe_map` | Keyframe cloud storage, map and submap building |
| `slam_messages` | GTSAM ↔ ROS message conversion, covariance frame conversion |
| `slam_parameters` | Declaring and validating every parameter |

Other changes:

- **Removed:** dead code (`last_measured_pose`, `odom_noise`, `fitness_epsilon`, which GICP ignores, and unused includes).
- **Formatting:** code reformatted with the repo's `ament_code_style.cfg`.
- **Dependencies:** added `tf2` and an `rviz2` exec dependency. The `rviz/` directory is now installed.

## Parameters

All parameters are in `config/slam_params.yaml`, and every one is validated at
startup. Invalid values throw an error that names the parameter.

- **Renamed:** `lidar_frontend.maximum_fitness_score` → `lidar_frontend.maximum_fitness_score_m2`. Any custom YAML that uses the old name must be updated.
- **New:**
  - `path_topic`, `map_topic`, `gps_topic` (now in the YAML) and `publish_tf`
  - `keyframe.maximum_interval_s` and `lidar_frontend.minimum_inlier_fraction`
  - `registration.*`, `lidar_factor.*`, `prior.*`, `imu.*`, `gps.time_tolerance_s` and `map.*`
- **Changed defaults:**
  - **Fitness threshold:** 2.5 → 0.5 m², scored on inliers only, plus a new minimum inlier fraction of 0.8.
  - **Bias priors:** 1e-3 → 0.1 m/s² for the accelerometer and 0.01 rad/s for the gyro.
  - **Gravity:** 9.81 → 9.8, Gazebo's value.
  - **IMU noise densities:** 0.1 → 0.25 for the accelerometer and 0.01 → 0.03 for the gyro.
  - **LiDAR factor sigmas:** see "Factor graph".

**IMU noise values are sim-specific.** In the sim, the rover's suspension
effort PID makes the chassis vibrate at rest, with accelerometer std 2.3 m/s²
and gyro std 0.29 rad/s, against the configured sensor noise of 0.01 and 0.0005.
The noise densities were set from that measured vibration. On hardware,
re-derive them from logged IMU data, for example with an Allan variance
analysis.

## Launch and visualization

### Build

```bash
cd ~/rover_ws
colcon build --packages-select urc_slam urc_localization urc_bringup
source install/setup.bash
```

`urc_slam` defaults to an optimized `RelWithDebInfo` build. An explicit
`--cmake-args -DCMAKE_BUILD_TYPE=...` still takes precedence.

### Run in simulation

Use two terminals, each sourced with `install/setup.bash`:

```bash
# Terminal 1: simulation (Gazebo, bridge, suspension PID, ground truth)
ros2 launch urc_bringup sim.launch.py autonomy:=false

# Terminal 2: SLAM, navsat_transform and RViz
ros2 launch urc_slam slam.launch.py rviz:=true
```

SLAM waits for the LiDAR extrinsic from TF and for a settled IMU orientation,
then logs `SLAM initialized (roll ..., pitch ...)`.

### Launch arguments (`slam.launch.py`)

| Argument | Default | Purpose |
|---|---|---|
| `rviz` | `false` | Open `rviz/slam.rviz` |
| `gps_fix_topic` | `/gps/covariances` | NavSatFix input for navsat_transform; it must have a populated covariance |

`ros2 launch urc_slam slam.launch.py --show-args` lists them.

The RViz config shows:

- the SLAM map, coloured by height
- the keyframe path (yellow)
- SLAM odometry (red, with its covariance ellipse)
- ground truth (green)

### Debug logging

To see per-registration timing and quality, and per-keyframe LiDAR versus
optimizer motion, run the node directly at debug level instead of through the
launch file. Start navsat_transform separately if you need GPS.

```bash
ros2 run urc_slam SlamNode --ros-args \
  --params-file install/urc_slam/share/urc_slam/config/slam_params.yaml \
  --log-level slam_node:=debug
```

### Driving the rover

The rover is driven with `geometry_msgs/Twist` on `/cmd_vel`. It's a swerve
drive, so `linear.y` moves it sideways. For example:

```bash
ros2 topic pub -r 10 /cmd_vel geometry_msgs/msg/Twist "{linear: {x: -0.3}}"
```

Avoid the slope in +x of the spawn point and turning in place, because the sim
rover tends to flip there.

### Repeating the benchmark

The test route and benchmark used for the results below live in
[`testing/`](testing/README.md). One command runs a fresh sim, SLAM, the route
and the drift benchmark, then prints a summary:

```bash
src/urc_slam/testing/run_sim_trial.sh --rviz my_trial
src/urc_slam/testing/run_sim_trial.sh --override my_params.yaml tuned_trial
```

### Useful checks

```bash
ros2 topic hz /slam/odometry          # one message per LiDAR scan
ros2 topic echo /slam/odometry --once # pose, velocity and covariance
ros2 control list_controllers         # rocker_effort_controller should be active
```

## Validation

**Checks:**

- **Build:** `colcon build --packages-select urc_slam` is clean, with no warnings.
- **Lint:** `ament_uncrustify` (repo config), `ament_cpplint` (excluding copyright and include order; the repo's CMake disables cpplint), `ament_flake8`, `ament_lint_cmake`, `ament_xmllint` and `git diff --check` all pass.

**Sim route.** It is closed-loop on ground truth:

1. 10 s at rest
2. reverse 3 m
3. sideways 1.5 m
4. a 3 m arc turning about 105°
5. sideways back 1.5 m

**Metric.** SLAM odometry versus ground truth, both measured as displacement
from the start. Error is horizontal (x and y). Height error is reported
separately for runs made after ground truth started publishing z.

| Configuration | Runs | RMS error | Max error | IMU-only keyframes |
|---|---|---|---|---|
| Keyframe-only, original IMU noise | 2 | 0.29 / 0.31 m | 1.13 / 1.06 m | 2 / 3 |
| Keyframe-only, tuned IMU noise | 2 | 0.29 / 0.25 m | 0.68 / 0.71 m | 3 / 2 |
| Per-scan, Huber LiDAR factor, 0.3 m² gate | 3 | 0.16 / 0.29 / 0.76 m | 0.51 / 0.56 / 2.61 m | 0 / 2 / 5 |
| Per-scan, Gaussian LiDAR factor, 0.3 m² gate | 2 | 0.22 / 0.20 m | 1.17 / 0.69 m | 4 / 4 |
| **Per-scan, Gaussian, 0.5 m² / 0.8 inlier gate (final defaults)** | 6 | **0.13 / 0.09 / 0.16 / 0.12 / 0.17 / 0.12 m** | **0.35 / 0.27 / 0.32 / 0.36 / 0.53 / 0.25 m** | **0 in all** |

Height error with 3D ground truth, final defaults (3 runs): RMS 0.04 m in every
run, max 0.10–0.12 m.

**Drift of odometry between keyframes.** This is relevant for trajectory
following.

| | Keyframe-only | Final defaults (6 runs) |
|---|---|---|
| Drift since last keyframe, median | 0.12 m | 0.05 m |
| Drift since last keyframe, p95 | 0.44 m | 0.10–0.15 m |
| Drift since last keyframe, max | 0.85 m | 0.17–0.36 m |
| Correction jump at keyframes, median | 0.27 m | 0.04–0.07 m |
| Correction jump at keyframes, p95 | 0.55 m | 0.09–0.14 m |
| Correction jump at keyframes, max | 0.85 m | 0.09–0.21 m |

Final-defaults runs still show 0.02–0.16 m of horizontal error after the 10 s
rest. The optimizer agrees with the LiDAR during that period, so this could be
real body motion while the suspension settles, or differences in when each side
treats the rover as settled. I haven't determined which.

**Verified at runtime:**

- TF lookup of the LiDAR extrinsic waits correctly at startup.
- Duplicate scans are skipped.
- GPS duplicates are silent.
- Registration rejections log their diagnostics.

**Not verified:**

- Behaviour on hardware.
- Long runs (map and keyframe memory growth over many minutes).
- GPS corrections over a long distance.
- **Heading accuracy.** Only position was compared. Ground truth now carries the full orientation, so heading can be added to the benchmark.

## Known limitations and remaining work

- **No loop closure.** All LiDAR factors are between consecutive keyframes, so long-term drift is bounded only by GPS.
- **No scan deskewing.** Gazebo's LiDAR is instantaneous, so this matters only on hardware. It would need per-point timestamps.
- **Trajectory following.** Per-scan registration still leaves small correction jumps at keyframes, up to about 0.15 m in the sim. The standard long-term fix is the REP-105 split: smooth `odom → base_link` from the EKF or wheel odometry, with SLAM publishing only `map → odom`. That spans `urc_localization` and the controllers.
- **Sim rover stability.** The rover flipped on the slope in +x of spawn several times, and the test route avoids it. The suspension PID (kp=120, ki=10, kd=40) vibrates the chassis noticeably at rest.
- **Unbounded storage.** Keyframe clouds are kept for the whole run, roughly 800 points per keyframe after downsampling.
- **Commented-out code.** The disabled identity `backend.initialize(...)` block in the `SlamNode` constructor is kept on request. Delete it once the IMU-based initialization is confirmed (AGENTS.md disallows commented-out code).
- **File size.** `slam_node.cpp` is 481 lines after reformatting, above the 250-line review trigger. It holds only ROS wiring and orchestration; splitting further would scatter one callback flow across files.
