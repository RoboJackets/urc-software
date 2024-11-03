// #include "traversability_mapping.hpp"

// #include <grid_map_ros/grid_map_ros.hpp>
// #include <grid_map_msgs/msg/GridMap.hpp>
// #include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>
// #include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
// #include <geometry_msgs/msg/pose.hpp>
// #include <pcl/common/io.h> // Added for PCL operations
// #include <pcl/filters/passthrough.h>
// #include <pcl/filters/voxel_grid.h>

// namespace urc_perception
// {

// TraversabilityMapping::TraversabilityMapping(const rclcpp::NodeOptions & options)
// : Node("traversabilityMapping", options),
//   map_({"traversability"})
// {
//   RCLCPP_INFO(this->get_logger(), "Mapping node has been started.");

//   declare_parameter("map_frame", "odom");
//   declare_parameter("camera_frame", "camera_depth_frame");
//   declare_parameter("depth_topic", "/depth_camera/points");

//   declare_parameter("resolution", 0.1);
//   declare_parameter("width", 60);
//   declare_parameter("min_z", 0.1);
//   declare_parameter("max_z", 2.0);

//   declare_parameter("inflation_radius", 0.1);
//   declare_parameter("inflate_obstacles", true);
  
//   // Parameters for outlier removal and downsampling
//   declare_parameter("downsample_leaf_size", 0.05);
//   declare_parameter("apply_outlier_removal", true);
//   declare_parameter("outlier_removal_mean_k", 50);
//   declare_parameter("outlier_removal_std_dev", 1.0);

//   resolution_ = get_parameter("resolution").as_double();
//   width_ = get_parameter("width").as_int();
//   map_frame_ = get_parameter("map_frame").as_string();
//   camera_frame_ = get_parameter("camera_frame").as_string();
//   min_z_ = get_parameter("min_z").as_double();
//   max_z_ = get_parameter("max_z").as_double();

//   cell_inflation_radius_ = cellDistance(get_parameter("inflation_radius").as_double());
//   inflate_obstacles_ = get_parameter("inflate_obstacles").as_bool();
//   downsample_leaf_size_ = get_parameter("downsample_leaf_size").as_double();
//   apply_outlier_removal_ = get_parameter("apply_outlier_removal").as_bool();
//   outlier_removal_mean_k_ = get_parameter("outlier_removal_mean_k").as_int();
//   outlier_removal_std_dev_ = get_parameter("outlier_removal_std_dev").as_double();

//   // Initialize GridMap
//   map_.setFrameId(map_frame_);
//   map_.setGeometry(grid_map::Length(width_ * resolution_, width_ * resolution_), resolution_);
//   map_["traversability"].setZero();

//   depth_subscriber_ = create_subscription<sensor_msgs::msg::PointCloud2>(
//     get_parameter("depth_topic").as_string(), 10,
//     std::bind(&TraversabilityMapping::handlePointcloud, this, std::placeholders::_1));

//   map_publisher_ = create_publisher<grid_map_msgs::msg::GridMap>("/traversability_map", 10);

//   tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
//   tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
// }

// TraversabilityMapping::~TraversabilityMapping()
// {
// }

// geometry_msgs::msg::TransformStamped TraversabilityMapping::lookup_transform(
//   std::string target_frame,
//   std::string source_frame,
//   rclcpp::Time time)
// {
//   geometry_msgs::msg::TransformStamped transform;

//   try {
//     transform = tf_buffer_->lookupTransform(target_frame, source_frame, time);
//   } catch (tf2::TransformException & ex) {
//     RCLCPP_ERROR(this->get_logger(), "Could not lookup transform: %s", ex.what());
//   }

//   return transform;
// }

// void TraversabilityMapping::handlePointcloud(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
// {
//   // Transform the point cloud to the map frame
//   auto camera_to_map = lookup_transform(map_frame_, msg->header.frame_id, msg->header.stamp);
//   sensor_msgs::msg::PointCloud2 cloud_global_;
//   tf2::doTransform(*msg, cloud_global_, camera_to_map);

//   pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_cloud(new pcl::PointCloud<pcl::PointXYZ>);
//   pcl::fromROSMsg(cloud_global_, *pcl_cloud);

//   // Outlier Removal
//   if (apply_outlier_removal_) {
//     pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
//     sor.setInputCloud(pcl_cloud);
//     sor.setMeanK(outlier_removal_mean_k_);
//     sor.setStddevMulThresh(outlier_removal_std_dev_);
//     sor.filter(*pcl_cloud);
//   }

//   // Downsampling
//   pcl::VoxelGrid<pcl::PointXYZ> voxel_filter;
//   voxel_filter.setInputCloud(pcl_cloud);
//   voxel_filter.setLeafSize(downsample_leaf_size_, downsample_leaf_size_, downsample_leaf_size_);
//   voxel_filter.filter(*pcl_cloud);

//   // Update grid map geometry based on robot position
//   tf2::Stamped<tf2::Transform> trans;
//   tf2::fromMsg(lookup_transform(map_frame_, "base_link", msg->header.stamp), trans);
//   auto pos = trans.getOrigin();
//   grid_map::Position robot_position(pos.x(), pos.y());
//   map_.setPosition(robot_position);

//   // Reset the grid map
//   map_["traversability"].setZero();

//   // Populate the grid map with the point cloud data
//   for (const auto & point : pcl_cloud->points) {
//     if (point.z < min_z_ || point.z > max_z_) {
//       continue;
//     }

//     grid_map::Position position(point.x, point.y);
//     if (!map_.isInside(position)) {
//       continue;
//     }

//     double cost = (point.z - min_z_) / (max_z_ - min_z_) * max_cost_;
//     map_.at("traversability", position) = std::max(map_.at("traversability", position), cost);

//     if (inflate_obstacles_) {
//       inflate(position, cost);
//     }
//   }

//   auto map_msg = grid_map::GridMapRosConverter::toMessage(map_);
//   map_publisher_->publish(*map_msg);
// }

// void TraversabilityMapping::inflate(const grid_map::Position & position, double cell_cost)
// {
//   for (grid_map::CircleIterator it(map_, position, cell_inflation_radius_); !it.isPastEnd(); ++it) {
//     double dist = (map_.getPosition(*it) - position).norm();
//     double inflated_cost = gaussian(dist) * cell_cost;

//     if (inflated_cost > map_.at("traversability", *it)) {
//       map_.at("traversability", *it) = inflated_cost;
//     }
//   }
// }

// double TraversabilityMapping::gaussian(double x)
// {
//   return std::exp(-0.5 * x * x / cell_inflation_radius_);
// }

// } // namespace urc_perception

// #include <rclcpp_components/register_node_macro.hpp>
// RCLCPP_COMPONENTS_REGISTER_NODE(urc_perception::TraversabilityMapping)
