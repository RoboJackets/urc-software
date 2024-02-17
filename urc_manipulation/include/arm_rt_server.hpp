#ifndef INCLUDE_ARM_RT_SERVER_HPP__
#define INCLUDE_ARM_RT_SERVER_HPP__

#include <array>
#include <atomic>
#include <control_msgs/msg/detail/joint_jog__struct.hpp>
#include <cstdint>
#include <geometry_msgs/msg/detail/pose__struct.hpp>
#include <geometry_msgs/msg/detail/pose_stamped__struct.hpp>
#include <geometry_msgs/msg/detail/twist_stamped__struct.hpp>
#include <map>
#include <memory>
#include "map"
#include "thread"

#include "rclcpp/rclcpp.hpp"

#include "std_srvs/srv/trigger.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include "moveit_servo/servo.h"
#include "moveit/planning_scene_monitor/planning_scene_monitor.h"
#include "geometry_msgs/msg/twist_stamped.hpp"
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/msg/detail/collision_object__struct.hpp>
#include <moveit_msgs/msg/detail/planning_scene__struct.hpp>
#include <moveit_servo/pose_tracking.h>
#include <moveit_servo/servo_parameters.h>
#include <moveit_servo/servo_parameters.h>
#include <moveit_servo/make_shared_from_pool.h>
#include <mutex>
#include <rclcpp/executors/multi_threaded_executor.hpp>
#include <rclcpp/executors/single_threaded_executor.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rate.hpp>
#include <rclcpp/service.hpp>
#include <rclcpp/subscription.hpp>
#include <std_msgs/msg/detail/int8__struct.hpp>
#include <std_msgs/msg/detail/string__struct.hpp>
#include <std_srvs/srv/detail/set_bool__struct.hpp>
#include <thread>

namespace urc_manipulation
{

enum ControlMode
{
  POSE,
  TWIST,
  IDLE
};
class ArmRTServer : public rclcpp::Node
{
public:
  ArmRTServer(const rclcpp::NodeOptions & options);

private:
  ControlMode mode = ControlMode::TWIST;
  ControlMode desired_mode_ = ControlMode::TWIST;
  std::atomic_bool pose_tracking_pause = false;
  std::atomic_bool pose_tracking_stop = false;
  std::mutex mode_lock;
  geometry_msgs::msg::PoseStamped current_pose_target_;

  rclcpp::Rate::SharedPtr update_freq;
  std::array<double, 3> config_parameters;

  std::shared_ptr<rclcpp::Node> node_;
  std::unique_ptr<moveit_servo::Servo> servo_;
  std::unique_ptr<moveit_servo::PoseTracking> pose_tracking_;
  std::shared_ptr<rclcpp::Node> move_group_node_;
  std::shared_ptr<rclcpp::executors::MultiThreadedExecutor> move_group_node_executor_;
  std::shared_ptr<moveit::planning_interface::MoveGroupInterface> move_group_;

  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<planning_scene_monitor::PlanningSceneMonitor> planning_scene_monitor_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr pose_target_subscriber_;
  rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pose_target_publisher_;
  rclcpp::Publisher<std_msgs::msg::Int8>::SharedPtr control_status_publisher_;
  rclcpp::Publisher<geometry_msgs::msg::Pose>::SharedPtr current_pose_publisher_;

  /** \brief Start the servo loop. Must be called once to begin Servoing. */
  void startServo(
    const std::shared_ptr<std_srvs::srv::Trigger::Request> & request,
    const std::shared_ptr<std_srvs::srv::Trigger::Response> & response);
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr start_servo_service_;

  /** \brief Stop the servo loop. This involves more overhead than pauseCB, e.g. it clears the planning scene monitor.
   * We recommend using pauseCB/unpauseCB if you will resume the Servo loop soon.
   */
  void stopServo(
    const std::shared_ptr<std_srvs::srv::Trigger::Request> & request,
    const std::shared_ptr<std_srvs::srv::Trigger::Response> & response);
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr stop_servo_service_;

  /** \brief Pause the servo loop but continue monitoring joint state so we can resume easily. */
  void pauseServo(
    const std::shared_ptr<std_srvs::srv::Trigger::Request> & request,
    const std::shared_ptr<std_srvs::srv::Trigger::Response> & response);
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr pause_servo_service_;

  /** \brief Resume the servo loop after pauseCB has been called. */
  void unpauseServo(
    const std::shared_ptr<std_srvs::srv::Trigger::Request> & request,
    const std::shared_ptr<std_srvs::srv::Trigger::Response> & response);
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr unpause_servo_service_;

  /** \brief Switch servoing control mode. Only being effective during idle state.
   * True for twist, false for pose tracking.
   */
  void switchMode(
    const std::shared_ptr<std_srvs::srv::SetBool::Request> & request,
    const std::shared_ptr<std_srvs::srv::SetBool::Response> & response);
  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr swtich_mode_service;

  void moveToPoseUpdate();
};

}  // namespace urc_manipulation

#endif /* INCLUDE_ARM_RT_SERVER_HPP__ */
