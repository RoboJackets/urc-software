#ifndef BT_ORCHESTOR_A6C307B5_B644_4561_AE6D_9833D66C7A1E_HPP__
#define BT_ORCHESTOR_A6C307B5_B644_4561_AE6D_9833D66C7A1E_HPP__

#include "behaviortree_cpp/bt_factory.h"
#include "std_srvs/std_srvs/srv/detail/trigger__struct.hpp"
#include <memory>
#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rate.hpp>
#include <rclcpp/service.hpp>
#include <rclcpp/timer.hpp>
#include <string>
#include <urc_msgs/srv/detail/update_behavior_tree__struct.hpp>
#include <urc_msgs/srv/update_behavior_tree.hpp>

namespace behavior
{

using TriggerRequest = std_srvs::srv::Trigger::Request::ConstSharedPtr;
using TriggerResponse = std_srvs::srv::Trigger::Response::SharedPtr;
using UpdateBTReqest = urc_msgs::srv::UpdateBehaviorTree::Request::ConstSharedPtr;
using UpdateBTResponse = urc_msgs::srv::UpdateBehaviorTree::Response::SharedPtr;

class BehaviorTreeOrchestor : public rclcpp::Node
{
public:
  BehaviorTreeOrchestor(const rclcpp::NodeOptions & options);
  ~BehaviorTreeOrchestor();

protected:
  BT::BehaviorTreeFactory tree_factory_;
  std::unique_ptr<BT::Tree> tree_;

  void Initialize();

  bool RenewTree(bool use_dir, std::string dir, std::string content);
  bool Start();
  bool Stop();

  bool is_tree_loaded();
  bool is_running_;
  int tick_rate_ = 100;
  std::shared_ptr<std::string> tree_dir_ = nullptr;

  std::unique_ptr<rclcpp::Logger> logger_;
  std::shared_ptr<rclcpp::Node> bt_ros_nh_;
  std::shared_ptr<rclcpp::Logger> bt_ros_logger_;
  rclcpp::Service<urc_msgs::srv::UpdateBehaviorTree>::SharedPtr update_bt_service_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr reload_bt_service_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr start_bt_service_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr stop_bt_service_;
};

}  // namespace behavior

#endif /* BT_ORCHESTOR_F88CE7D9_55E9_48BD_B38C_30B689BFC542_HPP__ */
