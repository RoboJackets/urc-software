from __future__ import annotations

from dataclasses import dataclass
import math

from pose_estimation import Keypoint, Pose


REQUIRED_KEYPOINTS = (
    "left_shoulder",
    "right_shoulder",
    "left_elbow",
    "right_elbow",
    "left_wrist",
    "right_wrist",
)


@dataclass(frozen=True)
class FollowGestureThresholds:
    min_keypoint_confidence: float = 0.5
    min_elbow_angle_degrees: float = 120.0
    min_wrist_span_ratio: float = 2.0
    min_outward_margin_ratio: float = 0.05
    min_arm_elevation_degrees: float = -10.0
    max_arm_elevation_degrees: float = 75.0

    def __post_init__(self) -> None:
        if not 0.0 <= self.min_keypoint_confidence <= 1.0:
            raise ValueError("min_keypoint_confidence must be between 0 and 1")
        if not 0.0 <= self.min_elbow_angle_degrees <= 180.0:
            raise ValueError("min_elbow_angle_degrees must be between 0 and 180")
        if self.min_wrist_span_ratio <= 0.0:
            raise ValueError("min_wrist_span_ratio must be positive")
        if self.min_outward_margin_ratio < 0.0:
            raise ValueError("min_outward_margin_ratio must not be negative")
        if not -90.0 <= self.min_arm_elevation_degrees <= 90.0:
            raise ValueError("min_arm_elevation_degrees must be between -90 and 90")
        if not -90.0 <= self.max_arm_elevation_degrees <= 90.0:
            raise ValueError("max_arm_elevation_degrees must be between -90 and 90")
        if self.min_arm_elevation_degrees > self.max_arm_elevation_degrees:
            raise ValueError(
                "min_arm_elevation_degrees must not exceed "
                "max_arm_elevation_degrees"
            )


@dataclass(frozen=True)
class FollowGestureEvaluation:
    is_follow_gesture: bool
    keypoints_confident: bool
    arms_outward: bool
    arms_extended: bool
    arms_in_elevation_range: bool
    span_wide: bool
    left_elbow_angle_degrees: float
    right_elbow_angle_degrees: float
    left_arm_elevation_degrees: float
    right_arm_elevation_degrees: float
    wrist_span_ratio: float


