#ifndef URC_STATE_MACHINE__WAYPOINT_MISSION_HPP_
#define URC_STATE_MACHINE__WAYPOINT_MISSION_HPP_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <geometry_msgs/msg/point.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <urc_msgs/action/execute_autonomous_mission.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

namespace waypoint_mission
{

// Drives a fixed route of map-frame waypoints as NavCoordinator route missions,
// one at a time: each waypoint is sent once the previous one succeeds, retried
// a bounded number of times on failure, then skipped. A mission the
// coordinator pauses for teleop is canceled and counted as a failed attempt.
class WaypointMission : public rclcpp::Node
{
public:
  explicit WaypointMission(const rclcpp::NodeOptions & options);

private:
  using Route = urc_msgs::action::ExecuteAutonomousMission;
  using RouteGoalHandle = rclcpp_action::ClientGoalHandle<Route>;

  enum class Phase
  {
    WaitingForStartup,
    Active,
    RetryPending,
    Complete
  };

  void loadRoute();
  void step();
  bool startupReady();
  void sendCurrentWaypoint();
  void handleGoalResponse(std::uint64_t generation, const RouteGoalHandle::SharedPtr & handle);
  void handleFeedback(std::uint64_t generation, const std::string & state);
  void handleResult(std::uint64_t generation, const RouteGoalHandle::WrappedResult & result);
  void handleFailure(const std::string & reason);
  void advance();
  void publishMarkers() const;

  std::vector<geometry_msgs::msg::Point> route_;
  std::size_t current_index_ = 0;
  int attempts_ = 0;
  int laps_completed_ = 0;
  Phase phase_ = Phase::WaitingForStartup;
  // Identifies the goal in flight so callbacks from an earlier goal are ignored
  std::uint64_t goal_generation_ = 0;
  RouteGoalHandle::SharedPtr goal_handle_;
  bool cancel_requested_ = false;
  rclcpp::Time ready_since_;
  rclcpp::Time retry_at_;

  std::string frame_id_;
  std::string base_frame_id_;
  int laps_ = 1;
  int max_attempts_ = 3;
  double start_delay_s_ = 5.0;
  double retry_delay_s_ = 2.0;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
  rclcpp_action::Client<Route>::SharedPtr route_client_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace waypoint_mission

#endif  // URC_STATE_MACHINE__WAYPOINT_MISSION_HPP_
