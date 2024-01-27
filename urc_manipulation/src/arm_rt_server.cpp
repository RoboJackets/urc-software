#include "arm_rt_server.hpp"
#include <Eigen/src/Core/Matrix.h>
#include <control_msgs/msg/detail/joint_jog__struct.hpp>
#include <geometry_msgs/msg/detail/pose__struct.hpp>
#include <geometry_msgs/msg/detail/pose_stamped__struct.hpp>
#include <geometry_msgs/msg/detail/transform_stamped__struct.hpp>
#include <geometry_msgs/msg/detail/twist_stamped__struct.hpp>
#include <memory>
#include <moveit/planning_scene_monitor/planning_scene_monitor.h>
#include <moveit_msgs/msg/detail/planning_scene__struct.hpp>
#include <moveit_servo/pose_tracking.h>
#include <moveit_servo/servo.h>
#include <moveit_servo/servo_parameters.h>
#include <mutex>
#include <rclcpp/executors/multi_threaded_executor.hpp>
#include <rclcpp/executors/single_threaded_executor.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/node_options.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/rate.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <std_msgs/msg/detail/int8__struct.hpp>
#include <std_msgs/msg/detail/string__struct.hpp>
#include <std_srvs/srv/detail/set_bool__struct.hpp>
#include <string>
#include <thread>
#include <unistd.h>