class FollowGestureClassifier:
    def __init__(self, thresholds: FollowGestureThresholds) -> None:
        self._thresholds = thresholds

    def evaluate(self, pose: Pose) -> FollowGestureEvaluation:
        if any(name not in pose.keypoints for name in REQUIRED_KEYPOINTS):
            return self._failed_evaluation()

        points = {name: pose.keypoints[name] for name in REQUIRED_KEYPOINTS}
        keypoints_confident = all(
            point.confidence >= self._thresholds.min_keypoint_confidence
            for point in points.values()
        )

        left_shoulder = points["left_shoulder"]
        right_shoulder = points["right_shoulder"]
        left_elbow = points["left_elbow"]
        right_elbow = points["right_elbow"]
        left_wrist = points["left_wrist"]
        right_wrist = points["right_wrist"]

        shoulder_width = self._distance(left_shoulder, right_shoulder)
        if shoulder_width <= 1e-6:
            return self._failed_evaluation(keypoints_confident=keypoints_confident)

        torso_center_x = (left_shoulder.x + right_shoulder.x) / 2.0
        outward_margin = shoulder_width * self._thresholds.min_outward_margin_ratio
        arms_outward = all(
            (
                self._extends_outward(
                    left_shoulder,
                    left_elbow,
                    torso_center_x,
                    outward_margin,
                ),
                self._extends_outward(
                    left_elbow,
                    left_wrist,
                    torso_center_x,
                    outward_margin,
                ),
                self._extends_outward(
                    right_shoulder,
                    right_elbow,
                    torso_center_x,
                    outward_margin,
                ),
                self._extends_outward(
                    right_elbow,
                    right_wrist,
                    torso_center_x,
                    outward_margin,
                ),
            )
        )

        left_angle = self._joint_angle_degrees(
            left_shoulder,
            left_elbow,
            left_wrist,
        )
        right_angle = self._joint_angle_degrees(
            right_shoulder,
            right_elbow,
            right_wrist,
        )
        arms_extended = (
            left_angle >= self._thresholds.min_elbow_angle_degrees
            and right_angle >= self._thresholds.min_elbow_angle_degrees
        )

        left_elevation = self._arm_elevation_degrees(left_shoulder, left_wrist)
        right_elevation = self._arm_elevation_degrees(right_shoulder, right_wrist)
        arms_in_elevation_range = all(
            self._thresholds.min_arm_elevation_degrees
            <= elevation
            <= self._thresholds.max_arm_elevation_degrees
            for elevation in (left_elevation, right_elevation)
        )

        wrist_span_ratio = abs(left_wrist.x - right_wrist.x) / shoulder_width
        span_wide = wrist_span_ratio >= self._thresholds.min_wrist_span_ratio
        is_follow_gesture = all(
            (
                keypoints_confident,
                arms_outward,
                arms_extended,
                arms_in_elevation_range,
                span_wide,
            )
        )

        return FollowGestureEvaluation(
            is_follow_gesture=is_follow_gesture,
            keypoints_confident=keypoints_confident,
            arms_outward=arms_outward,
            arms_extended=arms_extended,
            arms_in_elevation_range=arms_in_elevation_range,
            span_wide=span_wide,
            left_elbow_angle_degrees=left_angle,
            right_elbow_angle_degrees=right_angle,
            left_arm_elevation_degrees=left_elevation,
            right_arm_elevation_degrees=right_elevation,
            wrist_span_ratio=wrist_span_ratio,
        )

    @staticmethod
    def _distance(first: Keypoint, second: Keypoint) -> float:
        return math.hypot(second.x - first.x, second.y - first.y)

    @staticmethod
    def _extends_outward(
        inner: Keypoint,
        outer: Keypoint,
        torso_center_x: float,
        margin: float,
    ) -> bool:
        inner_offset = inner.x - torso_center_x
        outer_offset = outer.x - torso_center_x
        same_side = inner_offset * outer_offset > 0.0
        farther_from_torso = abs(outer_offset) >= abs(inner_offset) + margin
        return same_side and farther_from_torso

    @staticmethod
    def _joint_angle_degrees(
        first: Keypoint,
        vertex: Keypoint,
        third: Keypoint,
    ) -> float:
        first_vector = (first.x - vertex.x, first.y - vertex.y)
        third_vector = (third.x - vertex.x, third.y - vertex.y)
        first_length = math.hypot(*first_vector)
        third_length = math.hypot(*third_vector)
        if first_length <= 1e-6 or third_length <= 1e-6:
            return 0.0

        cosine = (
            first_vector[0] * third_vector[0]
            + first_vector[1] * third_vector[1]
        ) / (first_length * third_length)
        return math.degrees(math.acos(max(-1.0, min(1.0, cosine))))

    @staticmethod
    def _arm_elevation_degrees(shoulder: Keypoint, wrist: Keypoint) -> float:
        horizontal_distance = abs(wrist.x - shoulder.x)
        vertical_rise = shoulder.y - wrist.y
        return math.degrees(math.atan2(vertical_rise, horizontal_distance))

    @staticmethod
    def _failed_evaluation(
        keypoints_confident: bool = False,
    ) -> FollowGestureEvaluation:
        return FollowGestureEvaluation(
            is_follow_gesture=False,
            keypoints_confident=keypoints_confident,
            arms_outward=False,
            arms_extended=False,
            arms_in_elevation_range=False,
            span_wide=False,
            left_elbow_angle_degrees=0.0,
            right_elbow_angle_degrees=0.0,
            left_arm_elevation_degrees=0.0,
            right_arm_elevation_degrees=0.0,
            wrist_span_ratio=0.0,
        )


class FollowGestureConfirmation:
    def __init__(self, required_consecutive_frames: int) -> None:
        if required_consecutive_frames < 1:
            raise ValueError("required_consecutive_frames must be at least 1")
        self._required_consecutive_frames = required_consecutive_frames
        self._matching_frames = 0

    @property
    def matching_frames(self) -> int:
        return self._matching_frames

    @property
    def required_frames(self) -> int:
        return self._required_consecutive_frames

    def update(self, matches: bool) -> bool:
        self._matching_frames = self._matching_frames + 1 if matches else 0
        return self._matching_frames >= self._required_consecutive_frames

    def reset(self) -> None:
        self._matching_frames = 0
