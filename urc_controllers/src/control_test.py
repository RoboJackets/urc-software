#!/usr/bin/env python3

import rclpy
import math
from rclpy.node import Node
from geometry_msgs.msg import Twist
from urc_msgs.msg import Swerve


class ControlTestNode(Node):
    def __init__(self):
        #TODO: read in module positions from config file
        # Module positions (meters from robot center)
        # These values should match your actual robot dimensions
        module_x = 0.3  # Distance in x-direction (front/back)
        module_y = 0.3  # Distance in y-direction (left/right)

        self.modules = [
            SwerveModule(module_x, module_y, "FL"),    # Front Left
            SwerveModule(-module_x, module_y, "FR"),   # Front Right
            SwerveModule(-module_x, -module_y, "BL"),  # Back Left
            SwerveModule(module_x, -module_y, "BR")    # Back Right
        ]
        
        
        super().__init__('control_test_node')
        self.subscription = self.create_subscription(
            Twist,
            '/cmd_vel',
            self.direction_callback,
            10
        )
        self.swerve_publisher = self.create_publisher(
            Swerve,
            '/swerve/command',
            10
        )

    def direction_callback(self, msg):
        # Control inputs
        desired_vx = msg.linear.x
        desired_vy = msg.linear.y
        desired_omega = msg.angular.z

        for module in self.modules:
            module.calculate_kinematics(
                desired_vx,
                desired_vy,
                desired_omega,
                module.x,
                module.y
            )

        swerve_msg = Swerve()
        swerve_msg.FL_drive_ang_vel = self.modules[0].speed
        swerve_msg.FL_steer_ang = self.modules[0].angle
        swerve_msg.FR_drive_ang_vel = self.modules[1].speed
        swerve_msg.FR_steer_ang = self.modules[1].angle
        swerve_msg.BL_drive_ang_vel = self.modules[2].speed
        swerve_msg.BL_steer_ang = self.modules[2].angle
        swerve_msg.BR_drive_ang_vel = self.modules[3].speed
        swerve_msg.BR_steer_ang = self.modules[3].angle

        self.swerve_publisher.publish(swerve_msg)
    


class SwerveModule:
    def __init__(self, x, y, name):
        self.x = x  # Position relative to robot center
        self.y = y
        self.name = name
        self.angle = 0  # Wheel orientation angle (radians)
        self.speed = 0  # Wheel speed

    def calculate_kinematics(self, vx, vy, omega, robot_x, robot_y):
        # Calculate wheel velocity components
        # vx, vy: desired robot velocity in x, y
        # omega: desired robot angular velocity

        # Velocity due to translation
        wheel_vx = vx
        wheel_vy = vy

        # Velocity due to rotation around robot center
        wheel_vx += -omega * self.y
        wheel_vy += omega * self.x

        # Calculate wheel angle and speed
        self.speed = math.sqrt(wheel_vx**2 + wheel_vy**2)
        if self.speed > 0:
            self.angle = math.atan2(wheel_vy, wheel_vx)
        



def main(args=None):
    rclpy.init(args=args)
    node = ControlTestNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()