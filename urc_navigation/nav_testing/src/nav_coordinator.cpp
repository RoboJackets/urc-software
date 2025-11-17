#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include "nav_coordinator.hpp"
#include "astar.hpp"

namespace nav_coordinator
{
NavCoordinator::NavCoordinator(const rclcpp::NodeOptions & options)
: rclcpp::Node("nav_coordinator", options)
{
    RCLCPP_INFO(get_logger(), "Nav Coordinator started.");

    // --- Subscribers --- //
    // IMPLEMENT AS ACTION SERVER LATER
    // Create localization subscriber
    localization_subscriber_ = create_subscription<TODO>(
        "/TODO_localization_topic",
        rclcpp::SystemDefaultsQoS(),
        std::bind(&NavCoordinator::handleLocalization, this, std::placeholder::_1));

    // Create goal subscriber
    goal_subscriber_ = create_subscription<TODO>(
        "/nav_goal",
        rclcpp::SystemDefaultsQoS(),
        std::bind(&NavCoordinator::handleGoal, this, std::placeholders::_1));
    // create goal subscriber
    cancel_subscriber_ = create_subscription<TODO>(
        "/nav_cancel",
        rclcpp::SystemDefaultsQoS(),
        std::bind(&NavCoordinator::handleGoal, this, std::placeholders::_1));
    // TODO: combine start and goal handles to one handle?
    
    // --- Publishers --- //

    // --- Planner Service Client --- //
    planner_client_ = rclcpp::create_client<urc_msgs::action::GeneratePlan>(
        this,
        "/plan"
    );
    std::thread(std::bind(&NavCoordinator::sendPlannerRequest, this)).detach();

    // --- Follower Action Client --- //
    follower_client_ = rclcpp_action::create_client<urc_msgs::action::FollowPath>(
        this,
        "/follow_path"
    );

    // --- NavCoordinator Timer Callback --- //
    // one second timer callback
    timer_ = this->create_wall_timer(
        std::chrono::seconds(1),
        std::bind(&NavCoordinator::timerCallback, this)
    );


}

void NavCoordinator::handleGoal(const TODO::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "Received new goal");
    
    
}

// --- planner request --- //

void NavCoordinator::sendPlannerRequest()
{
    RCLCPP_INFO(this->get_logger(), "Waiting for planner service...");
    // if (!planner_client_->wait_for_service(std::chrono::seconds(10))){
    //     RCLCPP_ERROR(this->get_logger(), "Couldn't find planner service");
    //     return;
    // }
    while (!planner_client_->wait_for_action_server(std::chrono::seconds(1))) {
        RCLCPP_INFO(this->get_logger(), "Waiting for planner server...");
    }
    RCLCPP_INFO(this->get_logger(), "Planner service ready");
    auto planner_request = std::make_shared<urc_msgs::srv::GeneratePlan::Request>();

    // TODO Request stuff
    request->start.pose = TODO_start_msg_;
    request->goal.pose = TODO_goal_msg_;

    auto result = planner_client_->async_send_request(planner_request);
    RCLCPP_INFO(this->get_logger(), "Planner request sent");
    if (result.wait_for(std::chrono::seconds(10)) == std::future_status::timeout) {
        RCLCPP_ERROR(this->get_logger(), "Planner service took too long to complete!");
        return;
    }
    RCLCPP_INFO(this->get_logger(), "Planner service completed");
    
}

// ---- follower callbacks ---- //
void NavCoordinator::timerCallback()
{
    timer_->cancel(); //one-shot timer

    rclcpp_action::Client<urc_msgs::action::FollowPath>::SendGoalOptions follower_goal_options;
    follower_goal_options.goal_response_callback = std::bind(
        &NavCoordinator::followerGoalResponseCallback, this, std::placeholders::_1);
    follower_goal_options.feedback_callback = std::bind(
        &NavCoordinator::followerFeedbackCallback, this, std::placeholders::_1, std::placeholders::_2);
    follower_goal_options.result_callback = std::bind(
        &NavCoordinator::followerResultCallback, this, std::placeholders::_1);

    urc_msgs::action::FollowPath::Goal follower_goal;

    // TODO?

    follower_client_->async_send_goal(follower_goal, follower_goal_options);
}

void NavCoordinator::followerGoalResponseCallback(
    const rclcpp_action::ClientGoalHandle<urc_msgs::action::FollowPath>::SharedPtr goal_handle) 
{
    if (!goal_handle) {
        RCLCPP_ERROR(this->get_logger(), "Goal was rejected by the follower server");
    } else {
        RCLCPP_INFO(this->get_logger(), "Goal accepted by the follower server, waiting for result");
    }
}
void NavCoordinator::followerFeedbackCallback(
    rclcpp_action::ClientGoalHandle<urc_msgs::action::FollowPath>::SharedPtr,
    const std::shared_ptr<const urc_msgs::action::FollowPath::Feedback> feedback) 
{
    RCLCPP_INFO(this->get_logger(), "feedback TODO %f", feedback->distance_to_goal);
    
}

void NavCoordinator::followerResultCallback(
    const rclcpp_action::ClientGoalHandle<urc_msgs::action::FollowPath>::WrappedResult & result)
{
    switch(result.code) {
        case rclcpp_action::ResultCode::SUCCEEDED:
            RCLCPP_INFO(this->get_logger(), "SUCCEEDED TODO");
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(), "ABORTED Error Code %d", result.result->error_code);
            sendPlannerRequest(); // replan
            break; // return ?
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_ERROR(this->get_logger(), "CANCELED TODO");
            break; // return ?
        default:
            RCLCPP_ERROR(this->get_logger(), "Unkown result code for follower client");
            break; // return ?
    }
}

Nav::~NavCoordinator()
{
    RCLCPP_INFO(this->get_logger(), "Nav Coordinator has been stopped.");
}

} // namespace nav_coordinator

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(nav_coordinator::NavCoordinator)
