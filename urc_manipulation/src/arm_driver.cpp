#include "arm_driver.hpp"

// To change controls or setup a new controller, all you should to do is change the above enums and the follow 2
// functions
/** \brief // This converts a joystick axes and buttons array to a TwistStamped or JointJog message
 * @param axes The vector of continuous controller joystick axes
 * @param buttons The vector of discrete controller button values
 * @param twist A TwistStamped message to update in prep for publishing
 * @param joint A JointJog message to update in prep for publishing
 * @return return true if you want to publish a Twist, false if you want to publish a JointJog
 */
bool convertJoyToCmd(const std::vector<float>& axes, const std::vector<int>& buttons,
                     std::unique_ptr<geometry_msgs::msg::TwistStamped>& twist,
                     std::unique_ptr<control_msgs::msg::JointJog>& joint)
{
  // Give joint jogging priority because it is only buttons
  // If any joint jog command is requested, we are only publishing joint commands
  if (buttons[A] || buttons[B] || buttons[X] || buttons[Y] || axes[D_PAD_X] || axes[D_PAD_Y])
  {
    // Map the D_PAD to the proximal joints
    joint->joint_names.push_back("panda_joint1");
    joint->velocities.push_back(axes[D_PAD_X]);
    joint->joint_names.push_back("panda_joint2");
    joint->velocities.push_back(axes[D_PAD_Y]);

    // Map the diamond to the distal joints
    joint->joint_names.push_back("panda_joint7");
    joint->velocities.push_back(buttons[B] - buttons[X]);
    joint->joint_names.push_back("panda_joint6");
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
void updateCmdFrame(std::string& frame_name, const std::vector<int>& buttons)
{
  if (buttons[CHANGE_VIEW] && frame_name == EEF_FRAME_ID)
  {
    frame_name = BASE_FRAME_ID;
  }
  else if (buttons[MENU] && frame_name == BASE_FRAME_ID)
  {
    frame_name = EEF_FRAME_ID;
  }
}

namespace moveit_servo
{
class JoyToServoPub : public rclcpp::Node
{
public:
  JoyToServoPub(const rclcpp::NodeOptions& options)
    : Node("joy_to_twist_publisher", options), frame_to_publish_(BASE_FRAME_ID)
  {
    // Setup pub/sub
    joy_sub_ = create_subscription<sensor_msgs::msg::Joy>(JOY_TOPIC, rclcpp::SystemDefaultsQoS(),
                                                          [this](const sensor_msgs::msg::Joy::ConstSharedPtr& msg) {
                                                            return joyCB(msg);
                                                          });

    twist_pub_ = create_publisher<geometry_msgs::msg::TwistStamped>(TWIST_TOPIC, rclcpp::SystemDefaultsQoS());
    joint_pub_ = create_publisher<control_msgs::msg::JointJog>(JOINT_TOPIC, rclcpp::SystemDefaultsQoS());
    collision_pub_ = create_publisher<moveit_msgs::msg::PlanningScene>("/planning_scene", rclcpp::SystemDefaultsQoS());

    // Create a service client to start the ServoNode
    servo_start_client_ = create_client<std_srvs::srv::Trigger>("/servo_node/start_servo");
    servo_start_client_->wait_for_service(std::chrono::seconds(1));
    servo_start_client_->async_send_request(std::make_shared<std_srvs::srv::Trigger::Request>());

    // Load the collision scene asynchronously
    collision_pub_thread_ = std::thread([this]() {
      rclcpp::sleep_for(std::chrono::seconds(3));
      // Create collision object, in the way of servoing
      moveit_msgs::msg::CollisionObject collision_object;
      collision_object.header.frame_id = "panda_link0";
      collision_object.id = "box";

      shape_msgs::msg::SolidPrimitive table_1;
      table_1.type = table_1.BOX;
      table_1.dimensions = { 0.4, 0.6, 0.03 };

      geometry_msgs::msg::Pose table_1_pose;
      table_1_pose.position.x = 0.6;
      table_1_pose.position.y = 0.0;
      table_1_pose.position.z = 0.4;

      shape_msgs::msg::SolidPrimitive table_2;
      table_2.type = table_2.BOX;
      table_2.dimensions = { 0.6, 0.4, 0.03 };

      geometry_msgs::msg::Pose table_2_pose;
      table_2_pose.position.x = 0.0;
      table_2_pose.position.y = 0.5;
      table_2_pose.position.z = 0.25;

      collision_object.primitives.push_back(table_1);
      collision_object.primitive_poses.push_back(table_1_pose);
      collision_object.primitives.push_back(table_2);
      collision_object.primitive_poses.push_back(table_2_pose);
      collision_object.operation = collision_object.ADD;

      moveit_msgs::msg::PlanningSceneWorld psw;
      psw.collision_objects.push_back(collision_object);

      auto ps = std::make_unique<moveit_msgs::msg::PlanningScene>();
      ps->world = psw;
      ps->is_diff = true;
      collision_pub_->publish(std::move(ps));
    });
  }

  ~JoyToServoPub() override
  {
    if (collision_pub_thread_.joinable())
      collision_pub_thread_.join();
  }

  void joyCB(const sensor_msgs::msg::Joy::ConstSharedPtr& msg)
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
      twist_msg->header.stamp = now();
      twist_pub_->publish(std::move(twist_msg));
    }
    else
    {
      // publish the JointJog
      joint_msg->header.stamp = now();
      joint_msg->header.frame_id = "panda_link3";
      joint_pub_->publish(std::move(joint_msg));
    }
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr twist_pub_;
  rclcpp::Publisher<control_msgs::msg::JointJog>::SharedPtr joint_pub_;
  rclcpp::Publisher<moveit_msgs::msg::PlanningScene>::SharedPtr collision_pub_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr servo_start_client_;

  std::string frame_to_publish_;

  std::thread collision_pub_thread_;
};  // class JoyToServoPub

}

RCLCPP_COMPONENTS_REGISTER_NODE(moveit_servo::JoyToServoPub)