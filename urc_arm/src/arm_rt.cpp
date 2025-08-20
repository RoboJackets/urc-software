#include "urc_arm/arm_rt.hpp"
#include "Eigen/src/Core/Matrix.h"
#include "Eigen/src/Core/util/Constants.h"
#include "pinocchio/algorithm/kinematics.hpp"
#include "pinocchio/math/rotation.hpp"
#include "pinocchio/multibody/fwd.hpp"
#include "pinocchio/multibody/joint/joint-basic-visitors.hpp"
#include "pinocchio/parsers/urdf.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
#include "pinocchio/algorithm/model.hpp"
#include "pinocchio/spatial/explog.hpp"
#include "pinocchio/spatial/fwd.hpp"
#include "pinocchio/algorithm/jacobian.hpp"
#include "pinocchio/algorithm/joint-configuration.hpp"
#include "std_msgs/msg/string.hpp"
#include "pinocchio/parsers/urdf.hpp"
#include <Eigen/src/SVD/JacobiSVD.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <geometry_msgs/msg/twist.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <iterator>
#include <memory>
#include <mutex>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/node_options.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/time.hpp>
#include <realtime_tools/realtime_publisher.h>
#include <sensor_msgs/msg/detail/joint_state__struct.hpp>
#include <std_msgs/msg/detail/float64_multi_array__struct.hpp>
#include <std_msgs/msg/detail/string__struct.hpp>
#include <realtime_tools/thread_priority.hpp>
#include <std_srvs/srv/detail/trigger__struct.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <string>
#include <thread>
#include <utility>

namespace urc_arm
{
using namespace pinocchio;

ArmRT::ArmRT(const rclcpp::NodeOptions & options)
: rclcpp::Node("arm_rt_pinocchio", options), is_model_loaded_(false)
{
  logger_ = std::make_unique<rclcpp::Logger>(get_logger());
  logger_->set_level(rclcpp::Logger::Level::Debug);
  RCLCPP_INFO(*logger_, "Waiting for /robot_description topic...");
  robot_description_subscription_ = create_subscription<std_msgs::msg::String>(
    "/robot_description", rclcpp::QoS(1).transient_local(),
    [this](const std_msgs::msg::String & description) {load_model(description.data);});

  // TODO: change to parameters for more flexibiltiy
  vel_command_topic_ = "/arm_controller/commands";
  active_joints_ = {"shoulderjoint", "bicepjoint", "elbowjoint", "wristjoint", "clawjoint"};
  locking_joints_ = {"left_rear_wheel_joint", "left_center_wheel_joint", "left_front_wheel_joint",
    "right_rear_wheel_joint", "right_center_wheel_joint", "right_front_wheel_joint",
    "leftgripperjoint", "rightgripperjoint"};
  joint_mapping_ = {
    {"shoulderjoint", 0}, {"bicepjoint", 1}, {"elbowjoint", 2}, {"wristjoint", 3}, {"clawjoint", 4},
  };

  std::thread(
    [this]() {
      rclcpp::Time start = this->get_clock()->now();
      while ((this->get_clock()->now() - start).seconds() < 10 && !is_model_loaded_) {
      }
      if (is_model_loaded_) {
        robot_description_subscription_.reset();
        initialize();
      } else {
        RCLCPP_ERROR(*logger_, "Fail to load robot model after 10 seconds. Shutting down.");
        robot_description_subscription_.reset();
        throw std::exception();
      }
    }).detach();
}

ArmRT::~ArmRT()
{
  is_running_ = false;
}


void ArmRT::initialize()
{
  if (!realtime_tools::has_realtime_kernel()) {
    RCLCPP_WARN(*logger_, "Realtime Kernel is recommended for more consistent control.");
  }

  pose_buffer_.initRT(geometry_msgs::msg::Pose());
  pose_subscription_ = create_subscription<geometry_msgs::msg::Pose>(
    "/cmd_pose", rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::Pose & pose) {pose_buffer_.writeFromNonRT(pose);});
  twist_buffer_.initRT(geometry_msgs::msg::Twist());
  twist_subscription_ = create_subscription<geometry_msgs::msg::Twist>(
    "/cmd_twist", rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::Twist & twist) {twist_buffer_.writeFromNonRT(twist);});
  joint_state_buffer_.initRT(sensor_msgs::msg::JointState());
  joint_state_subscription_ = create_subscription<sensor_msgs::msg::JointState>(
    "/joint_states", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::JointState & joint_state) {
      joint_state_buffer_.writeFromNonRT(joint_state);
    });

  vel_command_publisher_ =
    std::make_shared<realtime_tools::RealtimePublisher<std_msgs::msg::Float64MultiArray>>(
    create_publisher<std_msgs::msg::Float64MultiArray>(
      vel_command_topic_,
      rclcpp::SystemDefaultsQoS()));
  vel_command_publisher_->msg_ = std_msgs::msg::Float64MultiArray();
  vel_command_publisher_->msg_.data = {0.0, 0.0, 0.0, 0.0, 0.0};

  start_servo_service_ = create_service<std_srvs::srv::Trigger>(
    "~/start_servo",
    [this](const std_srvs::srv::Trigger::Request::SharedPtr,
    std_srvs::srv::Trigger::Response::SharedPtr response) {
      // one time initialization: set the current control target to the pose
      if (!is_initialized_) {
        pinocchio::forwardKinematics(*model_, *data_, q_);
        T_f_ = T_c_;
        T_c_ = data_->oMi[target_joint_id_];
        RCLCPP_DEBUG(*logger_, "Servo Inited!");
        is_initialized_ = true;
      }
      response->success = true;
    });

  stop_servo_service_ = create_service<std_srvs::srv::Trigger>(
    "~/stop_servo",
    [this](const std_srvs::srv::Trigger::Request::SharedPtr,
    std_srvs::srv::Trigger::Response::SharedPtr response) {
      if (is_initialized_) {
        is_initialized_ = false;
        RCLCPP_DEBUG(*logger_, "Servo Stopped!");
      }
      response->success = true;
    });

  // starting main thread
  is_running_ = true;
  is_initialized_ = false;
  std::thread(
    [this]() {
      realtime_tools::configure_sched_fifo(92);
      while (is_running_) {
        if (is_model_loaded_) {
          update_kinematics();
        }
        if (is_model_loaded_ && is_initialized_) {
          update_command();
        }
      }
    }).detach();
}

