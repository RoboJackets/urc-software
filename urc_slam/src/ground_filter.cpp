#include "ground_filter.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <unordered_map>

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

        CellIndex cellOf(const Eigen::Vector3d &point, double cell_size_m) {
            return {static_cast<int>(std::floor(point.x() / cell_size_m)),
                    static_cast<int>(std::floor(point.y() / cell_size_m))};
        }

    }

    std::vector<ElevatedPoint> removeGround(
        const PointCloud3d &cloud, double cell_size_m, double clearance_m
    ) {
        std::unordered_map<CellIndex, double, CellHash> lowest_z;
        for (const Eigen::Vector3d &point : cloud) {
            const auto [it, inserted] = lowest_z.try_emplace(cellOf(point, cell_size_m), point.z());
            if (!inserted) {
                it->second = std::min(it->second, point.z());
            }
        }

        std::vector<ElevatedPoint> elevated;
        for (const Eigen::Vector3d &point : cloud) {
            const CellIndex cell = cellOf(point, cell_size_m);
            double ground_z = std::numeric_limits<double>::infinity();
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    const auto neighbour = lowest_z.find({cell.first + dx, cell.second + dy});
                    if (neighbour != lowest_z.end()) {
                        ground_z = std::min(ground_z, neighbour->second);
                    }
                }
            }
            const double height_m = point.z() - ground_z;
            if (height_m > clearance_m) {
                elevated.push_back({point, height_m});
            }
        }
        return elevated;
    }

}
