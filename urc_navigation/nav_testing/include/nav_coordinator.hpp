#ifndef NAV_COORDINATOR_HPP_
#define NAV_COORDINATOR_HPP_

#include <math.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <geographic_msgs/msg/geo_point.hpp>
#include <geodesy/utm.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <optional>
#include <urc_msgs/msg/waypoint.hpp>
#include <urc_msgs/action/navigate_to_waypoint.hpp>
#include <std_msgs/msg/string.hpp>

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

    enum class ErrorType
    {
        NONE,
        PLANNER_FAILURE,
        OBSTACLE_DETECTED,
        PLANNING_FAILED_IN_FOLLOWER,
        FOLLOWER_FAILURE,
        SERVER_UNAVAILABLE,
        UNKNOWN_ERROR
    };

    void handleWaypoint(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
    void handleGpsWaypoint(const urc_msgs::msg::Waypoint::SharedPtr msg);
    void sendFollowerGoal(const geometry_msgs::msg::PoseStamped & waypoint);
    std::optional<geometry_msgs::msg::PoseStamped> convertGpsToMapWaypoint(
        const urc_msgs::msg::Waypoint & waypoint);

    void handleGoalResponse(const GoalHandleNavigate::SharedPtr & goal_handle);
    void handleFeedback(
        GoalHandleNavigate::SharedPtr,
        const std::shared_ptr<const NavigateToWaypoint::Feedback> feedback);
    void handleResult(const GoalHandleNavigate::WrappedResult & result);

    void transitionTo(State new_state, const std::string & reason);
    void handleError(ErrorType error_type, const std::string & details);
    void publishState();
    std::string errorTypeToString(ErrorType error_type) const;
    std::string stateToString(State state) const;

    State state_;
    std::string follower_action_name_;
    bool cancel_on_new_waypoint_;
    std::string map_frame_id_;
    std::string utm_frame_id_;
    double tf_lookup_timeout_sec_;

    geometry_msgs::msg::PoseStamped active_waypoint_;
    GoalHandleNavigate::SharedPtr active_goal_handle_;

    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr waypoint_subscriber_;
    rclcpp::Subscription<urc_msgs::msg::Waypoint>::SharedPtr gps_waypoint_subscriber_;
    rclcpp_action::Client<NavigateToWaypoint>::SharedPtr follower_client_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr state_publisher_;
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

    ErrorType last_error_;
    std::string last_error_details_;
};

}

#endif