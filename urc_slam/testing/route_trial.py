"""Drive a fixed route in simulation and compare /slam/odometry with ground truth.

The route is closed-loop on /ground_truth/odom, so it covers the same distances
regardless of the simulator's real-time factor:

    rest 10 s -> reverse 3 m -> sideways 1.5 m -> forward arc 3 m -> sideways back 1.5 m

Errors compare displacement from the first SLAM odometry message, so they are
independent of where each frame's origin is. Requires the simulation and SLAM
to be running.
"""
import math
import sys
import time

from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import rclpy
from rclpy.node import Node

REST_S = 10.0
LEG_M = 3.0
LATERAL_LEG_M = 1.5
SPEED_MPS = 0.3
LATERAL_SPEED_MPS = 0.25
ARC_TURN_RATE_RADPS = 0.15
LEG_TIMEOUT_S = 90.0
SETTLE_AFTER_LEG_S = 1.5
STARTUP_TIMEOUT_S = 30.0


def yaw(q):
    return math.atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z))


def wrap(angle):
    return math.atan2(math.sin(angle), math.cos(angle))


def rms(values):
    return math.sqrt(sum(v * v for v in values) / len(values))


class RouteTrial(Node):

    def __init__(self):
        super().__init__('slam_route_trial')
        self.cmd = self.create_publisher(Twist, '/cmd_vel', 10)
        self.truth = None
        self.slam = None
        self.start = None
        self.errors = []
        self.z_errors = []
        self.create_subscription(Odometry, '/ground_truth/odom', self.on_truth, 50)
        self.create_subscription(Odometry, '/slam/odometry', self.on_slam, 50)

    def on_truth(self, msg):
        p = msg.pose.pose
        self.truth = (p.position.x, p.position.y, yaw(p.orientation), p.position.z)

    def on_slam(self, msg):
        p = msg.pose.pose
        self.slam = (p.position.x, p.position.y, yaw(p.orientation), p.position.z)
        if self.start is None and self.truth is not None:
            self.start = (self.slam, self.truth)
        if self.start is not None:
            self.errors.append(self.horizontal_error())
            self.z_errors.append(abs(self.z_error()))

    def displacements(self):
        slam_start, truth_start = self.start
        return (
            (self.slam[0] - slam_start[0], self.slam[1] - slam_start[1]),
            (self.truth[0] - truth_start[0], self.truth[1] - truth_start[1]),
        )

    def horizontal_error(self):
        slam, truth = self.displacements()
        return math.hypot(slam[0] - truth[0], slam[1] - truth[1])

    def z_error(self):
        slam_start, truth_start = self.start
        return (self.slam[3] - slam_start[3]) - (self.truth[3] - truth_start[3])

    def distance_from(self, origin):
        return math.hypot(self.truth[0] - origin[0], self.truth[1] - origin[1])

    def drive(self, twist, done):
        end = time.time() + LEG_TIMEOUT_S
        while time.time() < end and not done():
            self.cmd.publish(twist)
            rclpy.spin_once(self, timeout_sec=0.02)
        self.cmd.publish(Twist())
        settle_end = time.time() + SETTLE_AFTER_LEG_S
        while time.time() < settle_end:
            rclpy.spin_once(self, timeout_sec=0.02)

    def hold_still(self, seconds):
        end = time.time() + seconds
        self.drive(Twist(), lambda: time.time() >= end)

    def drive_distance(self, metres, vx=0.0, vy=0.0, wz=0.0):
        twist = Twist()
        twist.linear.x = vx
        twist.linear.y = vy
        twist.angular.z = wz
        origin = self.truth
        self.drive(twist, lambda: self.distance_from(origin) >= metres)

    def report(self, label):
        slam, truth = self.displacements()
        print(
            f'{label:<14} slam ({slam[0]:6.2f},{slam[1]:6.2f})  '
            f'truth ({truth[0]:6.2f},{truth[1]:6.2f})  '
            f'error {self.horizontal_error():.2f} m  z error {self.z_error():+.2f} m',
            flush=True)


def main():
    rclpy.init()
    trial = RouteTrial()
    deadline = time.time() + STARTUP_TIMEOUT_S
    while trial.start is None and time.time() < deadline:
        rclpy.spin_once(trial, timeout_sec=0.1)
    if trial.start is None:
        print('No /slam/odometry and /ground_truth/odom received; is SLAM running?')
        return 1

    trial.hold_still(REST_S)
    trial.report('after rest')

    trial.drive_distance(LEG_M, vx=-SPEED_MPS)
    trial.report('reverse')
    trial.drive_distance(LATERAL_LEG_M, vy=LATERAL_SPEED_MPS)
    trial.report('sideways')
    start_yaw = trial.truth[2]
    trial.drive_distance(LEG_M, vx=SPEED_MPS, wz=ARC_TURN_RATE_RADPS)
    print(f'  arc turned {math.degrees(wrap(trial.truth[2] - start_yaw)):.0f} deg (truth)')
    trial.report('arc')
    trial.drive_distance(LATERAL_LEG_M, vy=-LATERAL_SPEED_MPS)
    trial.report('sideways back')

    print(f'horizontal error RMS {rms(trial.errors):.2f} m  max {max(trial.errors):.2f} m  '
          f'samples {len(trial.errors)}')
    print(f'z error RMS {rms(trial.z_errors):.2f} m  max {max(trial.z_errors):.2f} m')
    return 0


if __name__ == '__main__':
    sys.exit(main())
