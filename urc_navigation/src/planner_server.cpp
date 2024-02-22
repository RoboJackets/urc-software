#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include "rclcpp_components/register_node_macro.hpp"
#include "planner_server.hpp"
#include "astar.hpp"

namespace planner_server
{
    PlannerServer::PlannerServer(const rclcpp::NodeOptions &options) : rclcpp::Node("planner_server", options)
    {
        RCLCPP_INFO(get_logger(), "Planner server started.");

        // Create the service
        plan_service_ = create_service<urc_msgs::srv::GeneratePlan>(
            "plan",
            std::bind(&PlannerServer::generatePlan, this, std::placeholders::_1, std::placeholders::_2));

        // Create the publisher
        plan_publisher_ = create_publisher<nav_msgs::msg::Path>(
            "/path",
            rclcpp::SystemDefaultsQoS());

        // Setup the costmap
        costmap_subscriber_ = create_subscription<nav_msgs::msg::OccupancyGrid>(
            "/costmap",
            rclcpp::SystemDefaultsQoS(),
            std::bind(&PlannerServer::handleCostmap, this, std::placeholders::_1));
    }

    void PlannerServer::handleCostmap(const nav_msgs::msg::OccupancyGrid::SharedPtr msg)
    {
        current_costmap_ = *msg;
    }

    PlannerServer::~PlannerServer() {}

    void PlannerServer::waitForCostmap()
    {
        while (rclcpp::ok() && current_costmap_.info.width == 0)
        {
            RCLCPP_INFO(get_logger(), "Waiting for costmap data...");
            rclcpp::sleep_for(std::chrono::milliseconds(250));
        }
    }

    void PlannerServer::generatePlan(const std::shared_ptr<urc_msgs::srv::GeneratePlan::Request> request,
                                     std::shared_ptr<urc_msgs::srv::GeneratePlan::Response> response)
    {
        waitForCostmap();

        auto start = request->start.pose;
        auto goal = request->goal.pose;

        astar::AStar astar(current_costmap_, start, goal, 1);
        std::vector<astar::AStar::GridBlock> path = astar.calculate();

        std::vector<geometry_msgs::msg::PoseStamped> poses;

        for (auto &block : path)
        {
            geometry_msgs::msg::PoseStamped pose;

            pose.header.frame_id = "base_link";
            pose.header.stamp = get_clock()->now();

            pose.pose.position.x = block.location.x;
            pose.pose.position.y = block.location.y;

            // pose.pose.orientation.x = block.pose.orientation.x;
            // pose.pose.orientation.y = block.pose.orientation.y;
            // pose.pose.orientation.z = block.pose.orientation.z;
            // pose.pose.orientation.w = block.pose.orientation.w;

            poses.push_back(pose);
        }

        nav_msgs::msg::Path plan;
        plan.header.frame_id = "map";
        plan.header.stamp = get_clock()->now();
        plan.poses = poses;

        publishPlan(plan);
    }

    void PlannerServer::publishPlan(const nav_msgs::msg::Path &plan)
    {
        auto msg = std::make_unique<nav_msgs::msg::Path>(plan);
        if (plan_publisher_->get_subscription_count() > 0)
        {
            plan_publisher_->publish(std::move(msg));
        }
    }
} // namespace planner_server

RCLCPP_COMPONENTS_REGISTER_NODE(planner_server::PlannerServer)