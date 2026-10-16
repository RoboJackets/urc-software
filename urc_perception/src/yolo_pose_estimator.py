from __future__ import annotations

import os

import numpy as np

from pose_estimation import BoundingBox, COCO_KEYPOINT_NAMES, Keypoint, Pose, PoseEstimator


class YoloPoseEstimator(PoseEstimator):
    def __init__(
        self,
        model_path: str,
        device: str = "auto",
        detection_confidence: float = 0.25,
    ) -> None:
        if not 0.0 <= detection_confidence <= 1.0:
            raise ValueError("detection_confidence must be between 0 and 1")

        os.environ.setdefault("PYTORCH_ENABLE_MPS_FALLBACK", "1")
        try:
            import torch
            from ultralytics import YOLO
        except ImportError as error:
            raise RuntimeError(
                "The YOLO backend requires the 'torch' and 'ultralytics' packages."
            ) from error

        self._device = self._resolve_device(torch, device)
        self._model = YOLO(model_path)
        self._detection_confidence = detection_confidence

    @property
    def name(self) -> str:
        return f"YOLO Pose ({self._device})"

    def estimate(self, image: np.ndarray) -> list[Pose]:
        if image.ndim != 3 or image.shape[2] != 3:
            raise ValueError("YOLO expects a three-channel BGR image")

        predictions = self._model.predict(
            source=image,
            conf=self._detection_confidence,
            device=self._device,
            verbose=False,
        )
        if not predictions or predictions[0].keypoints is None:
            return []

        result = predictions[0]
        coordinates = result.keypoints.xy.detach().cpu().numpy()
        keypoint_confidences = result.keypoints.conf
        if keypoint_confidences is None:
            confidences = np.ones(coordinates.shape[:2], dtype=float)
        else:
            confidences = keypoint_confidences.detach().cpu().numpy()

        boxes = None
        box_confidences = None
        if result.boxes is not None:
            boxes = result.boxes.xyxy.detach().cpu().numpy()
            box_confidences = result.boxes.conf.detach().cpu().numpy()

        poses = []
        for person_index, person_coordinates in enumerate(coordinates):
            keypoints = {
                name: Keypoint(
                    x=float(person_coordinates[index][0]),
                    y=float(person_coordinates[index][1]),
                    confidence=float(confidences[person_index][index]),
                )
                for index, name in enumerate(COCO_KEYPOINT_NAMES)
            }

            bounding_box = None
            pose_confidence = float(np.mean(confidences[person_index]))
            if boxes is not None and person_index < len(boxes):
                x_min, y_min, x_max, y_max = boxes[person_index]
                bounding_box = BoundingBox(
                    x_min=float(x_min),
                    y_min=float(y_min),
                    x_max=float(x_max),
                    y_max=float(y_max),
                )
                pose_confidence = float(box_confidences[person_index])

            poses.append(
                Pose(
                    keypoints=keypoints,
                    confidence=pose_confidence,
                    bounding_box=bounding_box,
                )
            )

        return poses

    @staticmethod
    def _resolve_device(torch_module, requested_device: str) -> str:
        if requested_device != "auto":
            return requested_device

        mps_backend = getattr(torch_module.backends, "mps", None)
        if mps_backend is not None and mps_backend.is_available():
            return "mps"
        if torch_module.cuda.is_available():
            return "0"
        return "cpu"
