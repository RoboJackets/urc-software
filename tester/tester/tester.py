import rclpy
from rclpy.node import Node
from nav_msgs.msg import OccupancyGrid
from geometry_msgs.msg import PoseStamped
from urc_msgs.srv import GeneratePlan
import numpy as np
import time


class TesterNode(Node):

    def __init__(self):
        super().__init__('tester')
        self.costmap_pub = self.create_publisher(
            OccupancyGrid,
            "/costmap",
            10
        )

        self.client = self.create_client(GeneratePlan, "plan")

        self.costmap_generate()
        self.get_logger().info("Costmap Publish Initialized")

        time.sleep(3)

        self.call_planner_client()
        self.get_logger().info("Planner Server Called")

    def call_planner_client(self):

        req = GeneratePlan.Request()

        initialPose = PoseStamped()
        initialPose.header.frame_id = "map"
        initialPose.header.stamp = rclpy.time.Time().to_msg()
        initialPose.pose.position.x = 0.0
        initialPose.pose.position.y = 0.0

        goalPose = PoseStamped()
        goalPose.header.frame_id = "map"
        goalPose.header.stamp = rclpy.time.Time().to_msg()
        goalPose.pose.position.x = 10.0
        goalPose.pose.position.y = 10.0

        req.start = initialPose
        req.goal = goalPose

        self.future = self.client.call_async(req)


    def costmap_generate(self):

        self.get_logger().info("Costmap Publish Looping...")

        costmap = OccupancyGrid()
        costmap.header.frame_id = "map"
        costmap.header.stamp = rclpy.time.Time().to_msg()

        costmap.info.resolution = 1.0
        costmap.info.width = 100
        costmap.info.height = 100
       
        costmap.info.origin.position.x = 0.0
        costmap.info.origin.position.y = 0.0
        costmap.info.origin.position.z = 0.0
        costmap.info.origin.orientation.x = 0.0
        costmap.info.origin.orientation.y = 0.0
        costmap.info.origin.orientation.z = 0.0
        costmap.info.origin.orientation.w = 1.0

        map = np.ones((100, 100), dtype=np.int8)
        map[4:8, 4:8] *= 10
        costmap.data = map.flatten().tolist()


        costmap.data

        self.costmap_pub.publish(costmap)


def main(args=None):

    rclpy.init(args=args)
    controller = TesterNode()
    rclpy.spin(controller)

    
    controller.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()