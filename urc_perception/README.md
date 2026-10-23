# URC Perception

`urc_perception` owns terrain mapping and camera-based perception components
used by autonomous rover behaviors.

## Mapping pipeline

`TraversabilityMapping`:

1. Filters non-finite points and points outside the configured sensor radius.
2. Transforms the cloud into the `map` frame.
3. Extracts an elevation grid and applies the configured Grid Map filter chain.
4. Computes slope and roughness, combines them into traversability cost, and
   inflates that cost with the package's Gaussian filter plugin.
5. Merges the result into a rolling cache centered on the latest odometry pose.

With the default configuration, the node consumes `/scan/points` and
`/odometry/filtered_global`, then publishes `/costmap` as
`grid_map_msgs/msg/GridMap`. Navigation consumes its
`traversability_inflated` layer.

## Configuration

- [`config/traversability_params.yaml`](config/traversability_params.yaml)
  defines topics, frames, cache geometry, point filtering, and the Grid Map
  filter chain.
- [`config/pcl_grid_map_params.yaml`](config/pcl_grid_map_params.yaml) controls
  point-cloud preprocessing and elevation-grid extraction.
- [`filter_plugins.xml`](filter_plugins.xml) exports
  `urcPerception/GaussianFilter` for use in Grid Map filter chains.

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

Install the non-ROS Python runtime dependencies in the environment used to run
ROS:

```bash
python3 -m pip install -r \
  "$(ros2 pkg prefix --share urc_perception)/requirements.txt"
```

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
name. `AstronautFollow` remains the outer sub-mission contract; state-machine
orchestration will invoke this recognition action and then start rover behavior.
