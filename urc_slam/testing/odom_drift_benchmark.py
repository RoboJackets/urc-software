"""Measure how far /slam/odometry drifts between keyframes.

Run alongside a drive. Odometry messages whose stamp later appears in
/slam/path are keyframe messages; the rest are between keyframes. For each
in-between message, drift is its ground-truth error minus the error of the
most recent keyframe message, i.e. the error added since the last optimize().
The correction jump is the drift of the last message before each keyframe.

Stops after the given duration or on SIGUSR1, then prints the statistics.
"""
import argparse
import math
import signal
import sys
import time

from nav_msgs.msg import Odometry, Path
import rclpy
from rclpy.node import Node


def stamp_ns(stamp):
    return stamp.sec * 1_000_000_000 + stamp.nanosec


def percentile(values, fraction):
    ordered = sorted(values)
    return ordered[min(len(ordered) - 1, int(fraction * len(ordered)))]


def summary(values):
    return (f'median {percentile(values, 0.5):.3f} m  p95 {percentile(values, 0.95):.3f} m  '
            f'max {max(values):.3f} m')


class OdometryDriftBenchmark(Node):

    def __init__(self):
        super().__init__('odom_drift_benchmark')
        self.truth = None
        # (odometry stamp ns, slam xy, truth xy, wall time)
        self.samples = []
        self.keyframe_stamps = set()
        self.create_subscription(Odometry, '/ground_truth/odom', self.on_truth, 50)
        self.create_subscription(Odometry, '/slam/odometry', self.on_slam, 50)
        self.create_subscription(Path, '/slam/path', self.on_path, 10)

    def on_truth(self, msg):
        self.truth = (msg.pose.pose.position.x, msg.pose.pose.position.y)

    def on_slam(self, msg):
        if self.truth is None:
            return
        p = msg.pose.pose.position
        self.samples.append((stamp_ns(msg.header.stamp), (p.x, p.y), self.truth, time.time()))

    def on_path(self, msg):
        for pose in msg.poses:
            self.keyframe_stamps.add(stamp_ns(pose.header.stamp))

    def report(self):
        if len(self.samples) < 10:
            print('Not enough /slam/odometry received')
            return 1
        slam_start, truth_start = self.samples[0][1], self.samples[0][2]

        def error(sample):
            return (sample[1][0] - slam_start[0] - (sample[2][0] - truth_start[0]),
                    sample[1][1] - slam_start[1] - (sample[2][1] - truth_start[1]))

        keyframe_error = None
        keyframe_time = None
        last_drift = None
        drifts = []
        drift_ages = []
        jumps = []
        for sample in self.samples:
            e = error(sample)
            if sample[0] in self.keyframe_stamps:
                if last_drift is not None:
                    jumps.append(last_drift)
                keyframe_error, keyframe_time, last_drift = e, sample[3], None
                continue
            if keyframe_error is None:
                continue
            drift = math.hypot(e[0] - keyframe_error[0], e[1] - keyframe_error[1])
            drifts.append(drift)
            drift_ages.append((drift, sample[3] - keyframe_time))
            last_drift = drift

        keyframe_count = sum(1 for s in self.samples if s[0] in self.keyframe_stamps)
        print(f'odometry messages {len(self.samples)}  keyframe messages {keyframe_count}')
        if not drifts:
            print('No odometry between keyframes')
            return 1
        _, worst_age = max(drift_ages)
        print(f'drift since last keyframe: {summary(drifts)} '
              f'({worst_age:.1f} s after its keyframe)')
        if jumps:
            print(f'correction jump at keyframes: {summary(jumps)}  (n={len(jumps)})')
        return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument('duration_s', type=float, nargs='?', default=600.0,
                        help='Maximum recording time in seconds')
    args = parser.parse_args()

    rclpy.init()
    benchmark = OdometryDriftBenchmark()
    stop_requested = []
    signal.signal(signal.SIGUSR1, lambda *_: stop_requested.append(True))
    end = time.time() + args.duration_s
    while time.time() < end and not stop_requested:
        rclpy.spin_once(benchmark, timeout_sec=0.05)
    return benchmark.report()


if __name__ == '__main__':
    sys.exit(main())
