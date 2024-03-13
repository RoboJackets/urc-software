#include "urc_bt_nodes/base/call_trigger.hpp"
#include "std_srvs/std_srvs/srv/detail/trigger__struct.hpp"
#include <future>
#include <memory>
#include <rclcpp/time.hpp>

namespace behavior::base
{

NodeStatus CallTrigger::tick()
{
  {
    if (client_ == nullptr)
    {
      auto node = getInput<rclcpp::Node::SharedPtr>("nh");
      client_ = node->get()->create_client<std_srvs::srv::Trigger>(getInput<std::string>("service_name").value());
    }

    try
    {
      if (!in_progress_)
      {
        result_ = std::async(std::launch::async, [this]() {
          auto start_time = rclcpp::Time().seconds();
          auto end_time = start_time + getInput<int>("timeout").value();

          if (!client_->service_is_ready())
          {
            if (rclcpp::Time().seconds() > end_time)
              return false;
          }

          auto result = client_->async_send_request(std::make_shared<std_srvs::srv::Trigger::Request>());
          while (result.wait_for(0s) != std::future_status::ready)
          {
            if (rclcpp::Time().seconds() > end_time)
              return false;
          }

          return result.get()->success;
        });
      }

      if (result_.wait_for(0s) == std::future_status::ready)
      {
        return result_.get() ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
        in_progress_ = false;
      }
      else
      {
        return BT::NodeStatus::RUNNING;
      }
    }
    catch (std::exception& e)
    {
      return BT::NodeStatus::FAILURE;
    }
  }
}

}  // namespace behavior::base
