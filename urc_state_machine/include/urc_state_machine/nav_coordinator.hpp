#ifndef URC_STATE_MACHINE__NAV_COORDINATOR_HPP_
#define URC_STATE_MACHINE__NAV_COORDINATOR_HPP_
#include <cstdint>
#include <memory>
#include <optional>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <urc_msgs/action/execute_astronaut_mission.hpp>
#include <urc_msgs/action/execute_autonomous_mission.hpp>
#include <urc_msgs/msg/aruco_detection.hpp>
#include <urc_msgs/msg/astronaut_command.hpp>
#include <urc_msgs/msg/waypoint.hpp>
#include "urc_state_machine/active_mission.hpp"
#include "urc_state_machine/astronaut_tracking.hpp"
#include "urc_state_machine/mission_parameters.hpp"
#include "urc_state_machine/navigation_client.hpp"

namespace nav_coordinator
{
// ROS boundary and mission owner. All mission callbacks share the default mutually
// exclusive callback group; TF owns its own thread-safe observation buffer.
class NavCoordinator : public rclcpp::Node
{
public:
  explicit NavCoordinator(const rclcpp::NodeOptions & options);

private:
  using State = urc_state_machine::State;
  using Event = urc_state_machine::Event;
  using Kind = urc_state_machine::MissionKind;
  using Route = urc_msgs::action::ExecuteAutonomousMission;
  using Astronaut = urc_msgs::action::ExecuteAstronautMission;
  using RouteHandle = rclcpp_action::ServerGoalHandle<Route>;
  using AstronautHandle = rclcpp_action::ServerGoalHandle<Astronaut>;
  using Pose = geometry_msgs::msg::PoseStamped;
  using Command = urc_msgs::msg::AstronautCommand;

  void initializeRouteAction();
  void initializeAstronautAction();
  void initializeInputs();
  bool canAccept(const Pose & waypoint) const;
  void begin(Kind kind, const Pose & waypoint);
  void command(const Command & input);
  void waypoint(const Pose & input);
  void gpsWaypoint(const urc_msgs::msg::Waypoint & input);
  void updateMission();
  void updateCurrentState();
  void updateStopping();
  void transitionOn(Event event);
  void changeState(State state);
  void driveToWaypoint();
  void searchForMarker();
  void calculateMarkerApproach(const Pose & rover);
  void driveToMarker();
  void verifyMarkerArrival(const Pose & rover);
  void driveToAstronaut(const Pose & rover);
  void followAstronaut(const Pose & rover);
  void waitForStay(const Pose & rover);
  void returnToAstronaut(const Pose & rover);
  bool requireAstronautObservation();
  void updateAstronautNavigation(const Pose & rover);
  void completeToolPlaceholder();
  void updateRecovery();
  void updateNavigationOutcome(urc_state_machine::NavigationResult result);
  void startNavigation(const Pose & goal);
  void retryStateOrFail(State resume, uint16_t code, const std::string & reason);
  void stopMission(State next, uint16_t code, const std::string & reason);
  void finishMission();
  void publishState();
  void publishFeedback();
  double phaseElapsed() const;
  bool fresh(const builtin_interfaces::msg::Time & stamp, double max_age) const;
  std::optional<Pose> mapPose(const Pose & input) const;
  std::optional<Pose> roverPose() const;
  bool astronautFresh() const;
  bool markerFresh() const;

  urc_state_machine::MissionParameters parameters_;
  urc_state_machine::ActiveMission mission_;
  urc_state_machine::AstronautTracking tracking_;
  std::unique_ptr<urc_state_machine::NavigationClient> navigation_;
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
  rclcpp_action::Server<Route>::SharedPtr route_server_;
  rclcpp_action::Server<Astronaut>::SharedPtr astronaut_server_;
  std::shared_ptr<RouteHandle> route_handle_;
  std::shared_ptr<AstronautHandle> astronaut_handle_;
  rclcpp::Subscription<Command>::SharedPtr command_sub_;
  rclcpp::Subscription<Pose>::SharedPtr astronaut_sub_, waypoint_sub_;
  rclcpp::Subscription<urc_msgs::msg::ArucoDetection>::SharedPtr aruco_sub_;
  rclcpp::Subscription<urc_msgs::msg::Waypoint>::SharedPtr gps_sub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr state_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Time last_command_stamp_{0, 0, RCL_ROS_TIME};
};
}  // namespace nav_coordinator
#endif
