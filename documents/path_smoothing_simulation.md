# Path-Smoothing Simulation Runbook

This runbook assumes the container is running and its browser desktop is already
open at `http://localhost:6060`. Every instruction below is performed in a
terminal inside that browser desktop. Container startup is intentionally outside
the runbook because it depends on the host operating system.

Every browser-terminal command block explicitly enters the workspace and
sources ROS 2 and the workspace, so each block can be copied independently.

## 1. Build the workspace

Open a terminal in the **browser desktop** and run:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
if [ -f install/setup.bash ]; then source install/setup.bash; fi &&
export CMAKE_BUILD_PARALLEL_LEVEL=1 MAKEFLAGS=-j1 &&
colcon build --symlink-install --executor sequential
```

Do not continue if the build reports a failure. Close this terminal after the
build succeeds, or reuse it as Browser Terminal 1.

## 2. Start Gazebo and autonomy

Open **Browser Terminal 1** and run:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
ros2 launch urc_bringup sim.launch.py \
  autonomy:=true \
  add_cube:=true \
  cube_x:=2.5 \
  cube_y:=0.0
```

Keep Browser Terminal 1 running. Gazebo, `ros_gz_bridge`, the sensor covariance
adapters, traversability mapping, and the planner must remain alive.

This launch creates the static `cube_obstacle` at `(2.5, 0.0)`. The cube is
2 m wide, so it blocks the direct route from the test start `(0.0, 0.0)` to the
goal `(4.5, 0.0)`. Before continuing, confirm that Browser Terminal 1 reports a
successful entity creation and that the red cube is visible in Gazebo.

## 3. Verify simulator sensor traffic

Open **Browser Terminal 2** and run:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
echo "Checking simulation clock..." &&
ros2 topic echo /clock --once &&
echo "Checking raw IMU..." &&
ros2 topic echo /imu/data_raw --once --qos-reliability best_effort &&
echo "Checking fused IMU..." &&
ros2 topic echo /imu/fused --once --qos-reliability best_effort &&
echo "Checking LiDAR point cloud..." &&
ros2 topic echo /scan/points --once --qos-reliability best_effort
```

Each check must print one message and advance to the next. Do not start SLAM if
the command stops at one topic without receiving data.

If the clock check blocks, run this in Browser Terminal 2:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
ign topic -l | grep -E 'clock|imu|scan'
```


## 4. Start SLAM

Reuse **Browser Terminal 2** after every sensor check passes:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
ros2 launch urc_slam slam.launch.py rviz:=false
```

Keep Browser Terminal 2 running. Wait for output similar to:

```text
SLAM initialized (roll ..., pitch ...)
```

SLAM requires approximately one second of stable IMU orientation, a LiDAR scan,
and the `base_link` sensor transforms before it publishes the `map` frame.

## 5. Open RViz

Open **Browser Terminal 3** and run:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
ros2 run rviz2 rviz2 \
  -d "$(ros2 pkg prefix urc_bringup)/share/urc_bringup/rviz/autonomy_demo.rviz" \
  --ros-args -p use_sim_time:=true
```

In RViz:

1. Keep the fixed frame set to `map`.
2. Enable `Costmap (traversability_inflated)` and `A* plan`.
3. Set `A* plan` to `Billboards` with a visible line width.
4. Set the path Z offset to approximately `0.5` if the terrain hides it.

## 6. Display raw A*

Open **Browser Terminal 4** and run:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
ros2 param set /planner_server smoothing.bspline.enabled false &&
ros2 param set /planner_server smoothing.smoothness_weight 0.0 &&
ros2 service call /plan urc_msgs/srv/GeneratePlan \
  "{start: {header: {frame_id: map}, pose: {position: {x: 0.0, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}, goal: {header: {frame_id: map}, pose: {position: {x: 4.5, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}}"
```

The response must contain `error_code: 0`. Save a screenshot if a raw-path
baseline is needed.

## 7. Display the gradient-descent path

Reuse **Browser Terminal 4**:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
ros2 param set /planner_server smoothing.bspline.enabled false &&
ros2 param set /planner_server smoothing.data_weight 0.5 &&
ros2 param set /planner_server smoothing.smoothness_weight 0.2 &&
ros2 service call /plan urc_msgs/srv/GeneratePlan \
  "{start: {header: {frame_id: map}, pose: {position: {x: 0.0, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}, goal: {header: {frame_id: map}, pose: {position: {x: 4.5, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}}"
```

Save a screenshot of the gradient-descent path as the B-spline baseline.

## 7. Display the B-Spline path

Reuse **Browser Terminal 4**:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
ros2 param set /planner_server smoothing.data_weight 0.5 &&
ros2 param set /planner_server smoothing.smoothness_weight 0.0 &&
ros2 param set /planner_server smoothing.bspline.sample_spacing 0.1 &&
ros2 param set /planner_server smoothing.bspline.enabled true &&
ros2 service call /plan urc_msgs/srv/GeneratePlan \
  "{start: {header: {frame_id: map}, pose: {position: {x: 0.0, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}, goal: {header: {frame_id: map}, pose: {position: {x: 4.5, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}}"
```

## 8. Display the gradient-descent and B-spline path

Reuse **Browser Terminal 4**:

```bash
cd /home/ubuntu/urc_container/rover_ws &&
source /opt/ros/humble/setup.bash &&
source install/setup.bash &&
ros2 param set /planner_server smoothing.bspline.sample_spacing 0.1 &&
ros2 param set /planner_server smoothing.bspline.enabled true &&
ros2 service call /plan urc_msgs/srv/GeneratePlan \
  "{start: {header: {frame_id: map}, pose: {position: {x: 0.0, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}, goal: {header: {frame_id: map}, pose: {position: {x: 4.5, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}}"
```

The newly published `/path` is the gradient-descent result followed by the
B-spline stage. Compare it with the gradient-descent screenshot, focusing on
heading transitions, waypoint spacing, and clearance around the cube. RViz
shows only the latest path.

The smoothing pipeline does not yet perform post-smoothing costmap validation,
so use these paths only in simulation.

## 9. Shut down

Press `Ctrl+C` in Browser Terminals 4, 3, 2, and 1. Close the browser desktop
when all ROS processes have stopped.
