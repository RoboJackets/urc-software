#ifndef SEARCH_FOR_ARUCO_HPP_
#define SEARCH_FOR_ARUCO_HPP_

#include <future>

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <nav_msgs/msg/path.hpp>

#include <urc_msgs/action/follow_path.hpp>
#include <urc_msgs/action/search_aruco.hpp>

#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

#include <geometry_msgs/msg/pose_array.hpp>
#include <std_msgs/msg/bool.hpp>

namespace urc_behaviors
{
class SearchForAruco : public rclcpp::Node, public std::enable_shared_from_this<SearchForAruco>
{
public:
  using FollowPath = urc_msgs::action::FollowPath;
  using SearchAruco = urc_msgs::action::SearchAruco;
  using GoalHandleFollowPath = rclcpp_action::ClientGoalHandle<FollowPath>;
  using GoalHandleSearchAruco = rclcpp_action::ServerGoalHandle<urc_msgs::action::SearchAruco>;

  explicit SearchForAruco(const rclcpp::NodeOptions & options);

  ~SearchForAruco() = default;

private:
  void search(const std::shared_ptr<GoalHandleSearchAruco> goal_handle);

  nav_msgs::msg::Path generate_search_path(double spiral_coeff);

  void goal_response_callback(const GoalHandleFollowPath::SharedPtr & goal_handle);
  void result_callback(const GoalHandleFollowPath::WrappedResult & result);
  void feedback_callback(
    GoalHandleFollowPath::SharedPtr,
    const std::shared_ptr<const FollowPath::Feedback> feedback);

  rclcpp_action::Client<FollowPath>::SharedPtr follow_path_client_;

  bool aruco_seen_ = false;
  bool cancel_requested_ = false;
  rclcpp::Time aruco_first_seen_time_;
  void aruco_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg);
  void handle_accepted(const std::shared_ptr<GoalHandleSearchAruco> goal_handle);
  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const urc_msgs::action::SearchAruco::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::SearchAruco>> goal_handle);

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
  rclcpp_action::Server<urc_msgs::action::SearchAruco>::SharedPtr search_server_;
  rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr aruco_seen_subscriber_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr aruco_seen_publisher_;
};

} // namespace urc_behaviors

#endif // SEARCH_FOR_ARUCO_HPP_
