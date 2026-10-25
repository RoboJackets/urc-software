#ifndef URC_SLAM__LIDAR_FRONTEND_HPP_
#define URC_SLAM__LIDAR_FRONTEND_HPP_

#include <limits>
#include <vector>

#include <gtsam/geometry/Pose3.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace urc_slam
{

struct LidarFrontendParameters
{
  double voxel_size_m;
  double minimum_range_m;
  double maximum_range_m;
  double maximum_correspondence_distance_m;
  int maximum_iterations;
  double transformation_epsilon;
  // Mean squared distance of inlier correspondences, in m^2
  double maximum_fitness_score_m2;
  double minimum_inlier_fraction;
};

struct LidarRegistrationResult
{
  bool converged = false;
  bool accepted = false;
  double fitness_score_m2 = std::numeric_limits<double>::infinity();
  double inlier_fraction = 0.0;
  gtsam::Pose3 relative_pose;
};

class LidarFrontend
{
public:
  using Point = pcl::PointXYZ;
  using Cloud = pcl::PointCloud<Point>;

  explicit LidarFrontend(const LidarFrontendParameters & parameters);

  // Range-filters in the sensor frame, transforms into base_link and
  // voxel-downsamples. The returned cloud is in base_link.
  Cloud::Ptr preprocess(
    const Cloud & sensor_cloud,
    const gtsam::Pose3 & base_T_lidar
  ) const;

  // Estimates the pose of the source cloud's base_link in the target
  // cloud's base_link frame. Initial guesses are tried in order and the
  // first accepted result is returned; otherwise the last attempt is.
  LidarRegistrationResult registerClouds(
    const Cloud::ConstPtr & target_cloud,
    const Cloud::ConstPtr & source_cloud,
    const std::vector<gtsam::Pose3> & initial_guesses
  ) const;

private:
  LidarFrontendParameters parameters_;
};

}  // namespace urc_slam

#endif  // URC_SLAM__LIDAR_FRONTEND_HPP_
