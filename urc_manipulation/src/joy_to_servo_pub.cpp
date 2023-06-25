#include "joy_to_servo_pub.hpp"

namespace joy_to_servo_pub
{

JoyToServoPub::JoyToServoPub(const rclcpp::NodeOptions & options)
: Node("arm_driver", options)
{
  declare_parameter<std::string>("joy_topic", "/joy");
  get_parameter<std::string>("joy_topic", joy_topic);

  declare_parameter<std::string>("twist_topic", "/servo_node/delta_twist_cmds");
  get_parameter<std::string>("twist_topic", twist_topic);

  declare_parameter<std::string>("base_frame_id", "base_link");
  get_parameter<std::string>("base_frame_id", base_frame_id);

  // Setup pub/sub
  joy_sub_ = create_subscription<sensor_msgs::msg::Joy>(
    joy_topic, rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Joy::ConstSharedPtr & msg) {
      return joyCB(msg);
    });

  twist_pub_ = create_publisher<geometry_msgs::msg::TwistStamped>(
    twist_topic,
    rclcpp::SystemDefaultsQoS());
  collision_pub_ = create_publisher<moveit_msgs::msg::PlanningScene>(
    "/planning_scene",
    rclcpp::SystemDefaultsQoS());

  // Create a service client to start the ServoNode
  servo_start_client_ = create_client<std_srvs::srv::Trigger>("/servo_node/start_servo");
  servo_start_client_->wait_for_service(std::chrono::seconds(1));
  servo_start_client_->async_send_request(std::make_shared<std_srvs::srv::Trigger::Request>());

  // Load the collision scene asynchronously
  collision_pub_thread_ = std::thread(
    [this]() {
      rclcpp::sleep_for(std::chrono::seconds(3));
      // Create collision object, in the way of servoing
      moveit_msgs::msg::CollisionObject collision_object;
      collision_object.header.frame_id = base_frame_id;
      collision_object.id = "box";

      // Create a solid primitive to represent the rover body
      // Prevents the arm from colliding into the rover
      shape_msgs::msg::SolidPrimitive rover_body;
      rover_body.type = rover_body.BOX;
      //TODO These are made up numbers, fix them later
      rover_body.dimensions = {1.0, 0.5, 0.5};

      geometry_msgs::msg::Pose rover_body_pose;
      // Made up numbers, change later
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

void JoyToServoPub::convertJoyToCmd(
  const std::vector<float> & axes, const std::vector<int> & buttons,
  std::unique_ptr<geometry_msgs::msg::TwistStamped> & twist)
{
  // Right stick up controls along z axis
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

  // Left and right bumper controls the manipulator z rotation
  double roll_positive = buttons[RIGHT_BUMPER];
  double roll_negative = -1 * (buttons[LEFT_BUMPER]);
  twist->twist.angular.z = roll_positive + roll_negative; // Added together to account for negation
}

void JoyToServoPub::joyCB(const sensor_msgs::msg::Joy::ConstSharedPtr & msg)
{
  // Create the messages we might publish
  auto twist_msg = std::make_unique<geometry_msgs::msg::TwistStamped>();

  // Convert the joystick message to Twist and publish
  convertJoyToCmd(msg->axes, msg->buttons, twist_msg);

  // publish the TwistStamped
  twist_msg->header.frame_id = base_frame_id;
  twist_msg->header.stamp = now();
  twist_pub_->publish(std::move(twist_msg));

}

JoyToServoPub::~JoyToServoPub()
{
  if (collision_pub_thread_.joinable()) {
    collision_pub_thread_.join();
  }
}

}

RCLCPP_COMPONENTS_REGISTER_NODE(joy_to_servo_pub::JoyToServoPub)
