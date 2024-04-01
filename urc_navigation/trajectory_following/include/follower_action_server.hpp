#ifndef FOLLOWER_ACTION_SERVER_HPP_
#define FOLLOWER_ACTION_SERVER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/path.hpp>
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "urc_msgs/action/follow_path.hpp"

namespace follower_action_server
{
class FollowerActionServer : public rclcpp::Node
{
public:
  explicit FollowerActionServer(const rclcpp::NodeOptions & options);

  ~FollowerActionServer();

private:
  geometry_msgs::msg::TransformStamped lookup_odom_to_base_link();

  visualization_msgs::msg::Marker create_lookahead_circle(
    double x, double y, double radius,
    std::string frame_id);

  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const urc_msgs::action::FollowPath::Goal> goal);

  rclcpp_action::CancelResponse handle_cancel(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::FollowPath>> goal_handle);

  void handle_accepted(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::FollowPath>> goal_handle);

  void execute(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::FollowPath>> goal_handle);

  rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr carrot_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
  rclcpp_action::Server<urc_msgs::action::FollowPath>::SharedPtr follow_path_server_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr transformed_path_pub_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;

  geometry_msgs::msg::PoseStamped current_pose_;
};
} // namespace follower_action_server

#endif // FOLLOWER_ACTION_SERVER_HPP_
