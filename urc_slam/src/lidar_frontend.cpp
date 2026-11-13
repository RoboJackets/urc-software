#include "urc_slam/lidar_frontend.hpp"

#include <Eigen/Core>
#include <pcl/common/point_tests.h>
#include <pcl/common/transforms.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/gicp.h>

namespace urc_slam
{

namespace
{
using Gicp = pcl::GeneralizedIterativeClosestPoint<
  LidarFrontend::Point, LidarFrontend::Point>;

struct AlignmentQuality
{
  double fitness_score_m2;
  double inlier_fraction;
};

// Scores only correspondences within the correspondence distance so that
// newly visible terrain does not count against a correct alignment.
AlignmentQuality measureAlignment(
  Gicp & gicp,
  const LidarFrontend::Cloud & aligned_cloud,
  double maximum_correspondence_distance_m
)
{
  const double maximum_distance_squared =
    maximum_correspondence_distance_m * maximum_correspondence_distance_m;
  const auto search = gicp.getSearchMethodTarget();

  pcl::Indices nearest_index(1);
  std::vector<float> nearest_distance_squared(1);
  double inlier_distance_sum = 0.0;
  std::size_t inlier_count = 0;

  for (const auto & point : aligned_cloud.points) {
    if (search->nearestKSearch(point, 1, nearest_index, nearest_distance_squared) == 0) {
      continue;
    }
    if (nearest_distance_squared[0] > maximum_distance_squared) {
      continue;
    }
    inlier_distance_sum += nearest_distance_squared[0];
    ++inlier_count;
  }

  if (inlier_count == 0) {
    return {std::numeric_limits<double>::infinity(), 0.0};
  }
  return {
    inlier_distance_sum / static_cast<double>(inlier_count),
    static_cast<double>(inlier_count) / static_cast<double>(aligned_cloud.size())
  };
}

gtsam::Pose3 toPose3(const Eigen::Matrix4f & transform)
{
  const Eigen::Matrix4d transform_d = transform.cast<double>();
  return gtsam::Pose3(
    gtsam::Rot3(transform_d.block<3, 3>(0, 0)),
    gtsam::Point3(transform_d.block<3, 1>(0, 3))
  );
}
}  // namespace

LidarFrontend::LidarFrontend(const LidarFrontendParameters & parameters)
: parameters_(parameters)
{
}

LidarFrontend::Cloud::Ptr LidarFrontend::preprocess(
  const Cloud & sensor_cloud,
  const gtsam::Pose3 & base_T_lidar
) const
{
  Cloud::Ptr range_filtered(new Cloud);
  range_filtered->reserve(sensor_cloud.size());

  const double minimum_range_squared =
    parameters_.minimum_range_m * parameters_.minimum_range_m;
  const double maximum_range_squared =
    parameters_.maximum_range_m * parameters_.maximum_range_m;

  for (const Point & point : sensor_cloud.points) {
    if (!pcl::isFinite(point)) {
      continue;
    }
    const double range_squared =
      point.x * point.x + point.y * point.y + point.z * point.z;
    if (range_squared < minimum_range_squared || range_squared > maximum_range_squared) {
      continue;
    }
    range_filtered->push_back(point);
  }

  pcl::transformPointCloud(
    *range_filtered, *range_filtered, base_T_lidar.matrix().cast<float>());

  Cloud::Ptr downsampled(new Cloud);
  pcl::VoxelGrid<Point> voxel_filter;
  voxel_filter.setInputCloud(range_filtered);
  voxel_filter.setLeafSize(
    parameters_.voxel_size_m, parameters_.voxel_size_m, parameters_.voxel_size_m);
  voxel_filter.filter(*downsampled);
  return downsampled;
}

LidarRegistrationResult LidarFrontend::registerClouds(
  const Cloud::ConstPtr & target_cloud,
  const Cloud::ConstPtr & source_cloud,
  const std::vector<gtsam::Pose3> & initial_guesses
) const
{
  LidarRegistrationResult result;
  if (!target_cloud || !source_cloud || target_cloud->empty() || source_cloud->empty()) {
    return result;
  }

  // One GICP instance so point covariances are computed once across guesses
  Gicp gicp;
  gicp.setInputSource(source_cloud);
  gicp.setInputTarget(target_cloud);
  gicp.setMaxCorrespondenceDistance(parameters_.maximum_correspondence_distance_m);
  gicp.setMaximumIterations(parameters_.maximum_iterations);
  gicp.setTransformationEpsilon(parameters_.transformation_epsilon);

  Cloud aligned_cloud;
  for (const gtsam::Pose3 & guess : initial_guesses) {
    gicp.align(aligned_cloud, guess.matrix().cast<float>());

    result = LidarRegistrationResult();
    result.converged = gicp.hasConverged();
    if (!result.converged) {
      continue;
    }

    const AlignmentQuality quality = measureAlignment(
      gicp, aligned_cloud, parameters_.maximum_correspondence_distance_m);
    result.fitness_score_m2 = quality.fitness_score_m2;
    result.inlier_fraction = quality.inlier_fraction;
    result.relative_pose = toPose3(gicp.getFinalTransformation());
    result.accepted =
      quality.fitness_score_m2 <= parameters_.maximum_fitness_score_m2 &&
      quality.inlier_fraction >= parameters_.minimum_inlier_fraction;
    if (result.accepted) {
      return result;
    }
  }
  return result;
}

}  // namespace urc_slam
