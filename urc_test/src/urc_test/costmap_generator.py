import rclpy
from rclpy.node import Node
from nav_msgs.msg import OccupancyGrid
import numpy as np


class CostmapGenerator(Node):

    def __init__(self):
        super().__init__("urc_test")
        self.costmap_pub = self.create_publisher(OccupancyGrid, "/costmap", 10)
        self.timer = self.create_timer(0.02, self.publish_costmap)

    def publish_costmap(self):
        costmap = OccupancyGrid()
        costmap.header.frame_id = "odom"
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

        self.costmap_pub.publish(costmap)


def main(args=None):
    rclpy.init(args=args)
    tester_node = CostmapGenerator()
    rclpy.spin(tester_node)

    tester_node.destroy_node()


if __name__ == "__main__":
    main()
