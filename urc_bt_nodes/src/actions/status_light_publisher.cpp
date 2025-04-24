#include "urc_bt_nodes/actions/status_light_publisher.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <rclcpp/logging.hpp>

namespace behavior::actions
{
bool StatusLightPublisher::setMessage(urc_msgs::msg::StatusLightCommand & msg)
{
  std::string color = getInput<std::string>("color").value();
  std::string state = getInput<std::string>("state").value();

  try {
    msg.color = stringToColor(color);
    msg.state = stringToState(state);
  } catch (std::invalid_argument & e) {
    return false;
  }

  return true;
}
}

#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(behavior::actions::StatusLightPublisher, "StatusLightPublisher");
