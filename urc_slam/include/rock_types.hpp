#ifndef ROCK_TYPES_HPP_
#define ROCK_TYPES_HPP_

#include <cmath>
#include <vector>
#include <Eigen/Core>

namespace urc_slam {

    // A planar scan in the style of sensor_msgs/LaserScan, kept ROS-free so the
    // extractor can be unit-tested without ROS. Beam i has bearing
    // angle_min_rad + i * angle_increment_rad, measured counter-clockwise from
    // the sensor +x axis.
    struct PlanarScan {
        std::vector<float> ranges_m;
        double angle_min_rad = 0.0;
        double angle_increment_rad = 0.0;
        double range_min_m = 0.0;
        double range_max_m = 0.0;
    };

    // One rock seen in one scan, in the SENSOR frame (x forward, y left).
    struct RockObservation {
        double range_m = 0.0;
        double bearing_rad = 0.0;
        // Diameter estimate of the visible arc, not of the true rock.
        double size_m = 0.0;

        Eigen::Vector2d sensorPoint() const {
            return {range_m * std::cos(bearing_rad), range_m * std::sin(bearing_rad)};
        }
    };

}

#endif
