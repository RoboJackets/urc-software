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

    // --- Nav Action Server --- //
    // to mannually send a goal, use 
    // ros2 action send_goal /nav_coordinator urc_msgs/action/NavToGoal "{path: {poses: [{header: {frame_id: 'map'}, pose: {position: {x: 1.0, y: 1.0, z: 0,0}, orientation: {x: 0.0, y: 0.0, z: 0.0, w: 1.0}}}]}}" 
    nav_action_server_ = rclcpp_action::create_server<urc_msgs::action::NavToGoal>(
        this,
        "nav_coordinator",
        std::bind(
            &NavCoordinator::handle_goal, this, std::placeholders::_1,
            std::placeholders::_2),
            std::bind(&NavCoordinator::handle_cancel, this, std::placeholders::_1),
            std::bind(&NavCoordinator::handle_accepted, this, std::placeholders::_1));
    
    // --- Subscribers --- //
    // Create localization subscriber    
    localization_subscriber_ = create_subscription<TODO>(
        "/rover_ground_truth", //TODO_localization_topic
        rclcpp::SystemDefaultsQoS(),
        [this](const nav_msgs::msg::Odometry::SharedPtr msg)
        {
        geometry_msgs::msg::PoseStamped pose;
        pose.header = msg->header;
        pose.pose = msg->pose.pose;
        current_pose_ = pose;
        });


    // --- Planner Service Client --- //
    /* IN PROGRESS
    planner_client_ = rclcpp::create_client<urc_msgs::action::GeneratePlan>(
        this,
        "/plan"
    );
    std::thread(std::bind(&NavCoordinator::sendPlannerRequest, this)).detach();
    */

    // // --- NavCoordinator Timer Callback --- //
    // // one second timer callback
    // timer_ = this->create_wall_timer(
    //     std::chrono::seconds(1),
    //     std::bind(&NavCoordinator::timerCallback, this)
    // );


}

// --- nav action server functions --- //

rclcpp_action::GoalResponse NavCoordinator::handle_goal(
    const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const urc_msgs::action::NavToGoal::Goal> goal)
{
  RCLCPP_INFO(this->get_logger(), "Received goal request");

  (void)uuid;
  (void)goal;

  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse NavCoordinator::handle_cancel(
    const std::shared_ptr<rclcpp::action::ServerGoalHandle<urc_msgs::action::NavToGoal>> goal_handle)
{
  RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");

  (void)goal_handle;

  return rclcpp_action::CancelResponse::ACCEPT;
}

void NavCoordinator::handle_accepted(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::NavToGoal>> goal_handle)
{
  // this needs to return quickly to avoid blocking the executor, so spin up a new thread
  std::thread{std::bind(&NavCoordinator::execute, this, std::placeholders::_1),
    goal_handle}
  .detach();
}
/*
void NavCoordinator::executeTODO(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::NavToGoal>> goal_handle)
{
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    
    auto feedback = std::make_shared<urc_msgs::action::NavToGoal::Feedback>();
    feedback->distance_to_goal = std::numeric_limits<double>::max();

    auto result = std::make_shared<urc_msgs::action::NavToGoal::Result>();
    auto & path = goal_handle->get_goal()->path;
    
    while (rclcpp::ok()) {
    if (goal_handle->is_canceling()) {
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Follower Goal has been canceled");
        break;
    // } else if (feedback->distance_to_goal < get_parameter("goal_tolerance").as_double()) {
    } else if (TODO_next_path_point_reached_condition) {
        // result->error_code = urc_msgs::action::NavToGoal::Result::SUCCESS;
        // goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Moving to next path point");
        sendNextPathPoint();
    } else if (TODO_last_path_point_reached_condition) {
        result->error_code = urc_msgs::action::NavToGoal::Result::SUCCESS;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Final Goal has been reached!");
        break;
    // } else if (getCost(
    //     current_costmap_, output.lookahead_point.point.x,
    //     output.lookahead_point.point.y) > get_parameter("lethal_cost_threshold").as_int())
    // } else if (TODO_obstacle_detected_condition || TODO_new_goal_received)    // repath
        {
        RCLCPP_INFO(this->get_logger(), "Replanning Path: Obstacle detected!");
        // TODO: Call planner service to generate new path
        sendPlannerRequest(); 
        break;
    } else if (TODO_path_planner_failure) {
        result->error_code = urc_msgs::action::TODO::Result::PLANNER_FAILURE;
        goal_handle->abort(result);
        RCLCPP_INFO(this->get_logger(), "Path Planner Failure!");
        break;
    }
}
*/

void NavCoordinator::execute(
    const std::shared_ptr<rclcpp_action::ServerGoalHandle<urc_msgs::action::NavToGoal>> goal_handle)
{
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    
    auto feedback = std::make_shared<urc_msgs::action::NavToGoal::Feedback>();
    feedback->distance_to_goal = std::numeric_limits<double>::max();

    auto result = std::make_shared<urc_msgs::action::NavToGoal::Result>();
    auto & path = goal_handle->get_goal()->path;

    while (rclcpp::ok()) {
    if (goal_handle->is_canceling()) {
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Follower Goal has been canceled");
        break;
    // } else if (feedback->distance_to_goal < get_parameter("goal_tolerance").as_double()) {
    } else if (goal_handle->) {
        result->error_code = urc_msgs::action::NavToGoal::Result::SUCCESS;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Final Goal has been reached!");
        break;
    }
}

// --- planner service request --- //
/* IN PROGRESS
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
    // Request: Start pose and goal pose (geometry_msgs/PoseStamped)
    planner_request->start.pose = TODO_start_msg_; // rover starting position    
    planner_request->goal.pose = TODO_goal_msg_;

    auto result = planner_client_->async_send_request(planner_request);
    RCLCPP_INFO(this->get_logger(), "Planner request sent");
    if (result.wait_for(std::chrono::seconds(10)) == std::future_status::timeout) {
        RCLCPP_ERROR(this->get_logger(), "Planner service took too long to complete!");
        return;
    }
    RCLCPP_INFO(this->get_logger(), "Planner service completed");
    
}
*/

} // namespace nav_coordinator

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(nav_coordinator::NavCoordinator)
