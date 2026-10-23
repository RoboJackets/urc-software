from __future__ import annotations

from dataclasses import dataclass
import os

from rclpy.node import Node

from follow_gesture_classifier import FollowGestureThresholds


MAX_UINT16 = 65_535


@dataclass(frozen=True)
class FollowGestureNodeConfig:
    action_name: str
    image_topic: str
    model_path: str
    device: str
    detection_confidence: float
    confirmation_frames: int
    default_timeout_sec: float
    inference_rate_hz: float
    thresholds: FollowGestureThresholds

    @classmethod
    def from_node(cls, node: Node) -> FollowGestureNodeConfig:
        config = cls(
            action_name=node.declare_parameter(
                "action_name", "recognize_follow_gesture"
            ).value,
            image_topic=node.declare_parameter(
                "image_topic", "/camera/camera/color/image_raw"
            ).value,
            model_path=node.declare_parameter("model_path", "").value,
            device=node.declare_parameter("device", "cpu").value,
            detection_confidence=node.declare_parameter(
                "detection_confidence", 0.25
            ).value,
            confirmation_frames=node.declare_parameter(
                "confirmation_frames", 5
            ).value,
            default_timeout_sec=node.declare_parameter(
                "default_timeout_sec", 30.0
            ).value,
            inference_rate_hz=node.declare_parameter(
                "inference_rate_hz", 10.0
            ).value,
            thresholds=_load_thresholds(node),
        )
        config.validate()
        return config

    @property
    def minimum_inference_period(self) -> float:
        return 1.0 / self.inference_rate_hz

    def validate(self) -> None:
        if not self.action_name:
            raise ValueError("action_name must not be empty")
        if not self.image_topic:
            raise ValueError("image_topic must not be empty")
        if not self.model_path:
            raise ValueError("model_path must not be empty")
        if not os.path.isabs(self.model_path):
            raise ValueError("model_path must be an absolute path")
        if not os.path.isfile(self.model_path):
            raise ValueError(f"model_path does not exist: {self.model_path}")
        if not self.device:
            raise ValueError("device must not be empty")
        if not 0.0 <= self.detection_confidence <= 1.0:
            raise ValueError("detection_confidence must be between 0 and 1")
        if not 1 <= self.confirmation_frames <= MAX_UINT16:
            raise ValueError("confirmation_frames must be between 1 and 65535")
        if self.default_timeout_sec <= 0.0:
            raise ValueError("default_timeout_sec must be positive")
        if self.inference_rate_hz <= 0.0:
            raise ValueError("inference_rate_hz must be positive")


def _load_thresholds(node: Node) -> FollowGestureThresholds:
    return FollowGestureThresholds(
        min_keypoint_confidence=node.declare_parameter(
            "min_keypoint_confidence", 0.5
        ).value,
        min_elbow_angle_degrees=node.declare_parameter(
            "min_elbow_angle_degrees", 120.0
        ).value,
        min_wrist_span_ratio=node.declare_parameter(
            "min_wrist_span_ratio", 2.0
        ).value,
        min_outward_margin_ratio=node.declare_parameter(
            "min_outward_margin_ratio", 0.05
        ).value,
        min_arm_elevation_degrees=node.declare_parameter(
            "min_arm_elevation_degrees", -10.0
        ).value,
        max_arm_elevation_degrees=node.declare_parameter(
            "max_arm_elevation_degrees", 75.0
        ).value,
    )
