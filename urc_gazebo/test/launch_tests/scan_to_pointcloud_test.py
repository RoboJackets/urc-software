import time
import unittest
import rclpy
import launch
import launch_ros.actions
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
import launch_testing
import launch_testing_ros
import pytest
import sensor_msgs.msg


@pytest.mark.rostest
def generate_test_description():

    scan_to_pointcloud = launch_ros.actions.Node(
        package="urc_gazebo",
        executable="urc_gazebo_ScanToPointCloud",
        output="screen",
        parameters=[
            PathJoinSubstitution(
                [
                    FindPackageShare("urc_gazebo"),
                    "config",
                    "scan_to_pointcloud_params.yaml",
                ]
            )
        ],
    )

    return (
        launch.LaunchDescription(
            [scan_to_pointcloud, launch_testing.actions.ReadyToTest()]
        ),
        locals(),
    )


class TestScanToPointCloudNode(unittest.TestCase):
    def setUp(self):
        self.context = rclpy.Context()
        rclpy.init(context=self.context)
        self.node = rclpy.create_node(
            "test_scan_to_pointcloud_node",
            context=self.context,
            allow_undeclared_parameters=True,
            automatically_declare_parameters_from_overrides=True,
        )
        self.message_pump = launch_testing_ros.MessagePump(
            self.node, context=self.context
        )

        self.pub = self.node.create_publisher(sensor_msgs.msg.PointCloud2, "/pc2", 1)

        self.sub = self.node.create_subscription(
            sensor_msgs.msg.PointCloud2, "/pc2", self.callback, 1
        )
        self.received_msg = None

        self.message_pump.start()

    def tearDown(self):
        self.message_pump.stop()
        self.node.destroy_node()
        rclpy.shutdown(context=self.context)

    def test_0_invalidTransform(self):
        pointcloud_msg = sensor_msgs.msg.PointCloud2()
        pointcloud_msg.data = [12, 12, 12]

        while self.received_msg is None:
            self.pub.publish(pointcloud_msg)
            time.sleep(0.1)

        self.assertIsNotNone(pointcloud_msg)

        self.assertNotAlmostEqual(self.received_msg.data[0], -1)
        self.assertNotAlmostEqual(self.received_msg.data[1], -1)
        self.assertNotAlmostEqual(self.received_msg.data[2], -1)

    def test_1_validTransform(self):
        pointcloud_msg = sensor_msgs.msg.PointCloud2()
        pointcloud_msg.data = [1, 1, 1]

        while self.received_msg is None:
            self.pub.publish(pointcloud_msg)
            time.sleep(0.1)

        self.assertIsNotNone(pointcloud_msg)

        self.assertAlmostEqual(self.received_msg.data[0], 1)
        self.assertAlmostEqual(self.received_msg.data[1], 1)
        self.assertAlmostEqual(self.received_msg.data[2], 1)

    def callback(self, msg):
        self.received_msg = sensor_msgs.msg.PointCloud2()
        self.received_msg = msg
