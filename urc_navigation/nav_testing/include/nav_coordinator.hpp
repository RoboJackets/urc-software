#ifndef NAV_COORDINATOR_HPP_
#define NAV_COORDINATOR_HPP_

namespace nav_coordinator
{
class NavCoordinator : public rclcpp::Node
{
    public:
        explicit NavCoordinator(const rclcpp::NodeOptions & options);
        ~NavCoordinator();

    private:
        // --- Subscribers --- //
        rclcpp::Subscription<TODO>::SharedPtr localization_subscriber_;
        rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_subscriber_;
        rclcpp::Subscription<TODO>::SharedPtr cancel_subscriber_;

        // --- Publishers --- //

        // --- Planner Service Client --- //
        rclcpp::Client<urc_msgs::action::GeneratePlan>::SharedPtr planner_client_;

        rclcpp::TimerBase::SharedPtr timer_;

        // TODO

}

        // void timerCallback();

        void handleLocalization(const TODO::SharedPtr msg);
        void handleGoal(const TODO::SharedPtr msg);
        void handleStart(const TODO::SharedPtr msg);

} // namespace nav_coordinator

#endif // NAV_COORDINATOR_HPP_