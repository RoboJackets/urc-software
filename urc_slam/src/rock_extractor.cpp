#include "rock_extractor.hpp"

#include <algorithm>
#include <cmath>
#include <Eigen/Core>

namespace urc_slam {

    namespace {

        bool isUsableRange(float range, const PlanarScan &scan) {
            // NaN/inf are how LaserScan encodes "no return"; they also break
            // clusters, because a gap means two different objects.
            return std::isfinite(range) &&
                   range >= scan.range_min_m && range <= scan.range_max_m;
        }

        bool isRockSized(const std::vector<Eigen::Vector2d> &points,
                         double extent_m, const RockExtractorParams &params) {
            return points.size() >= params.min_points &&
                   points.size() <= params.max_points &&
                   extent_m >= params.min_extent_m &&
                   extent_m <= params.max_extent_m;
        }

        // Returns true and fills `rock` when the cluster passes the size tests.
        bool summarizeCluster(const std::vector<Eigen::Vector2d> &points,
                              const RockExtractorParams &params,
                              RockObservation &rock) {
            Eigen::Vector2d centroid = Eigen::Vector2d::Zero();
            for (const Eigen::Vector2d &point : points) {
                centroid += point;
            }
            centroid /= static_cast<double>(points.size());

            // Twice the largest centroid distance is a linear-time diameter
            // estimate; the exact diameter needs all point pairs.
            double largest_radius = 0.0;
            for (const Eigen::Vector2d &point : points) {
                largest_radius = std::max(largest_radius, (point - centroid).norm());
            }
            const double extent_m = 2.0 * largest_radius;

            if (!isRockSized(points, extent_m, params)) {
                return false;
            }

            // TODO(AJ): A 2D LiDAR sees only the near arc of a rock, so the
            // centroid is biased toward the sensor and shifts with viewing direction.
            // Work out the effect on re-observation from the opposite side.
            rock.range_m = centroid.norm();
            rock.bearing_rad = std::atan2(centroid.y(), centroid.x());
            rock.size_m = extent_m;
            return true;
        }

    }

    RockExtractor::RockExtractor(const RockExtractorParams &params)
        : params_(params) {}

    bool RockExtractor::scanPlaneIsUsable(double /*roll_rad*/, double /*pitch_rad*/) const {
        return true;
    }

    std::vector<RockObservation> RockExtractor::extract(const PlanarScan &scan) const {
        std::vector<RockObservation> rocks;
        std::vector<Eigen::Vector2d> cluster;
        float previous_range = 0.0F;

        const auto flushCluster = [&]() {
            RockObservation rock;
            if (!cluster.empty() && summarizeCluster(cluster, params_, rock)) {
                rocks.push_back(rock);
            }
            cluster.clear();
        };

        for (std::size_t beam = 0; beam < scan.ranges_m.size(); ++beam) {
            const float range = scan.ranges_m[beam];
            if (!isUsableRange(range, scan)) {
                flushCluster();
                continue;
            }

            if (!cluster.empty() &&
                std::abs(range - previous_range) > params_.cluster_range_jump_m) {
                flushCluster();
            }

            const double angle = scan.angle_min_rad +
                                 static_cast<double>(beam) * scan.angle_increment_rad;
            cluster.emplace_back(range * std::cos(angle), range * std::sin(angle));
            previous_range = range;
        }
        flushCluster();

        return rocks;
    }

}
