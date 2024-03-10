import rclpy
from rclpy.node import Node
from nav_msgs.msg import OccupancyGrid
from geometry_msgs.msg import PoseStamped
from urc_msgs.srv import GeneratePlan
import numpy as np
import time
from rclpy.action import ActionClient
from urc_msgs.action import FollowPath


class TesterNode(Node):

    def __init__(self):
        super().__init__('tester')
        self.costmap_pub = self.create_publisher(
            OccupancyGrid,
            "/costmap",
            10
        )

        self.planner_client = self.create_client(GeneratePlan, "plan")

        self.follower_client = ActionClient(self, FollowPath, "follow_path")

        # self.costmap_generate()

        self.create_timer(0.02, self.costmap_generate)

        planner_response = self.call_planner_client()
        while planner_response.error_code == 1:
            time.sleep(0.5)
            planner_response = self.call_planner_client()

        print(planner_response.path.poses)

        follower_future = self.call_trajectory_follower(planner_response.path)
        follower_future.add_done_callback(self.follower_response_callback)
        # print(follower_response)
        # while follower_response.error_code == 1:
        #     time.sleep(0.5)
        #     follower_response = self.call_trajectory_follower()

    def follower_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return

        self.get_logger().info('Goal accepted :)')

        self._get_result_future = goal_handle.get_result_async()

        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        result = future.result().result
        self.get_logger().info('Result: {0}'.format(result.sequence))


    def call_trajectory_follower(self, path):

        goal_msg = FollowPath.Goal()
        goal_msg.path = path 

        self.follower_client.wait_for_server()

        self.follower_future = self.follower_client.send_goal_async(goal_msg)
        self.get_logger().info("Trajectory Follower Called...")
        
        # rclpy.spin_until_future_complete(self, self.follower_future)
        # self.get_logger().info("Trajectory Follower Future Complete...")

        return self.follower_future

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

        self.planner_future = self.planner_client.call_async(req)
        self.get_logger().info("Planner Server Called...")

        rclpy.spin_until_future_complete(self, self.planner_future)

        self.get_logger().info("Planner Server Future Complete...")
        return self.planner_future.result()

    def costmap_generate(self):

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
        # map[4:8, 4:8] *= 10
        costmap.data = map.flatten().tolist()

        costmap.data

        self.costmap_pub.publish(costmap)

        # self.get_logger().info("Costmap Published...")


def main(args=None):

    rclpy.init(args=args)
    controller = TesterNode()
    rclpy.spin(controller)

    controller.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
