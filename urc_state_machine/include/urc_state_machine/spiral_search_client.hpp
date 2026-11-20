#ifndef URC_STATE_MACHINE__SPIRAL_SEARCH_CLIENT_HPP_
#define URC_STATE_MACHINE__SPIRAL_SEARCH_CLIENT_HPP_

#include <cstdint>
#include <optional>
#include <string>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/rclcpp.hpp>
#include <urc_msgs/srv/generate_spiral_search.hpp>

namespace urc_state_machine
{
// All methods and responses share the node's default mutually exclusive callback group.
class SpiralSearchClient
{
public:
  SpiralSearchClient(rclcpp::Node & node, const std::string & service_name);
  bool request(const geometry_msgs::msg::PoseStamped & center, double radius);
  void cancel();
  bool failed() const;
  std::optional<nav_msgs::msg::Path> takePath();

private:
  using Service = urc_msgs::srv::GenerateSpiralSearch;
  rclcpp::Client<Service>::SharedPtr client_;
  std::optional<int64_t> request_id_;
  std::optional<nav_msgs::msg::Path> path_;
  uint64_t generation_{0};
  bool failed_{false};
};
}  // namespace urc_state_machine
#endif  // URC_STATE_MACHINE__SPIRAL_SEARCH_CLIENT_HPP_
