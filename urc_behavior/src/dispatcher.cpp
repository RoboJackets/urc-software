#include "urc_behavior/dispatcher.hpp"

namespace urc_behavior
{
    Dispatcher::Dispatcher(const rclcpp::NodeOptions &options) : rclcpp::Node("dispatcher", options)
    {
        RCLCPP_INFO(get_logger(), "Dispatcher node started");

        get_goal_service_ = create_service<urc_msgs::srv::GetGoal>(
            "~/get_goal",
            std::bind(&Dispatcher::handleGetGoal, this, std::placeholders::_1, std::placeholders::_2));

        add_goal_service_ = create_service<urc_msgs::srv::AddGoal>(
            "~/add_goal",
            std::bind(&Dispatcher::handleAddGoal, this, std::placeholders::_1, std::placeholders::_2));
    }

    Dispatcher::~Dispatcher() {}

    void Dispatcher::handleGetGoal(
        const std::shared_ptr<urc_msgs::srv::GetGoal::Request> request,
        const std::shared_ptr<urc_msgs::srv::GetGoal::Response> response)
    {
        std::lock_guard<std::mutex> lock(queue_mutex_);

        if (!goal_queue_.empty())
        {
            response->goal = goal_queue_.front();
            goal_queue_.pop();
            response->success = true;
        }
        else
        {
            response->success = false;
        }
    }

    void Dispatcher::handleAddGoal(
        const std::shared_ptr<urc_msgs::srv::AddGoal::Request> request,
        const std::shared_ptr<urc_msgs::srv::AddGoal::Response> response)
    {
        try
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            goal_queue_.push(request->goal);
            response->success = true;
        }
        catch (const std::exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to add goal: %s", e.what());
            response->success = false;
        }
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_behavior::Dispatcher)