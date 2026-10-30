#ifndef URC_SLAM__KEYFRAME_MAP_HPP_
#define URC_SLAM__KEYFRAME_MAP_HPP_

#include <cstddef>
#include <functional>
#include <vector>

#include <gtsam/geometry/Pose3.h>
#include <rclcpp/time.hpp>

#include "urc_slam/lidar_frontend.hpp"

namespace urc_slam
{

// Stores keyframe clouds in their own base_link frame and builds the
// map-frame point cloud and local registration submaps from pose estimates.
class KeyframeMap
{
public:
  using Cloud = LidarFrontend::Cloud;
  using PoseLookup = std::function<gtsam::Pose3(std::size_t)>;

  KeyframeMap(double map_voxel_size_m, double submap_voxel_size_m);

  // Keyframes must be added in index order; cloud is in base_link
  void addKeyframe(
    const rclcpp::Time & stamp,
    const Cloud::ConstPtr & cloud,
    const gtsam::Pose3 & map_T_base
  );

  // Forces the next update() to re-project every keyframe, e.g. after
  // a GPS correction moved past poses
  void markPosesChanged();

  // Brings the map cloud up to date and returns whether it changed
  bool update(const PoseLookup & map_T_base_at);

  const Cloud & mapCloud() const;
  const std::vector<rclcpp::Time> & stamps() const;
  // Keyframe clouds by index, each in its own base_link frame
  const std::vector<Cloud::ConstPtr> & clouds() const;
  std::size_t size() const;

  // Union of the newest keyframe_count keyframes, expressed in the
  // newest keyframe's base_link frame and voxel-downsampled
  Cloud::Ptr buildLocalSubmap(
    std::size_t keyframe_count,
    const PoseLookup & map_T_base_at
  ) const;

private:
  double map_voxel_size_m;
  double submap_voxel_size_m;
  std::vector<rclcpp::Time> keyframe_stamps;
  std::vector<Cloud::ConstPtr> keyframe_clouds;
  Cloud::Ptr map_cloud;
  bool has_unfiltered_points = false;
  bool poses_changed = false;
};

}  // namespace urc_slam

#endif  // URC_SLAM__KEYFRAME_MAP_HPP_