void ArmRT::load_model(const std::string & decsription)
{
  RCLCPP_DEBUG(*logger_, "Description discovered!");

  Model full_model;
  pinocchio::urdf::buildModelFromXML(decsription, full_model);
  auto q_neutral = pinocchio::neutral(full_model);
  std::vector<JointIndex> joint_to_lock_by_id;
  for (std::vector<std::string>::const_iterator it = locking_joints_.begin();
    it != locking_joints_.end(); ++it)
  {
    const std::string & joint_name = *it;
    if (full_model.existJointName(joint_name)) {
      joint_to_lock_by_id.push_back(full_model.getJointId(joint_name));
    } else {
      RCLCPP_ERROR(
        *logger_, "Joint %s does not belong to the model. Skipping locking.",
        joint_name.c_str());
    }
  }

  model_ =
    std::make_shared<Model>(
    pinocchio::buildReducedModel(
      full_model, joint_to_lock_by_id,
      q_neutral));
  Data data(*model_);
  data_ = std::make_shared<Data>(data);

  RCLCPP_DEBUG(*logger_, "Robot %s is loaded!", model_->name.c_str());
  RCLCPP_INFO_STREAM(
    *logger_,
    "Model status: models has nq = " << model_->nq << "; nv = " << model_->nv);
  for (JointIndex joint_id = 1; joint_id < model_->joints.size(); ++joint_id) {
    RCLCPP_INFO_STREAM(*logger_, "\t- " << model_->names[joint_id]);
  }

  J = pinocchio::Data::Matrix6x(6, model_->nv);
  J.setZero();
  is_model_loaded_ = true;
}

