#include "urc_bt_nodes/actions/status_light_publisher.hpp"
#include "behaviortree_cpp/basic_types.h"
#include <rclcpp/logging.hpp>

namespace behavior::actions
{
    bool StatusLightPublisher::setMessage(std_msgs::msg::Int8& msg) {
        msg = getInput<std_msgs::msg::Int8>("value").value();
        return true;
    }
}

namespace BT
{
template<>
inline std_msgs::msg::Int8 convertFromString(StringView str)
{
  std_msgs::msg::Int8 output;
  output.data = convertFromString<int8_t>(str);
  return output;
}
} // namespace BT


#include "behaviortree_ros2/plugins.hpp"
CreateRosNodePlugin(behavior::actions::StatusLightPublisher, "StatusLightPublisher");
