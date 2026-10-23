# Rock landmark loop closure: review notes

Branch `feature/rock-landmarks` (local only, never pushed). Everything here is
new files under `urc_slam/`; no existing file was modified.

**Verification status.** This machine has no GTSAM/Boost (WSL Ubuntu has none,
no sudo, Docker daemon was off). So:
- **Built and passing (g++/Eigen only, in WSL):** `test_rock_extractor` and
  `test_jcbb_search` (the R1/R2/R3 worked example, ties, search budget).
- **Written but NOT compiled or run (need GTSAM):** `landmark_associator.cpp`,
  `landmark_manager.cpp`, `rock_landmark_params.cpp`,
  `test_jcbb_vs_nearest_neighbor`, `test_ambiguity`, `test_loop_closure_graph`.
  Treat every GTSAM API call as unchecked against a compiler.

**Design pivot (2D -> 3D).** The first version extracted rocks from a 2D
`LaserScan`. The repo's LiDAR is a 3D `PointCloud2`, so the extractor now works
on the 3D cloud (ground removal, clustering, sphere fit), observations carry a
real elevation, and association gates in 3 dimensions instead of 2.

---

## 1. Architecture as found

**iSAM2 instance.** `SlamBackend::isam` (`slam_backend.hpp:103`), a default
`ISAM2(ISAM2Params())`. Factors/values are staged in the private members
`new_factors` / `new_values`; `SlamBackend::optimize()` (`slam_backend.cpp:274`)
calls `isam.update(new_factors, new_values)`, then `calculateEstimate()` into
`estimate`, clears the staging containers, and caches the latest pose, velocity
and bias. Every public `add*Factor` ends with `optimize()` (so each GPS/LiDAR/
odometry factor triggers its own `update()`), except `addKeyframe`, which only
stages the IMU factor, bias-between factor and predicted values.
`initialize()` does its own `update()` with priors on `x0`, `v0`, `b0`.

**Symbols.** `x(i)` Pose3, `v(i)` Vector3 velocity, `b(i)` imu bias
(`slam_backend.cpp:325-335`, `gtsam::Symbol('x'|'v'|'b', index)`), one index per
keyframe. There are **no landmark keys today**. This work uses `'l'`
(`LandmarkManager::landmarkKey`), which does not collide.

**Factors.**
- LiDAR: `BetweenFactor<Pose3>` x(from)->x(to) from GICP, noise `lidar_noise`.
- Wheel odometry: `BetweenFactor<Pose3>` (`odom_noise`) plus
  `BetweenFactor<Vector3>` on velocities using the translation block of
  `odom_noise`. Built in `SlamNode::processOdometry` from planar x/y only
  (z and orientation zeroed), keyframe-matched by timestamp (0.1 s tolerance).
- GPS: `GPSFactor` on `x(i)` with the covariance taken from the message
  (`addGpsFactor`), buffered and keyframe-matched in `processGPSMeasurements`.
- IMU: `ImuFactor` on (x,v)(prev) -> (x,v)(new) with bias `b(prev)`, plus a
  `BetweenFactor<ConstantBias>` between biases (`addKeyframe`).

**LiDAR message and arrival.** `sensor_msgs::msg::PointCloud2`, subscribed in
`SlamNode` on `lidar_topic` (YAML: `/scan/points`), `SensorDataQoS`, handled in
`SlamNode::lidarCallback`. This is a 3D cloud (the task text expected a 2D
`LaserScan`); the 3D extractor consumes it directly. The callback
voxel-filters it, runs GICP against the last keyframe cloud, and returns early
unless the IMU-predicted motion exceeds the keyframe thresholds (0.5 m /
0.1745 rad). So **sweeps that are not keyframes never have a pose node**, which
matters for when rocks can be processed.

**Measurement-noise parameters in the repo.** All are hard-coded in the
`SlamNode` constructor (`slam_node.cpp:42-51`); none are in YAML. All are
sigmas (`Diagonal::Sigmas`).

