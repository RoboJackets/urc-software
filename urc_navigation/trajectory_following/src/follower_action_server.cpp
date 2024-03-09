#include "follower_action_server.hpp"
#include "geometry_util.hpp"
#include "pure_pursuit.hpp"

namespace follower_action_server
{
  FollowerActionServer::FollowerActionServer(const rclcpp::NodeOptions &options)
      : Node("follower_action_server", options)
  {
    RCLCPP_INFO(this->get_logger(), "Follower node has been started.");

    // Create a publisher for the carrot point
    carrot_pub_ = create_publisher<geometry_msgs::msg::PointStamped>("carrot", 10);

    cmd_vel_pub_ = create_publisher<geometry_msgs::msg::TwistStamped>("cmd_vel", 10);

    // Create an action server for the follow_path action
    follow_path_server_ = rclcpp_action::create_server<urc_msgs::action::FollowPath>(
        this,
        "follow_path",
        std::bind(&FollowerActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&FollowerActionServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&FollowerActionServer::handle_accepted, this, std::placeholders::_1));
  }

  FollowerActionServer::~FollowerActionServer()
  {
    RCLCPP_INFO(this->get_logger(), "Follower action server has been stopped.");
  }

  rclcpp_action::GoalResponse FollowerActionServer::handle_goal(
      const rclcpp_action::GoalUUID &uuid,
      std::shared_ptr<const urc_msgs::action::FollowPath::Goal> goal)
  {
    RCLCPP_INFO(this->get_logger(), "Received goal request");

    (void)uuid;
    (void)goal;

    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  rclcpp_action::CancelResponse FollowerActionServer::handle_cancel(
      const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::FollowPath>> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");

    (void)goal_handle;

    return rclcpp_action::CancelResponse::ACCEPT;
  }

  void FollowerActionServer::handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::FollowPath>> goal_handle)
  {
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&FollowerActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
  }

  void FollowerActionServer::execute(const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::FollowPath>> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Executing goal");

    auto feedback = std::make_shared<urc_msgs::action::FollowPath::Feedback>();
    auto result = std::make_shared<urc_msgs::action::FollowPath::Result>();
    auto &path = goal_handle->get_goal()->path;

    // Create a PurePursuit object
    pure_pursuit::PurePursuitParams params;
    params.lookahead_distance = 0.5;
    params.desired_linear_velocity = 0.5;
    pure_pursuit::PurePursuit pure_pursuit(params);

    // Set the path in the PurePursuit object
    pure_pursuit.setPath(path);

    // Create a timer to publish the carrot point
    auto timer = create_wall_timer(
        std::chrono::milliseconds(100),
        [this, &pure_pursuit, &path, &feedback, &goal_handle]()
        {
          auto cmd_vel = pure_pursuit.getCommandVelocity(current_pose_);
          cmd_vel_pub_->publish(cmd_vel);

          // Publish feedback
          feedback->distance_to_goal = geometry_util::dist2D(current_pose_.pose.position, path.poses.back().pose.position);
          goal_handle->publish_feedback(feedback);
        });

    // Wait for the goal to be canceled
    while (rclcpp::ok())
    {
      if (goal_handle->is_canceling())
      {
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal has been canceled");
        return;
      }

      rclcpp::spin_some(this->get_node_base_interface());
    }

    // Cancel the timer
    timer->cancel();
  }

} // namespace follower_node
