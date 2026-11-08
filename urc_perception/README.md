# URC Perception

`urc_perception` owns terrain mapping and camera-based perception components
used by autonomous rover behaviors.

## Mapping pipeline

`TraversabilityMapping`:

1. Transforms the input cloud into the `map` frame and crops it to the cache
   window plus `crop_margin_m`.
2. Extracts an elevation grid and applies the configured Grid Map filter chain.
3. Computes slope, roughness and step height, scores each cell against the
   rover's limits, and inflates lethal cells by the rover footprint.
4. Merges the result into a rolling cache centered on the latest odometry pose.

With the default configuration, the node consumes the SLAM map
(`/slam/map_points`) and `/slam/odometry`, then publishes `/costmap` as
`grid_map_msgs/msg/GridMap`. Navigation consumes its
`traversability_inflated` layer.

## Cost contract

- Cost runs from 0 (easy) to 1 (lethal). `TraversabilityCostFilter` takes the
  worst of slope ÷ `max_slope_rad`, roughness ÷ `max_roughness_m` and
  step height ÷ `max_step_height_m`, capped at 1. Step height is the height
  change to a neighboring cell beyond what the local slope explains.
- `FootprintInflationFilter` makes every cell within `inscribed_radius_m` of a
  lethal cell lethal, then decays cost below lethal out to
  `inflation_radius_m`.
- NaN means the cell has not been observed. Unknown cells are never reported
  as 0.
- The roughness and step limits are provisional and should be set from what
  the rover can actually climb. At 0.25 m resolution, a step near the limit is
  hard to tell apart from a slope near the limit.

## Configuration

- [`config/traversability_params.yaml`](config/traversability_params.yaml)
  defines topics, frames, cache geometry, cropping, rover limits, and the Grid
  Map filter chain.
- [`config/pcl_grid_map_params.yaml`](config/pcl_grid_map_params.yaml) controls
  elevation-grid extraction. It is tuned for the 0.2 m voxel SLAM map and is
  read once at startup.
- [`filter_plugins.xml`](filter_plugins.xml) exports
  `urcPerception/TraversabilityCostFilter` and
  `urcPerception/FootprintInflationFilter`.

## Usage

Start the complete autonomy stack, including mapping and Grid Map visualization:

```bash
ros2 launch urc_bringup autonomy.launch.py
```

Start only the traversability mapper:

```bash
ros2 launch urc_perception mapping.launch.py
```

The standalone mapping launch does not start a point-cloud source, localization,
or the required TF tree. Incoming clouds are skipped when their sensor frame
cannot be transformed into `map`. Tune the map resolution, cache size, filter
radii, and cost calculation together with their navigation consumers.

## Follow-gesture recognition

`follow_gesture_recognition` is a Python ROS node that loads a YOLO pose ONNX
model once, subscribes to the configured RealSense color-image topic, and serves
the `RecognizeFollowGesture` action. The node receives images continuously but
discards them without conversion or inference unless an action goal is active.
While active, it retains only the newest image and limits inference to the
configured rate so stale camera frames cannot build an unbounded queue.

The action reports whether it is waiting for an image, evaluating frames, or has
confirmed the gesture. Feedback includes processed-frame count, consecutive
matching frames, model confidence, and inference latency. A successful result
contains the timestamped astronaut bounding box. Cancellation, missing camera
frames, recognition timeout, and inference failure are distinct outcomes.

Build the packages from the workspace root, then create a Python environment
with access to the ROS Python packages. The following CPU installation matches
the validated Ubuntu 22.04 / Python 3.10 amd64 environment:

```bash
source /opt/ros/humble/setup.bash
colcon build --symlink-install --packages-up-to urc_perception
source install/setup.bash
sudo apt install python3.10-venv
python3 -m venv --system-site-packages .venv
touch .venv/COLCON_IGNORE
source .venv/bin/activate
python -m pip install torch==2.14.1 torchvision==0.29.2 \
  --index-url https://download.pytorch.org/whl/cpu
python -m pip install -r \
  "$(ros2 pkg prefix --share urc_perception)/requirements.txt"
```

The pinned NumPy, OpenCV, ONNX, and `ml-dtypes` versions preserve Humble
`cv_bridge` compatibility. Installing the CPU PyTorch wheels first avoids pulling
CUDA dependencies. The recognition launch disables Ultralytics automatic package
installation so inference cannot silently replace these versions. Activate this
environment in each recognition terminal; model artifacts are supplied
separately and are not installed by this package.

Download the exact validated ONNX model and verify its checksum using
[`docs/follow_gesture_model.md`](docs/follow_gesture_model.md). This uses an
immutable URL from the earlier published commit; no re-export is necessary.

Start the camera and recognition node in separate sourced terminals. The model
path must be absolute because model artifacts are not installed by this package:

```bash
ros2 launch urc_perception d435i.launch.py

ros2 launch urc_perception follow_gesture_recognition.launch.py \
  model_path:=/absolute/path/to/yolo26n-pose.onnx
```

Before sending a goal, confirm the camera topic and action server are available:

```bash
ros2 topic hz /camera/camera/color/image_raw
ros2 action info recognize_follow_gesture
ros2 node info /follow_gesture_recognition
```

Run a bounded recognition attempt and stream its diagnostic feedback:

```bash
ros2 action send_goal --feedback recognize_follow_gesture \
  urc_msgs/action/RecognizeFollowGesture \
  "{recognition_timeout: {sec: 30, nanosec: 0}}"
```

Runtime defaults are in
[`config/follow_gesture_recognition.yaml`](config/follow_gesture_recognition.yaml).
Override `image_topic` at launch when the RealSense wrapper publishes a different
name. Pass `use_sim_time:=true` when using simulated camera timestamps and the
simulation ROS clock.

[`docs/follow_gesture_integration.md`](docs/follow_gesture_integration.md)
documents the coordinator handoff, result handling, cancellation, validation,
and remaining camera/tracking work. `ExecuteAstronautMission` owns the mission;
the coordinator does not yet invoke recognition.
