#include "search_for_aruco.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include "urc_msgs/action/search_aruco.hpp"

namespace urc_behaviors
{
SearchForAruco::SearchForAruco(const rclcpp::NodeOptions & options)
: Node("search_for_aruco", options)
{
  RCLCPP_INFO(this->get_logger(), "Search for ARUCO behavior server has been started.");

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

  search_server_ = rclcpp_action::create_server<urc_msgs::action::SearchAruco>(
    this,
    "search_for_aruco",
    std::bind(
      &SearchForAruco::handle_goal, this,
      std::placeholders::_1, std::placeholders::_2),
    std::bind(
      &SearchForAruco::handle_cancel, this,
      std::placeholders::_1),
    std::bind(
      &SearchForAruco::handle_accepted, this,
      std::placeholders::_1)
    );

  follow_path_client_ = rclcpp_action::create_client<urc_msgs::action::FollowPath>(
    this,
    "follow_path");
}

void SearchForAruco::search(const std::shared_ptr<GoalHandleSearchAruco> goal_handle)
{
  // Wait until base_link to map transform is available
  while (!tf_buffer_->canTransform("map", "base_link", tf2::TimePointZero)) {
    RCLCPP_INFO(this->get_logger(), "Waiting for transform from base_link to map...");
    rclcpp::sleep_for(std::chrono::seconds(1));
  }

  RCLCPP_INFO(this->get_logger(), "Transform from base_link to map is available.");

  // Generate a search path
  auto path = generate_search_path(0.1);

  // Send the path to the follow_path action server
  auto goal = FollowPath::Goal();
  goal.path = path;

  // Handle the case where the goal type is GPS, so return success immediately
  if (goal_handle->get_goal()->goal_type == urc_msgs::action::SearchAruco::Goal::GPS) {
    auto result = std::make_shared<urc_msgs::action::SearchAruco::Result>();
    goal_handle->succeed(result);
    RCLCPP_INFO(this->get_logger(), "Goal succeeded immediately");
    return;
  }

  aruco_seen_subscriber_ = this->create_subscription<geometry_msgs::msg::PoseArray>(
    "/aruco_poses", 10,
    [this](geometry_msgs::msg::PoseArray::SharedPtr msg) {
      this->aruco_callback(msg);
    });

  aruco_seen_publisher_ = this->create_publisher<std_msgs::msg::Bool>(
    "/aruco_seen_", 10);

  RCLCPP_INFO(this->get_logger(), "Aruco seen node has been started.");

  auto send_goal_options = rclcpp_action::Client<FollowPath>::SendGoalOptions();
  send_goal_options.goal_response_callback = std::bind(
    &SearchForAruco::goal_response_callback,
    this, std::placeholders::_1);
  send_goal_options.result_callback = std::bind(
    &SearchForAruco::result_callback, this,
    std::placeholders::_1);
  send_goal_options.feedback_callback = std::bind(
    &SearchForAruco::feedback_callback, this,
    std::placeholders::_1, std::placeholders::_2);

  auto goal_handle_future = follow_path_client_->async_send_goal(
    goal, send_goal_options);

  if (rclcpp::spin_until_future_complete(std::enable_shared_from_this<SearchForAruco>::shared_from_this(), goal_handle_future) != 
    rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_ERROR(this->get_logger(), "Failed to send goal to follow_path action server");
    return;
  }

  rclcpp_action::ClientGoalHandle<FollowPath>::SharedPtr follow_path_goal_handle_ = goal_handle_future.get();
  if (!goal_handle) {
    RCLCPP_ERROR(this->get_logger(), "Failed to receive goal handle");
    return;
  }

  auto result_future = follow_path_client_->async_get_result(follow_path_goal_handle_);
  auto wait_result = rclcpp::spin_until_future_complete(std::enable_shared_from_this<SearchForAruco>::shared_from_this(), result_future, std::chrono::seconds(3));
  auto result = result_future.get();

  if (rclcpp::FutureReturnCode::TIMEOUT == wait_result) {
    RCLCPP_ERROR(this->get_logger(), "Timed out waiting for result");
    auto cancel_result_future = follow_path_client_->async_cancel_goal(follow_path_goal_handle_);
    if (rclcpp::spin_until_future_complete(std::enable_shared_from_this<SearchForAruco>::shared_from_this(), cancel_result_future) !=
      rclcpp::FutureReturnCode::SUCCESS)
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to cancel goal");
      return;
    }
    RCLCPP_INFO(this->get_logger(), "Goal is being canceled");
  } else if (rclcpp::FutureReturnCode::SUCCESS != wait_result) {
    RCLCPP_ERROR(this->get_logger(), "Failed to get result");
    return;
  }

