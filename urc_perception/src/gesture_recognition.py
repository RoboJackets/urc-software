from __future__ import annotations

import argparse
import os
import time

try:
    import cv2
except ImportError as error:
    raise SystemExit(
        "The camera demo requires OpenCV. Install the 'opencv-python' package."
    ) from error

from follow_gesture_classifier import (
    FollowGestureClassifier,
    FollowGestureConfirmation,
    FollowGestureEvaluation,
    FollowGestureThresholds,
)
from movenet_pose_estimator import DEFAULT_MOVENET_MODEL_URL, MoveNetPoseEstimator
from pose_estimation import COCO_SKELETON, Pose, PoseEstimator
from yolo_pose_estimator import YoloPoseEstimator


WINDOW_NAME = "URC Follow Gesture Prototype"


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Test follow-gesture recognition with a local camera."
    )
    parser.add_argument(
        "--backend",
        choices=("yolo", "movenet"),
        default=os.environ.get("GESTURE_POSE_BACKEND"),
    )
    parser.add_argument("--camera-index", type=int, default=0)
    parser.add_argument("--yolo-model", default="yolo26n-pose.pt")
    parser.add_argument("--device", default="auto")
    parser.add_argument("--movenet-model-url", default=DEFAULT_MOVENET_MODEL_URL)
    parser.add_argument("--detection-confidence", type=float, default=0.25)
    parser.add_argument("--min-keypoint-confidence", type=float, default=0.5)
    parser.add_argument("--min-elbow-angle", type=float, default=120.0)
    parser.add_argument("--min-wrist-span-ratio", type=float, default=2.0)
    parser.add_argument("--min-outward-margin-ratio", type=float, default=0.05)
    parser.add_argument("--min-arm-elevation", type=float, default=-10.0)
    parser.add_argument("--max-arm-elevation", type=float, default=75.0)
    parser.add_argument("--confirmation-frames", type=int, default=5)
    return parser.parse_args()


def select_backend(requested_backend: str | None) -> str:
    if requested_backend is not None:
        return requested_backend

    try:
        selection = input("Pose backend [yolo/movenet] (yolo): ").strip().lower()
    except EOFError:
        return "yolo"

    if not selection:
        return "yolo"
    if selection not in ("yolo", "movenet"):
        raise ValueError(f"Unsupported pose backend: {selection}")
    return selection


def create_estimator(backend: str, arguments: argparse.Namespace) -> PoseEstimator:
    if backend == "yolo":
        return YoloPoseEstimator(
            model_path=arguments.yolo_model,
            device=arguments.device,
            detection_confidence=arguments.detection_confidence,
        )
    if backend == "movenet":
        return MoveNetPoseEstimator(model_url=arguments.movenet_model_url)
    raise ValueError(f"Unsupported pose backend: {backend}")


def create_classifier(arguments: argparse.Namespace) -> FollowGestureClassifier:
    thresholds = FollowGestureThresholds(
        min_keypoint_confidence=arguments.min_keypoint_confidence,
        min_elbow_angle_degrees=arguments.min_elbow_angle,
        min_wrist_span_ratio=arguments.min_wrist_span_ratio,
        min_outward_margin_ratio=arguments.min_outward_margin_ratio,
        min_arm_elevation_degrees=arguments.min_arm_elevation,
        max_arm_elevation_degrees=arguments.max_arm_elevation,
    )
    return FollowGestureClassifier(thresholds)


def draw_pose(
    image,
    pose: Pose,
    minimum_confidence: float,
    color: tuple[int, int, int],
) -> None:
    for start_name, end_name in COCO_SKELETON:
        start = pose.keypoints[start_name]
        end = pose.keypoints[end_name]
        if min(start.confidence, end.confidence) < minimum_confidence:
            continue
        cv2.line(
            image,
            (round(start.x), round(start.y)),
            (round(end.x), round(end.y)),
            color,
            2,
        )

    for keypoint in pose.keypoints.values():
        if keypoint.confidence < minimum_confidence:
            continue
        cv2.circle(
            image,
            (round(keypoint.x), round(keypoint.y)),
            4,
            color,
            -1,
        )

    if pose.bounding_box is not None:
        cv2.rectangle(
            image,
            (round(pose.bounding_box.x_min), round(pose.bounding_box.y_min)),
            (round(pose.bounding_box.x_max), round(pose.bounding_box.y_max)),
            color,
            2,
        )


