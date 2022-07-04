#include "motor_controller.hpp"

namespace motor_controller
{
  MotorController::MotorController(const rclcpp::NodeOptions &options)
      : rclcpp::Node("motor_controller", options)
  {
    _cmd_sub = create_subscription<urc_msgs::msg::VelocityPair>(
        "~/motors",
        rclcpp::SystemDefaultsQoS(),
        [this](const urc_msgs::msg::VelocityPair msg)
        { MotorController::cmdCallback(msg); });

    _enc_pub = create_publisher<urc_msgs::msg::VelocityPair>(
        "~/encoders",
        1000);

    _enabled_pub = create_publisher<std_msgs::msg::Bool>(
        "~/robot_enabled",
        rclcpp::SystemDefaultsQoS());

    _battery_pub = create_publisher<std_msgs::msg::Float64>(
        "~/battery",
        rclcpp::SystemDefaultsQoS());

    // Create server socket
    get_parameter("ip_addr", ip_addr_);
    get_parameter("port", tcpport_);
    socket_ = EthernetSocket(ip_addr_, tcpport_);

    // Battery variables
    get_parameter("battery_alpha", battery_alpha_);
    get_parameter("min_battery_voltage", min_battery_voltage_);
    battery_avg_ = min_battery_voltage_;

    // PID variables
    get_parameter("p_l", p_l_);
    get_parameter("p_r", p_r_);
    get_parameter("d_l", d_l_);
    get_parameter("d_r", d_r_);
    get_parameter("i_r", i_r_);
    get_parameter("i_l", i_l_);
    get_parameter("kv_l", kv_l_);
    get_parameter("kv_r", kv_r_);

    get_parameter("watchdog_delay", watchdog_delay_);
    get_parameter_or("log_period", log_period_, 5.0);

    mc_updater_.setHardwareID("Motor Controller");
    mc_updater_.add("MC Diagnostic", this, &MotorController::mc_diagnostic);

    battery_updater_.setHardwareID("Battery Controller");
    battery_updater_.add("Battery Diagnostic", this, &MotorController::battery_diagnostic);

    get_parameter("frequency", frequency_);
    rclcpp::Rate rate(frequency_);

    setPID();

    while (rclcpp::ok())
    {
      sendRequest();
      receiveResponse();
      mc_updater_.update();
      battery_updater_.update();
      rate.sleep();
    }
  }

  void MotorController::cmdCallback(const urc_msgs::msg::VelocityPair &msg)
  {
    current_motor_command_ = msg;
    last_motors_message_ = rclcpp::Clock().now();
  }

  void MotorController::mc_diagnostic(diagnostic_updater::DiagnosticStatusWrapper &stat)
  {
    stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Motor Controller Online");
    stat.add("Motor Controller Publishing Frequency ", std::to_string(mc_hertz) + " Hz");
  }

  void MotorController::battery_diagnostic(diagnostic_updater::DiagnosticStatusWrapper &stat)
  {
    if (battery_avg_ < min_battery_voltage_)
    {
      stat.summary(diagnostic_msgs::DiagnosticStatus::ERROR, "Battery voltage dangerously low");
    }
    else if (battery_avg_ < (min_battery_voltage_ + 0.25))
    {
      stat.summary(diagnostic_msgs::DiagnosticStatus::WARN, "Battery voltage low");
    }
    else
    {
      stat.summary(diagnostic_msgs::DiagnosticStatus::OK, "Battery voltage okay");
    }
    stat.add("battery voltage", battery_avg_);
  }

