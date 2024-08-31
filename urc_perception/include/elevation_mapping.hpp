#ifndef ELEVATION_MAPPING_HPP_
#define ELEVATION_MAPPING_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

namespace urc_perception
{

class ElevationMapping : public rclcpp::Node
{
public:
  explicit ElevationMapping(const rclcpp::NodeOptions & options);
  ~ElevationMapping();

private:
  void handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg);

  geometry_msgs::msg::TransformStamped lookup_transform(
    std::string target_frame,
    std::string source_frame,
    rclcpp::Time time);

  bool worldToMap(double x, double y, nav_msgs::msg::MapMetaData info, std::pair<int, int> & out);

  int cellDistance(double world_dist)
  {
    return std::ceil(world_dist / resolution_);
  }

  void inflate(int cell_x, int cell_y, double cell_cost, int radius);

  double gaussian(double x);

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr depth_subscriber_;
  rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr map_publisher_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  nav_msgs::msg::OccupancyGrid map_;

  int cell_inflation_radius_;
  bool inflate_obstacles_;

  int8_t max_cost_ = 100;

  double resolution_;
  double min_z_;
  double max_z_;
  unsigned int width_;
  std::string map_frame_;
  std::string camera_frame_;
};

} // namespace urc_perception

#endif // ELEVATION_MAPPING_HPP_
