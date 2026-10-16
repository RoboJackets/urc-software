#ifndef URC_STATE_MACHINE__NAVIGATION_CLIENT_HPP_
#define URC_STATE_MACHINE__NAVIGATION_CLIENT_HPP_

#include <cstdint>
#include <optional>
#include <string>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <urc_msgs/action/navigate_to_waypoint.hpp>

namespace urc_state_machine
{
enum class NavigationResult { REACHED, FAILED, CANCELED, STOPPED };

// All methods and callbacks use the node's default mutually exclusive callback group.
class NavigationClient
{
public:
  NavigationClient(rclcpp::Node & node, const std::string & action_name);
  bool ready() const;
  bool busy() const;
  // Coalesce updates and wait for the old terminal result before sending the newest goal.
  void replace(const geometry_msgs::msg::PoseStamped & goal);
  // Discard pending replacements. busy() remains true until stopping is acknowledged.
  void cancel();
  // Consume one completion. Internal replacement cancellations are not mission failures.
  std::optional<NavigationResult> takeResult();
  float distance() const;
  uint16_t replans() const;

private:
  using Action = urc_msgs::action::NavigateToWaypoint;
  using Handle = rclcpp_action::ClientGoalHandle<Action>;
  void send(const geometry_msgs::msg::PoseStamped & goal);
  void accepted(uint64_t generation, Handle::SharedPtr handle);
  void completed(uint64_t generation, const Handle::WrappedResult & result);
  void finish(NavigationResult result);
  void cancelAcceptedGoal();

  rclcpp_action::Client<Action>::SharedPtr client_;
  Handle::SharedPtr handle_;
  std::optional<geometry_msgs::msg::PoseStamped> pending_;
  std::optional<NavigationResult> result_;
  bool sending_{false};
  bool stopping_{false};
  bool cancel_sent_{false};
  uint64_t generation_{0};
  float distance_{0.0F};
  uint16_t replans_{0};
};
}  // namespace urc_state_machine
#endif
