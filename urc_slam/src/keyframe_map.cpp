#include "urc_slam/keyframe_map.hpp"

#include <algorithm>

#include <pcl/common/transforms.h>
#include <pcl/filters/voxel_grid.h>

namespace urc_slam
{

namespace
{
void appendTransformed(
  const KeyframeMap::Cloud & cloud,
  const gtsam::Pose3 & target_T_cloud,
  KeyframeMap::Cloud & destination
)
{
  KeyframeMap::Cloud transformed;
  pcl::transformPointCloud(cloud, transformed, target_T_cloud.matrix().cast<float>());
  destination += transformed;
}

KeyframeMap::Cloud::Ptr voxelDownsample(
  const KeyframeMap::Cloud::ConstPtr & cloud,
  double voxel_size_m
)
{
  KeyframeMap::Cloud::Ptr filtered(new KeyframeMap::Cloud);
  pcl::VoxelGrid<LidarFrontend::Point> voxel_filter;
  voxel_filter.setInputCloud(cloud);
  voxel_filter.setLeafSize(voxel_size_m, voxel_size_m, voxel_size_m);
  voxel_filter.filter(*filtered);
  return filtered;
}
}  // namespace

KeyframeMap::KeyframeMap(double map_voxel_size_m, double submap_voxel_size_m)
: map_voxel_size_m(map_voxel_size_m),
  submap_voxel_size_m(submap_voxel_size_m),
  map_cloud(new Cloud)
{
}

void KeyframeMap::addKeyframe(
  const rclcpp::Time & stamp,
  const Cloud::ConstPtr & cloud,
  const gtsam::Pose3 & map_T_base
)
{
  keyframe_stamps.push_back(stamp);
  keyframe_clouds.push_back(cloud);
  appendTransformed(*cloud, map_T_base, *map_cloud);
  has_unfiltered_points = true;
}

void KeyframeMap::markPosesChanged()
{
  poses_changed = true;
}

bool KeyframeMap::update(const PoseLookup & map_T_base_at)
{
  if (poses_changed) {
    map_cloud.reset(new Cloud);
    for (std::size_t index = 0; index < keyframe_clouds.size(); ++index) {
      appendTransformed(*keyframe_clouds[index], map_T_base_at(index), *map_cloud);
    }
    poses_changed = false;
    has_unfiltered_points = true;
  }
  if (!has_unfiltered_points) {
    return false;
  }
  map_cloud = voxelDownsample(map_cloud, map_voxel_size_m);
  has_unfiltered_points = false;
  return true;
}

const KeyframeMap::Cloud & KeyframeMap::mapCloud() const
{
  return *map_cloud;
}

const std::vector<rclcpp::Time> & KeyframeMap::stamps() const
{
  return keyframe_stamps;
}

std::size_t KeyframeMap::size() const
{
  return keyframe_clouds.size();
}

KeyframeMap::Cloud::Ptr KeyframeMap::buildLocalSubmap(
  std::size_t keyframe_count,
  const PoseLookup & map_T_base_at
) const
{
  Cloud::Ptr submap(new Cloud);
  if (keyframe_clouds.empty()) {
    return submap;
  }

  const std::size_t newest = keyframe_clouds.size() - 1;
  const std::size_t count = std::clamp<std::size_t>(keyframe_count, 1, keyframe_clouds.size());
  if (count == 1) {
    *submap = *keyframe_clouds[newest];
    return submap;
  }

  const gtsam::Pose3 newest_T_map = map_T_base_at(newest).inverse();
  for (std::size_t index = newest + 1 - count; index <= newest; ++index) {
    appendTransformed(
      *keyframe_clouds[index], newest_T_map.compose(map_T_base_at(index)), *submap);
  }
  return voxelDownsample(submap, submap_voxel_size_m);
}

}  // namespace urc_slam
