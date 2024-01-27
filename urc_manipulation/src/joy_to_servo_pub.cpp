#include "joy_to_servo_pub.hpp"
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>

namespace joy_to_servo_pub
{

JoyToServoPub::JoyToServoPub(const rclcpp::NodeOptions& options) : Node("arm_driver", options)
{
  declare_parameter<std::string>("joy_topic", "/joy");
  get_parameter<std::string>("joy_topic", joy_topic);

  declare_parameter<std::string>("twist_topic", "/servo_node/delta_twist_cmds");
  get_parameter<std::string>("twist_topic", twist_topic);

  declare_parameter<std::string>("joint_topic", "/servo_node/delta_joint_cmds");
  get_parameter<std::string>("joint_topic", joint_topic);

  declare_parameter<std::string>("base_frame_id", "arm_base_link");
  get_parameter<std::string>("base_frame_id", base_frame_id);

  declare_parameter<std::string>("eef_frame_id", "leftgripper");
  get_parameter<std::string>("eef_frame_id", eef_frame_id);

  // Setup pub/sub
  joy_sub_ = create_subscription<sensor_msgs::msg::Joy>(
      joy_topic, rclcpp::SystemDefaultsQoS(),
      [this](const sensor_msgs::msg::Joy::ConstSharedPtr& msg) { return joyCB(msg); });

  twist_pub_ = create_publisher<geometry_msgs::msg::TwistStamped>(twist_topic, rclcpp::SystemDefaultsQoS());
  joint_pub_ = this->create_publisher<control_msgs::msg::JointJog>(joint_topic, rclcpp::SystemDefaultsQoS());
  collision_pub_ = create_publisher<moveit_msgs::msg::PlanningScene>("/planning_scene", rclcpp::SystemDefaultsQoS());

  // Create a service client to start the ServoNode
  servo_start_client_ = create_client<std_srvs::srv::Trigger>("/servo_node/start_servo");
  servo_start_client_->wait_for_service(std::chrono::seconds(1));
  servo_start_client_->async_send_request(std::make_shared<std_srvs::srv::Trigger::Request>());

  // Load the collision scene asynchronously
  collision_pub_thread_ = std::thread([this]() {
    rclcpp::sleep_for(std::chrono::seconds(3));
    moveit_msgs::msg::PlanningSceneWorld psw;

    auto ps = std::make_unique<moveit_msgs::msg::PlanningScene>();
    ps->world = psw;
    ps->is_diff = true;
    collision_pub_->publish(std::move(ps));
  });
}

JoyToServoPub::~JoyToServoPub()
{
  if (collision_pub_thread_.joinable())
  {
    collision_pub_thread_.join();
  }
}

bool JoyToServoPub::convertJoyToCmd(const std::vector<float>& axes, const std::vector<int>& buttons,
                                    std::unique_ptr<geometry_msgs::msg::TwistStamped>& twist,
                                    std::unique_ptr<control_msgs::msg::JointJog>& joint)
{
  // Give joint jogging priority because it is only buttons
  // If any joint jog command is requested, we are only publishing joint commands
  if (buttons[A] || buttons[B] || buttons[X] || buttons[Y] || axes[D_PAD_X] || axes[D_PAD_Y])
  {
    // Map the D_PAD to the proximal joints
    joint->joint_names.push_back("shoulderjoint");
    joint->velocities.push_back(axes[D_PAD_X]);
    joint->joint_names.push_back("bicepjoint");
    joint->velocities.push_back(axes[D_PAD_Y]);

    // Map the diamond to the distal joints
    joint->joint_names.push_back("leftgripper");
    joint->velocities.push_back(buttons[B] - buttons[X]);
    joint->joint_names.push_back("clawjoint");
    joint->velocities.push_back(buttons[Y] - buttons[A]);
    return false;
  }

  // The bread and butter: map buttons to twist commands
  twist->twist.linear.z = axes[RIGHT_STICK_Y];
  twist->twist.linear.y = axes[RIGHT_STICK_X];

  double lin_x_right = -0.5 * (axes[RIGHT_TRIGGER] - AXIS_DEFAULTS.at(RIGHT_TRIGGER));
  double lin_x_left = 0.5 * (axes[LEFT_TRIGGER] - AXIS_DEFAULTS.at(LEFT_TRIGGER));
  twist->twist.linear.x = lin_x_right + lin_x_left;

  twist->twist.angular.y = axes[LEFT_STICK_Y];
  twist->twist.angular.x = axes[LEFT_STICK_X];

  double roll_positive = buttons[RIGHT_BUMPER];
  double roll_negative = -1 * (buttons[LEFT_BUMPER]);
  twist->twist.angular.z = roll_positive + roll_negative;

  return true;
}

/** \brief // This should update the frame_to_publish_ as needed for changing command frame via controller
 * @param frame_name Set the command frame to this
 * @param buttons The vector of discrete controller button values
 */
void JoyToServoPub::updateCmdFrame(std::string& frame_name, const std::vector<int>& buttons)
{
  if (buttons[CHANGE_VIEW] && frame_name == eef_frame_id)
  {
    frame_name = base_frame_id;
  }
  else if (buttons[MENU] && frame_name == base_frame_id)
  {
    frame_name = eef_frame_id;
  }
}

void JoyToServoPub::joyCB(const sensor_msgs::msg::Joy::ConstSharedPtr& msg)
{
  // Create the messages we might publish
  auto twist_msg = std::make_unique<geometry_msgs::msg::TwistStamped>();
  auto joint_msg = std::make_unique<control_msgs::msg::JointJog>();

  // This call updates the frame for twist commands
  updateCmdFrame(frame_to_publish_, msg->buttons);

  // Convert the joystick message to Twist or JointJog and publish
  if (convertJoyToCmd(msg->axes, msg->buttons, twist_msg, joint_msg))
  {
    // publish the TwistStamped
    twist_msg->header.frame_id = frame_to_publish_;
    twist_msg->header.stamp = this->now();
    twist_pub_->publish(std::move(twist_msg));
  }
  else
  {
    // publish the JointJog
    joint_msg->header.stamp = this->now();
    joint_msg->header.frame_id = "elbowjoint";
    joint_pub_->publish(std::move(joint_msg));
  }
}

}  // namespace joy_to_servo_pub

RCLCPP_COMPONENTS_REGISTER_NODE(joy_to_servo_pub::JoyToServoPub)
