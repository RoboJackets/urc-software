#ifndef URC_STATE_MACHINE__WAYPOINT_MISSION_HPP_
#define URC_STATE_MACHINE__WAYPOINT_MISSION_HPP_

#include <memory>
#include <string>
#include <vector>

#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <visualization_msgs/msg/marker_array.hpp>

namespace waypoint_mission
{

// Drives a fixed route of map-frame waypoints through NavCoordinator, one at a
// time: each waypoint is sent once the previous one succeeds, retried a
// bounded number of times on failure, then skipped.
class WaypointMission : public rclcpp::Node
{
public:
  explicit WaypointMission(const rclcpp::NodeOptions & options);

private:
  enum class Phase
  {
    WaitingForStartup,
    AwaitingAcceptance,
    Tracking,
    RetryPending,
    Complete
  };

  void loadRoute();
  void step();
  bool startupReady();
  void handleCoordinatorState(const std_msgs::msg::String::SharedPtr msg);
  void handleSuccess();
  void handleFailure(const std::string & state);
  void sendCurrentWaypoint();
  void advance();
  void publishMarkers() const;

  std::vector<geometry_msgs::msg::Point> route_;
  std::size_t current_index_ = 0;
  int attempts_ = 0;
  int laps_completed_ = 0;
  Phase phase_ = Phase::WaitingForStartup;
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
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr waypoint_publisher_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_publisher_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr state_subscriber_;
  rclcpp::TimerBase::SharedPtr timer_;
};

}  // namespace waypoint_mission

#endif  // URC_STATE_MACHINE__WAYPOINT_MISSION_HPP_
