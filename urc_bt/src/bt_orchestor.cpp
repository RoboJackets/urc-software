#include "urc_bt/bt_orchestor.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include <algorithm>
#include <exception>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/node_options.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/service.hpp>
#include <rclcpp/utilities.hpp>
#include <urc_msgs/srv/detail/update_behavior_tree__struct.hpp>
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
  declare_parameter<std::vector<std::string>>("node_lib_dirs");
  declare_parameter<std::string>("tree_file_dir");

  // register all the specified libraries
  if (has_parameter("node_lib_dirs"))
  {
    std::vector<std::string> temp;
    get_parameter("node_lib_dirs", temp);
    RCLCPP_INFO(*logger_, "All Loaded Plugins:");
    for (const auto& node_lib_dir : temp)
    {
      RCLCPP_INFO(*logger_, "\t%s", node_lib_dir.c_str());
      tree_factory_.registerFromPlugin(node_lib_dir);
    }
  }

  // create default tree if a file is speficied
  if (has_parameter("tree_file_dir"))
  {
    std::string temp;
    get_parameter("tree_file_dir", temp);
    RCLCPP_INFO(*logger_, "Creating tree from configuration file %s.", temp.c_str());
    tree_ = std::make_unique<BT::Tree>(tree_factory_.createTreeFromFile(temp));
  }
  else
  {
    RCLCPP_WARN(*logger_,
                "No behavior tree file set. Will not able to start the orchestor until upon calling service "
                "/update_tree.");
  }

  // TODO: add a service to hot-update tree on the fly
  update_bt_service_ = create_service<urc_msgs::srv::UpdateBehaviorTree>(
      "~/update_tree",                                                          //
      [this](                                                                   //
          const urc_msgs::srv::UpdateBehaviorTree::Request::SharedPtr request,  //
          urc_msgs::srv::UpdateBehaviorTree::Response::SharedPtr response) {
        std::unique_ptr<BT::Tree> new_tree_;

        try
        {
          if (request->use_dir)
          {
            new_tree_ = std::make_unique<BT::Tree>(tree_factory_.createTreeFromFile(request->tree_dir));
          }
          else
          {
            new_tree_ = std::make_unique<BT::Tree>(tree_factory_.createTreeFromText(request->tree_content));
          }

          Clear();
          RCLCPP_DEBUG(*logger_, "Load tree successfull. Start hot swapping...");
          tree_ = std::move(new_tree_);

          Start();
          RCLCPP_DEBUG(*logger_, "Hot swapping successful!");
        }
        catch (std::exception& e)
        {
          RCLCPP_ERROR(*logger_, "Fail to load new tree. %s.", e.what());
          is_running_ = false;
          tree_.reset(nullptr);  // auto stop tree
          response->success = false;
          return response;
        }

        response->success = true;
        return response;
      });

  // if the tree is loaded, start the tree.
  if (TreeLoaded())
  {
    Start();
  }
}

BehaviorTreeOrchestor::~BehaviorTreeOrchestor()
{
  Clear();
}

void BehaviorTreeOrchestor::RenewTree()
{
}

void BehaviorTreeOrchestor::Start()
{
  if (!TreeLoaded())
  {
    RCLCPP_ERROR(*logger_, "Tree is not loaded! Not able to start the orchestor.");
    return;
  }

  is_running_ = true;
  std::thread([this]() {
    RCLCPP_DEBUG(*logger_, "Staring BT Orchestor...");
    while (is_running_)
      tree_->tickExactlyOnce();
  }).detach();
}

void BehaviorTreeOrchestor::Clear()
{
  is_running_ = false;
}

bool BehaviorTreeOrchestor::TreeLoaded()
{
  return tree_ != nullptr;
}

}  // namespace behavior

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(behavior::BehaviorTreeOrchestor);