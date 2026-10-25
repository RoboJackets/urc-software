# URC Localization

`urc_localization` prepares sensor data and estimates rover pose. It combines
package-specific ROS 2 components with the `robot_localization` EKF and NavSat
nodes.

## Localization pipeline

[`launch/ekf.launch.py`](launch/ekf.launch.py) starts three nodes:

1. A local EKF fuses `/odom` and `/imu/fused`, publishes
   `/odometry/filtered`, and owns `odom -> base_link`.
2. `navsat_transform_node` combines `/gps/covariances`, `/imu/fused`, and the
   global estimate to publish `/odometry/gps`.
3. A global EKF fuses GPS position with the local estimate, publishes
   `/odometry/filtered_global`, and owns `map -> odom`.

The filter inputs, frames, fused state variables, and noise settings are defined
in [`config/ekf_redemption.yaml`](config/ekf_redemption.yaml).

## Package components

| Executable | Responsibility |
| --- | --- |
| `urc_localization_CovariancesOnImu` | Restamps IMU data and assigns the covariance and `imu_link` frame expected by the filters |
| `urc_localization_CovariancesOnGps` | Restamps GPS fixes and assigns the covariance and `gps_link` frame expected by NavSat |
| `urc_localization_GroundTruth` | Converts a simulation transform into planar ground-truth odometry |
| `urc_localization_GpsImuLocalizer` | Provides a simpler GPS/IMU map-pose estimator outside the EKF pipeline |

These executables are also registered as composable ROS 2 components. Topic
names are parameters; inspect the component source or use `ros2 param describe`
for the complete interface.

## Usage

The full simulation launch starts the covariance adapters, ground-truth adapter,
and EKF pipeline:

```bash
ros2 launch urc_bringup sim.launch.py
```

To start only the filter pipeline:

```bash
ros2 launch urc_localization ekf.launch.py
```

The standalone EKF launch expects its sensor topics to already be available.
Its current configuration enables simulation time, planar estimation, and fixed
sensor covariance assumptions; review those settings before physical-rover use.