void ArmRT::update_kinematics()
{
  std::unique_lock lock(pin_data_lock_);
  const auto * joint_state = joint_state_buffer_.readFromRT();
  bool valid = true;

  for (unsigned long i = 0; i < joint_state->name.size(); ++i) {
    if (joint_mapping_.find(joint_state->name[i]) == joint_mapping_.end()) {
      continue;
    }
    q_(joint_mapping_[joint_state->name[i]], 0) = joint_state->position[i];
    qd_(joint_mapping_[joint_state->name[i]], 0) = joint_state->velocity[i];
    valid = valid && joint_state->position[i] != 0;
  }
  pinocchio::forwardKinematics(*model_, *data_, q_);
  T_c_ = data_->oMi[target_joint_id_];
}

int search_joint_pos(std::vector<std::string> & joint_list, std::string joint_name)
{
  return std::distance(
    joint_list.begin(),
    std::find(joint_list.begin(), joint_list.end(), joint_name));
}

Eigen::Matrix3d rpy_to_rot_mat(double roll, double pitch, double yaw)
{
  // Create rotation matrices for roll, pitch, and yaw
  Eigen::Matrix3d rollMatrix;
  rollMatrix << 1, 0, 0, 0, cos(roll), -sin(roll), 0, sin(roll), cos(roll);

  Eigen::Matrix3d pitchMatrix;
  pitchMatrix << cos(pitch), 0, sin(pitch), 0, 1, 0, -sin(pitch), 0, cos(pitch);

  Eigen::Matrix3d yawMatrix;
  yawMatrix << cos(yaw), -sin(yaw), 0, sin(yaw), cos(yaw), 0, 0, 0, 1;

  // Combine the rotation matrices
  Eigen::Matrix3d rotationMatrix = yawMatrix * pitchMatrix * rollMatrix;

  return rotationMatrix;
}

void ArmRT::update_command()
{
  std::unique_lock lock(pin_data_lock_);
  geometry_msgs::msg::Twist * vel_target = twist_buffer_.readFromRT();

  pinocchio::SE3 delta;
  delta.translation()(0, 0) = vel_target->linear.x;
  delta.translation()(1, 0) = vel_target->linear.y;
  delta.translation()(2, 0) = vel_target->linear.z;
  delta.rotation() = rpy_to_rot_mat(
    vel_target->angular.x, vel_target->angular.y,
    vel_target->angular.z);

  pinocchio::SE3 iMd;
  V_target = pinocchio::log6(delta).toVector();
  bool stationary = V_target.norm() < 1e-2;

  if (stationary) {
    if (!is_stationary_) {
      is_stationary_ = true;
      T_f_ = T_c_;
    }
    V_target = pinocchio::log6(T_c_.actInv(T_f_));
  } else {
    is_stationary_ = false;
  }

  pinocchio::computeJointJacobian(*model_, *data_, q_, target_joint_id_, J);
  pinocchio::Data::Matrix6 Jlog;
  pinocchio::Jlog6(iMd.inverse(), Jlog);
  J = -Jlog * J;
  pinocchio::Data::Matrix6 JJt;
  JJt.noalias() = J * J.transpose();
  JJt.diagonal().array() += 1e-7;

  qd_target_.noalias() = -J.transpose() * JJt.ldlt().solve(V_target);
  qd_target_ *= calc_joint_limit_scaling_factor(qd_target_);

  auto sing_result = calc_singularity_scaling_factor();
  qd_target_ *= sing_result.first;
  update_status(sing_result.second);

  if (vel_command_publisher_->trylock()) {
    for (unsigned long i = 0; i < 5; ++i) {
      if (qd_target_(i, 0) != qd_target_(i, 0)) {
        RCLCPP_WARN(*logger_, "NaN Commands!");
        return;
      }
      vel_command_publisher_->msg_.data[i] = qd_target_(i, 0);
    }

    vel_command_publisher_->unlockAndPublish();
  }
}

double ArmRT::calc_joint_limit_scaling_factor(WalliArmState & joint_commands_)
{
  double min_factor = 1;
  for (unsigned int i = 0; i < joint_velocity_limits_.size(); ++i) {
    double bounded_vel = std::clamp(
      joint_commands_(
        i,
        0), joint_velocity_limits_[i],
      -joint_velocity_limits_[i]);
    min_factor = std::min(std::abs(bounded_vel / joint_commands_(i, 0)), min_factor);
  }
  return min_factor;
}

