#include "urc_bt_nodes/actions/status_light_publisher.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <rclcpp/logging.hpp>

namespace behavior::actions
{
    bool StatusLightPublisher::setMessage(std_msgs::msg::Int8& msg) {
        RCLCPP_INFO(node_->get_logger(), "Published DATA!");
        msg.data = 1;
        return true;
    }
}

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(behavior::actions::StatusLightPublisher, "StatusLightPublisher");
