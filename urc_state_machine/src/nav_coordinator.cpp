#include "urc_state_machine/nav_coordinator.hpp"
#include <chrono>
#include <rclcpp_components/register_node_macro.hpp>
#include "urc_state_machine/mission_geometry.hpp"

namespace nav_coordinator
{
NavCoordinator::NavCoordinator(const rclcpp::NodeOptions & options)
: Node("nav_coordinator", options),
  parameters_(urc_state_machine::declareMissionParameters(*this))
{
  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
  navigation_ = std::make_unique<urc_state_machine::NavigationClient>(
    *this, parameters_.follower_action);
  state_pub_ = create_publisher<std_msgs::msg::String>(
    parameters_.state_topic, rclcpp::QoS(1).reliable().transient_local());
  initializeRouteAction();
  initializeAstronautAction();
  initializeInputs();
  timer_ = create_wall_timer(
    std::chrono::duration<double>(parameters_.tick_period), [this]() {
      updateMission();
    });
  if (parameters_.tool_placeholder_success) {
    RCLCPP_WARN(get_logger(), "TEST MODE: FETCH and GIVE simulate success; no arm moves");
  }
  publishState();
}

bool NavCoordinator::canAccept(const Pose & waypoint) const
{
  return mission_.kind == Kind::NONE && !navigation_->busy() && navigation_->ready() &&
         waypoint.header.frame_id == parameters_.map_frame &&
         urc_state_machine::validPose(waypoint);
}

void NavCoordinator::begin(Kind kind, const Pose & waypoint)
{
  mission_ = urc_state_machine::ActiveMission();
  mission_.kind = kind;
  mission_.waypoint = waypoint;
  tracking_.reset();
  last_command_stamp_ = now();
}

void NavCoordinator::publishState()
{
  std_msgs::msg::String message;
  message.data = std::string("state=") + urc_state_machine::stateName(mission_.state);
  if (!mission_.reason.empty()) {
    message.data += " details=" + mission_.reason;
  }
  state_pub_->publish(message);
}

double NavCoordinator::phaseElapsed() const
{
  return std::chrono::duration<double>(
    urc_state_machine::MissionClock::now() - mission_.phase_started).count();
}
}  // namespace nav_coordinator
RCLCPP_COMPONENTS_REGISTER_NODE(nav_coordinator::NavCoordinator)
