#!/usr/bin/env python3

from __future__ import annotations

import time

from cv_bridge import CvBridge
import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.logging import get_logger
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data
from sensor_msgs.msg import Image
from urc_msgs.action import RecognizeFollowGesture

from follow_gesture_action_messages import (
    create_detection,
    create_observation_feedback,
    create_result,
    create_waiting_feedback,
    duration_seconds,
    has_valid_timeout,
)
from follow_gesture_classifier import FollowGestureClassifier
from follow_gesture_node_config import FollowGestureNodeConfig
from follow_gesture_recognition import (
    FollowGestureRecognitionSession,
    RecognitionObservation,
)
from latest_image_buffer import LatestImageBuffer
from yolo_pose_estimator import YoloPoseEstimator


class FollowGestureRecognitionNode(Node):
    def __init__(self) -> None:
        super().__init__("follow_gesture_recognition")

        self._config = FollowGestureNodeConfig.from_node(self)
        self._callback_group = ReentrantCallbackGroup()
        self._images = LatestImageBuffer()

        self._bridge = CvBridge()
        self._classifier = FollowGestureClassifier(self._config.thresholds)
        self._estimator = YoloPoseEstimator(
            model_path=self._config.model_path,
            device=self._config.device,
            detection_confidence=self._config.detection_confidence,
        )
        self._image_subscription = self.create_subscription(
            Image,
            self._config.image_topic,
            self._handle_image,
            qos_profile_sensor_data,
            callback_group=self._callback_group,
        )
        self._action_server = ActionServer(
            self,
            RecognizeFollowGesture,
            self._config.action_name,
            execute_callback=self._execute_recognition,
            goal_callback=self._handle_goal,
            cancel_callback=self._handle_cancel,
            callback_group=self._callback_group,
        )
        self._log_ready()

    def _log_ready(self) -> None:
        self.get_logger().info(
            "Follow-gesture recognition ready: "
            f"model='{self._config.model_path}', "
            f"estimator='{self._estimator.name}', "
            f"image_topic='{self._config.image_topic}', "
            f"action='{self._config.action_name}', "
            f"inference_rate={self._config.inference_rate_hz:.1f} Hz"
        )

    def _handle_goal(self, goal_request) -> GoalResponse:
        if not has_valid_timeout(goal_request.recognition_timeout):
            self.get_logger().warning("Rejected recognition goal with invalid timeout")
            return GoalResponse.REJECT

        if not self._images.reserve_goal():
            self.get_logger().warning(
                "Rejected recognition goal because another goal is active"
            )
            return GoalResponse.REJECT

        self.get_logger().info("Accepted follow-gesture recognition goal")
        return GoalResponse.ACCEPT

    def _handle_cancel(self, _goal_handle) -> CancelResponse:
        self.get_logger().info("Accepted follow-gesture recognition cancellation")
        return CancelResponse.ACCEPT

    def _handle_image(self, image_message: Image) -> None:
        self._images.capture(image_message)

    def _execute_recognition(self, goal_handle):
        session = FollowGestureRecognitionSession(
            self._estimator,
            self._classifier,
            self._config.confirmation_frames,
        )
        timeout_sec = self._goal_timeout_seconds(goal_handle)
        self._images.activate()
        goal_handle.publish_feedback(
            create_waiting_feedback(session.required_frames)
        )

        try:
            return self._run_recognition(goal_handle, session, timeout_sec)
        except Exception as error:
            self.get_logger().error(f"Follow-gesture inference failed: {error}")
            goal_handle.abort()
            return create_result(
                RecognizeFollowGesture.Result.INFERENCE_FAILED,
                str(error),
            )
        finally:
            self._images.release_goal()

    def _run_recognition(self, goal_handle, session, timeout_sec: float):
        deadline = time.monotonic() + timeout_sec
        last_image_sequence = -1

        while rclpy.ok():
            terminal_result = self._terminal_result(
                goal_handle,
                session.processed_frames,
                deadline,
            )
            if terminal_result is not None:
                return terminal_result

            image_message, sequence = self._images.latest_after(last_image_sequence)
            if image_message is None:
                time.sleep(0.01)
                continue

            frame_started_at = time.monotonic()
            image = self._bridge.imgmsg_to_cv2(image_message, "bgr8")
            observation = session.evaluate(image)
            last_image_sequence = sequence
            self._publish_observation(goal_handle, observation)
            if observation.confirmed:
                return self._complete_success(
                    goal_handle,
                    observation,
                    image_message,
                    image.shape[1],
                    image.shape[0],
                )
            self._limit_inference_rate(frame_started_at)

        goal_handle.abort()
        return create_result(
            RecognizeFollowGesture.Result.INFERENCE_FAILED,
            "ROS stopped before recognition completed.",
        )

    def _terminal_result(self, goal_handle, processed_frames: int, deadline: float):
        if goal_handle.is_cancel_requested:
            goal_handle.canceled()
            return create_result(
                RecognizeFollowGesture.Result.CANCELED,
                "Follow-gesture recognition canceled.",
            )
        if time.monotonic() < deadline:
            return None

        goal_handle.abort()
        if processed_frames == 0:
            error_code = RecognizeFollowGesture.Result.CAMERA_UNAVAILABLE
            message = "No camera image was received before timeout."
        else:
            error_code = RecognizeFollowGesture.Result.RECOGNITION_TIMEOUT
            message = "Follow gesture was not confirmed before timeout."
        self.get_logger().warning(message)
        return create_result(error_code, message)

    def _complete_success(
        self,
        goal_handle,
        observation: RecognitionObservation,
        image_message: Image,
        image_width: int,
        image_height: int,
    ):
        if observation.pose is None:
            raise RuntimeError("Gesture confirmed without an astronaut pose")
        detection = create_detection(
            observation.pose,
            image_message,
            image_width,
            image_height,
        )
        goal_handle.succeed()
        self.get_logger().info(
            "Follow gesture confirmed after "
            f"{observation.processed_frames} processed frames"
        )
        return create_result(
            RecognizeFollowGesture.Result.SUCCESS,
            "Follow gesture confirmed.",
            detection,
        )

    def _publish_observation(
        self,
        goal_handle,
        observation: RecognitionObservation,
    ) -> None:
        state = (
            RecognizeFollowGesture.Feedback.STATE_GESTURE_CONFIRMED
            if observation.confirmed
            else RecognizeFollowGesture.Feedback.STATE_EVALUATING
        )
        goal_handle.publish_feedback(
            create_observation_feedback(state, observation)
        )

    def _goal_timeout_seconds(self, goal_handle) -> float:
        duration = goal_handle.request.recognition_timeout
        timeout_sec = duration_seconds(duration)
        return timeout_sec or self._config.default_timeout_sec

    def _limit_inference_rate(self, frame_started_at: float) -> None:
        frame_duration = time.monotonic() - frame_started_at
        remaining_period = self._config.minimum_inference_period - frame_duration
        time.sleep(max(0.0, remaining_period))


def main(args=None) -> None:
    rclpy.init(args=args)
    node = None
    executor = None
    try:
        node = FollowGestureRecognitionNode()
        executor = MultiThreadedExecutor(num_threads=2)
        executor.add_node(node)
        executor.spin()
    except KeyboardInterrupt:
        pass
    except (RuntimeError, ValueError) as error:
        get_logger("follow_gesture_recognition").fatal(str(error))
    finally:
        if executor is not None:
            executor.shutdown()
        if node is not None:
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
