"""Drive a fixed route in simulation and compare /slam/odometry with ground truth.

Routes are closed-loop on /ground_truth/odom, so they cover the same distances
regardless of the simulator's real-time factor:

    default: rest 10 s -> reverse 3 m -> sideways 1.5 m -> forward arc 3 m
             -> sideways back 1.5 m
    sphere:  (world sphere_test.sdf, sphere SPHERE_AHEAD_M straight ahead of
             the spawn) rest 10 s -> approach to STAND_OFF_M -> turn -> half
             orbit at STAND_OFF_M -> turn to face it -> close to RETURN_STOP_M

Errors compare displacement from the first SLAM odometry message, so they are
independent of where each frame's origin is. Requires the simulation and SLAM
to be running. Usage: route_trial.py [default|sphere]
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
# Generous: a cold sim start in the container can take minutes before SLAM publishes
STARTUP_TIMEOUT_S = 300.0
# Must match run_sim_trial.sh's spawn offset for the sphere route
SPHERE_AHEAD_M = 8.0
# Far enough from the sphere (radius 0.5 m) that the rover can turn in place
STAND_OFF_M = 2.5
RETURN_STOP_M = 1.5
TURN_RATE_RADPS = 0.4
TURN_TOLERANCE_RAD = 0.05


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

    def distance_to(self, point):
        return math.hypot(point[0] - self.truth[0], point[1] - self.truth[1])

    def turn_to(self, target_yaw):
        direction = 1.0 if wrap(target_yaw - self.truth[2]) > 0 else -1.0
        twist = Twist()
        twist.angular.z = direction * TURN_RATE_RADPS
        # Stops on reaching the heading or on overshooting it
        self.drive(twist, lambda: direction * wrap(target_yaw - self.truth[2]) < TURN_TOLERANCE_RAD)

    def orbit_half(self, centre, radius):
        """Counter-clockwise half circle around centre, ending on its far side."""
        bearing = lambda: math.atan2(self.truth[1] - centre[1], self.truth[0] - centre[0])
        state = {'last': bearing(), 'swept': 0.0}

        def done():
            now = bearing()
            state['swept'] += wrap(now - state['last'])
            state['last'] = now
            return state['swept'] >= math.pi

        twist = Twist()
        twist.linear.x = SPEED_MPS
        twist.angular.z = SPEED_MPS / radius
        self.drive(twist, done)

    def report(self, label):
        slam, truth = self.displacements()
        print(
            f'{label:<14} slam ({slam[0]:6.2f},{slam[1]:6.2f})  '
            f'truth ({truth[0]:6.2f},{truth[1]:6.2f})  '
            f'error {self.horizontal_error():.2f} m  z error {self.z_error():+.2f} m',
            flush=True)


def default_route(trial):
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


def sphere_route(trial):
    x, y, heading, _ = trial.truth
    sphere = (x + SPHERE_AHEAD_M * math.cos(heading), y + SPHERE_AHEAD_M * math.sin(heading))
    twist = Twist()
    twist.linear.x = SPEED_MPS
    trial.drive(twist, lambda: trial.distance_to(sphere) <= STAND_OFF_M)
    trial.report('approach')
    # Counter-clockwise orbit: tangent heading is the bearing from the sphere + 90 deg
    trial.turn_to(wrap(math.atan2(trial.truth[1] - sphere[1], trial.truth[0] - sphere[0]) + math.pi / 2))
    trial.report('turn')
    trial.orbit_half(sphere, STAND_OFF_M)
    trial.report('half orbit')
    trial.turn_to(math.atan2(sphere[1] - trial.truth[1], sphere[0] - trial.truth[0]))
    trial.report('face sphere')
    trial.drive(twist, lambda: trial.distance_to(sphere) <= RETURN_STOP_M)
    trial.report('return')


ROUTES = {'default': default_route, 'sphere': sphere_route}


def main():
    route = sys.argv[1] if len(sys.argv) > 1 else 'default'
    if route not in ROUTES:
        print(f'Unknown route {route}; choose from {", ".join(ROUTES)}')
        return 1
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
    ROUTES[route](trial)

    print(f'horizontal error RMS {rms(trial.errors):.2f} m  max {max(trial.errors):.2f} m  '
          f'samples {len(trial.errors)}')
    print(f'z error RMS {rms(trial.z_errors):.2f} m  max {max(trial.z_errors):.2f} m')
    return 0


if __name__ == '__main__':
    sys.exit(main())
