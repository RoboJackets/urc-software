#ifndef ROCK_TYPES_HPP_
#define ROCK_TYPES_HPP_

#include <cmath>
#include <vector>
#include <Eigen/Core>

namespace urc_slam {

    // Points of one LiDAR sweep in the SENSOR frame (x forward, y left, z up),
    // already stripped of NaNs. Kept independent of PCL/ROS so the extractor
    // can be unit-tested without them; converting PointCloud2 is one loop.
    using PointCloud3d = std::vector<Eigen::Vector3d>;

    // One rock seen in one sweep, in the SENSOR frame.
    struct RockObservation {
        // Fitted sphere centre. Clusters without a trustworthy fit produce no
        // observation at all.
        Eigen::Vector3d sensor_point = Eigen::Vector3d::Zero();
        double radius_m = 0.0;
        
        // Highest visible point above the locally estimated ground.
        double height_m = 0.0;

        double range_m() const { return sensor_point.norm(); }
        double azimuth_rad() const { return std::atan2(sensor_point.y(), sensor_point.x()); }
        double elevation_rad() const {
            return std::atan2(sensor_point.z(), sensor_point.head<2>().norm());
        }
    };

}

#endif