| Name (ctor arg) | Value | Where | Describes |
|---|---|---|---|
| `pose_prior_sigmas` | 0.1 (all 6) | slam_node.cpp:45 | Prior on x0 |
| `velocity_prior_sigmas` | 1.0 (3) | slam_node.cpp:46 | Prior on v0 |
| `odom_sigmas` | 1.0 (all 6) | slam_node.cpp:47 | Wheel-odometry relative pose (and its translation block for velocity change) |
| `lidar_sigmas` | 0.2 (all 6) | slam_node.cpp:48 | **GICP relative pose between keyframes**, not raw point range noise and not a feature |
| `bias_prior_sigmas` | 1e-3 (6) | slam_node.cpp:49 | IMU bias prior |
| `bias_between_sigmas` | 1e-4 (6) | slam_node.cpp:50 | IMU bias random walk |
| IMU accel / gyro / integration cov | 0.1^2 / 0.01^2 / 1e-8 | slam_backend.cpp:49-51 | IMU preintegration |
| GPS covariance | from message | slam_node.cpp:287 | GPS position |

**Result: there is no range or bearing noise for raw LiDAR points or for an
extracted feature anywhere in the repo.** The closest, `lidar_sigmas`, is the
noise of an ICP relative pose and is unsuitable for a range/bearing factor.
So the rock noise is a new parameter pair, left unset (NaN, rejected by
`validate()`) with `TODO(AJ): set from repo/measurement`. The tests use
clearly labelled test-only values.

**GTSAM version / marginal APIs.** **Not verified: GTSAM is not installed on
this machine.** The repo pins no version (`find_package(GTSAM REQUIRED)`,
`<depend>gtsam</depend>`); the target is the `osrf/ros:humble-desktop` image
(`docker/docker-compose.yml`). The code uses `boost::shared_ptr`
(`slam_backend.hpp:116`), which means GTSAM 4.x built before the
`std::shared_ptr` switch. From memory (to confirm with the real headers):
`ISAM2::marginalCovariance(Key)` gives a single-key marginal; ISAM2 has no
joint-marginal call, so a pose-landmark joint covariance needs
`gtsam::Marginals(isam.getFactorsUnsafe(), isam.calculateEstimate())
.jointMarginalCovariance({x, l})`, which re-factorizes the whole graph. That is
too slow per scan, hence the approximation in section 6.

## 2. Data flow for one scan

A sensor-frame point cloud (`PointCloud3d`) goes into `RockExtractor::extract`.
It drops points outside a range band, removes ground (`removeGround`: the
lowest z in each point's 3x3 grid neighbourhood is "ground", and points more
than `ground_clearance_m` above it survive), groups the survivors with
Euclidean clustering (`clusterPoints`), keeps clusters of rock-like point
count, width and height, and estimates each rock's centre by least-squares
sphere fit (`fitSphere`), falling back to the visible-point centroid when the
fit is implausible. `LandmarkManager::processScan` then reads the current pose
estimate and marginal covariance from iSAM2, collects existing landmarks
(position + marginal covariance), and calls `LandmarkAssociator::associate`.
The associator predicts each landmark's position in the sensor frame, gates
every (observation, landmark) pair individually with a 3-dof chi-square test
on the Mahalanobis distance, and runs JCBB over the survivors to find the
largest set that is jointly compatible; the shared pose uncertainty correlates
the innovations. Each observation comes back as *matched* (add a Huber-wrapped
`BearingRangeFactor<Pose3,Point3>` from the pose to that landmark), *new* (no
gated candidate at all: add a landmark node initialised from pose plus
measurement, and its factor), or *ambiguous* (log and add nothing). The manager
returns the factors/values as a `LandmarkGraphUpdate` for the backend to merge
into its pending iSAM2 update.

## 3. Reading order

1. `include/rock_types.hpp`, `include/rock_landmark_params.hpp`: data types and
   every tunable. Note the NaN noise.
2. `src/rock_extractor.cpp` (orchestration, size filters, the centre TODO), then
   `src/ground_filter.cpp`, `src/point_clustering.cpp`, `src/sphere_fit.cpp`
   (each one idea; note what each assumes).
3. `include/jcbb_search.hpp` then `src/jcbb_search.cpp`: the algorithm, ROS-
   and GTSAM-free. Look at `jointDistanceSq` (the pose-covariance coupling
   block is the whole idea) and the `>=` bound in `descend` (why ties survive).
4. `src/landmark_associator.cpp`: where the Jacobians and the covariance
   approximation live (`pairTerm`), and how search results become dispositions.
5. `src/landmark_manager.cpp`: association-before-creation, factor/noise
   construction, landmark initialisation.
