#ifndef PLANNER_SERVER_HPP_
#define PLANNER_SERVER_HPP_

#include <rclcpp/rclcpp.hpp>

#include <nav2_msgs/msg/costmap.hpp>
#include <nav_msgs/msg/path.hpp>

namespace planner_server
{
    class PlannerServer : public rclcpp::Node
    {
    public:
        explicit PlannerServer(const rclcpp::NodeOptions &options);

        ~PlannerServer();

    protected:
        /**
         * @brief Call the A* algorithm to generate the plan
         */
        void generatePlan();

        /**
         * @brief Publish the plan to the /path topic for *visualization* purposes. The plan will be returned as a response to the service call.
         * @param plan The plan to be published
         */
        void publishPlan(const nav_msgs::msg::Path &plan);

        /**
         * @brief Handle the costmap data
         * @param msg The costmap data
         */
        void handleCostmap(const nav2_msgs::msg::Costmap::SharedPtr msg);

        nav2_msgs::msg::Costmap current_costmap_;
        rclcpp::Subscription<nav2_msgs::msg::Costmap>::SharedPtr costmap_subscriber_;
        rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_publisher_;
        rclcpp::Service<nav_msgs::srv::GetPlan>::SharedPtr plan_service_;
    }
} // namespace planner_server

#endif // PLANNER_SERVER_HPP_