std::pair<double, ServoStatus> ArmRT::calc_singularity_scaling_factor()
{
  const size_t dims = 5;
  WalliArmState q_curr = q_;
  pinocchio::Data::Matrix6 J_curr;
  pinocchio::Data::Matrix6 J_next;
  Eigen::JacobiSVD<Eigen::MatrixXd> SVD_curr;
  Eigen::JacobiSVD<Eigen::MatrixXd> SVD_next;
  ServoStatus status;

  // calculate current svd and condition numbers
  pinocchio::computeJointJacobian(*model_, *data_, q_curr, target_joint_id_, J_curr);

  SVD_curr.compute(J_curr, Eigen::ComputeThinU | Eigen::ComputeThinV);

  const double c_curr =
    std::abs(SVD_curr.singularValues()(0) / SVD_curr.singularValues()(dims - 1));
  Eigen::VectorXd v_sing = SVD_curr.matrixU().col(dims - 1);
  pinocchio::Data::Matrix6 JJt;
  JJt.noalias() = J * J.transpose();
  JJt.diagonal().array() += 1e-4;

  const Eigen::Matrix<double, 6, 1> delta_x = v_sing * singularity_config_.singularity_step_scale;
  WalliArmState q_next = q_curr - J.transpose() * JJt.ldlt().solve(delta_x);
  pinocchio::computeJointJacobian(*model_, *data_, q_next, target_joint_id_, J_next);
  SVD_next.compute(J_next, Eigen::ComputeThinU | Eigen::ComputeThinV);
  const double c_next =
    std::abs(SVD_next.singularValues()(0) / SVD_next.singularValues()(dims - 1));

  // if current number is decresing, the direction of vector should be flipped
  const bool moving_towards_singularity = c_next <= c_curr;
  if (c_next <= c_curr) {
    v_sing *= -1;
  }

  double velocity_scale = 1.0;
  const bool is_above_lower_limit = c_curr > singularity_config_.lower_threshold;
  const bool is_below_hard_stop_limit = c_curr < singularity_config_.hardstop_threshold;

  if (is_above_lower_limit && is_below_hard_stop_limit) {
    velocity_scale -= (c_curr - singularity_config_.lower_threshold) /
      (singularity_config_.hardstop_threshold - singularity_config_.lower_threshold);
    velocity_scale *= 0.8;

    if (!moving_towards_singularity) {
      velocity_scale *= singularity_config_.leaving_multiplier;
    }
    velocity_scale *= singularity_config_.leaving_multiplier;

    status = moving_towards_singularity ? ServoStatus::DECELERATING_FOR_APPROACHING_SINGULARITY :
      ServoStatus::DECELERATING_FOR_LEAVING_SINGULARITY;
  }
  // If condition number has crossed hard stop limit, halt the robot.
  else if (!is_below_hard_stop_limit) {
    status = ServoStatus::HALTING_IN_SINGULARITY;
    velocity_scale = 0.01;
  } else {
    status = ServoStatus::NORMAL;
  }

  return {velocity_scale, status};
}

void ArmRT::update_status(ServoStatus status)
{
  if (status_ != status) {
    RCLCPP_INFO(*logger_, "Transitioning from status %d to %d.", status_, status);
    status_ = status;

    switch (status) {
      case HALTING_IN_SINGULARITY:
        RCLCPP_WARN(
          *logger_,
          "Arm is in singularity! Locked the arm's movement for safety considerations.");
        break;
      case NORMAL:
        RCLCPP_INFO(*logger_, "Back to dexterous workspace!");
        break;
      case DECELERATING_FOR_APPROACHING_SINGULARITY:
      case DECELERATING_FOR_LEAVING_SINGULARITY:
        RCLCPP_WARN(*logger_, "Entering deceleration for approaching / leaving singularity.");
        break;
    }
  }
}

}  // namespace urc_arm

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_arm::ArmRT);
