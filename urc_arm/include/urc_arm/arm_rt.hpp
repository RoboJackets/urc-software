#ifndef URC_ARM_ARM_RT_HPP__
#define URC_ARM_ARM_RT_HPP__

#include "pinocchio/multibody/fwd.hpp"
#include <geometry_msgs/msg/detail/twist__struct.hpp>
#include <geometry_msgs/msg/pose.hpp>
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

  std::shared_ptr<Model> model_;
  std::shared_ptr<Data> data_;

  ServoStatus status_ = NORMAL;
  WalliArmState q_;
  WalliArmState qd_;
  WalliArmState qd_target_;
  pinocchio::Data::Matrix6x J;
  SE3 T_c_;
  SE3 T_f_;
  Vector6d V_target;

  std::unique_ptr<rclcpp::Logger> logger_;
  bool is_model_loaded_ = false;
  bool is_initialized_ = false;
  bool is_running_ = false;
  bool is_stationary_ = false;
  bool is_valid_ = false;

  // parameters
  std::string vel_command_topic_;
  std::vector<std::string> active_joints_;
  std::vector<std::string> locking_joints_;
  std::vector<double> joint_velocity_limits_ = { 2, 2, 2, 2, 2 };
  SingularityConfig singularity_config_{ 20.0, 100.0, 0.50, 0.01 };
  std::unordered_map<std::string, int> joint_mapping_;
};

}  // namespace urc_arm

#endif /* URC_ARM_ARM_RT_HPP__ */
