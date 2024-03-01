#ifndef BT_ORCHESTOR_F88CE7D9_55E9_48BD_B38C_30B689BFC542_HPP__
#define BT_ORCHESTOR_F88CE7D9_55E9_48BD_B38C_30B689BFC542_HPP__

#include "behaviortree_cpp/bt_factory.h"
#include <memory>
#include <rclcpp/node.hpp>

class BehaviorTreeOrchestor : public rclcpp::Node
{
public:
  BehaviorTreeOrchestor();
  ~BehaviorTreeOrchestor() = default;

private:
  BT::BehaviorTreeFactory tree_factory_;
  std::shared_ptr<BT::Tree> tree_;

  void RenewTree();
  void Start();
  void End();
}

#endif /* BT_ORCHESTOR_F88CE7D9_55E9_48BD_B38C_30B689BFC542_HPP__ */
