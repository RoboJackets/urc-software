#ifndef BT_ORCHESTOR_A6C307B5_B644_4561_AE6D_9833D66C7A1E_HPP__
#define BT_ORCHESTOR_A6C307B5_B644_4561_AE6D_9833D66C7A1E_HPP__

#include "behaviortree_cpp/bt_factory.h"
#include <memory>
#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/service.hpp>
#include <urc_msgs/srv/detail/update_behavior_tree__struct.hpp>
#include <urc_msgs/srv/update_behavior_tree.hpp>

namespace behavior
{

class BehaviorTreeOrchestor : public rclcpp::Node
{
public:
  BehaviorTreeOrchestor(const rclcpp::NodeOptions& options);
  ~BehaviorTreeOrchestor();

protected:
  BT::BehaviorTreeFactory tree_factory_;
  std::unique_ptr<BT::Tree> tree_;

  void Register();
  void RenewTree();
  void Start();
  void Clear();

  bool TreeLoaded();

  bool is_running_;

  std::unique_ptr<rclcpp::Logger> logger_;
  rclcpp::Service<urc_msgs::srv::UpdateBehaviorTree>::SharedPtr update_bt_service_;
};

}  // namespace behavior

#endif /* BT_ORCHESTOR_F88CE7D9_55E9_48BD_B38C_30B689BFC542_HPP__ */
