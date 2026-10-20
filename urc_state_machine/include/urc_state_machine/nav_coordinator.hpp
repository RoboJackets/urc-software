#ifndef NAV_COORDINATOR_HPP_
#define NAV_COORDINATOR_HPP_

#include <memory>
#include <string>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <urc_msgs/action/execute_autonomous_mission.hpp>
#include <urc_msgs/action/navigate_to_waypoint.hpp>
#include <urc_msgs/msg/waypoint.hpp>
#include "urc_state_machine/active_mission.hpp"
#include "urc_state_machine/mission_state.hpp"
#include "urc_state_machine/detection_confirmation.hpp"
#include "urc_state_machine/mission_state.hpp"
#include "urc_state_machine/spiral_search_pattern.hpp"
#include <vision_msgs/msg/detection2_d_array.hpp>
#include <urc_msgs/msg/detection_bounding_box.hpp>
#include <sensor_msgs/msg/camera_info.hpp>

namespace nav_coordinator
{
class NavCoordinator : public rclcpp::Node
{
public:
  explicit NavCoordinator(const rclcpp::NodeOptions & options);
  ~NavCoordinator() override = default;

private:
  using NavigateToWaypoint = urc_msgs::action::NavigateToWaypoint;
  using GoalHandleNavigate = rclcpp_action::ClientGoalHandle<NavigateToWaypoint>;
  using ExecuteMission = urc_msgs::action::ExecuteAutonomousMission;
  using MissionGoalHandle = rclcpp_action::ServerGoalHandle<ExecuteMission>;
  using LegResultHandler = std::function<void (const GoalHandleNavigate::WrappedResult &)>;

  enum class ErrorType
  {
    NONE,
    PLANNER_FAILURE,
    OBSTACLE_DETECTED,
    PLANNING_FAILED_IN_FOLLOWER,
    FOLLOWER_FAILURE,
    SERVER_UNAVAILABLE,
    SEARCH_FAILURE,
    UNKNOWN_ERROR
  };

  void handleWaypoint(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
  void handleGpsWaypoint(const urc_msgs::msg::Waypoint::SharedPtr msg);
  void sendFollowerGoal(const geometry_msgs::msg::PoseStamped & waypoint);

  void initializeMissionActionServer();

  void handleGoalResponse(const GoalHandleNavigate::SharedPtr & goal_handle);
  void handleFeedback(
    GoalHandleNavigate::SharedPtr,
    const std::shared_ptr<const NavigateToWaypoint::Feedback> feedback);
  void handleResult(const GoalHandleNavigate::WrappedResult & result);
  rclcpp_action::GoalResponse handleMissionGoal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const ExecuteMission::Goal> goal);

  rclcpp_action::CancelResponse handleMissionCancel(
    std::shared_ptr<MissionGoalHandle> goal_handle);

  void handleMissionAccepted(
    std::shared_ptr<MissionGoalHandle> goal_handle);
  // void sendMissionNavigation();
  void startMissionNavigation();
  void sendWaypointGoal(const geometry_msgs::msg::PoseStamped & goal_pose, std::uint8_t feedback_state,
    std::uint16_t failure_code, LegResultHandler on_result);

  void finishMissionNavigation(
    const GoalHandleNavigate::WrappedResult & result);
  void finishCanceledMission();

  void failMissionNavigation(const std::string & reason);
  void failMission(std::uint16_t error_code, ErrorType error_type, const std::string & reason);

  void initializeYoloSearch();
  void startYoloSearch();
  void sendNextSearchLeg();
  void finishSearchLeg(const GoalHandleNavigate::WrappedResult & result);
  void handleYoloDetections(const vision_msgs::msg::Detection2DArray & detections);
  void succeedYoloSearch(const urc_msgs::msg::DetectionBoundingBox & bounding_box);
  
  void transitionTo(urc_state_machine::MissionState new_state, const std::string & reason);
  void handleError(ErrorType error_type, const std::string & details);
  void publishState();
  std::string errorTypeToString(ErrorType error_type) const;
  std::string stateToString(urc_state_machine::MissionState state) const;

  urc_state_machine::MissionState state_{urc_state_machine::MissionState::IDLE};
  std::shared_ptr<urc_state_machine::ActiveMission> active_mission_;
  std::string follower_action_name_;
  bool cancel_on_new_waypoint_;
  std::string map_frame_id_;
  std::string utm_frame_id_;

  geometry_msgs::msg::PoseStamped active_waypoint_;
  GoalHandleNavigate::SharedPtr active_goal_handle_;

  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr waypoint_subscriber_;
  rclcpp::Subscription<urc_msgs::msg::Waypoint>::SharedPtr gps_waypoint_subscriber_;
  rclcpp_action::Client<NavigateToWaypoint>::SharedPtr follower_client_;
  rclcpp_action::Server<ExecuteMission>::SharedPtr mission_server_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr state_publisher_;
  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  rclcpp::Subscription<vision_msgs::msg::Detection2DArray>::SharedPtr yolo_detection_subscriber_;
  rclcpp::Subscription<sensor_msgs::msg::CameraInfo>::SharedPtr camera_info_subscriber_;
  std::optional<urc_state_machine::DetectionConfirmation> yolo_confirmation_;
  urc_state_machine::SpiralSearchConfig spiral_search_config_;
  int max_consecutive_search_leg_failures_{3};
  std::uint32_t camera_image_width_{0};
  std::uint32_t camera_image_height_{0};

  ErrorType last_error_{ErrorType::NONE};
  std::string last_error_details_;
};

}

#endif