namespace urc_manipulation
{
ArmRTServer::ArmRTServer(const rclcpp::NodeOptions& options)
  : rclcpp::Node("arm_rt_server", options), node_{ std::make_shared<rclcpp::Node>("servo_node", options) }
// , move_group_node_{ std::make_shared<rclcpp::Node>("move_group_node", options) }
{
  RCLCPP_INFO(get_logger(), "Servo node starting...");
  if (!options.use_intra_process_comms())
  {
    RCLCPP_WARN_STREAM(get_logger(),
                       "Intra-process communication is disabled, consider enabling it by adding: "
                       "\nextra_arguments=[{'use_intra_process_comms' : True}]\nto the Servo composable node "
                       "in the launch file");
  }

  declare_parameter<std::string>("arm_planning_group", "arm");

  // Set up services for interacting with Servo
  start_servo_service_ = node_->create_service<std_srvs::srv::Trigger>(
      "~/start_servo", [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>& request,
                              const std::shared_ptr<std_srvs::srv::Trigger::Response>& response) {
        return startServo(request, response);
      });
  stop_servo_service_ = node_->create_service<std_srvs::srv::Trigger>(
      "~/stop_servo", [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>& request,
                             const std::shared_ptr<std_srvs::srv::Trigger::Response>& response) {
        return stopServo(request, response);
      });
  pause_servo_service_ = node_->create_service<std_srvs::srv::Trigger>(
      "~/pause_servo", [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>& request,
                              const std::shared_ptr<std_srvs::srv::Trigger::Response>& response) {
        return pauseServo(request, response);
      });
  unpause_servo_service_ = node_->create_service<std_srvs::srv::Trigger>(
      "~/unpause_servo", [this](const std::shared_ptr<std_srvs::srv::Trigger::Request>& request,
                                const std::shared_ptr<std_srvs::srv::Trigger::Response>& response) {
        return unpauseServo(request, response);
      });
  swtich_mode_service = node_->create_service<std_srvs::srv::SetBool>(
      "~/switch_mode", [this](const std::shared_ptr<std_srvs::srv::SetBool::Request>& request,
                              const std::shared_ptr<std_srvs::srv::SetBool::Response>& response) {
        return switchMode(request, response);
      });

  pose_target_subscriber_ = node_->create_subscription<geometry_msgs::msg::PoseStamped>(
      "~/pose_target_cmds", rclcpp::SystemDefaultsQoS(),
      [this](const geometry_msgs::msg::PoseStamped::SharedPtr msg) { current_pose_target_ = *msg; });
  pose_target_publisher_ =
      node_->create_publisher<geometry_msgs::msg::PoseStamped>("/target_pose", rclcpp::SystemDefaultsQoS());

  control_status_publisher_ =
      node_->create_publisher<std_msgs::msg::Int8>("~/control_status", rclcpp::SystemDefaultsQoS());
  current_pose_publisher_ =
      node_->create_publisher<geometry_msgs::msg::Pose>("~/current_pose", rclcpp::SystemDefaultsQoS());

  // Can set robot_description name from parameters
  std::string robot_description_name = "robot_description";
  node_->get_parameter_or("robot_description_name", robot_description_name, robot_description_name);

  // Get the servo parameters
  auto servo_parameters = moveit_servo::ServoParameters::makeServoParameters(node_);
  if (servo_parameters == nullptr)
  {
    RCLCPP_ERROR(get_logger(), "Failed to load the servo parameters");
    throw std::runtime_error("Failed to load the servo parameters");
  }

  // Set up planning_scene_monitor
  planning_scene_monitor_ = std::make_shared<planning_scene_monitor::PlanningSceneMonitor>(
      node_, robot_description_name, "planning_scene_monitor");
  planning_scene_monitor_->startStateMonitor(servo_parameters->joint_topic);
  planning_scene_monitor_->startSceneMonitor(servo_parameters->monitored_planning_scene_topic);
  planning_scene_monitor_->setPlanningScenePublishingFrequency(25);
  planning_scene_monitor_->getStateMonitor()->enableCopyDynamics(true);
  planning_scene_monitor_->startPublishingPlanningScene(planning_scene_monitor::PlanningSceneMonitor::UPDATE_SCENE,
                                                        std::string(node_->get_fully_qualified_name()) +
                                                            "/publish_planning_scene");
  // If the planning scene monitor in servo is the primary one we provide /get_planning_scene service so RViz displays
  // or secondary planning scene monitors can fetch the scene, otherwise we request the planning scene from the
  // primary planning scene monitor (e.g. move_group)
  if (servo_parameters->is_primary_planning_scene_monitor)
    planning_scene_monitor_->providePlanningSceneService();
  else
    planning_scene_monitor_->requestPlanningSceneState();
  std::cout << servo_parameters->ee_frame_name << std::endl;

  double update_freq_value = get_parameter_or("update_freq", 30.0);
  update_freq = std::make_shared<rclcpp::Rate>(update_freq_value);
  config_parameters[0] = get_parameter_or("position_err_tolerance_meters", 0.01);
  config_parameters[1] = get_parameter_or("velocity_err_tolerance_meters", 0.05);
  config_parameters[2] = get_parameter_or("angular_err_tolerance_radians", 0.0349);

  // Create threads
  std::thread([this]() {
    for (;;)
    {
      auto msg = std_msgs::msg::Int8();
      switch (mode)
      {
        case POSE:
          msg.data = 1;
          break;
        case TWIST:
          msg.data = 2;
          break;
        default:
          msg.data = 0;
      }
      control_status_publisher_->publish(msg);
      update_freq->sleep();
    }
  }).detach();

  // Create Servo
  servo_ = std::make_unique<moveit_servo::Servo>(node_, servo_parameters, planning_scene_monitor_);
  servo_->setPaused(true);
  RCLCPP_INFO(get_logger(), "Servo node has started.");
  pose_tracking_ = std::make_unique<moveit_servo::PoseTracking>(node_, servo_parameters, planning_scene_monitor_);
  pose_tracking_->stopMotion();
  pose_tracking_pause = true;
  RCLCPP_INFO(get_logger(), "Pose tracking node has started.");
}

void ArmRTServer::startServo(const std::shared_ptr<std_srvs::srv::Trigger::Request>& /* unused */,
                             const std::shared_ptr<std_srvs::srv::Trigger::Response>& response)
{
  std::unique_lock<std::mutex> lock(mode_lock);
  if (mode != IDLE)
  {
    RCLCPP_WARN(get_logger(), "RT Control has already started!");
    response->success = false;
    response->message = "RT Control has already started!";
    return;
  }

  pose_tracking_->stopMotion();
  servo_->setPaused(true);

  if (desired_mode_ == ControlMode::POSE)
  {
    mode = ControlMode::POSE;
    pose_tracking_->resetTargetPose();
    pose_tracking_pause = false;
    pose_tracking_stop = false;
    std::thread([this]() { moveToPoseUpdate(); }).detach();
  }
  else if (desired_mode_ == ControlMode::TWIST)
  {
    mode = ControlMode::TWIST;
    servo_->setPaused(false);
    servo_->start();
  }
  mode_lock.unlock();
  response->success = true;
}

void ArmRTServer::stopServo(const std::shared_ptr<std_srvs::srv::Trigger::Request>& /* unused */,
                            const std::shared_ptr<std_srvs::srv::Trigger::Response>& response)
{
  std::unique_lock<std::mutex> lock(mode_lock);
  mode = IDLE;

  servo_->setPaused(true);
  pose_tracking_stop = true;
  pose_tracking_->stopMotion();
  response->success = true;
}

void ArmRTServer::pauseServo(const std::shared_ptr<std_srvs::srv::Trigger::Request>& /* unused */,
                             const std::shared_ptr<std_srvs::srv::Trigger::Response>& response)
{
  std::unique_lock<std::mutex> lock(mode_lock);
  if (desired_mode_ == ControlMode::POSE)
  {
    servo_->setPaused(true);
  }
  else if (desired_mode_ == ControlMode::TWIST)
  {
    pose_tracking_pause = true;
  }

  mode = ControlMode::IDLE;
  response->success = true;
}

void ArmRTServer::unpauseServo(const std::shared_ptr<std_srvs::srv::Trigger::Request>& /* unused */,
                               const std::shared_ptr<std_srvs::srv::Trigger::Response>& response)
{
  std::unique_lock<std::mutex> lock(mode_lock);
  if (desired_mode_ == ControlMode::POSE)
  {
    servo_->setPaused(false);
  }
  else if (desired_mode_ == ControlMode::TWIST)
  {
    pose_tracking_pause = false;
  }
  else
  {
    RCLCPP_WARN(get_logger(), "Invalid desired mode!");
    response->success = false;
    return;
  }

  mode = desired_mode_;
  response->success = true;
}

void ArmRTServer::switchMode(const std::shared_ptr<std_srvs::srv::SetBool::Request>& request,
                             const std::shared_ptr<std_srvs::srv::SetBool::Response>& response)
{
  std::unique_lock<std::mutex> lock(mode_lock);
  if (request->data)
  {
    desired_mode_ = ControlMode::POSE;
  }
  else
  {
    desired_mode_ = ControlMode::TWIST;
  }
  response->success = true;
}

void ArmRTServer::moveToPoseUpdate()
{
  for (;;)
  {
    if (mode != POSE)
      break;

    if (pose_tracking_stop)
    {
      RCLCPP_INFO(get_logger(), "Stop flag see. Stopping...");
      pose_tracking_stop = false;
      break;
    }

    if (!pose_tracking_pause)
    {
      geometry_msgs::msg::TransformStamped current_ee_tf;
      pose_tracking_->getCommandFrameTransform(current_ee_tf);

      current_pose_target_.header.frame_id = current_ee_tf.header.frame_id;
      current_pose_target_.header.stamp = node_->get_clock()->now();

      pose_target_publisher_->publish(current_pose_target_);
      pose_tracking_->moveToPose(Eigen::Vector3d(config_parameters[0], config_parameters[0], config_parameters[0]),
                                 config_parameters[2], 1.0);
    }

    update_freq->sleep();
  }
}

}  // namespace urc_manipulation

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(urc_manipulation::ArmRTServer);
