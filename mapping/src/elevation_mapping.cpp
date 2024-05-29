#include "elevation_mapping.hpp"

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>
#include <pcl/PCLPointCloud2.h>

#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <geometry_msgs/msg/pose.hpp>

namespace mapping
{

ElevationMapping::ElevationMapping(const rclcpp::NodeOptions & options)
: Node("elevation_mapping", options)
{
  RCLCPP_INFO(this->get_logger(), "Mapping node has been started.");

  declare_parameter("map_frame", "odom");
  declare_parameter("camera_frame", "camera_depth_frame");
  declare_parameter("depth_topic", "/depth_camera/points");

  declare_parameter("resolution", 0.1);
  declare_parameter("width", 60);
  declare_parameter("min_z", 0.1);
  declare_parameter("max_z", 2.0);

  declare_parameter("inflation_radius", 0.1);
  declare_parameter("inflate_obstacles", true);

  width_ = get_parameter("width").as_int();
  resolution_ = get_parameter("resolution").as_double();
  map_frame_ = get_parameter("map_frame").as_string();
  camera_frame_ = get_parameter("camera_frame").as_string();
  min_z_ = get_parameter("min_z").as_double();
  max_z_ = get_parameter("max_z").as_double();

  cell_inflation_radius_ = cellDistance(get_parameter("inflation_radius").as_double());
  inflate_obstacles_ = get_parameter("inflate_obstacles").as_bool();

  RCLCPP_INFO(this->get_logger(), "Cell inflation radius set to %d", cell_inflation_radius_);
  RCLCPP_INFO(
    this->get_logger(), "Inflate obstacles set to %s.", inflate_obstacles_ ? "true" : "false");

  map_.header.frame_id = map_frame_;
  map_.info.resolution = resolution_;
  map_.info.width = map_.info.height = width_;
  map_.data.resize(map_.info.width * map_.info.height);

  depth_subscriber_ = create_subscription<sensor_msgs::msg::PointCloud2>(
    get_parameter("depth_topic").as_string(), 10,
    std::bind(&ElevationMapping::handlePointcloud, this, std::placeholders::_1));

  map_publisher_ = create_publisher<nav_msgs::msg::OccupancyGrid>("/costmap", 10);

  tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
  tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
}

ElevationMapping::~ElevationMapping()
{
}

geometry_msgs::msg::TransformStamped ElevationMapping::lookup_transform(
  std::string target_frame,
  std::string source_frame,
  rclcpp::Time time)
{
  geometry_msgs::msg::TransformStamped transform;

  try {
    transform = tf_buffer_->lookupTransform(target_frame, source_frame, time);
  } catch (tf2::TransformException & ex) {
    RCLCPP_ERROR(this->get_logger(), "Could not lookup transform: %s", ex.what());
  }

  return transform;
}

bool ElevationMapping::worldToMap(
  double x, double y, nav_msgs::msg::MapMetaData info,
  std::pair<int, int> & out)
{
  if (x < info.origin.position.x || x >= info.origin.position.x + info.width * info.resolution ||
    y < info.origin.position.y || y >= info.origin.position.y + info.height * info.resolution)
  {
    return false;
  }

  out.first = (x - info.origin.position.x) / info.resolution;
  out.second = (y - info.origin.position.y) / info.resolution;

  return true;
}

void ElevationMapping::handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  // Transform the point cloud to the map frame
  auto camera_to_map = lookup_transform(map_frame_, msg->header.frame_id, msg->header.stamp);
  sensor_msgs::msg::PointCloud2 cloud_global_;
  tf2::doTransform(*msg, cloud_global_, camera_to_map);

  // Convert the transformed point cloud to a PCL point cloud
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromROSMsg(cloud_global_, *cloud);

  // Remove NaN values from the point cloud
  std::vector<int> indices;
  pcl::removeNaNFromPointCloud(*cloud, *cloud, indices);

  // Set the origin of the costmap to the current position of the robot
  tf2::Stamped<tf2::Transform> trans;
  tf2::fromMsg(lookup_transform(map_frame_, "base_link", msg->header.stamp), trans);

  auto pos = trans.getOrigin();
  double x = static_cast<int>(pos.x() / map_.info.resolution) * map_.info.resolution;
  double y = static_cast<int>(pos.y() / map_.info.resolution) * map_.info.resolution;

  map_.info.origin.position.x = x - map_.info.width * map_.info.resolution * 0.5;
  map_.info.origin.position.y = y - map_.info.height * map_.info.resolution * 0.5;
  map_.info.origin.position.z = 0.0;
  map_.info.origin.orientation.w = 1.0;

  // Reset the costmap
  std::fill(map_.data.begin(), map_.data.end(), 0);

  // Update the costmap with the point cloud
  for (unsigned int i = 0; i < cloud->size(); i++) {
    auto & point = cloud->points[i];

    std::pair<int, int> map_coord;
    if (!worldToMap(point.x, point.y, map_.info, map_coord)) {
      continue;
    }

    double z = point.z - pos.z();
    double y = point.y - pos.y();
    double x = point.x - pos.x();

    if (z < min_z_ || std::sqrt(x * x + y * y) > 2.8) {
      continue;
    }

    int costmap_index = map_coord.first + map_coord.second * map_.info.width;

    double cost = 0.0;

    if (z > max_z_) {
      cost = max_cost_;
    } else {
      cost = (z - min_z_) / (max_z_ - min_z_) * max_cost_;
    }

    if (cost > map_.data[costmap_index]) {
      map_.data[costmap_index] = cost;

      if (inflate_obstacles_) {
        inflate(map_coord.first, map_coord.second, cost, cell_inflation_radius_);
      }
    }
  }

  map_.header.stamp = get_clock()->now();
  map_publisher_->publish(map_);
}

void ElevationMapping::inflate(int cell_x, int cell_y, double cell_cost, int radius)
{
  for (int x = cell_x - radius; x <= cell_x + radius; x++) {
    for (int y = cell_y - radius; y <= cell_y + radius; y++) {
      if (x < 0 || x >= map_.info.width || y < 0 || y >= map_.info.height) {
        continue;
      }

      int dist = std::sqrt(std::pow(x - cell_x, 2) + std::pow(y - cell_y, 2));

      if (dist <= radius) {
        int index = x + y * map_.info.width;
        double inflated_cost = gaussian(dist) * cell_cost;

        if (inflated_cost > map_.data[index]) {
          map_.data[index] = inflated_cost;
        }
      }
    }
  }
}

double ElevationMapping::gaussian(double x)
{
  return std::exp(-0.5 * x * x / cell_inflation_radius_);
}

} // namespace mapping

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(mapping::ElevationMapping)