  if (result.code == rclcpp_action::ResultCode::SUCCEEDED) {
    if (result.result->SUCCESS == urc_msgs::action::FollowPath::Result::SUCCESS) {
      RCLCPP_INFO(this->get_logger(), "Aruco marker found, goal succeeded.");
      follow_path_client_->async_cancel_goal(follow_path_goal_handle_);
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal completed but aruco marker not seen.");
    }
  } else if (result.code == rclcpp_action::ResultCode::ABORTED) {
    RCLCPP_INFO(this->get_logger(), "Goal was aborted");
    return;
  } else if (result.code == rclcpp_action::ResultCode::CANCELED) {
    RCLCPP_INFO(this->get_logger(), "Goal was canceled");
    return;
  }

  auto result_msg = std::make_shared<urc_msgs::action::SearchAruco::Result>();
  goal_handle->succeed(result_msg);
}

void SearchForAruco::goal_response_callback(const GoalHandleFollowPath::SharedPtr & goal_handle)
{
  if (!goal_handle) {
    RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
  } else {
    RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
  }
}

void SearchForAruco::result_callback(const GoalHandleFollowPath::WrappedResult & result)
{
  switch (result.code) {
    case rclcpp_action::ResultCode::SUCCEEDED:
      RCLCPP_INFO(this->get_logger(), "Goal succeeded");
      break;
    case rclcpp_action::ResultCode::ABORTED:
      RCLCPP_INFO(this->get_logger(), "Goal was aborted");
      break;
    case rclcpp_action::ResultCode::CANCELED:
      RCLCPP_INFO(this->get_logger(), "Goal was canceled");
      break;
    default:
      RCLCPP_ERROR(this->get_logger(), "Unknown result code");
      break;
  }
}

void SearchForAruco::feedback_callback(
  GoalHandleFollowPath::SharedPtr,
  const std::shared_ptr<const FollowPath::Feedback> feedback)
{
  RCLCPP_INFO(this->get_logger(), "Received feedback: %f", feedback->distance_to_goal);
}

void SearchForAruco::aruco_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg) {
  bool aruco_seen_ = !msg->poses.empty();
  std_msgs::msg::Bool aruco_seen_msg;
  aruco_seen_msg.data = aruco_seen_;

  aruco_seen_publisher_->publish(aruco_seen_msg);
  
  if (aruco_seen_ && !cancel_requested_) {
    RCLCPP_INFO(this->get_logger(), "Aruco marker seen! Preempting follow_path.");
    cancel_requested_ = true;
    aruco_seen_ = true;
    follow_path_client_->async_cancel_all_goals();
  }
}

nav_msgs::msg::Path SearchForAruco::generate_search_path(double spiral_coeff)
{
  rclcpp::Time now = this->now();
  nav_msgs::msg::Path path;
  path.header.frame_id = "map";
  path.header.stamp = now;

  // Lookup transform from base_link to map
  geometry_msgs::msg::TransformStamped transform;
  try {
    transform = tf_buffer_->lookupTransform("map", "base_link", tf2::TimePointZero);
  } catch (tf2::TransformException & ex) {
    RCLCPP_ERROR(this->get_logger(), "Failed to lookup transform: %s", ex.what());
    throw std::runtime_error("Failed to lookup transform.");
  }

  for (double t = 0; t < 12 * M_PI; t += M_PI / 4) {
    geometry_msgs::msg::PoseStamped pose;
    pose.header.frame_id = "map";
    pose.header.stamp = now;

    pose.pose.position.x = spiral_coeff * t * cos(t);
    pose.pose.position.y = spiral_coeff * t * sin(t);
    pose.pose.orientation.w = 1.0;

    // Transform pose to map frame
    tf2::doTransform(pose.pose, pose.pose, transform);

    path.poses.push_back(pose);
  }

  return path;
}

void SearchForAruco::handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::SearchAruco>> goal_handle) {
  std::thread{std::bind(
    &SearchForAruco::search, this,
    goal_handle)}.detach();
}

rclcpp_action::GoalResponse SearchForAruco::handle_goal(
  const rclcpp_action::GoalUUID & uuid,
  std::shared_ptr<const urc_msgs::action::SearchAruco::Goal> goal)
{
  RCLCPP_INFO(this->get_logger(), "Received goal request");
  (void)uuid;
  (void)goal;
  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse SearchForAruco::handle_cancel(
  const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::SearchAruco>> goal_handle)
{
  RCLCPP_INFO(this->get_logger(), "Received cancel request");
  (void)goal_handle;
  return rclcpp_action::CancelResponse::ACCEPT;
}
} // namespace urc_behaviors

#include <rclcpp_components/register_node_macro.hpp>