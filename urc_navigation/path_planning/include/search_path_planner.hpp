#ifndef SEARCH_FOR_ARUCO_HPP_
#define SEARCH_FOR_ARUCO_HPP_

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <nav_msgs/msg/path.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <urc_msgs/srv/detail/generate_search_path__struct.hpp>
#include <urc_msgs/srv/generate_search_path.hpp>
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include <std_msgs/msg/bool.hpp>

namespace search_path_planner
{
class SearchPathPlanner : public rclcpp::Node
{
public:
  explicit SearchPathPlanner(const rclcpp::NodeOptions & options);

  ~SearchPathPlanner() = default;

protected:
  rclcpp::Service<urc_msgs::srv::GenerateSearchPath>::SharedPtr generate_search_path_service_;
  geometry_msgs::msg::Pose current_pose_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr robot_pose_subscriber_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  void generateSearchPath(
    const std::shared_ptr<urc_msgs::srv::GenerateSearchPath::Request> request,
    std::shared_ptr<urc_msgs::srv::GenerateSearchPath::Response> response);

};

} // namespace urc_behaviors

#endif // SEARCH_FOR_ARUCO_HPP_
