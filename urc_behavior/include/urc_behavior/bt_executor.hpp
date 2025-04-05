#ifndef BEHAVIOR_TREE_EXECUTOR_HPP_
#define BEHAVIOR_TREE_EXECUTOR_HPP_

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include <behaviortree_ros2/tree_execution_server.hpp>
#include <behaviortree_cpp/loggers/bt_cout_logger.h>

namespace urc_behavior
{
    class BTExecutor : public BT::TreeExecutionServer
    {
    public:
        BTExecutor(const rclcpp::NodeOptions &options);
        ~BTExecutor();

        void onTreeCreated(BT::Tree &tree) override;
        std::optional<std::string> onTreeExecutionCompleted(BT::NodeStatus status, bool was_cancelled) override;

    private:
        std::shared_ptr<BT::StdCoutLogger> logger_cout_;
        rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_sub_;
    };

} // namespace urc_behavior

#endif // BEHAVIOR_TREE_EXECUTOR_HPP_