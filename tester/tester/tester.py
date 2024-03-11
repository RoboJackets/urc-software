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
        self.costmap_pub = self.create_publisher(OccupancyGrid, "/costmap", 10)
        self.timer = self.create_timer(0.02, self.publish_costmap)

        self.planner_client = self.create_client(GeneratePlan, "plan")
        self.follower_client = ActionClient(self, FollowPath, "follow_path")


    def call_trajectory_follower(self, path):
        goal_msg = FollowPath.Goal()
        goal_msg.path = path 

        self.follower_client.wait_for_server()

        follower_future = self.follower_client.send_goal_async(goal_msg)
        self.get_logger().info("Trajectory Follower Called...")

        follower_future.add_done_callback(self.goal_response_callback)
    
    def goal_response_callback(self, future):
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
        rclpy.shutdown()

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        self.get_logger().info('Received feedback: {0}'.format(feedback.partial_sequence))


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

        planner_response = self.planner_future.result()

        return planner_response


    def publish_costmap(self):
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

        self.costmap_pub.publish(costmap)


def main(args=None):

    rclpy.init(args=args)
    tester_node = TesterNode()
    
    res = tester_node.call_planner_client()
    
    while int(res.error_code) == 1:
        time.sleep(0.5)
        res = tester_node.call_planner_client()
        tester_node.get_logger().info(f"{res.error_code}") 

    tester_node.call_trajectory_follower(res.path)
    rclpy.spin(tester_node)

    tester_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
