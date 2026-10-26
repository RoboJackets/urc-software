# URC SLAM

`urc_slam` estimates a 3D trajectory using LiDAR registration, IMU
preintegration, GPS positions, and planar wheel odometry in a GTSAM graph.

Build and source the workspace, start the simulation, then start SLAM:

```bash
ros2 launch urc_bringup sim.launch.py
ros2 launch urc_slam slam.launch.py
```

SLAM waits for a settled IMU orientation and sensor transforms before starting.
To run SLAM, the rolling traversability costmap, and the waypoint mission together:

```bash
ros2 launch urc_bringup autonomy_demo.launch.py
```

Parameters are in `config/slam_params.yaml`. The defaults use simulation time.
SLAM publishes `/slam/odometry`, `/slam/path`, `/slam/map_points`, and the
`map` to `base_link` transform. Do not run a competing localization TF publisher.

## Wheel odometry contract

Wheel odometry poses must be in `wheel_odometry.frame` (default `odom`), with
twist expressed in the configured `base_link_frame`. Unexpected frames,
non-finite planar measurements, invalid quaternions, and non-increasing timestamps
are rejected. Valid quaternions are normalized before extracting yaw.

The relative pose retains measured yaw and expresses translation in the previous
body frame. Wheel factors constrain relative x, y, and yaw; they do not treat
unmeasured height, roll, or pitch as zero observations. Velocity factors compare
measured body x/y velocity with the graph's map velocity rotated into the body
frame using the estimated pose. No absolute wheel position or heading is assumed
to be aligned with `map`.

Measurements are matched to keyframes within `wheel_odometry.time_tolerance_sec`.
`wheel_odometry.velocity_sigmas_mps` configures independent x/y velocity standard
deviations in metres per second. `wheel_odometry.translation_sigma_m` and
`wheel_odometry.yaw_sigma_rad` configure relative pose uncertainty. The defaults preserve the previous
numerical velocity noise scale; calibrate them for the deployed drivetrain.

Wheel factors follow the backend's staged-update contract. Delayed wheel updates
refresh the path and invalidate the map for its next timer tick; they do not
reset the current IMU integration window or publish TF with an old timestamp.

The rock landmark pipeline is compiled but is not connected to the running node.
