#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <moveit_msgs/msg/planning_scene.hpp>
#include <rclcpp/client.hpp>
#include <rclcpp/experimental/buffers/intra_process_buffer.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/qos.hpp>
#include <rclcpp/qos_event.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/time.hpp>
#include <rclcpp/utilities.hpp>
#include <thread>
#include <rclcpp_components/register_node_macro.hpp>

namespace joy_to_servo_pub
{

// For XBOX 1 controller
enum Axis
{
  LEFT_STICK_X = 0,
  LEFT_STICK_Y = 1,
  LEFT_TRIGGER = 2,
  RIGHT_STICK_X = 3,
  RIGHT_STICK_Y = 4,
  RIGHT_TRIGGER = 5,
  D_PAD_X = 6,
  D_PAD_Y = 7
};

enum Button
{
  A = 0,
  B = 1,
  X = 2,
  Y = 3,
  LEFT_BUMPER = 4,
  RIGHT_BUMPER = 5,
  CHANGE_VIEW = 6,
  MENU = 7,
  HOME = 8,
  LEFT_STICK_CLICK = 9,
  RIGHT_STICK_CLICK = 10
};

class JoyToServoPub : public rclcpp::Node
{
public:
  /** \brief // This converts a joystick axes and buttons array to a TwistStamped message
   * @param axes The vector of continuous controller joystick axes
   * @param buttons The vector of discrete controller button values
   * @param twist A TwistStamped message to update in prep for publishing
   */
  void convertJoyToCmd(
    const std::vector<float> & axes, const std::vector<int> & buttons,
    std::unique_ptr<geometry_msgs::msg::TwistStamped> & twist);
  
  JoyToServoPub(const rclcpp::NodeOptions & options);
  ~JoyToServoPub() override;
  void joyCB(const sensor_msgs::msg::Joy::ConstSharedPtr & msg);

private:
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr twist_pub_;
  rclcpp::Publisher<moveit_msgs::msg::PlanningScene>::SharedPtr collision_pub_;
  rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr servo_start_client_;

  std::thread collision_pub_thread_;

  std::string joy_topic;
  std::string twist_topic;
  std::string base_frame_id;

  // Some axes have offsets (e.g. the default trigger position is 1.0 not 0)
  // This will map the default values for the axes
  std::map<Axis, double> AXIS_DEFAULTS = {{LEFT_TRIGGER, 1.0}, {RIGHT_TRIGGER, 1.0}};

};  // class JoyToServoPub

}
