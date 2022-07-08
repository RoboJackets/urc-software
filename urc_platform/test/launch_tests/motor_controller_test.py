import unittest
import rclpy
import launch
import launch_ros.actions
import launch_testing
import launch_testing_ros
import pytest
import urc_msgs.msg

from ament_index_python.packages import get_package_share_directory
import os
import yaml


@pytest.mark.rostest
def generate_test_description():
    parameters_file_path = os.path.join(get_package_share_directory("urc_platform"),
                                        "config", "urc_platform_params.yaml")
    with open(parameters_file_path, 'r') as file:
        motor_controller_params = yaml.safe_load(file)['motor_controller']['ros_parameters']

    motor_controller = launch_ros.actions.Node(
            package='urc_platform',
            executable='urc_platform_MotorController',
            output='screen',
            parameters=[
                motor_controller_params
            ],
            remappings=[
                ('/motor_controller/motors', '/motors'),
                ('/motor_controller/encoders', '/encoders')
            ]
        )

    return launch.LaunchDescription([
        motor_controller,
        launch_testing.actions.ReadyToTest()
    ]), locals()


class TestMotorControllerDriver(unittest.TestCase):
    def setUp(self):
        self.context = rclpy.Context()
        rclpy.init(context=self.context)
        self.node = rclpy.create_node(
            'test_motor_controller_node', context=self.context,
            allow_undeclared_parameters=True, automatically_declare_parameters_from_overrides=True
        )
        self.message_pump = launch_testing_ros.MessagePump(
            self.node, context=self.context
        )

        self.velocityPub = self.node.create_publisher(
            urc_msgs.msg.VelocityPair, '/motors', 1
        )

        self.velocitySub = self.node.create_subscription(
            urc_msgs.msg.VelocityPair, '/encoders', self.velocityCallback, 1
        )
        self.received_vel_msg = None

        self.message_pump.start()

    def velocityCallback(self, msg):
        self.received_vel_msg = msg

    def tearDown(self):
        self.message_pump.stop()
        self.node.destroy_node()
        rclpy.shutdown(context=self.context)
