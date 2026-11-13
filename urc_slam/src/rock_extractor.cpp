#include "rock_extractor.hpp"

#include <algorithm>
#include <cmath>
#include <optional>

#include "ground_filter.hpp"
#include "point_clustering.hpp"
#include "sphere_fit.hpp"

namespace urc_slam {

    namespace {

        PointCloud3d withinSensorWindow(const PointCloud3d &cloud, const RockExtractorParams &params) {
            PointCloud3d kept;
            kept.reserve(cloud.size());
            for (const Eigen::Vector3d &point : cloud) {
                const double range = point.norm();
                const double elevation_rad = std::atan2(point.z(), point.head<2>().norm());
                if (range >= params.min_range_m && range <= params.max_range_m &&
                    elevation_rad <= params.max_elevation_rad) {
                    kept.push_back(point);
                }
            }
            return kept;
        }

        struct ClusterShape {
            PointCloud3d points;
            Eigen::Vector3d centroid = Eigen::Vector3d::Zero();
            double horizontal_extent_m = 0.0;
            double height_m = 0.0;
        };

        ClusterShape describeCluster(
            const std::vector<ElevatedPoint> &elevated, const std::vector<std::size_t> &indices
        ) {
            ClusterShape shape;
            Eigen::Vector2d low = Eigen::Vector2d::Constant(INFINITY);
            Eigen::Vector2d high = Eigen::Vector2d::Constant(-INFINITY);
            for (std::size_t index : indices) {
                const ElevatedPoint &entry = elevated[index];
                shape.points.push_back(entry.point);
                shape.centroid += entry.point;
                shape.height_m = std::max(shape.height_m, entry.height_m);
                low = low.cwiseMin(entry.point.head<2>());
                high = high.cwiseMax(entry.point.head<2>());
            }
            shape.centroid /= static_cast<double>(indices.size());
            shape.horizontal_extent_m = (high - low).maxCoeff();
            return shape;
        }

        bool isRockSized(const ClusterShape &shape, const RockExtractorParams &params) {
            return shape.points.size() >= params.min_points &&
                   shape.points.size() <= params.max_points &&
                   shape.height_m <= params.max_height_m &&
                   shape.horizontal_extent_m >= params.min_radius_m &&
                   shape.horizontal_extent_m <= 2.0 * params.max_radius_m;
        }

        // Metres to the nearest window limit; the elevation limit is measured
        // as arc length at the point's range.
        double distanceToWindowEdge(const Eigen::Vector3d &point, const RockExtractorParams &params) {
            const double range = point.norm();
            const double elevation_rad = std::atan2(point.z(), point.head<2>().norm());
            return std::min({range - params.min_range_m, params.max_range_m - range,
                             (params.max_elevation_rad - elevation_rad) * range});
        }

        bool isClippedByWindow(const ClusterShape &shape, const RockExtractorParams &params) {
            return std::any_of(shape.points.begin(), shape.points.end(),
                [&](const Eigen::Vector3d &point) {
                    return distanceToWindowEdge(point, params) < params.window_edge_margin_m;
                });
        }

        // Accepts a sphere only if it looks like a round object seen from outside.
        std::optional<SphereFit> trustworthySphere(
            const ClusterShape &shape, const RockExtractorParams &params
        ) {
            const std::optional<SphereFit> fit = fitSphere(shape.points);
            if (!fit || fit->radius_m < params.min_radius_m || fit->radius_m > params.max_radius_m ||
                fit->rms_residual_m > params.max_sphere_rms_m) {
                return std::nullopt;
            }
            // Viewed from outside, the centre lies farther from the sensor than
            // the visible surface. A nearer centre is an inverted (concave) fit,
            // e.g. to a bank or the inside of a wall.
            if (fit->center.norm() <= shape.centroid.norm()) {
                return std::nullopt;
            }
            return fit;
        }

        // No observation without a trustworthy sphere: the visible-point
        // centroid sits on the near cap, biased toward the sensor by roughly
        // 0.8 * radius, which would corrupt the landmark it is associated with.
        std::optional<RockObservation> observe(const ClusterShape &shape, const RockExtractorParams &params) {
            // TODO(AJ): A 3D LiDAR still sees only the near cap of a rock.
            // Irregular rocks bias the sphere fit toward the sensor; work out
            // the effect on re-observation from the opposite side.
            const std::optional<SphereFit> fit = trustworthySphere(shape, params);
            if (!fit) {
                return std::nullopt;
            }
            RockObservation rock;
            rock.sensor_point = fit->center;
            rock.radius_m = fit->radius_m;
            rock.height_m = shape.height_m;
            return rock;
        }

    }

    RockExtractor::RockExtractor(const RockExtractorParams &params)
        : params_(params) {}

    bool RockExtractor::attitudeIsUsable(double /*roll_rad*/, double /*pitch_rad*/) const {
        return true;
    }

    std::vector<RockObservation> RockExtractor::extract(const PointCloud3d &cloud) const {
        const std::vector<ElevatedPoint> elevated = removeGround(
            withinSensorWindow(cloud, params_), params_.ground_cell_size_m, params_.ground_clearance_m,
            params_.ground_max_slope);

        std::vector<RockObservation> rocks;
        for (const std::vector<std::size_t> &indices : clusterPoints(elevated, params_.cluster_tolerance_m)) {
            const ClusterShape shape = describeCluster(elevated, indices);
            if (!isRockSized(shape, params_) || isClippedByWindow(shape, params_)) {
                continue;
            }
            if (const std::optional<RockObservation> rock = observe(shape, params_)) {
                rocks.push_back(*rock);
            }
        }
        return rocks;
    }

}
