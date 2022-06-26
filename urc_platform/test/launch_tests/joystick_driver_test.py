import time
import unittest
import rclpy
import launch
import launch_ros.actions
import launch_testing
import launch_testing_ros
import pytest
import sensor_msgs
import urc_msgs

from ament_index_python.packages import get_package_share_directory
import os


@pytest.mark.rostest
def generate_test_description():

    joystick_driver = launch_ros.actions.Node(
            package='urc_platform',
            executable='urc_platform_JoystickDriver',
            output='screen',
            parameters=[]
        )

    return launch.LaunchDescription([
        joystick_driver,
        launch_testing.actions.ReadyToTest()
    ]), locals()


class TestJoystickDriver(unittest.TestCase):
    def setUp(self):
        self.context = rclpy.Context()
        rclpy.init(context=self.context)
        self.node = rclpy.create_node(
            'test_joystick_driver_node', context=self.context,
            allow_undeclared_parameters=True, automatically_declare_parameters_from_overrides=True
        )
        self.message_pump = launch_testing_ros.MessagePump(
            self.node, context=self.context
        )

        self.pub = self.node.create_publisher(
            urc_msgs.msg.VelocityPair, '/motors', 1
        )

        self.joySub = self.node.create_subscription(
            sensor_msgs.msg.Joy, '/joy', self.joyCallback, 1
        )
        self.received_joy_msg = None

        self.velocitySub = self.node.create_subscription(
            urc_msgs.msg.VelocityPair, '/motors', self.velocityCallback, 1
        )
        self.received_vel_msg = None

        self.message_pump.start()

    def test_0_fullForward(self):

    def test_1_fullReverse(self):

    def test_2_spinRight(self):

    def test_3_spinLeft(self):

    def test_4_halfForward(self):

    def test_5_halfReverse(self):

    def test_6_halfSpinRight(self):

    def test_7_halfSpinLeft(self):

    def joyCallback(self, msg):
        self.recieved_joy_msg = sensor_msgs.msg.Joy()
        self.recieved_joy_msg = msg

    def velocityCallback(self, msg):
        self.recieved_vel_msg = urc_msgs.msg.VelocityPair()
        self.recieved_vel_msg = msg

    def tearDown(self):
        self.message_pump.stop()
        self.node.destroy_node()
        rclpy.shutdown(context=self.context)