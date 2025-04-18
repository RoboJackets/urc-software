#ifndef SEARCH_FOR_ARUCO_HPP_
#define SEARCH_FOR_ARUCO_HPP_

#include <future>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <nav_msgs/msg/path.hpp>

#include <urc_msgs/action/follow_path.hpp>

#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

#include <geometry_msgs/msg/pose_array.hpp>
#include <std_msgs/msg/bool.hpp>

namespace urc_behaviors
{
class SearchForAruco : public rclcpp::Node
{
public:
  using FollowPath = urc_msgs::action::FollowPath;
  using GoalHandleFollowPath = rclcpp_action::ClientGoalHandle<FollowPath>;

  explicit SearchForAruco(const rclcpp::NodeOptions & options);

  ~SearchForAruco() = default;

private:
  void search();

  nav_msgs::msg::Path generate_search_path(double spiral_coeff);

  void goal_response_callback(const GoalHandleFollowPath::SharedPtr & goal_handle);
  void result_callback(const GoalHandleFollowPath::WrappedResult & result);
  void feedback_callback(
    GoalHandleFollowPath::SharedPtr,
    const std::shared_ptr<const FollowPath::Feedback> feedback);

  rclcpp_action::Client<FollowPath>::SharedPtr follow_path_client_;

  bool aruco_seen_;
  rclcpp::Time aruco_first_seen_time_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
};

class ArucoSeen : public rclcpp::Node
{
public:
  ArucoSeen(const rclcpp::NodeOptions & options);

private:
  void aruco_callback(const std_msgs::msg::Bool::SharedPtr msg);
  bool aruco_seen_ = false;
  
  rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr aruco_seen_subscriber_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr aruco_seen_publisher_;
};
} // namespace urc_behaviors

#endif // SEARCH_FOR_ARUCO_HPP_
