#include "motor_controller.hpp"

#define NODE_MAIN_LOGGER_NAME "urc_platform_MotorController"

namespace motor_controller
{
MotorController::MotorController(const rclcpp::NodeOptions & options)
: rclcpp::Node("motor_controller", options)
{
  _cmd_sub = create_subscription<urc_msgs::msg::VelocityPair>(
    "~/motors",
    rclcpp::SystemDefaultsQoS(),
    [this](const urc_msgs::msg::VelocityPair msg)
    {MotorController::cmdCallback(msg);});

  _enc_pub = create_publisher<urc_msgs::msg::VelocityPair>(
    "~/encoders",
    1000);

  _enabled_pub = create_publisher<std_msgs::msg::Bool>(
    "~/robot_enabled",
    rclcpp::SystemDefaultsQoS());

  _battery_pub = create_publisher<std_msgs::msg::Float64>(
    "~/battery",
    rclcpp::SystemDefaultsQoS());

  // // Create server socket
  ip_addr_ = declare_parameter<std::string>("ip_addr");
  tcpport_ = declare_parameter<int>("port");
  socket_ = std::make_unique<EthernetSocket>(ip_addr_, tcpport_);

  // // Battery variables
  // battery_alpha_ = declare_parameter<double>("battery_alpha");
  // min_battery_voltage_ = declare_parameter<double>("min_battery_voltage");
  // battery_avg_ = min_battery_voltage_;

  // // PID variables
  // p_l_ = declare_parameter<double>("p_l");
  // p_r_ = declare_parameter<double>("p_r");
  // d_l_ = declare_parameter<double>("d_l");
  // d_r_ = declare_parameter<double>("d_r");
  // i_r_ = declare_parameter<double>("i_r");
  // i_l_ = declare_parameter<double>("i_l");
  // kv_l_ = declare_parameter<double>("kv_l");
  // kv_r_ = declare_parameter<double>("kv_r");

  // watchdog_delay_ = declare_parameter<double>("watchdog_delay");
  // log_period_ = declare_parameter<double>("log_period");

  // mc_updater_->setHardwareID("Motor Controller");
  // mc_updater_->add("MC Diagnostic", this, &MotorController::mc_diagnostic);

  // battery_updater_->setHardwareID("Battery Controller");
  // battery_updater_->add("Battery Diagnostic", this, &MotorController::battery_diagnostic);

  frequency_ = declare_parameter<double>("frequency");
  rclcpp::Rate rate(frequency_);

  int i = 0;

  while (rclcpp::ok()) {

    // urc_msgs::msg::VelocityPair encoder_msg;

    // encoder_msg.left_velocity = i++;
    // encoder_msg.right_velocity = -1 * (i++);
    // encoder_msg.header.stamp = this->get_clock()->now();

    // _enc_pub->publish(encoder_msg);

    receiveResponse();
    
    rate.sleep();
  }
}

void MotorController::cmdCallback(const urc_msgs::msg::VelocityPair & msg)
{
  current_motor_command_ = msg;
  last_motors_message_ = rclcpp::Clock().now();
}

void MotorController::mc_diagnostic(diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Motor Controller Online");
  stat.add("Motor Controller Publishing Frequency ", std::to_string(mc_hertz) + " Hz");
}

void MotorController::battery_diagnostic(diagnostic_updater::DiagnosticStatusWrapper & stat)
{
  if (battery_avg_ < min_battery_voltage_) {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Battery voltage dangerously low");
  } else if (battery_avg_ < (min_battery_voltage_ + 0.25)) {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::WARN, "Battery voltage low");
  } else {
    stat.summary(diagnostic_msgs::msg::DiagnosticStatus::OK, "Battery voltage okay");
  }
  stat.add("battery voltage", battery_avg_);
}

