from __future__ import annotations

from dataclasses import dataclass
import time
from typing import TYPE_CHECKING

from follow_gesture_classifier import (
    FollowGestureClassifier,
    FollowGestureConfirmation,
)
from pose_estimation import Pose, PoseEstimator

if TYPE_CHECKING:
    import numpy as np


@dataclass(frozen=True)
class RecognitionObservation:
    pose: Pose | None
    confirmed: bool
    processed_frames: int
    matching_frames: int
    required_frames: int
    detection_confidence: float
    inference_milliseconds: float


class FollowGestureRecognitionSession:
    def __init__(
        self,
        estimator: PoseEstimator,
        classifier: FollowGestureClassifier,
        confirmation_frames: int,
    ) -> None:
        self._estimator = estimator
        self._classifier = classifier
        self._confirmation = FollowGestureConfirmation(confirmation_frames)
        self._processed_frames = 0

    @property
    def processed_frames(self) -> int:
        return self._processed_frames

    @property
    def required_frames(self) -> int:
        return self._confirmation.required_frames

    def evaluate(self, image: np.ndarray) -> RecognitionObservation:
        inference_started_at = time.monotonic()
        poses = self._estimator.estimate(image)
        inference_milliseconds = (
            time.monotonic() - inference_started_at
        ) * 1000.0

        selected_pose = max(poses, key=lambda pose: pose.confidence, default=None)
        candidate_matches = selected_pose is not None and self._classifier.evaluate(
            selected_pose
        ).is_follow_gesture
        confirmed = self._confirmation.update(candidate_matches)
        self._processed_frames += 1

        return RecognitionObservation(
            pose=selected_pose,
            confirmed=confirmed,
            processed_frames=self._processed_frames,
            matching_frames=self._confirmation.matching_frames,
            required_frames=self._confirmation.required_frames,
            detection_confidence=(
                selected_pose.confidence if selected_pose is not None else 0.0
            ),
            inference_milliseconds=inference_milliseconds,
        )