def draw_status(
    image,
    estimator_name: str,
    inference_milliseconds: float,
    pose_count: int,
    evaluation: FollowGestureEvaluation | None,
    confirmation: FollowGestureConfirmation,
    confirmed: bool,
) -> None:
    status = "FOLLOW CONFIRMED" if confirmed else "waiting"
    color = (0, 255, 0) if confirmed else (0, 200, 255)
    lines = [
        estimator_name,
        f"inference={inference_milliseconds:.1f} ms people={pose_count}",
        (
            f"gesture={status} frames={confirmation.matching_frames}/"
            f"{confirmation.required_frames}"
        ),
    ]
    if evaluation is not None:
        lines.extend(
            (
                f"elbows={evaluation.left_elbow_angle_degrees:.0f}/"
                f"{evaluation.right_elbow_angle_degrees:.0f} deg",
                f"elevation={evaluation.left_arm_elevation_degrees:.0f}/"
                f"{evaluation.right_arm_elevation_degrees:.0f} deg",
                f"wrist/shoulder span={evaluation.wrist_span_ratio:.2f}",
                (
                    "checks: confidence={} outward={} extended={} "
                    "elevation={} span={}".format(
                        int(evaluation.keypoints_confident),
                        int(evaluation.arms_outward),
                        int(evaluation.arms_extended),
                        int(evaluation.arms_in_elevation_range),
                        int(evaluation.span_wide),
                    )
                ),
            )
        )

    for line_index, line in enumerate(lines):
        cv2.putText(
            image,
            line,
            (12, 28 + line_index * 24),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.6,
            color,
            2,
            cv2.LINE_AA,
        )


def run_camera(arguments: argparse.Namespace) -> None:
    backend = select_backend(arguments.backend)
    estimator = create_estimator(backend, arguments)
    classifier = create_classifier(arguments)
    confirmation = FollowGestureConfirmation(arguments.confirmation_frames)

    camera = cv2.VideoCapture(arguments.camera_index)
    if not camera.isOpened():
        raise RuntimeError(
            f"Could not open camera index {arguments.camera_index}. "
            "Check macOS camera permissions for the terminal or editor."
        )

    print(f"Running {estimator.name}. Press Q or Escape to quit.")
    try:
        while True:
            frame_available, frame = camera.read()
            if not frame_available:
                raise RuntimeError("The camera stopped returning frames")

            inference_started = time.perf_counter()
            poses = estimator.estimate(frame)
            inference_milliseconds = (
                time.perf_counter() - inference_started
            ) * 1000.0

            selected_pose = max(poses, key=lambda pose: pose.confidence, default=None)
            evaluation = None
            if selected_pose is not None:
                evaluation = classifier.evaluate(selected_pose)
                candidate_matches = evaluation.is_follow_gesture
            else:
                candidate_matches = False

            confirmed = confirmation.update(candidate_matches)
            display = frame.copy()
            if selected_pose is not None:
                pose_color = (0, 255, 0) if candidate_matches else (0, 200, 255)
                draw_pose(
                    display,
                    selected_pose,
                    arguments.min_keypoint_confidence,
                    pose_color,
                )

            draw_status(
                display,
                estimator.name,
                inference_milliseconds,
                len(poses),
                evaluation,
                confirmation,
                confirmed,
            )
            cv2.imshow(WINDOW_NAME, display)

            key = cv2.waitKey(1) & 0xFF
            if key in (ord("q"), 27):
                break
    finally:
        camera.release()
        cv2.destroyAllWindows()


def main() -> None:
    arguments = parse_arguments()
    try:
        run_camera(arguments)
    except (RuntimeError, ValueError) as error:
        raise SystemExit(str(error)) from error


if __name__ == "__main__":
    main()
