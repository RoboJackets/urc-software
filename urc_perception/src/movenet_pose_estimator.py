from __future__ import annotations

import numpy as np

from pose_estimation import BoundingBox, COCO_KEYPOINT_NAMES, Keypoint, Pose, PoseEstimator


DEFAULT_MOVENET_MODEL_URL = "https://tfhub.dev/google/movenet/singlepose/lightning/4"


class MoveNetPoseEstimator(PoseEstimator):
    def __init__(
        self,
        model_url: str = DEFAULT_MOVENET_MODEL_URL,
        bounding_box_keypoint_confidence: float = 0.2,
    ) -> None:
        if not 0.0 <= bounding_box_keypoint_confidence <= 1.0:
            raise ValueError(
                "bounding_box_keypoint_confidence must be between 0 and 1"
            )

        try:
            import cv2
            import tensorflow as tf
            import tensorflow_hub as hub
        except ImportError as error:
            raise RuntimeError(
                "The MoveNet backend requires 'opencv-python', 'tensorflow', and "
                "'tensorflow-hub'."
            ) from error

        self._cv2 = cv2
        self._tf = tf
        module = hub.load(model_url)
        self._inference = module.signatures["serving_default"]
        self._input_size = 192
        self._bounding_box_keypoint_confidence = bounding_box_keypoint_confidence
        logical_gpus = tf.config.list_logical_devices("GPU")
        self._device_description = "TensorFlow GPU" if logical_gpus else "TensorFlow CPU"

    @property
    def name(self) -> str:
        return f"MoveNet Lightning ({self._device_description})"

    def estimate(self, image: np.ndarray) -> list[Pose]:
        if image.ndim != 3 or image.shape[2] != 3:
            raise ValueError("MoveNet expects a three-channel BGR image")

        model_input, scale, pad_left, pad_top = self._prepare_input(image)
        tensor = self._tf.convert_to_tensor(model_input, dtype=self._tf.int32)
        outputs = self._inference(tensor)
        output_tensor = outputs.get("output_0", next(iter(outputs.values())))
        raw_keypoints = output_tensor.numpy()[0, 0]

        image_height, image_width = image.shape[:2]
        keypoints = {}
        for index, name in enumerate(COCO_KEYPOINT_NAMES):
            normalized_y, normalized_x, confidence = raw_keypoints[index]
            input_x = float(normalized_x) * self._input_size
            input_y = float(normalized_y) * self._input_size
            x = np.clip((input_x - pad_left) / scale, 0.0, image_width - 1.0)
            y = np.clip((input_y - pad_top) / scale, 0.0, image_height - 1.0)
            keypoints[name] = Keypoint(
                x=float(x),
                y=float(y),
                confidence=float(confidence),
            )

        pose_confidence = float(np.mean(raw_keypoints[:, 2]))
        return [
            Pose(
                keypoints=keypoints,
                confidence=pose_confidence,
                bounding_box=self._bounding_box(keypoints),
            )
        ]

    def _prepare_input(self, image: np.ndarray) -> tuple[np.ndarray, float, int, int]:
        image_height, image_width = image.shape[:2]
        scale = min(self._input_size / image_width, self._input_size / image_height)
        resized_width = max(1, round(image_width * scale))
        resized_height = max(1, round(image_height * scale))
        pad_left = (self._input_size - resized_width) // 2
        pad_top = (self._input_size - resized_height) // 2

        rgb_image = self._cv2.cvtColor(image, self._cv2.COLOR_BGR2RGB)
        resized = self._cv2.resize(
            rgb_image,
            (resized_width, resized_height),
            interpolation=self._cv2.INTER_LINEAR,
        )
        model_input = np.zeros(
            (1, self._input_size, self._input_size, 3),
            dtype=np.uint8,
        )
        model_input[
            0,
            pad_top : pad_top + resized_height,
            pad_left : pad_left + resized_width,
        ] = resized
        return model_input, scale, pad_left, pad_top

    def _bounding_box(self, keypoints: dict[str, Keypoint]) -> BoundingBox | None:
        visible = [
            keypoint
            for keypoint in keypoints.values()
            if keypoint.confidence >= self._bounding_box_keypoint_confidence
        ]
        if not visible:
            return None

        return BoundingBox(
            x_min=min(keypoint.x for keypoint in visible),
            y_min=min(keypoint.y for keypoint in visible),
            x_max=max(keypoint.x for keypoint in visible),
            y_max=max(keypoint.y for keypoint in visible),
        )
