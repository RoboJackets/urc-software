from __future__ import annotations

from abc import ABC, abstractmethod
from dataclasses import dataclass
from typing import Mapping, TYPE_CHECKING

if TYPE_CHECKING:
    import numpy as np


COCO_KEYPOINT_NAMES = (
    "nose",
    "left_eye",
    "right_eye",
    "left_ear",
    "right_ear",
    "left_shoulder",
    "right_shoulder",
    "left_elbow",
    "right_elbow",
    "left_wrist",
    "right_wrist",
    "left_hip",
    "right_hip",
    "left_knee",
    "right_knee",
    "left_ankle",
    "right_ankle",
)

COCO_SKELETON = (
    ("left_shoulder", "right_shoulder"),
    ("left_shoulder", "left_elbow"),
    ("left_elbow", "left_wrist"),
    ("right_shoulder", "right_elbow"),
    ("right_elbow", "right_wrist"),
    ("left_shoulder", "left_hip"),
    ("right_shoulder", "right_hip"),
    ("left_hip", "right_hip"),
    ("left_hip", "left_knee"),
    ("left_knee", "left_ankle"),
    ("right_hip", "right_knee"),
    ("right_knee", "right_ankle"),
)


@dataclass(frozen=True)
class Keypoint:
    """A body keypoint in unmirrored input-image pixel coordinates."""

    x: float
    y: float
    confidence: float


@dataclass(frozen=True)
class BoundingBox:
    x_min: float
    y_min: float
    x_max: float
    y_max: float


@dataclass(frozen=True)
class Pose:
    keypoints: Mapping[str, Keypoint]
    confidence: float
    bounding_box: BoundingBox | None = None


class PoseEstimator(ABC):
    """Converts a BGR image into model-independent human poses."""

    @property
    @abstractmethod
    def name(self) -> str:
        """Return a display name for the active estimator."""

    @abstractmethod
    def estimate(self, image: np.ndarray) -> list[Pose]:
        """Estimate human poses in an unmirrored BGR image."""
