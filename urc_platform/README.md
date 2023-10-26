# URC Platform

This package is a collection of lower-level nodes focused on hardware interaction.

## Joystick Driver

Deals with the manual control of the rover. Takes in joystick messages (sensor_msgs::msg::Joy) and publishes velocity messages (urc_msgs::msg::VelocityPair) telling the motors what to do.

- [More info on how the Joystick inputs are fed in to the rover](../urc_dashboard/)

## Motor Controller

Directs the operation of the motors. Takes in velocity messages (urc_msgs::msg::VelocityPair) and publishes what they mean to the motor encoders over the rover's on-board LAN.

- [More info on how the transmission works](../urc_util/src/ethernet_socket.cpp)
- [More info on how the info is encapsulated](../urc_nanopb/)
- [Actual hardware implementation of messages can be seen in the firmware repo](https://github.com/RoboJackets/urc-firmware)
