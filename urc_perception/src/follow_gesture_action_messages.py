from __future__ import annotations

from sensor_msgs.msg import Image
from urc_msgs.action import RecognizeFollowGesture
from urc_msgs.msg import DetectionBoundingBox

from follow_gesture_recognition import RecognitionObservation
from pose_estimation import Pose


MAX_UINT32 = 4_294_967_295
NANOSECONDS_PER_SECOND = 1_000_000_000


def create_waiting_feedback(
    required_frames: int,
) -> RecognizeFollowGesture.Feedback:
    feedback = RecognizeFollowGesture.Feedback()
    feedback.state = RecognizeFollowGesture.Feedback.STATE_WAITING_FOR_IMAGE
    feedback.required_frames = required_frames
    return feedback


def create_observation_feedback(
    state: int,
    observation: RecognitionObservation,
) -> RecognizeFollowGesture.Feedback:
    feedback = RecognizeFollowGesture.Feedback()
    feedback.state = state
    feedback.processed_frames = min(observation.processed_frames, MAX_UINT32)
    feedback.matching_frames = observation.matching_frames
    feedback.required_frames = observation.required_frames
    feedback.detection_confidence = observation.detection_confidence
    feedback.inference_milliseconds = observation.inference_milliseconds
    return feedback


def create_detection(
    pose: Pose,
    image_message: Image,
    image_width: int,
    image_height: int,
) -> DetectionBoundingBox:
    if pose.bounding_box is None:
        raise RuntimeError("Confirmed pose did not include a bounding box")

    detection = DetectionBoundingBox()
    detection.header = image_message.header
    detection.class_name = "astronaut"
    detection.confidence = pose.confidence
    detection.image_width = image_width
    detection.image_height = image_height
    detection.x_min = _bounded_pixel(pose.bounding_box.x_min, image_width)
    detection.y_min = _bounded_pixel(pose.bounding_box.y_min, image_height)
    detection.x_max = _bounded_pixel(pose.bounding_box.x_max, image_width)
    detection.y_max = _bounded_pixel(pose.bounding_box.y_max, image_height)
    return detection


def create_result(
    error_code: int,
    message: str,
    detection: DetectionBoundingBox | None = None,
) -> RecognizeFollowGesture.Result:
    result = RecognizeFollowGesture.Result()
    result.error_code = error_code
    result.message = message
    result.has_astronaut_detection = detection is not None
    if detection is not None:
        result.astronaut_detection = detection
    return result


def _bounded_pixel(value: float, dimension: int) -> int:
    return max(0, min(dimension, round(value)))


def has_valid_timeout(duration) -> bool:
    return (
        duration.sec >= 0
        and 0 <= duration.nanosec < NANOSECONDS_PER_SECOND
    )


def duration_seconds(duration) -> float:
    return duration.sec + duration.nanosec / NANOSECONDS_PER_SECOND
