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
        // Best estimate of the rock's centre: the fitted sphere centre when the
        // fit was trustworthy, else the centroid of the visible points.
        Eigen::Vector3d sensor_point = Eigen::Vector3d::Zero();
        // Fitted radius, or half the horizontal extent when the fit was rejected.
        double radius_m = 0.0;
        // Highest visible point above the locally estimated ground.
        double height_m = 0.0;
        bool center_from_sphere_fit = false;

        double range_m() const { return sensor_point.norm(); }
        double azimuth_rad() const { return std::atan2(sensor_point.y(), sensor_point.x()); }
        double elevation_rad() const {
            return std::atan2(sensor_point.z(), sensor_point.head<2>().norm());
        }
    };

}

#endif
