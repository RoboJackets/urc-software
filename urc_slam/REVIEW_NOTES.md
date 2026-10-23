# Rock landmark loop closure: review notes

Branch `feature/rock-landmarks` (local only, never pushed). Everything here is
new files under `urc_slam/`; no existing file was modified.

**Verification status: the tests have been written but NOT built or run.**
This machine has no GTSAM/Boost (WSL Ubuntu has none, no sudo, Docker daemon
was off). See "How to run the tests" at the end. Treat every GTSAM API call
below as unchecked against a compiler until that is done.

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
`SlamNode::lidarCallback`. **It is a 3D point cloud, not the 2D `LaserScan`
the task expected.** The callback voxel-filters it, runs GICP against the last
keyframe cloud, and returns early unless the IMU-predicted motion exceeds the
keyframe thresholds (0.5 m / 0.1745 rad). So **scans that are not keyframes
never have a pose node**, which matters for when rocks can be processed.

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

A planar scan (`PlanarScan`) goes into `RockExtractor::extract`, which converts
beams to 2D points, splits them into clusters wherever consecutive ranges jump
by more than a threshold, keeps rock-sized clusters and reports each one's
centroid as (range, bearing, size). `LandmarkManager::processScan` then reads
the current pose estimate and its marginal covariance from iSAM2, collects the
existing landmarks (position + marginal covariance), and hands both to
`LandmarkAssociator::associate`. The associator predicts each landmark's
position in the sensor frame, gates every (observation, landmark) pair
individually with a chi-square test on the Mahalanobis distance, and then
runs JCBB over the surviving pairs to find the largest set that is jointly
compatible, where the shared pose uncertainty correlates the innovations.
Each observation comes back as *matched* (add a Huber-wrapped
`BearingRangeFactor<Pose3,Point3>` from the pose to that landmark), *new* (it
had no gated candidate at all: add a landmark node initialised from pose plus
measurement, and its factor), or *ambiguous* (log and add nothing). The
manager returns the factors/values as a `LandmarkGraphUpdate` for the backend
to merge into its pending iSAM2 update.

## 3. Reading order

1. `include/rock_types.hpp`, `include/rock_landmark_params.hpp`: data types and
   every tunable. Note the NaN noise.
2. `src/rock_extractor.cpp`: clustering; find the centroid TODO and think about it.
3. `include/jcbb_search.hpp` then `src/jcbb_search.cpp`: the algorithm, ROS-
   and GTSAM-free. Look at `jointDistanceSq` (the pose-covariance coupling
   block is the whole idea) and the `>=` bound in `descend` (why ties survive).
4. `src/landmark_associator.cpp`: where the Jacobians and the covariance
   approximation live (`pairTerm`), and how search results become dispositions.
5. `src/landmark_manager.cpp`: association-before-creation, factor/noise
   construction, landmark initialisation.
6. `test/test_jcbb_vs_nearest_neighbor.cpp` (the clearest statement of why JCBB),
   then `test_ambiguity.cpp`, `test_loop_closure_graph.cpp`, `test_rock_extractor.cpp`.

## 4. Parameters added

| Parameter | Default | Effect of raising it |
|---|---|---|
| `extractor.cluster_range_jump_m` | 0.3 | Fewer splits; rocks merge with neighbours/walls |
| `extractor.min_points` / `max_points` | 3 / 100 | Looser size filter by beam count |
| `extractor.min_extent_m` / `max_extent_m` | 0.1 / 1.5 | Looser size filter by width |
| `noise.range_sigma_m` | **unset (NaN)** | `TODO(AJ)`. Larger: wider gates, weaker range constraint |
| `noise.bearing_sigma_rad` | **unset (NaN)** | `TODO(AJ)`. Same, for bearing (also used for the unobserved elevation axis) |
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
   - **Input adapter (a real decision for AJ):** the cloud is 3D
     `PointCloud2`, the extractor wants a `PlanarScan`. Either subscribe to a
     2D `LaserScan` (e.g. from `pointcloud_to_laserscan`) or slice the filtered
     cloud by a height band and bin by bearing. Not written: it needs the
     sensor mounting height, which the repo does not define.
   - Call site: in `lidarCallback`, after `backend.addLidarFactor(...)`
     (and in the first-keyframe branch), run
     `extract -> manager.processScan(obs, current_index, backend.isam()) ->
     backend.addLandmarkUpdate(...)`. This must come **after** the pose is in
     iSAM2 and **before** the next scan. Non-keyframe scans are dropped
     earlier in that function, so rocks are only processed at keyframes
     (0.5 m / 10 deg apart).
   - Pass a `LogSink` that forwards to `RCLCPP_INFO_THROTTLE`.
   - Optional: IMU roll/pitch into `RockExtractor::scanPlaneIsUsable` (hook).
3. **`CMakeLists.txt`**: add the five new `.cpp` files to the library. No new
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
- 2D gating only (x, y in the sensor frame). The scan plane carries no z
  information; the landmark height is unobserved and its factor treats
  elevation as measured 0 with the bearing sigma.
- **Centroid bias** (the verbatim TODO): the near-arc centroid sits between the
  surface and the true centre and moves with viewing direction. A re-observation
  from the opposite side is biased by up to ~a rock radius in the opposite
  direction. The noise model does not account for it. Unsolved by design.
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
- Scans wrapping 360 degrees can split one rock across the first/last beam.
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