6. `test/test_jcbb_vs_nearest_neighbor.cpp` (the clearest statement of why JCBB),
   `test_jcbb_search.cpp` (same example without GTSAM), `test_ambiguity.cpp`,
   `test_loop_closure_graph.cpp`, `test_rock_extractor.cpp` (prints sphere-fit vs
   centroid error).

## 4. Parameters added

| Parameter | Default | Effect of raising it |
|---|---|---|
| `extractor.min_range_m` / `max_range_m` | 1.0 / 30.0 | Wider band: more points, but far returns are too sparse to cluster |
| `extractor.ground_cell_size_m` | 0.5 | Larger: tolerates wider rocks and more slope error, but the ground estimate gets coarser. Keep slope x cell < clearance |
| `extractor.ground_clearance_m` | 0.10 | Larger: low rocks vanish; smaller: uneven ground leaks in as false rocks |
| `extractor.cluster_tolerance_m` | 0.15 | Larger: rocks merge with neighbours. Must exceed point spacing at max range |
| `extractor.min_points` / `max_points` | 20 / 20000 | Point-count filter |
| `extractor.min_radius_m` / `max_radius_m` | 0.1 / 1.0 | Bounds sphere radius and (doubled) horizontal extent |
| `extractor.max_height_m` | 1.5 | Rejects people/poles/walls |
| `extractor.max_sphere_rms_m` | 0.05 | Larger: accepts rougher rocks for sphere-fit centres (less centroid fallback, riskier fits) |
| `noise.range_sigma_m` | **unset (NaN)** | `TODO(AJ)`. Larger: wider gates, weaker range constraint. Should include sphere-fit error, not only sensor noise |
| `noise.bearing_sigma_rad` | **unset (NaN)** | `TODO(AJ)`. Same, for azimuth and elevation (one shared sigma: the factor's Unit3 tangent has no preferred axis) |
| `associator.gate_confidence` | 0.99 | Larger gate: more candidates, more JCBB work, more ambiguity |
| `associator.recently_seen_window_poses` | 10 | Larger: more landmarks count as "recent", so single-pairing matches are allowed more often |
| `associator.min_pairings_for_reassociation` | 2 | Larger: loop closures need more simultaneously visible rocks (safer, rarer) |
| `associator.ambiguity_margin` | 2.0 (chi-square units) | Larger: more scans declared ambiguous. Heuristic, not derived |
| `associator.max_search_nodes` | 20000 | JCBB budget; exceeding it marks the scan ambiguous |
| `huber_kernel_width` | 1.345 | Larger: behaves more like plain Gaussian (less outlier protection) |
| `base_T_sensor` | identity | Same placeholder the repo uses (`addKeyframeToMap`) |

Proposed YAML is in `config/rock_landmarks.yaml` (not loaded by anything).

## 5. Required changes to existing files (NOT made)

1. **`include/slam_backend.hpp` / `src/slam_backend.cpp`**:
   - Add `const gtsam::ISAM2 &isam() const` (the member is private) and
     `std::size_t latestIndex() const`. `LandmarkManager::processScan` needs
     both.
   - Add `void addLandmarkUpdate(const NonlinearFactorGraph &, const Values &)`
     that appends to `new_factors`/`new_values` and calls `optimize()`.
     Why: only the backend may touch its staging containers, and it must keep
     `estimate` and the cached latest state in sync.
2. **`src/slam_node.cpp` / `include/slam_node.hpp`**:
   - Declare the parameters in section 4; build a `RockLandmarkParams`; own a
     `RockExtractor` and `LandmarkManager`.
   - **Input adapter:** convert the `PointCloud2` to `PointCloud3d` (finite
     points, sensor frame; one loop). Feed it the raw or lightly filtered cloud,
     **not** the 0.2 m voxel-downsampled one from `LidarFrontend::preprocess`:
     a 0.2 m voxel exceeds `cluster_tolerance_m` and is too sparse for a sphere
     fit on a small rock. This costs a second pass over the cloud per keyframe.
   - Call site: in `lidarCallback`, after `backend.addLidarFactor(...)`
     (and in the first-keyframe branch), run
     `extract -> manager.processScan(obs, current_index, backend.isam()) ->
     backend.addLandmarkUpdate(...)`. This must come **after** the pose is in
     iSAM2 and **before** the next scan. Non-keyframe scans are dropped
     earlier in that function, so rocks are only processed at keyframes
     (0.5 m / 10 deg apart).
   - Pass a `LogSink` that forwards to `RCLCPP_INFO_THROTTLE`.
   - Optional: IMU roll/pitch into `RockExtractor::attitudeIsUsable` (hook; better, rotate the cloud into a gravity-aligned frame first).
3. **`CMakeLists.txt`**: add the eight new `.cpp` files to the library. No new
   package dependencies (GTSAM/Eigen already linked). Optionally
   `add_subdirectory(test)` under `BUILD_TESTING`.
4. **`config/slam_params.yaml`**: merge `config/rock_landmarks.yaml`, and move
   the rock noise out of code once measured.

Unrelated, noticed while reading (not touched): `slam_node.hpp:88` declares
`constexpr std::size_t maximum_odom_buffer_size = 200;` as a non-static member,
which should not compile (needs `static constexpr`). If the branch you based
this on builds for you, ignore this.

## 6. Approximations, assumptions, known weaknesses

- **Pose-landmark cross-covariance is ignored** (block-diagonal joint covariance;
  `landmark_associator.cpp`, `pairTerm`). The innovation depends on pose error
  minus landmark error; for a landmark mapped from a nearby pose these are
  positively correlated, so the true innovation covariance is *smaller* than
  what is used. Consequence: the gate is **too loose**, never too tight. More
  false candidates reach JCBB, and a wrong match is less likely to be refused.
  Landmark-landmark cross terms are ignored for the same reason.
- **Centre bias** (the TODO in `rock_extractor.cpp`): the 3D sweep still sees
  only the near cap. The sphere fit removes most of the shift for round rocks
  (synthetic test: ~0.4 mm vs ~0.2 m centroid error), but that test uses
  perfect spheres. Real rocks are irregular, the algebraic fit is biased for
  small caps, and the centroid fallback keeps the old bias. Unsolved by design;
  needs real data.
- **Ground model is crude.** Lowest-z-in-3x3-cells assumes a roughly level
  sensor and gentle slope (slope x cell size < clearance); boulder fields and
  steep slopes will mis-segment. Half-buried rocks fit a sphere to the exposed
  cap only, so the "centre" is the fitted sphere's, not the rock's.
- Sensor z is assumed up; with vehicle pitch/roll the ground filter degrades
  (see the `attitudeIsUsable` hook).
- Elevation is now measured, but the Unit3 noise treats azimuth and elevation
  identically.
- Chi-square quantile is Wilson-Hilferty and the normal quantile A&S 26.2.23;
  accurate to well under 1% for the dof used, not exact.
- `ambiguity_margin` is a heuristic. An exactly symmetric scene gives a tie;
  a nearly symmetric one may or may not trip it.
- A matched observation uses the Huber kernel as a safety net, but iSAM2 is
  incremental: a wrong accepted match is not undone later.
- Cost: `marginalCovariance` is called for the pose and for **every** landmark
  on every scan. No spatial prefilter yet; this will not scale to a large map.
  JCBB is exponential in the worst case (bounded by `max_search_nodes`).
- Landmarks are never merged, pruned or re-initialised.
- A rock partly occluded or cut by the range-band edge can fail the size filter or the fit.
- A rock seen only once from a poorly known pose is initialised from that
  pose; the landmark is only as good as the pose at creation.
- Comment density follows `CLAUDE.md` ("explain why") rather than `AGENTS.md`
  ("comments are exceptional"); the two conflict and the task file is more
  specific. Tests use a tiny local `CHECK` macro instead of gtest/ament to keep
  the build to GTSAM + Eigen.

## 7. Questions to answer after reading

1. In the R1/R2/R3 example, why does `{R1,R3}` pass every *individual* gate yet
   fail the *joint* test? Which matrix block in `jointDistanceSq` encodes that?
2. Why does the associator return "new landmark" only for observations with no
   gated candidate, and "ambiguous" otherwise? What would break if every
   unmatched observation created a landmark?
3. The pose and a landmark estimated from it have correlated errors. In which
   direction does ignoring that correlation bias the gate, and how would you
   confirm it from a real log?

## How to run the tests

Needs CMake >= 3.16, a C++17 compiler, GTSAM 4.x (with its Boost dependency)
and Eigen. No ROS.

```
cmake -S urc_slam/test -B /tmp/rock_tests
cmake --build /tmp/rock_tests
ctest --test-dir /tmp/rock_tests --output-on-failure
```
