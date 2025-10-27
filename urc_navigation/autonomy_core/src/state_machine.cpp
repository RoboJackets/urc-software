// Core ROS2 Client
#include "rclcpp/rclcpp.hpp"

#include "urc_msgs/msg/navigation_status.hpp" // announce different states

#include "urc_msgs/msg/status_light_command.hpp" // Custom LED

#include "autonomy_core/state_machine.hpp" // helper methods, state declarations 

using namespace state_machine;

// This is the state machine node for autonomy
class StateMachineNode : public rclcpp::Node {

public:
  StateMachineNode() : Node("asm_demo_node"), current_state_(CurrentState::INITIALIZE) {
    
    // fsm/status publisher topic 
    status_pub_ = this->create_publisher<urc_msgs::msg::NavigationStatus>("asm/status", 10);

    // LED signal changes for different missions
    led_pub_ = this->create_publisher<urc_msgs::msg::StatusLightCommand>("asm/led_signal", 10);

    // command subscriber expects certain commands like "success" "failure" "reset"
    cmd_sub_ = this->create_subscription<urc_msgs::msg::NavigationStatus>(
      "asm/cmd", 10,
      std::bind(&StateMachineNode::cmd_callback, this, std::placeholders::_1)
    );
    
    // Logs beginner state information
    RCLCPP_INFO(this->get_logger(), "ASM Demo Node started on %s state",
                to_string(current_state_).c_str());
  }

private:
  void cmd_callback(const urc_msgs::msg::NavigationStatus::SharedPtr msg) {

    auto cmd = msg->status; // Receives the Message

    // Logs the Received Message

    RCLCPP_INFO(this->get_logger(), "Received command: %s", cmd.c_str());
    
    // If we receive a success message it can proceed
    if (cmd == "success") {
      handle_success();

    // if we receive a failure message we have to handle that failure 
    // Check which state we can go to based on that failure
    } else if (cmd == "failure") {

      handle_failure();

      // if the command is reset message we go back to the initial state INITIALIZE
    } else if (cmd == "reset") {

      current_state_ = CurrentState::INITIALIZE;
      
      // still need to fix the LED color display to match the 
      publish_led("yellow", "blink"); //  Just for testing purposes I set the blinking yellow to reset

      RCLCPP_INFO(this->get_logger(), "ASM reset to INITIALIZE");

    } else {
      // whenever we get an unknown command
      RCLCPP_WARN(this->get_logger(), "Unknown command: %s", cmd.c_str());
    }
    publish_state();
  }

  // This Method handles the success for different messages
  void handle_success() {

    switch (current_state_) {

      case CurrentState::INITIALIZE:
        // Initial Default State 
        transition_to(CurrentState::ASSIGN_GOAL, "red", "on");
      case CurrentState::ASSIGN_GOAL:
        transition_to(CurrentState::PATH_PLANNING, "red", "on"); // red for autonomous navigation 
        break;
      case CurrentState::PATH_PLANNING:
        transition_to(CurrentState::TRAJECTORY_PLANNING, "red", "on");
        break;
      case CurrentState::TRAJECTORY_PLANNING:
        transition_to(CurrentState::DISTANCE_TIME_CHECK, "red", "blink");
        break;
      case CurrentState::DISTANCE_TIME_CHECK:
        transition_to(CurrentState::CONFIRM_ARRIVAL, "red", "on");
        break;
      case CurrentState::CONFIRM_ARRIVAL:
        transition_to(CurrentState::SIGNAL_LED, "white", "blink");
        break;
      case CurrentState::SIGNAL_LED:
        transition_to(CurrentState::MISSION_COMPLETE, "green", "on");
        break;
      case CurrentState::MISSION_COMPLETE:
        RCLCPP_INFO(this->get_logger(), "Mission fully complete!");
        break;
      case CurrentState::SEARCH_BEHAVIOR:
        transition_to(CurrentState::CONFIRM_ARRIVAL, "white", "blink");
        break;
      default:
        break;
    }
  }

  void handle_failure() {
    switch (current_state_) {
      case CurrentState::PATH_PLANNING:
        transition_to(CurrentState::SEARCH_BEHAVIOR, "red", "blink");
        break;
      case CurrentState::TRAJECTORY_PLANNING:
      case CurrentState::DISTANCE_TIME_CHECK:
      case CurrentState::SEARCH_BEHAVIOR:
        transition_to(CurrentState::OPERATOR_INTERACTION, "red", "on");
        break;
      default:
        RCLCPP_WARN(this->get_logger(), "Failure in unexpected state: %s",
                    to_string(current_state_).c_str());
        break;
    }
  }
  
  // Transition to different State
  void transition_to(CurrentState new_state, const std::string &color, const std::string &mode) {
    current_state_ = new_state;

    publish_led(color, mode);

    RCLCPP_INFO(this->get_logger(), "Transitioned to: %s (%s)",
                to_string(current_state_).c_str(),
                describe(current_state_).c_str());
  }
 
  // Publish The State
  void publish_state() {

    urc_msgs::msg::NavigationStatus msg;

    msg.status = to_string(current_state_);

    status_pub_->publish(msg);
  }
  
  // Publish The LED
  void publish_led(const std::string &color, const std::string &mode) {

    urc_msgs::msg::StatusLightCommand led_msg;

    led_msg.color = color;

    led_msg.mode = mode;

    led_pub_->publish(led_msg);

  }
  
  
  CurrentState current_state_;

  rclcpp::Publisher<urc_msgs::msg::NavigationStatus>::SharedPtr status_pub_;

  rclcpp::Publisher<urc_msgs::msg::StatusLightCommand>::SharedPtr led_pub_;

  rclcpp::Subscription<urc_msgs::msg::NavigationStatus>::SharedPtr cmd_sub_;

};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<StateMachineNode>());
  rclcpp::shutdown();
  return 0;
}

