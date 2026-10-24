#ifndef LOOP_CLOSURE_ROS_HPP_
#define LOOP_CLOSURE_ROS_HPP_

#include <memory>
#include <rclcpp/rclcpp.hpp>

#include "lidar_frontend.hpp"
#include "loop_closure_detector.hpp"

namespace urc_slam {

    // Declares the loop_closure.* parameters on `node`. Returns nullptr when
    // loop_closure.enabled is false. `frontend` must outlive the detector.
    std::unique_ptr<LoopClosureDetector> createLoopClosureDetector(
        rclcpp::Node &node, const LidarFrontend &frontend);

}

#endif
