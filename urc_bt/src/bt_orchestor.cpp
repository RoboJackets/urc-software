#include "urc_bt/bt_orchestor.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include "behaviortree_ros2/plugins.hpp"
#include "behaviortree_ros2/ros_node_params.hpp"
#include <exception>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/node_options.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/rate.hpp>
#include <rclcpp/service.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp/utilities.hpp>
#include <std_srvs/srv/detail/trigger__struct.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <urc_msgs/srv/update_behavior_tree.hpp>
#include <string>
#include <thread>
#include <vector>

namespace behavior
{

BehaviorTreeOrchestor::BehaviorTreeOrchestor(const rclcpp::NodeOptions& options) : rclcpp::Node("bt_orchestor", options)
{
  logger_ = std::make_unique<rclcpp::Logger>(rclcpp::get_logger("bt_orchestor"));
  logger_->set_level(rclcpp::Logger::Level::Debug);
  declare_parameter<std::vector<std::string>>("normal_node_lib_dirs");
  declare_parameter<std::vector<std::string>>("ros_node_lib_dirs");
  declare_parameter<std::string>("tree_file_dir");
  declare_parameter<int>("tick_rate");
  declare_parameter<bool>("start_bridge", true);

  bt_ros_nh_ = create_sub_node("ros_nh");
  bt_ros_logger_ = std::make_shared<rclcpp::Logger>(bt_ros_nh_->get_logger());

  // register all the specified libraries
  if (has_parameter("normal_node_lib_dirs"))
  {
    std::vector<std::string> temp;
    get_parameter("normal_node_lib_dirs", temp);
    RCLCPP_INFO(*logger_, "Loading %ld Normal Plugin%s All Loaded Plugins:", temp.size(), temp.size() > 1 ? "s." : ".");

    for (const auto& node_lib_dir : temp)
    {
      RCLCPP_INFO(*logger_, "\t%s", node_lib_dir.c_str());
      tree_factory_.registerFromPlugin(node_lib_dir);
    }
  }
  if (has_parameter("ros_node_lib_dirs"))
  {
    std::vector<std::string> temp;
    get_parameter("ros_node_lib_dirs", temp);
    RCLCPP_INFO(*logger_, "Loading %ld ROS Plugin%s All Loaded Plugins:", temp.size(), temp.size() > 1 ? "s." : ".");

    BT::RosNodeParams params_;
    params_.nh = bt_ros_nh_;

    for (const auto& node_lib_dir : temp)
    {
      RCLCPP_INFO(*logger_, "\t%s", node_lib_dir.c_str());
      // tree_factory_.registerFromPlugin(node_lib_dir);
      RegisterRosNode(tree_factory_, node_lib_dir, params_);
    }
  }

  // create default tree if a file is speficied
  if (has_parameter("tree_file_dir"))
  {
    std::string temp;
    get_parameter("tree_file_dir", temp);
    tree_dir_ = std::make_shared<std::string>(temp);
    RCLCPP_INFO(*logger_, "Creating tree from configuration file %s.", temp.c_str());
    tree_ = std::make_unique<BT::Tree>(tree_factory_.createTreeFromFile(temp));
  }
  else
  {
    RCLCPP_WARN(*logger_,
                "No behavior tree file set. Will not able to start the orchestor until upon calling service "
                "/update_tree.");
  }
  if (has_parameter("tick_rate"))
  {
    tick_rate_ = get_parameter("tick_rate").as_int();
    RCLCPP_INFO(*logger_, "Tick rate set to %d Hz.", tick_rate_);
  }
  else
  {
    RCLCPP_WARN(*logger_, "No tick rate set, default to run at 100 Hz.");
  }

  // starts service
  update_bt_service_ = create_service<urc_msgs::srv::UpdateBehaviorTree>(
      "~/update_tree",                                                //
      [this](                                                         //
          const UpdateBTReqest request, UpdateBTResponse response) {  //
        response->success = RenewTree(request->use_dir, request->tree_dir, request->tree_content);
        return response;
      });
  reload_bt_service_ =
      create_service<std_srvs::srv::Trigger>("~/reload", [this](const TriggerRequest, TriggerResponse response) {
        if (tree_dir_ == nullptr)
        {
          RCLCPP_WARN(*logger_, "Tree dir is null, cannot perform reload.");
          response->success = false;
        }
        else
        {
          response->success = RenewTree(true, *tree_dir_, "");
        }
        return response;
      });
  start_bt_service_ = create_service<std_srvs::srv::Trigger>(  //
      "~/start_bt", [this](const TriggerRequest, TriggerResponse response) {
        if (!is_running_)
        {
          response->success = Start();
        }
        else
        {
          response->message = "Behavior tree has already been started.";
          response->success = false;
        }
        return response;
      });
  stop_bt_service_ =
      create_service<std_srvs::srv::Trigger>("~/stop_bt", [this](TriggerRequest, TriggerResponse response) {
        if (is_running_)
        {
          response->success = Stop();
        }
        else
        {
          response->message = "Behavior tree has not been started.";
          response->success = false;
        }
        return response;
      });

  // if the tree is loaded, start the tree.
  if (is_tree_loaded())
  {
    Initialize();
    Start();
  }
}

BehaviorTreeOrchestor::~BehaviorTreeOrchestor()
{
  Stop();
}

bool BehaviorTreeOrchestor::RenewTree(bool use_dir, std::string dir, std::string content)
{
  std::unique_ptr<BT::Tree> new_tree_;

  try
  {
    if (use_dir)
    {
      new_tree_ = std::make_unique<BT::Tree>(tree_factory_.createTreeFromFile(dir));
    }
    else
    {
      new_tree_ = std::make_unique<BT::Tree>(tree_factory_.createTreeFromText(content));
    }

    Stop();
    RCLCPP_DEBUG(*logger_, "Load tree successfull. Start hot swapping...");
    tree_ = std::move(new_tree_);

    Initialize();
    Start();  // auto start
    RCLCPP_DEBUG(*logger_, "Hot swapping successful!");
  }
  catch (std::exception& e)
  {
    RCLCPP_ERROR(*logger_, "Fail to load new tree. %s.", e.what());
    is_running_ = false;
    tree_.reset(nullptr);  // auto stop tree
    return false;
  }

  return true;
}

void BehaviorTreeOrchestor::Initialize()
{
  if (!get_parameter("start_bridge").get_parameter_value().to_value_msg().bool_value)
  {
    return;
  }

  // register current node to tree factory
  tree_->rootBlackboard()->set("ros_nh", bt_ros_nh_);
  tree_->rootBlackboard()->set("ros_log", bt_ros_logger_);
}

bool BehaviorTreeOrchestor::Start()
{
  if (!is_tree_loaded())
  {
    RCLCPP_ERROR(*logger_, "Tree is not loaded! Not able to start the orchestor.");
    return false;
  }

  is_running_ = true;
  std::thread([this]() {
    RCLCPP_DEBUG(*logger_, "Staring BT Orchestor...");
    rclcpp::Rate rate(tick_rate_);

    while (is_running_)
    {
      tree_->tickExactlyOnce();
      rate.sleep();
    }
  }).detach();
  return true;
}

bool BehaviorTreeOrchestor::Stop()
{
  is_running_ = false;
  RCLCPP_DEBUG(*logger_, "Stopping BT Orchestor...");
  return true;
}

bool BehaviorTreeOrchestor::is_tree_loaded()
{
  return tree_ != nullptr;
}

}  // namespace behavior

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(behavior::BehaviorTreeOrchestor);