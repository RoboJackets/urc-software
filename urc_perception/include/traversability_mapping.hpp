#ifndef TRAVERSABILITY_MAPPING_HPP_
#define TRAVERSABILITY_MAPPING_HPP_

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <filters/filter_chain.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <string>

#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

namespace urc_perception
{

class TraversabilityMapping : public rclcpp::Node
{
public:
  explicit TraversabilityMapping(const rclcpp::NodeOptions & options);
  ~TraversabilityMapping();

private:
  geometry_msgs::msg::TransformStamped lookupTransformSafe(
    const std::string & target_frame,
    const std::string & source_frame,
    const rclcpp::Time & stamp,
    const tf2::Duration & timeout,
    bool & success);

  void handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  void handleOdometry(const nav_msgs::msg::Odometry::SharedPtr msg);
  void filterSphere(
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
    float min_radius,
    float max_radius);
  void recenterCache(double center_x_world, double center_y_world);
  void publishCacheMap();

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_subscriber_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odometry_subscriber_;
  rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr grid_map_publisher_;
  rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr cache_map_publisher_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  grid_map::GridMap cache_map_;
  filters::FilterChain<grid_map::GridMap> filter_chain_;

  bool use_filter_chain_ = false;
  bool cache_initialized_ = false;

  double min_filter_radius_ = 0.2;
  double filter_radius_ = 5.0;
  double cache_size_x_ = 10.0;
  double cache_size_y_ = 10.0;
  double resolution_ = 0.25;
  double recenter_rate_hz_ = 20.0;
  double min_z_ = 0.0;
  double max_z_ = 0.0;
  unsigned int width_ = 0;

  std::string map_frame_ = "map";
  std::string odometry_topic_ = "/odometry/filtered_global";
  std::string pointcloud_topic_ = "/scan/points";
  std::string output_map_topic_ = "/costmap";
  std::string cache_map_topic_ = "/cache_map";
  std::string filter_chain_parameter_name_ = "filters";
};

} // namespace urc_perception

#endif // TRAVERSABILITY_MAPPING_HPP_
