#ifndef URC_PERCEPTION__TRAVERSABILITY_MAPPING_HPP_
#define URC_PERCEPTION__TRAVERSABILITY_MAPPING_HPP_

#include <memory>
#include <string>

#include <filters/filter_chain.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <grid_map_pcl/GridMapPclLoader.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>

#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"

namespace urc_perception
{

// Builds a rolling traversability grid around the rover. Cost layer values run
// from 0 to 1, where 1 is lethal; NaN cells have not been observed.
class TraversabilityMapping : public rclcpp::Node
{
public:
  explicit TraversabilityMapping(const rclcpp::NodeOptions & options);
  ~TraversabilityMapping();

private:
  using Cloud = pcl::PointCloud<pcl::PointXYZ>;

  geometry_msgs::msg::TransformStamped lookupTransformSafe(
    const std::string & target_frame,
    const std::string & source_frame,
    const rclcpp::Time & stamp,
    const tf2::Duration & timeout,
    bool & success);

  void handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  void handleOdometry(const nav_msgs::msg::Odometry::SharedPtr msg);
  Cloud::Ptr cropToCache(const Cloud & cloud) const;
  bool buildLocalMap(const Cloud::Ptr & cloud, grid_map::GridMap & local_map);
  void mergeIntoCache(const grid_map::GridMap & local_map);
  void recenterCache(double center_x_world, double center_y_world);
  void publishCacheMap();

  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_subscriber_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odometry_subscriber_;
  rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr grid_map_publisher_;

  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  grid_map::GridMap cache_map_;
  filters::FilterChain<grid_map::GridMap> filter_chain_;
  grid_map::GridMapPclLoader grid_map_loader_;

  bool cache_initialized_ = false;

  double cache_size_x_ = 10.0;
  double cache_size_y_ = 10.0;
  double resolution_ = 0.25;
  double crop_margin_m_ = 0.75;

  std::string map_frame_ = "map";
  std::string odometry_topic_ = "/odometry/filtered_global";
  std::string pointcloud_topic_ = "/scan/points";
  std::string output_map_topic_ = "/costmap";
  std::string filter_chain_parameter_name_ = "filters";
};

}  // namespace urc_perception

#endif  // URC_PERCEPTION__TRAVERSABILITY_MAPPING_HPP_