void MotorController::setPID()
{
  rclcpp::Rate rate(frequency_);
  bool valid_values = true;   // pid values have been set correctly

  // Buffer where we will store the request message
  uint8_t requestbuffer[256];
  size_t message_length;
  bool status;

  // Request message for the server
  RequestMessage request = RequestMessage_init_zero;
  pb_ostream_t ostream = pb_ostream_from_buffer(requestbuffer, sizeof(requestbuffer));

  // Indicate which fields will be in the buffer
  request.has_p_l = true;
  request.has_p_r = true;
  request.has_i_l = true;
  request.has_i_r = true;
  request.has_d_l = true;
  request.has_d_r = true;
  request.has_kv_l = true;
  request.has_kv_r = true;

  // Encapsulate the data in the buffer
  request.p_l = static_cast<float>(p_l_);
  request.p_r = static_cast<float>(p_r_);
  request.i_l = static_cast<float>(i_l_);
  request.i_r = static_cast<float>(i_r_);
  request.d_l = static_cast<float>(d_l_);
  request.d_r = static_cast<float>(d_r_);
  request.kv_l = static_cast<float>(kv_l_);
  request.kv_r = static_cast<float>(kv_r_);

  // Encode the protobuf PDU
  status = pb_encode(&ostream, RequestMessage_fields, &request);
  message_length = ostream.bytes_written;

  if (!status) {
    RCLCPP_ERROR(this->get_logger(), "Encoding Failed: \n%s", PB_GET_ERROR(&ostream));
    return;
  }

  size_t bytes_read;     // Socket response: 0 means connection closed, otherwise n = num bytes read
  uint8_t buffer[256];   // buffer to read response into

  // Send PID values via ethernet and recieve response to ensure proper setting
  while (rclcpp::ok() && valid_values) {
    (socket_)->sendMessage(reinterpret_cast<char *>(requestbuffer), message_length);

    memset(buffer, 0, sizeof(buffer));
    bytes_read = (socket_)->readMessage(buffer);   // blocks until data is read

    if (bytes_read == 0) {
      RCLCPP_ERROR(this->get_logger(), "Connection closed by server!");
      mc_updater_->broadcast(
        diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Failed to send PID. Connection Closed by "
        "server.");
      battery_updater_->broadcast(
        diagnostic_msgs::msg::DiagnosticStatus::ERROR, "Failed to send PID. Lost battery "
        "tracking.");
      return;
    }

    // Decoding message
    ResponseMessage response_msg = ResponseMessage_init_zero;
    pb_istream_t istream = pb_istream_from_buffer(buffer, bytes_read);
    status = pb_decode(&istream, ResponseMessage_fields, &response_msg);

    /* check for any errors.. */
    if (!status) {
      RCLCPP_ERROR(this->get_logger(), "Decoding failure!");
      mc_updater_->broadcast(
        diagnostic_msgs::msg::DiagnosticStatus::ERROR,
        "PID decoding failed. Shutting Down.");
      battery_updater_->broadcast(
        diagnostic_msgs::msg::DiagnosticStatus::ERROR, "PID decoding failed. Lost battery "
        "tracking.");
      return;
    }

    valid_values = (response_msg.p_l == static_cast<float>(p_l_)) &&
      (response_msg.p_r == static_cast<float>(p_r_)) &&
      (response_msg.i_l == static_cast<float>(i_l_)) &&
      (response_msg.i_r == static_cast<float>(i_r_)) &&
      (response_msg.d_l == static_cast<float>(d_l_)) &&
      (response_msg.d_r == static_cast<float>(d_r_)) &&
      (response_msg.kv_l == static_cast<float>(kv_l_)) &&
      (response_msg.kv_r == static_cast<float>(kv_r_));

    rate.sleep();
  }
}

void MotorController::sendRequest()
{
  // Buffer where we will store the request message.
  uint8_t requestbuffer[256];
  // Request message to the server
  RequestMessage request = RequestMessage_init_zero;
  // Create a stream that will write to our buffer
  pb_ostream_t ostream = pb_ostream_from_buffer(requestbuffer, sizeof(requestbuffer));

  // Indicate which fields will be in the buffer
  request.has_speed_l = true;
  request.has_speed_r = true;

  // Encapsulate the data in the buffer
  request.speed_l = static_cast<float>(current_motor_command_.left_velocity);
  request.speed_r = static_cast<float>(current_motor_command_.right_velocity);

  // Encode the protobuf PDU
  bool status = pb_encode(&ostream, RequestMessage_fields, &request);
  size_t message_length = ostream.bytes_written;

  if (!status) {
    RCLCPP_ERROR(this->get_logger(), "Encoding Failed: \n%s", PB_GET_ERROR(&ostream));
    return;
  }

  (socket_)->sendMessage(reinterpret_cast<char *>(requestbuffer), message_length);
}