  void MotorController::setPID()
  {
    rclcpp::Rate rate(frequency_);
    bool valid_values = true; // pid values have been set correctly

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

    if (!status)
    {
      RCLCPP_ERROR(this->get_logger(), "Encoding Failed: \n%s", PB_GET_ERROR(&ostream))
      return;
    }

    size_t response;     // Socket response: 0 means connection closed, otherwise n = num bytes read
    uint8_t buffer[256]; // buffer to read response into

    // Send PID values via ethernet and recieve response to ensure proper setting
    while (rclcpp::ok() && valid_values)
    {
      (socket_).sendMessage(reinterpret_cast<char *>(requestbuffer), message_length);

      memset(buffer, 0, sizeof(buffer));
      n = (socket_).readMessage(buffer); // blocks until data is read

      if (n == 0)
      {
        RCLCPP_ERROR(this->get_logger(), "Connection closed by server!");
        mc_updater_.broadcast(diagnostic_msgs::DiagnosticStatus::ERROR, "Failed to send PID. Connection Closed by "
                                                                        "server.");
        battery_updater_.broadcast(diagnostic_msgs::DiagnosticStatus::ERROR, "Failed to send PID. Lost battery "
                                                                             "tracking.");
        return;
      }

      // Decoding message
      ResponseMessage response = ResponseMessage_init_zero;
      pb_istream_t istream = pb_istream_from_buffer(buffer, n);
      status = pb_decode(&istream, ResponseMessage_fields, &response);

      /* check for any errors.. */
      if (!status)
      {
        RCLCPP_ERROR(this->get_logger(), "Decoding failure!");
        mc_updater_.broadcast(diagnostic_msgs::DiagnosticStatus::ERROR, "PID decoding failed. Shutting Down.");
        battery_updater_.broadcast(diagnostic_msgs::DiagnosticStatus::ERROR, "PID decoding failed. Lost battery "
                                                                             "tracking.");
        return;
      }

      valid_values = (response.p_l == static_cast<float>(p_l_)) && (response.p_r == static_cast<float>(p_r_)) &&
                     (response.i_l == static_cast<float>(i_l_)) && (response.i_r == static_cast<float>(i_r_)) &&
                     (response.d_l == static_cast<float>(d_l_)) && (response.d_r == static_cast<float>(d_r_)) &&
                     (response.kv_l == static_cast<float>(kv_l_)) && (response.kv_r == static_cast<float>(kv_r_));

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

    if (!status)
    {
      RCLCPP_ERROR(this->get_logger(), "Encoding Failed: \n%s", PB_GET_ERROR(&ostream))
      return;
    }

    (socket_).sendMessage(reinterpret_cast<char *>(requestbuffer), message_length);
  }

  void MotorController::receiveResponse()
  {
    size_t response;     // Socket response: 0 means connection closed, otherwise n = num bytes read
    uint8_t buffer[256]; // buffer to read response into

    memset(buffer, 0, sizeof(buffer));
    response = (socket_).readMessage(buffer);

    if (response == 0)
    {
      RCLCPP_ERROR(this->get_logger(), "Connection Closed by Server!")
      return;
    }

    // Empty message where the decoded buffer will be stored
    ResponseMessage response = ResponseMessage_init_zero;

    pb_istream_t istream = pb_istream_from_buffer(buffer, n);
    bool status = pb_decode(&istream, ResponseMessage_fields, &response);

    if (!status)
    {
      RCLCPP_ERROR(this->get_logger(), "Decoding Failed: \n%s", PB_GET_ERROR(&istream))
      return;
    }

    publishResponse(response);
  }

  void MotorController::publishResponse(const ResponseMessage &response)
  {
    /* update the exponentially weighted moving voltage average and publish */
    std_msgs::msg::Float64 battery_msg;
    battery_avg_ = (battery_alpha_ * battery_avg_) + ((1 - battery_alpha_) * response.voltage);
    battery_msg.data = battery_avg_;
    _battery_pub.publish(battery_msg);

    if (battery_avg_ < min_battery_voltage_)
    {
      RCLCPP_ERROR(this->get_logger(), "Battery voltage dangerously low at %f!", battery_avg_)
    }

    std_msgs::msg::Bool enabled_msg;
    enabled_msg.data = response.estop;
    _enabled_pub.publish(enabled_msg);

    // publish encoder feedback
    urc_msgs::msg::VelocityPair encoder_msg;

    encoder_msg.left_velocity = response.speed_l;
    encoder_msg.right_velocity = response.speed_r;
    encoder_msg.duration = response.dt_sec;
    encoder_msg.header.stamp = rclcpp::Clock().now() - rclcpp::Duration(response.dt_sec);

    _enc_pub.publish(encoder_msg);
  }
}

RCLCPP_COMPONENTS_REGISTER_NODE(motor_controller::MotorController)