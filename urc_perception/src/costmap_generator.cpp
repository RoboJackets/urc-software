#include "costmap_generator.hpp"

namespace costmap_generator
{
CostmapGenerator::CostmapGenerator(const rclcpp::NodeOptions & options)
: rclcpp::Node("costmap_generator", options)
{
  depth_subscriber = create_subscription<sensor_msgs::msg::Image>(
    "/camera/depth/image_rect_raw", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::Image msg) {DepthCallback(msg);});

  pose_subscriber = create_subscription<geometry_msgs::msg::Pose>(
    "/pose", rclcpp::SystemDefaultsQoS(),
    [this](const geometry_msgs::msg::Pose msg) {PoseCallback(msg);});
  laser_subscriber = create_subscription<sensor_msgs::msg::LaserScan>(
    "/laserscan", rclcpp::SystemDefaultsQoS(),
    [this](const sensor_msgs::msg::LaserScan msg) {LaserScanCallback(msg);});

  costmap_publisher = create_publisher<nav2_msgs::msg::Costmap>(
    "/costmap", rclcpp::SystemDefaultsQoS());

  costmap.metadata.resolution = 0.25;       // m/cell
  costmap.metadata.size_x = 100;
  costmap.metadata.size_y = 100;
  for (int i = 0; i < costmap.metadata.size_x * costmap.metadata.size_y; ++i) {
    costmap.data.push_back(0);
  }
  RCLCPP_INFO(this->get_logger(), "Costmap Capacity: %d", (int)(costmap.data.size()));
  direction = 0;
  robotGridX = 0;
  robotGridY = 0;
  maxCost = 0;
  minCost = DBL_MAX;
  delay = 0;

  // Needed Feature:
  // * Set home position (probably on web interface) that will allow us to put the costmap's left bottom corner where we are

}

void CostmapGenerator::PoseCallback(const geometry_msgs::msg::Pose & msg)
{
  double x = msg.orientation.x;
  double y = msg.orientation.y;
  double z = msg.orientation.z;
  double w = msg.orientation.w;
  double euler_z = atan2(2.0f * (w * z + x * y), w * w + x * x - y * y - z * z) + M_PI / 4;
  int rotation_id = (int(euler_z / (M_PI / 8))) % 8;
  RCLCPP_INFO(this->get_logger(), "%d", rotation_id);
  direction = rotation_id;
}


void CostmapGenerator::DepthCallback(const sensor_msgs::msg::Image & msg)
{
  // 90 91 92 93 94 95 96 97 98 99
  // 80 81 82 83 84 85 86 87 88 89
  // 70 71 72 73 74 75 76 77 78 79
  // 60 61 62 63 64 65 66 67 68 69
  // 50 51 52 53 54 55 56 57 58 59
  // 40 41 42 43 44 45 46 47 48 49
  // 30 31 32 33 34 35 36 37 38 39
  // 20 21 22 23 24 25 26 27 28 29
  // 10 11 12 13 14 15 16 17 18 19
  // 00 01 02 03 04 05 06 07 08 09
  // ^^ robot current position, with each number indicating index in the array
  // Directions:
  // 0: North
  // 1: Northeast
  // 2: East
  // 3: Southeast
  // 4: South
  // 5: Southwest
  // 6: West
  // 7: Northwests

  // Partition the image into 3 partitions, each divided vertically
  delay++;
  if (delay != 10) {
    return;
  }
  delay = 0;
  double costLeft = 0;
  double costMiddle = 0;
  double costRight = 0;
  for (int i = 0; i < msg.width; ++i) {
    for (int j = 0; j < msg.height; ++j) {
      if ((double)i < msg.width / 3.0) {
        costLeft += (255 - msg.data[j * msg.width + i]);
      } else if ((double)i < msg.width * 2.0 / 3.0) {
        costMiddle += (255 - msg.data[j * msg.width + i]);
      } else {
        costRight += (255 - msg.data[j * msg.width + i]);
      }
    }
  }

  // Scale relative to highest cost seen
  if (costLeft > maxCost) {
    maxCost = costLeft;
  }
  if (costMiddle > maxCost) {
    maxCost = costMiddle;
  }
  if (costRight > maxCost) {
    maxCost = costRight;
  }
  if (costLeft < minCost) {
    minCost = costLeft;
  }
  if (costMiddle < minCost) {
    minCost = costMiddle;
  }
  if (costRight < minCost) {
    minCost = costRight;
  }

  // Please don't mind this code.
  int * data = (int *)malloc(sizeof(int) * 8);
  memset(data, 0, sizeof(int) * 8);

  costLeft = (costLeft - minCost) / (maxCost - minCost);
  costMiddle = (costMiddle - minCost) / (maxCost - minCost);
  costRight = (costRight - minCost) / (maxCost - minCost);
  data[(direction - 1) % 8] = costLeft;
  data[(direction) % 8] = costMiddle;
  data[(direction + 1) % 8] = costRight;

  RCLCPP_INFO(this->get_logger(), "Left Cost: %f", costLeft);
  RCLCPP_INFO(this->get_logger(), "Middle Cost: %f", costMiddle);
  RCLCPP_INFO(this->get_logger(), "Right Cost: %f", costRight);

  if (robotGridY != costmap.metadata.size_y - 1) {       // Direction 0
    costmap.data[(robotGridY + 1) * costmap.metadata.size_x + (robotGridX + 0)] = std::max(
      0,
      data[0]);
  }
  if (robotGridY != costmap.metadata.size_y - 1 && robotGridX != costmap.metadata.size_x - 1) {        // Direction 1
    costmap.data[(robotGridY + 1) * costmap.metadata.size_x + (robotGridX + 1)] = std::max(
      0,
      data[1]);
  }
  if (robotGridX != costmap.metadata.size_x - 1) {        // Direction 2
    costmap.data[(robotGridY + 0) * costmap.metadata.size_x + (robotGridX + 1)] = std::max(
      0,
      data[2]);
  }
  if (robotGridY != 0 && robotGridX != costmap.metadata.size_x - 1) {        // Direction 3
    costmap.data[(robotGridY - 1) * costmap.metadata.size_x + (robotGridX + 1)] = std::max(
      0,
      data[3]);
  }
  if (robotGridY != 0) {       // Direction 4
    costmap.data[(robotGridY - 1) * costmap.metadata.size_x + (robotGridX + 0)] = std::max(
      0,
      data[4]);
  }
  if (robotGridY != 0 && robotGridX != 0) {       // Direction 5
    costmap.data[(robotGridY - 1) * costmap.metadata.size_x + (robotGridX - 1)] = std::max(
      0,
      data[5]);
  }
  if (robotGridX != 0) {       // Direction 6
    costmap.data[(robotGridY + 0) * costmap.metadata.size_x + (robotGridX - 1)] = std::max(
      0,
      data[6]);
  }
  if (robotGridY != costmap.metadata.size_y - 1 && robotGridX != 0) {       // Direction 7
    costmap.data[(robotGridY + 1) * costmap.metadata.size_x + (robotGridX - 1)] = std::max(
      0,
      data[7]);
  }


  costmap_publisher->publish(costmap);
}
void CostmapGenerator::LaserScanCallback(const sensor_msgs::msg::LaserScan & msg)
{
  // Convert laser scan to costmap
  // nav2_msgs::msg::Costmap costmap_msg;
  // costmap_publisher->publish(costmap_msg);
}
}

RCLCPP_COMPONENTS_REGISTER_NODE(costmap_generator::CostmapGenerator)
