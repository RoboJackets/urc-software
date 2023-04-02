#include "arm_driver.hpp"

namespace arm_driver
{

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

  // Right stick up controls along 
  twist->twist.linear.z = axes[RIGHT_STICK_Y];
  // Right stick right controls along y axis
  twist->twist.linear.y = axes[RIGHT_STICK_X];

  // Right trigger moves arm out, left trigger moves arm in
  double lin_x_right = -0.5 * (axes[RIGHT_TRIGGER] - AXIS_DEFAULTS.at(RIGHT_TRIGGER));
  double lin_x_left = 0.5 * (axes[LEFT_TRIGGER] - AXIS_DEFAULTS.at(LEFT_TRIGGER));
  twist->twist.linear.x = lin_x_right + lin_x_left; // Added together to account for negation

  // Left stick controls the manipulator x and y rotation
  twist->twist.angular.y = axes[LEFT_STICK_Y];
  twist->twist.angular.x = axes[LEFT_STICK_X];

  // Left and right bumbper controls the manipulator z rotation
  double roll_positive = buttons[RIGHT_BUMPER];
  double roll_negative = -1 * (buttons[LEFT_BUMPER]);
  twist->twist.angular.z = roll_positive + roll_negative; // Added together to account for negation

  return true;
}


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


  JoyToServoPub::JoyToServoPub(const rclcpp::NodeOptions& options)
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

      shape_msgs::msg::SolidPrimitive rover_body;
      rover_body.type = rover_body.BOX;
      // These are made up numbers, fix them later
      rover_body.dimensions = { 1.0, 0.5, 0.5 };

      geometry_msgs::msg::Pose rover_body_pose;
      // These are made up numbers, fix them later
      rover_body_pose.position.x = 0.5;
      rover_body_pose.position.y = 0.8;
      rover_body_pose.position.z = 0.1;

      collision_object.primitives.push_back(rover_body);
      collision_object.primitive_poses.push_back(rover_body_pose);
      collision_object.operation = collision_object.ADD;

      moveit_msgs::msg::PlanningSceneWorld psw;
      psw.collision_objects.push_back(collision_object);

      auto ps = std::make_unique<moveit_msgs::msg::PlanningScene>();
      ps->world = psw;
      ps->is_diff = true;
      collision_pub_->publish(std::move(ps));
    });
  }

  JoyToServoPub::~JoyToServoPub() override
  {
    if (collision_pub_thread_.joinable())
      collision_pub_thread_.join();
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
}

RCLCPP_COMPONENTS_REGISTER_NODE(moveit_servo::JoyToServoPub)