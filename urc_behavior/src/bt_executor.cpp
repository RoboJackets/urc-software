#include "bt_executor.hpp"

namespace urc_behavior
{
    BTExecutor::BTExecutor(const rclcpp::NodeOptions &options)
        : BT::TreeExecutionServer("bt_executor", options)
    {
        pose_sub_ = create_subscription<geometry_msgs::msg::PoseStamped>(
            "current_pose",
            10,
            [this](const geometry_msgs::msg::PoseStamped::SharedPtr msg)
            {
                globalBlackboard()->set("current_pose", msg->pose);
            });
    }

    void onTreeCreated(BT::Tree &tree) override
    {
        logger_cout_ = std::make_shared<BT::StdCoutLogger>(tree);
    }

    std::optional<std::string> onTreeExecutionCompleted(BT::NodeStatus status, bool was_cancelled) override
    {
        logger_cout_.reset();
        return std::nullopt;
    }
} // namespace urc_behavior