void MotorController::receiveResponse()
{
  size_t bytes_read;     // Socket response: 0 means connection closed, otherwise n = num bytes read
  uint8_t buffer[256];   // buffer to read response into

  memset(buffer, 0, sizeof(buffer));
  bytes_read = (socket_)->readMessage(buffer);

  if (bytes_read == 0) {
    RCLCPP_ERROR(this->get_logger(), "Connection Closed by Server!");
    return;
  }

  // Empty message where the decoded buffer will be stored
  // ResponseMessage response_msg = ResponseMessage_init_zero;
  DriveEncodersMessage response_msg = DriveEncodersMessage_init_zero;

  pb_istream_t istream = pb_istream_from_buffer(buffer, bytes_read);
  bool status = pb_decode(&istream, DriveEncodersMessage_fields, &response_msg);

  if (!status) {
    RCLCPP_ERROR(this->get_logger(), "Decoding Failed: \n%s", PB_GET_ERROR(&istream));
    return;
  }

  publishResponse(response_msg);
}

void MotorController::publishResponse(const DriveEncodersMessage & response)
{
  // /* update the exponentially weighted moving voltage average and publish */
  // std_msgs::msg::Float64 battery_msg;
  // battery_avg_ = (battery_alpha_ * battery_avg_) + ((1 - battery_alpha_) * response.voltage);
  // battery_msg.data = battery_avg_;
  // _battery_pub->publish(battery_msg);

  // if (battery_avg_ < min_battery_voltage_) {
  //   RCLCPP_ERROR(this->get_logger(), "Battery voltage dangerously low at %f!", battery_avg_);
  // }

  // std_msgs::msg::Bool enabled_msg;
  // enabled_msg.data = response.estop;
  // _enabled_pub->publish(enabled_msg);

  // publish encoder feedback
  urc_msgs::msg::VelocityPair encoder_msg;

  encoder_msg.left_velocity = response.frontLeftTicks;
  encoder_msg.right_velocity = response.frontRightTicks;
  encoder_msg.duration = response.timestamp;
  // encoder_msg.header.stamp = this->get_clock()->now() - rclcpp::Duration::from_seconds(response.timestamp);
  encoder_msg.header.stamp = this->get_clock()->now();

  _enc_pub->publish(encoder_msg);
}

bool MotorController::poll() {
  // If we haven't configured the server (MCU), just exit

  // Loop
  // (1) Wait for packets to be received with timeout
  //      Send in a pointer to a VelocityPair message
  // int rc = input_->getPacket(&scan->packets[i], config_.time_offset);
  // if (rc == 1) break;       // got a full packet?
  // if (rc < 0) return false; // end of file reached?
  // if (rc == 0) continue;    //timeout?

  // Publish the packet to the topic
  return true;
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(motor_controller::MotorController)

int main(int argc, char** argv)
{
  // // velodyne driver code:
  // ros::init(argc, argv, "velodyne_node");
  // ros::NodeHandle node;
  // ros::NodeHandle private_nh("~");

  // // start the driver
  // velodyne_driver::VelodyneDriver dvr(node, private_nh);

  // // loop until shut down or end of file
  // while(ros::ok())
  // {
  //   // poll device until end of file
  //   bool polled_ = dvr.poll();
  //   if (!polled_)
  //     ROS_ERROR_THROTTLE(1.0, "Velodyne - Failed to poll device.");

  //   ros::spinOnce();
  // }

  // return 0;

  auto args = rclcpp::init_and_remove_ros_arguments(argc, argv);
  rclcpp::Logger logger = rclcpp::get_logger(NODE_MAIN_LOGGER_NAME);
  rclcpp::executors::SingleThreadedExecutor exec;
  
  exec.spin();

  return 0;
}