# Follow-gesture ONNX model

The runtime uses `yolo26n-pose.onnx`. Download the validated artifact into the
workspace's `models/` directory, outside the source checkout. Exporting the model
is an offline preparation step; neither a camera nor the ROS node performs it.

## Obtain the validated artifact

The exact artifact is available from repository commit
`b8b74d970d254592ecf66b8305153375044bde0b`. The URL is pinned to that commit so
later branch changes cannot replace the downloaded model.

Run from the ROS workspace root on Ubuntu:

```bash
mkdir -p models
curl --fail --location \
  https://raw.githubusercontent.com/RoboJackets/urc-software/b8b74d970d254592ecf66b8305153375044bde0b/yolo26n-pose.onnx \
  --output models/yolo26n-pose.onnx
printf '%s  %s\n' \
  f7db70cd50c69c9461f6b6b3c46dfc31959123d7bf113a396179052ac25e4ea0 \
  models/yolo26n-pose.onnx | sha256sum --check
```

Proceed only if verification prints `models/yolo26n-pose.onnx: OK`. On macOS,
replace `sha256sum --check` with `shasum -a 256 --check`.

| Property | Validated artifact |
| --- | --- |
| Filename | `yolo26n-pose.onnx` |
| Size | 12,111,783 bytes |
| SHA-256 | `f7db70cd50c69c9461f6b6b3c46dfc31959123d7bf113a396179052ac25e4ea0` |
| Source checkpoint | `yolo26n-pose.pt` in the same pinned commit |
| Source checkpoint SHA-256 | `eb3bb8268828aeaf515cec23a4bfafd793944a86fe9af94ba7823609c14522a9` |

The `.pt` checkpoint is not needed to run the ROS endpoint. The artifact remains
in the earlier published commit's history; this change removes binaries from
the current source tree without rewriting that history or publishing a release.
The download and checksum were verified on 2026-11-01 against the local model
used for the ONNX smoke test.

## Run recognition

After sourcing ROS, the built workspace, and the Python environment described in
the [package README](../README.md#follow-gesture-recognition):

```bash
ros2 launch urc_perception follow_gesture_recognition.launch.py \
  model_path:="$(pwd)/models/yolo26n-pose.onnx"
```

The model path must be absolute. A ROS camera image publisher and an action goal
are required before recognition processes frames.

For a newly trained or exported model, record a new immutable download location
and checksum, and repeat gesture validation before deployment. Different
exporter versions or settings may produce different files. Do not change the
expected checksum just to bypass a failed download verification.
