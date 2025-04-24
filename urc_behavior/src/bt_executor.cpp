#include "urc_behavior/bt_executor.hpp"

namespace urc_behavior
{
BTExecutor::BTExecutor(const rclcpp::NodeOptions & options)
: BT::TreeExecutionServer(options)
{
  pose_sub_ = node()->create_subscription<geometry_msgs::msg::PoseStamped>(
    "current_pose",
    10,
    [this](const geometry_msgs::msg::PoseStamped::SharedPtr msg)
    {
      globalBlackboard()->set("current_pose", msg->pose);
    });
}

BTExecutor::~BTExecutor()
{
}

void BTExecutor::onTreeCreated(BT::Tree & tree)
{
  logger_cout_ = std::make_shared<BT::StdCoutLogger>(tree);
}

std::optional<std::string> BTExecutor::onTreeExecutionCompleted(
  BT::NodeStatus status,
  bool was_cancelled)
{
  logger_cout_.reset();
  return std::nullopt;
}
} // namespace urc_behavior

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(urc_behavior::BTExecutor);
