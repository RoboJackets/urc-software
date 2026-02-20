#ifndef NAV_COORDINATOR_HPP_
#define NAV_COORDINATOR_HPP_

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <urc_msgs/action/navigate_to_waypoint.hpp>

namespace nav_coordinator
{
class NavCoordinator : public rclcpp::Node
{
public:
    explicit NavCoordinator(const rclcpp::NodeOptions & options);
    ~NavCoordinator() override = default;

private:
    using NavigateToWaypoint = urc_msgs::action::NavigateToWaypoint;
    using GoalHandleNavigate = rclcpp_action::ClientGoalHandle<NavigateToWaypoint>;

    enum class State
    {
        IDLE,
        WAITING_FOR_SERVER,
        SENDING_GOAL,
        TRACKING_GOAL,
        SUCCEEDED,
        FAILED,
        CANCELED
    };

    void handleWaypoint(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
    void sendFollowerGoal(const geometry_msgs::msg::PoseStamped & waypoint);

    void handleGoalResponse(const GoalHandleNavigate::SharedPtr & goal_handle);
    void handleFeedback(
        GoalHandleNavigate::SharedPtr,
        const std::shared_ptr<const NavigateToWaypoint::Feedback> feedback);
    void handleResult(const GoalHandleNavigate::WrappedResult & result);

    void transitionTo(State new_state, const std::string & reason);

    State state_;
    std::string follower_action_name_;
    bool cancel_on_new_waypoint_;

    geometry_msgs::msg::PoseStamped active_waypoint_;
    GoalHandleNavigate::SharedPtr active_goal_handle_;

    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr waypoint_subscriber_;
    rclcpp_action::Client<NavigateToWaypoint>::SharedPtr follower_client_;
};

}

#endif