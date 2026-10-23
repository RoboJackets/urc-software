#include "rock_landmark_ros.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>

namespace urc_slam {

    namespace {

        constexpr double kMinimumMarkerRadiusM = 0.1;
        constexpr int kLogThrottleMs = 2000;

        RockExtractorParams declareExtractorParams(rclcpp::Node &node) {
            RockExtractorParams p;
            const std::string prefix = "rock_landmarks.extractor.";
            p.min_range_m = node.declare_parameter<double>(prefix + "min_range_m", p.min_range_m);
            p.max_range_m = node.declare_parameter<double>(prefix + "max_range_m", p.max_range_m);
            p.ground_cell_size_m = node.declare_parameter<double>(prefix + "ground_cell_size_m", p.ground_cell_size_m);
            p.ground_clearance_m = node.declare_parameter<double>(prefix + "ground_clearance_m", p.ground_clearance_m);
            p.cluster_tolerance_m = node.declare_parameter<double>(prefix + "cluster_tolerance_m", p.cluster_tolerance_m);
            p.min_points = static_cast<std::size_t>(node.declare_parameter<int>(prefix + "min_points", static_cast<int>(p.min_points)));
            p.max_points = static_cast<std::size_t>(node.declare_parameter<int>(prefix + "max_points", static_cast<int>(p.max_points)));
            p.min_radius_m = node.declare_parameter<double>(prefix + "min_radius_m", p.min_radius_m);
            p.max_radius_m = node.declare_parameter<double>(prefix + "max_radius_m", p.max_radius_m);
            p.max_height_m = node.declare_parameter<double>(prefix + "max_height_m", p.max_height_m);
            p.max_sphere_rms_m = node.declare_parameter<double>(prefix + "max_sphere_rms_m", p.max_sphere_rms_m);
            return p;
        }

        AssociatorParams declareAssociatorParams(rclcpp::Node &node) {
            AssociatorParams p;
            const std::string prefix = "rock_landmarks.associator.";
            p.gate_confidence = node.declare_parameter<double>(prefix + "gate_confidence", p.gate_confidence);
            p.recently_seen_window_poses = static_cast<std::size_t>(node.declare_parameter<int>(
                prefix + "recently_seen_window_poses", static_cast<int>(p.recently_seen_window_poses)));
            p.min_pairings_for_reassociation = static_cast<std::size_t>(node.declare_parameter<int>(
                prefix + "min_pairings_for_reassociation", static_cast<int>(p.min_pairings_for_reassociation)));
            p.ambiguity_margin = node.declare_parameter<double>(prefix + "ambiguity_margin", p.ambiguity_margin);
            p.max_search_nodes = static_cast<std::size_t>(node.declare_parameter<int>(
                prefix + "max_search_nodes", static_cast<int>(p.max_search_nodes)));
            return p;
        }

        RockLandmarkParams declareParams(rclcpp::Node &node) {
            RockLandmarkParams params;
            params.extractor = declareExtractorParams(node);
            params.associator = declareAssociatorParams(node);
            // NaN default on purpose: validate() rejects it until the noise is measured.
            params.noise.range_sigma_m = node.declare_parameter<double>(
                "rock_landmarks.noise.range_sigma_m", std::numeric_limits<double>::quiet_NaN());
            params.noise.bearing_sigma_rad = node.declare_parameter<double>(
                "rock_landmarks.noise.bearing_sigma_rad", std::numeric_limits<double>::quiet_NaN());
            params.huber_kernel_width = node.declare_parameter<double>(
                "rock_landmarks.huber_kernel_width", params.huber_kernel_width);
            return params;
        }

        visualization_msgs::msg::Marker baseMarker(
            const std::string &frame_id, const builtin_interfaces::msg::Time &stamp,
            int id, int type, const gtsam::Point3 &position
        ) {
            visualization_msgs::msg::Marker marker;
            marker.header.frame_id = frame_id;
            marker.header.stamp = stamp;
            marker.ns = "rock_landmarks";
            marker.id = id;
            marker.type = type;
            marker.action = visualization_msgs::msg::Marker::ADD;
            marker.pose.position.x = position.x();
            marker.pose.position.y = position.y();
            marker.pose.position.z = position.z();
            marker.pose.orientation.w = 1.0;
            return marker;
        }

    }

    std::unique_ptr<RockLandmarkPipeline> createRockPipeline(rclcpp::Node &node) {
        const bool enabled = node.declare_parameter<bool>("rock_landmarks.enabled", false);
        const RockLandmarkParams params = declareParams(node);
        if (!enabled) {
            return nullptr;
        }

        // Association diagnostics can fire every sweep; throttle so logging
        // never dominates the LiDAR callback.
        LogSink log = [&node](const std::string &message) {
            RCLCPP_INFO_THROTTLE(node.get_logger(), *node.get_clock(), kLogThrottleMs, "%s", message.c_str());
        };
        return std::make_unique<RockLandmarkPipeline>(params, std::move(log));
    }

    PointCloud3d toPointCloud3d(const LidarFrontend::Cloud &cloud) {
        PointCloud3d points;
        points.reserve(cloud.size());
        for (const LidarFrontend::Point &point : cloud.points) {
            if (std::isfinite(point.x) && std::isfinite(point.y) && std::isfinite(point.z)) {
                points.emplace_back(point.x, point.y, point.z);
            }
        }
        return points;
    }

    visualization_msgs::msg::MarkerArray makeLandmarkMarkers(
        const std::vector<LandmarkSnapshot> &landmarks,
        const std::string &frame_id,
        const builtin_interfaces::msg::Time &stamp
    ) {
        visualization_msgs::msg::MarkerArray array;
        array.markers.reserve(2 * landmarks.size());
        for (const LandmarkSnapshot &landmark : landmarks) {
            const double radius = std::max(landmark.radius_m, kMinimumMarkerRadiusM);
            // Distinct, stable ids so rviz updates a landmark in place as it is refined.
            const int sphere_id = static_cast<int>(2 * landmark.id);

            auto sphere = baseMarker(frame_id, stamp, sphere_id,
                                     visualization_msgs::msg::Marker::SPHERE, landmark.position);
            sphere.scale.x = sphere.scale.y = sphere.scale.z = 2.0 * radius;
            sphere.color.r = 1.0F;
            sphere.color.g = 0.5F;
            sphere.color.b = 0.0F;
            sphere.color.a = 0.8F;
            array.markers.push_back(sphere);

            auto label = baseMarker(frame_id, stamp, sphere_id + 1,
                                    visualization_msgs::msg::Marker::TEXT_VIEW_FACING,
                                    landmark.position + gtsam::Point3(0.0, 0.0, radius + 0.2));
            label.text = "L" + std::to_string(landmark.id);
            label.scale.z = 0.3;
            label.color.r = label.color.g = label.color.b = label.color.a = 1.0F;
            array.markers.push_back(label);
        }
        return array;
    }

}
