# Follow-gesture endpoint integration

## Ownership and current status

Perception serves `recognize_follow_gesture` using
[`urc_msgs/action/RecognizeFollowGesture`](../../urc_msgs/action/RecognizeFollowGesture.action).
The mission coordinator owns `ExecuteAstronautMission`, recognition activation,
mission transitions, retries, and cancellation. No coordinator action client is
implemented by this perception change.

The node loads the model wrapper at startup; Ultralytics initializes the ONNX
inference backend on the first image. It discards incoming images while dormant.
During a goal it processes only the newest available image at the configured
rate and accepts only one recognition goal at a time.

## Action contract

| Field or outcome | Meaning |
| --- | --- |
| `recognition_timeout` | Positive duration in seconds/nanoseconds; zero selects `default_timeout_sec` (30 seconds by default) |
| Feedback `state` | `STATE_WAITING_FOR_IMAGE`, `STATE_EVALUATING`, or `STATE_GESTURE_CONFIRMED` |
| Feedback counters | Processed frames and consecutive matching frames versus required frames |
| Feedback measurements | Selected person's detection confidence and model inference time in milliseconds |
| `SUCCESS` (0) | ROS status SUCCEEDED; `has_astronaut_detection=true` and the detection payload is available |
| `INVALID_REQUEST` (1) | Reserved result constant; malformed timeouts and concurrent requests are currently rejected before execution, with no result |
| `RECOGNITION_TIMEOUT` (2) | ROS status ABORTED; images were processed but no gesture was confirmed before the deadline |
| `CAMERA_UNAVAILABLE` (3) | ROS status ABORTED; no image was processed before the deadline |
| `INFERENCE_FAILED` (4) | ROS status ABORTED; conversion/inference failed or ROS stopped during recognition |
| `CANCELED` (5) | ROS status CANCELED after an accepted cancellation request |

Check both the ROS terminal status and `error_code`. A bounding box is valid only
when `has_astronaut_detection` is true. Its header preserves the camera image
timestamp and frame; bounds are pixels in the original, unmirrored image.
`class_name="astronaut"` labels the selected person for mission use; the model
does not verify an astronaut suit or personal identity.

## Coordinator implementation requirements

1. On entering `WAIT_FOLLOW`, request recognition asynchronously. Check server
   availability without blocking the mission timer; report an unavailable server
   and apply the coordinator's chosen retry or pause policy.
2. Associate each request with the current mission and recognition attempt.
   Retain its goal handle and permit at most one outstanding recognition request.
3. Accept a successful result only while that same mission remains in
   `WAIT_FOLLOW`. Supply the existing FOLLOW event, which transitions to
   `FOLLOWING`. The coordinator can invoke its internal event directly; the
   perception node does not publish `/command`.
4. Cancel recognition when leaving `WAIT_FOLLOW`, including remote FOLLOW,
   mission cancellation, abort, or shutdown. If a pending request is accepted
   after departure, cancel that goal as well. Discard late feedback/results using
   the mission/attempt identity and state check. Await cancellation completion
   before replacing a request.
5. Treat rejection, timeout, camera absence, and inference failure as distinct
   diagnostic outcomes. They must not initiate following. Choose explicit retry
   or pause behavior; recognition does not retry automatically.

This first integration covers the initial `WAIT_FOLLOW` phase. Gesture-based
resume from `PAUSED` requires a separate activation policy that checks the saved
mission phase; subscribing to the state string alone is insufficient.

The coordinator's existing `/command` input remains available for remote commands
and other producers. A producer using that interface must publish a new,
timestamped `AstronautCommand` with `command=FOLLOW` and `source=GESTURE`; the
coordinator rejects old/repeated timestamps and commands outside its age limit.
Use one path per recognition event to avoid duplicate FOLLOW delivery.

## Camera, tracking, and clock requirements

The input is a BGR-convertible `sensor_msgs/Image` on `image_topic`, defaulting
to `/camera/camera/color/image_raw`, with sensor-data QoS. A compatible YOLO pose
ONNX model must already exist at the absolute `model_path`. Use the
[validated model download and checksum](follow_gesture_model.md). Export models
offline; the camera itself is not converted to ONNX. See the
[package usage](../README.md#follow-gesture-recognition) for environment setup.

Camera, recognition, coordinator, and tracking producers must use the same ROS
clock. Set `use_sim_time:=true` for simulated inputs and ensure `/clock` exists.
Recognition deadlines currently use wall-monotonic time, so they continue while
simulation time is paused. Cancellation is checked between frames; an in-flight
inference cannot be interrupted. Camera header age is not currently validated by
the recognition node, so the coordinator should reject a stale detection before
acting on success. A strict inference-time deadline is not guaranteed.

Continuous `/astronaut/pose` (`geometry_msgs/PoseStamped`) tracking is a separate
requirement. The coordinator needs a fresh pose in, or transformable to, `map`
when following starts. A 2D bounding box supplies neither depth nor a map-frame
pose. Without tracking, the existing following logic enters recovery rather than
following the recognized person. The current estimator selects the
highest-confidence person on each frame; identity continuity across frames is
not established. Validate the initial endpoint with one person in view.

## Standalone inspection

After starting the camera and recognition launch in the same ROS domain:

```bash
ros2 action info /recognize_follow_gesture
ros2 node info /follow_gesture_recognition
ros2 topic hz /camera/camera/color/image_raw
ros2 action send_goal --feedback /recognize_follow_gesture \
  urc_msgs/action/RecognizeFollowGesture \
  "{recognition_timeout: {sec: 30, nanosec: 0}}"
```

Startup logs show the model, image topic, action name, and rate. Action feedback
shows confirmation progress without per-frame logs. Accepted/rejected goals,
cancellation requests, timeout, inference failure, and success have log messages.
The standard autonomy launch does not start this recognition node or a camera.

## Validation evidence and remaining work

Validated on 2026-11-01 in a ROS 2 Humble Ubuntu 22.04 amd64 Docker container
on an Apple Silicon Mac, using an isolated ROS domain (73):

- `urc_msgs` and `urc_perception` built successfully. Snapshot builds emitted
  warnings about omitted external submodules, without build failure.
- A direct ROS action client discovered the installed recognition server.
- ROS/OpenCV image conversion round-tripped correctly with NumPy 1.26.4.
- The exported ONNX model processed a blank image and returned zero poses.
- A two-second goal without a camera returned ABORTED / CAMERA_UNAVAILABLE
  after 2.025 seconds, with waiting feedback and no detection.
- A subsequent goal was accepted; cancellation returned CANCELED / CANCELED
  within 15 milliseconds. These timings are observations, not performance limits.
- The updated launch started successfully with automatic package installation
  disabled. A timed SIGINT stop produced a `KeyboardInterrupt` during node
  destruction; normal single-signal launch shutdown still needs verification.

The developer reports successful live Mac-camera gesture recognition with the
exported ONNX model in the standalone script. That checks the model/classifier
path; real-camera gesture success through the ROS action endpoint remains
unverified. Recorded Mac-camera images can exercise that ROS path before rover
hardware is available. The rover camera still requires validation of its driver,
timestamps, field of view, lighting, and frame rate.

False positives, multi-person behavior, cancellation during inference, target
tracking, and end-to-end mission behavior remain unverified. The no-camera check
validates CAMERA_UNAVAILABLE, not the separate RECOGNITION_TIMEOUT path with
non-matching images.
