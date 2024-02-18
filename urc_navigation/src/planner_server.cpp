#include <rclcpp/rclcpp.hpp>

#include "rclcpp_components/register_node_macro.hpp"
#include "planner_server.hpp"
#include "astar.hpp"

namespace planner_server
{
    PlannerServer::PlannerServer(const rclcpp::NodeOptions &options) : Node("planner_server", options)
    {
        // Create the service
        plan_service_ = create_service<urc_navigation::srv::GetPlan>(
            "plan",
            std::bind(&PlannerServer::generatePlan, this, std::placeholders::_1, std::placeholders::_2));

        // Create the publisher
        path_publisher_ = create_publisher<nav_msgs::msg::Path>(
            "/path",
            rclcpp::SystemDefaultsQoS());

        // Setup the costmap
        costmap_subscriber_ = create_subscription<nav2_msgs::msg::Costmap>(
            "/costmap",
            rclcpp::SystemDefaultsQoS(),
            std::bind(&PlannerServer::handleCostmap, this, std::placeholders::_1));
    }

    void PlannerServer::handleCostmap(const nav2_msgs::msg::Costmap::SharedPtr msg)
    {
        current_costmap_ = *msg;
    }

    PlannerServer::~PlannerServer() {}

    void PlannerServer::generatePlan()
    {
        // Call the A* algorithm
        auto plan = path_planning::AStar(current_costmap_);

        // Publish the plan
        publishPlan(plan);
    }

    void PlannerServer::publishPlan(const nav_msgs::msg::Path &plan)
    {
        auto msg = std::make_unique<nav_msgs::msg::Path>(plan);
        if (plan_publisher_->is_activated() && plan_publisher_->get_subscription_count() > 0)
        {
            plan_publisher_->publish(std::move(msg));
        }
    }
}

RCLCPP_COMPONENTS_REGISTER_NODE(urc_navigation::PlannerServer)