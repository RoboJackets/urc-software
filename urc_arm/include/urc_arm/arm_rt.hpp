#ifndef URC_ARM_ARM_RT_HPP__
#define URC_ARM_ARM_RT_HPP__

#include "pinocchio/multibody/fwd.hpp"
#include <array>
#include <atomic>
#include <geometry_msgs/msg/detail/twist__struct.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <map>
#include <mutex>
#include <rclcpp/service.hpp>
#include <realtime_tools/realtime_publisher.h>
#include <sensor_msgs/msg/detail/joint_state__struct.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <memory>
#include <rclcpp/logger.hpp>
#include <rclcpp/node.hpp>
#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <rclcpp/subscription.hpp>
#include <std_msgs/msg/detail/float64_multi_array__struct.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <realtime_tools/realtime_buffer.h>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "Eigen/src/Core/Matrix.h"
#include "pinocchio/spatial/fwd.hpp"

namespace urc_arm
{
using namespace pinocchio;
using Vector6d = Eigen::Matrix<double, 6, 1>;
// full walli arm state, including the two gripper joints.
using WalliArmState = Eigen::Matrix<double, 5, 1>;
struct SingularityConfig
{
  double lower_threshold;
  double hardstop_threshold;
  double leaving_multiplier;
  double singularity_step_scale;
};
enum ServoStatus
{
  NORMAL,
  HALTING_IN_SINGULARITY,
  DECELERATING_FOR_APPROACHING_SINGULARITY,
  DECELERATING_FOR_LEAVING_SINGULARITY,
};

class ArmRT : public rclcpp::Node
{
public:
  ArmRT(const rclcpp::NodeOptions& options);
  ~ArmRT();

private:
  /**
   * @brief Load pinocchio model from XML (URDF).
   * Load pinocchio model from XML (URDF) from a topic, usually from /robot_description. The urdf can be a full model,
   * some of the joints can be locked via parameters during the initialization process.
   * @param description urdf file in string.
   */
  void load_model(const std::string& description);
  /**
   * @brief Calling all the method for initializing the arm rt controller.
   * Calling initializing function so that the whole thing can be ready. This may include updating pose targets,
   * resetting states, etc.
   */
  void initialize();
  /**
   * @brief Read from joint state buffer and update pinocchio data.
   * Read from joint state buffer, and send the data for forward kinematics using pinocchio. Should be called in a
   * real-time loop.
   */
  void update_kinematics();
  void update_command();
  void update_scaling_factor(WalliArmState& joint_commands_);
  void update_status(ServoStatus status);

  double calc_joint_limit_scaling_factor(WalliArmState& joint_commands_);
  std::pair<double, ServoStatus> calc_singularity_scaling_factor();

  // subscriber and publishers
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr robot_description_subscription_;
  rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr pose_subscription_;
  realtime_tools::RealtimeBuffer<geometry_msgs::msg::Pose> pose_buffer_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscription_;
  realtime_tools::RealtimeBuffer<sensor_msgs::msg::JointState> joint_state_buffer_;
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr twist_subscription_;
  realtime_tools::RealtimeBuffer<geometry_msgs::msg::Twist> twist_buffer_;
  realtime_tools::RealtimePublisherSharedPtr<std_msgs::msg::Float64MultiArray> vel_command_publisher_;

  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr start_servo_service_;
  rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr stop_servo_service_;

  std::shared_ptr<Model> model_;
  std::shared_ptr<Data> data_;

  ServoStatus status_ = NORMAL;
  int target_joint_id_ = 5;
  WalliArmState q_;
  WalliArmState qd_;
  WalliArmState qd_target_;
  pinocchio::Data::Matrix6x J;
  SE3 T_c_;
  SE3 T_f_;
  Vector6d V_target;

  std::unique_ptr<rclcpp::Logger> logger_;
  std::atomic_bool is_model_loaded_ = false;
  std::atomic_bool is_initialized_ = false;
  std::atomic_bool is_running_ = false;
  std::atomic_bool is_stationary_ = false;
  std::mutex pin_data_lock_;

  // parameters
  std::string vel_command_topic_;
  std::vector<std::string> active_joints_;
  std::vector<std::string> locking_joints_;
  std::vector<double> joint_velocity_limits_ = { 2, 2, 2, 2, 2 };
  SingularityConfig singularity_config_{ 35.0, 200.0, 1.0, 0.001 };
  std::unordered_map<std::string, int> joint_mapping_;
};

}  // namespace urc_arm

#endif /* URC_ARM_ARM_RT_HPP__ */
