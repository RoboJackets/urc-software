import time
import unittest
import rclpy
import launch
import launch_ros.actions
import launch_testing
import launch_testing_ros
import pytest
import sensor_msgs.msg

from ament_index_python.packages import get_package_share_directory
import os

parameters_file_path = os.path.join(get_package_share_directory("urc_gazebo"), "config", "urc_gazebo_params.yaml")

@pytest.mark.rostest
def generate_test_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='urc_gazebo',
            executable='scan_to_pointcloud_node',
            parameters=[{
                parameters_file_path
            }]
        ),
        launch_testing.actions.ReadyToTest()
    ]), locals()


class TestScanToPointCloudNode(unittest.TestCase):
    def setUp(self):
        self.context = rclpy.Context()
        rclpy.init(context=self.context)
        self.node = rclpy.create_node('test_scan_to_pointcloud_node', context=self.context,
                all_undeclared_parameters=True, automatically_declare_parameters_from_overrides=True)
        self.message_pump = launch_testing_ros.MessagePump(
            self.node, context=self.context
        )

        self.pub = self.node.create_publisher(
            sensor_msgs.msg.PointCloud2, '/pc2', 1
        )

        self.sub_right = self.node.create_subscription(
            sensor_msgs.msg.PointCloud2, '/pc2', 1
        )
        self.received_msg_right = None

        self.sub_wrong = self.node.create_subscription(
            sensor_msgs.msg.PointCloud2, '/pc2', 1
        )
        self.received_msg_wrong = None

        self.message_pump.start()

    def tearDown(self):
        self.message_pump.stop()
        self.node.destroy_node()
        rclpy.shutdown(context=self.context)

    def invalidTransform(self):
        pointcloud_msg = sensor_msgs.msg.PointCloud2()
        pointcloud_msg.data = [1, 0, 0]

        while self.received_msg_right is None:
            self.pub.publish(pointcloud_msg)
            time.sleep(0.1)

        self.assertIsNotNone(pointcloud_msg)

        self.assertNotAlmostEqual(
            self.received_msg_right.data[0], -1.4142136)
        self.assertNotAlmostEqual(
            self.received_msg_right.data[0], 0)
        self.assertNotAlmostEqual(
            self.received_msg_right.data[0], 1)

    def validTransform(self):
        pointcloud_msg = sensor_msgs.msg.PointCloud2()
        pointcloud_msg.data = [1, 1, 1]

        while self.received_msg_right is None:
            self.pub.publish(pointcloud_msg)
            time.sleep(0.1)

        self.assertIsNotNone(pointcloud_msg)

        self.assertAlmostEqual(
            self.received_msg_right.data[0], -1.4142136)
        self.assertAlmostEqual(
            self.received_msg_right.data[0], 0)
        self.assertAlmostEqual(
            self.received_msg_right.data[0], 1)
