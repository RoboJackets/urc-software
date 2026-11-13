#include "ground_filter.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <unordered_map>
#include <Eigen/LU>

namespace urc_slam {

    namespace {

        using CellIndex = std::pair<int, int>;

        struct CellHash {
            std::size_t operator()(const CellIndex &cell) const {
                const std::uint64_t x = static_cast<std::uint32_t>(cell.first);
                const std::uint64_t y = static_cast<std::uint32_t>(cell.second);
                return static_cast<std::size_t>((x << 32) ^ y);
            }
        };

        using LowestPoints = std::unordered_map<CellIndex, Eigen::Vector3d, CellHash>;

        CellIndex cellOf(const Eigen::Vector3d &point, double cell_size_m) {
            return {static_cast<int>(std::floor(point.x() / cell_size_m)),
                    static_cast<int>(std::floor(point.y() / cell_size_m))};
        }

        template <typename Visit>
        void forEachNeighbourLowest(const LowestPoints &lowest, const CellIndex &cell, Visit visit) {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    const auto neighbour = lowest.find({cell.first + dx, cell.second + dy});
                    if (neighbour != lowest.end()) {
                        visit(neighbour->second);
                    }
                }
            }
        }

        // Gradient magnitude of the least-squares plane through the 3x3
        // neighbourhood's lowest points. Capped at max_slope so a rock top
        // among those points cannot tilt the ground model enough to hide the rock.
        double localSlope(const LowestPoints &lowest, const CellIndex &cell, double max_slope) {
            Eigen::Vector3d mean = Eigen::Vector3d::Zero();
            int count = 0;
            forEachNeighbourLowest(lowest, cell, [&](const Eigen::Vector3d &q) {
                mean += q;
                ++count;
            });
            if (count < 3) {
                return 0.0;
            }
            mean /= count;

            Eigen::Matrix2d normal = Eigen::Matrix2d::Zero();
            Eigen::Vector2d rhs = Eigen::Vector2d::Zero();
            forEachNeighbourLowest(lowest, cell, [&](const Eigen::Vector3d &q) {
                const Eigen::Vector3d d = q - mean;
                normal += d.head<2>() * d.head<2>().transpose();
                rhs += d.head<2>() * d.z();
            });
            const Eigen::FullPivLU<Eigen::Matrix2d> lu(normal);
            if (!lu.isInvertible()) {
                return 0.0;
            }
            return std::min(lu.solve(rhs).norm(), max_slope);
        }

    }

    std::vector<ElevatedPoint> removeGround(
        const PointCloud3d &cloud, double cell_size_m, double clearance_m, double max_slope
    ) {
        LowestPoints lowest;
        for (const Eigen::Vector3d &point : cloud) {
            const auto [it, inserted] = lowest.try_emplace(cellOf(point, cell_size_m), point);
            if (!inserted && point.z() < it->second.z()) {
                it->second = point;
            }
        }

        std::unordered_map<CellIndex, double, CellHash> slope;
        slope.reserve(lowest.size());
        for (const auto &[cell, unused] : lowest) {
            slope.emplace(cell, localSlope(lowest, cell, max_slope));
        }

        std::vector<ElevatedPoint> elevated;
        for (const Eigen::Vector3d &point : cloud) {
            const CellIndex cell = cellOf(point, cell_size_m);
            const double cell_slope = slope.at(cell);
            double height_m = -std::numeric_limits<double>::infinity();
            forEachNeighbourLowest(lowest, cell, [&](const Eigen::Vector3d &q) {
                const double run_m = (point - q).head<2>().norm();
                height_m = std::max(height_m, point.z() - q.z() - cell_slope * run_m);
            });
            if (height_m > clearance_m) {
                elevated.push_back({point, height_m});
            }
        }
        return elevated;
    }

}
