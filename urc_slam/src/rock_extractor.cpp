#include "rock_extractor.hpp"

#include <algorithm>
#include <cmath>
#include <optional>

#include "ground_filter.hpp"
#include "point_clustering.hpp"
#include "sphere_fit.hpp"

namespace urc_slam {

    namespace {

        PointCloud3d withinRangeBand(const PointCloud3d &cloud, const RockExtractorParams &params) {
            PointCloud3d kept;
            kept.reserve(cloud.size());
            for (const Eigen::Vector3d &point : cloud) {
                const double range = point.norm();
                if (range >= params.min_range_m && range <= params.max_range_m) {
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

        RockObservation observe(const ClusterShape &shape, const RockExtractorParams &params) {
            RockObservation rock;
            rock.height_m = shape.height_m;

            // TODO(AJ): A 3D LiDAR still sees only the near cap of a rock. The
            // sphere fit removes most of the viewing-direction shift of the
            // centroid for round rocks, but irregular rocks bias the fit toward
            // the sensor, and the centroid fallback is biased as before. Work out
            // the effect on re-observation from the opposite side.
            if (const auto fit = trustworthySphere(shape, params)) {
                rock.sensor_point = fit->center;
                rock.radius_m = fit->radius_m;
                rock.center_from_sphere_fit = true;
            } else {
                rock.sensor_point = shape.centroid;
                rock.radius_m = 0.5 * shape.horizontal_extent_m;
            }
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
            withinRangeBand(cloud, params_), params_.ground_cell_size_m, params_.ground_clearance_m);

        std::vector<RockObservation> rocks;
        for (const std::vector<std::size_t> &indices : clusterPoints(elevated, params_.cluster_tolerance_m)) {
            const ClusterShape shape = describeCluster(elevated, indices);
            if (isRockSized(shape, params_)) {
                rocks.push_back(observe(shape, params_));
            }
        }
        return rocks;
    }

}
