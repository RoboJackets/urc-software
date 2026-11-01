from __future__ import annotations

import threading

from sensor_msgs.msg import Image


class LatestImageBuffer:
    def __init__(self) -> None:
        self._lock = threading.Lock()
        self._goal_reserved = False
        self._active = False
        self._latest_image = None
        self._sequence = 0

    def reserve_goal(self) -> bool:
        with self._lock:
            if self._goal_reserved:
                return False
            self._goal_reserved = True
            return True

    def activate(self) -> None:
        with self._lock:
            self._active = True
            self._latest_image = None

    def release_goal(self) -> None:
        with self._lock:
            self._active = False
            self._goal_reserved = False
            self._latest_image = None

    def capture(self, image_message: Image) -> None:
        with self._lock:
            if not self._active:
                return
            self._latest_image = image_message
            self._sequence += 1

    def latest_after(self, sequence: int) -> tuple[Image | None, int]:
        with self._lock:
            if self._latest_image is None or self._sequence == sequence:
                return None, sequence
            return self._latest_image, self._sequence
