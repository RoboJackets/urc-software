#include "urc_bt_nodes/actions/status_light_color_publisher.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <rclcpp/logging.hpp>

namespace behavior::actions
{
    bool StatusLightColorPublisher::setMessage(std_msgs::msg::Int8& msg) {
        msg = getInput<std_msgs::msg::Int8>("color").value();
        return true;
    }
}

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(behavior::actions::StatusLightColorPublisher, "StatusLightColorPublisher");
