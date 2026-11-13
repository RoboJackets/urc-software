#include "loop_closure_ros.hpp"

#include <string>
#include <utility>

namespace urc_slam {

    namespace {

        constexpr int kLogThrottleMs = 2000;

        std::size_t declareCount(rclcpp::Node &node, const std::string &name, std::size_t fallback) {
            return static_cast<std::size_t>(node.declare_parameter<int>(name, static_cast<int>(fallback)));
        }

        LoopClosureParams declareParams(rclcpp::Node &node) {
            LoopClosureParams p;
            const std::string prefix = "loop_closure.";
            LoopCandidateParams &c = p.candidates;
            c.base_radius_m = node.declare_parameter<double>(prefix + "base_radius_m", c.base_radius_m);
            c.sigma_scale = node.declare_parameter<double>(prefix + "sigma_scale", c.sigma_scale);
            c.max_radius_m = node.declare_parameter<double>(prefix + "max_radius_m", c.max_radius_m);
            c.min_index_gap = declareCount(node, prefix + "min_index_gap", c.min_index_gap);
            c.min_path_gap_m = node.declare_parameter<double>(prefix + "min_path_gap_m", c.min_path_gap_m);
            c.max_candidates = declareCount(node, prefix + "max_candidates", c.max_candidates);
            p.max_fitness_score = node.declare_parameter<double>(prefix + "max_fitness_score", p.max_fitness_score);
            p.gate_confidence = node.declare_parameter<double>(prefix + "gate_confidence", p.gate_confidence);
            p.huber_kernel_width = node.declare_parameter<double>(prefix + "huber_kernel_width", p.huber_kernel_width);
            p.attempt_every_n_keyframes = declareCount(node, prefix + "attempt_every_n_keyframes", p.attempt_every_n_keyframes);
            p.cooldown_keyframes = declareCount(node, prefix + "cooldown_keyframes", p.cooldown_keyframes);
            return p;
        }

    }

    std::unique_ptr<LoopClosureDetector> createLoopClosureDetector(
        rclcpp::Node &node, const LidarFrontend &frontend
    ) {
        const bool enabled = node.declare_parameter<bool>("loop_closure.enabled", false);
        const LoopClosureParams params = declareParams(node);
        if (!enabled) {
            return nullptr;
        }

        // Rejections can fire on every keyframe; throttle so logging never
        // dominates the LiDAR callback.
        LogSink log = [&node](const std::string &message) {
            RCLCPP_INFO_THROTTLE(node.get_logger(), *node.get_clock(), kLogThrottleMs, "%s", message.c_str());
        };
        return std::make_unique<LoopClosureDetector>(params, frontend, std::move(log));
    }

}
