#include "point_clustering.hpp"

#include <array>
#include <cmath>
#include <cstdint>
#include <unordered_map>

namespace urc_slam {

    namespace {

        using VoxelIndex = std::array<int, 3>;

        struct VoxelHash {
            std::size_t operator()(const VoxelIndex &voxel) const {
                // Large odd primes spread neighbouring voxels across buckets.
                return static_cast<std::size_t>(
                    (static_cast<std::uint64_t>(static_cast<std::uint32_t>(voxel[0])) * 73856093ULL) ^
                    (static_cast<std::uint64_t>(static_cast<std::uint32_t>(voxel[1])) * 19349663ULL) ^
                    (static_cast<std::uint64_t>(static_cast<std::uint32_t>(voxel[2])) * 83492791ULL));
            }
        };

        using VoxelGrid = std::unordered_map<VoxelIndex, std::vector<std::size_t>, VoxelHash>;

        VoxelIndex voxelOf(const Eigen::Vector3d &point, double voxel_size_m) {
            return {static_cast<int>(std::floor(point.x() / voxel_size_m)),
                    static_cast<int>(std::floor(point.y() / voxel_size_m)),
                    static_cast<int>(std::floor(point.z() / voxel_size_m))};
        }

        // Unvisited points within tolerance of `points[index]`, found by
        // scanning the 27 surrounding voxels (voxel size == tolerance).
        std::vector<std::size_t> neighboursWithin(
            const std::vector<ElevatedPoint> &points, const VoxelGrid &grid,
            std::size_t index, double tolerance_m
        ) {
            std::vector<std::size_t> found;
            const VoxelIndex center = voxelOf(points[index].point, tolerance_m);
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dz = -1; dz <= 1; ++dz) {
                        const auto voxel = grid.find({center[0] + dx, center[1] + dy, center[2] + dz});
                        if (voxel == grid.end()) {
                            continue;
                        }
                        for (std::size_t other : voxel->second) {
                            if ((points[other].point - points[index].point).norm() <= tolerance_m) {
                                found.push_back(other);
                            }
                        }
                    }
                }
            }
            return found;
        }

    }

    std::vector<std::vector<std::size_t>> clusterPoints(
        const std::vector<ElevatedPoint> &points, double tolerance_m
    ) {
        VoxelGrid grid;
        for (std::size_t i = 0; i < points.size(); ++i) {
            grid[voxelOf(points[i].point, tolerance_m)].push_back(i);
        }

        std::vector<bool> visited(points.size(), false);
        std::vector<std::vector<std::size_t>> clusters;
        for (std::size_t seed = 0; seed < points.size(); ++seed) {
            if (visited[seed]) {
                continue;
            }
            visited[seed] = true;
            std::vector<std::size_t> cluster{seed};
            // `cluster` doubles as the BFS queue: it grows while we walk it.
            for (std::size_t next = 0; next < cluster.size(); ++next) {
                for (std::size_t neighbour : neighboursWithin(points, grid, cluster[next], tolerance_m)) {
                    if (!visited[neighbour]) {
                        visited[neighbour] = true;
                        cluster.push_back(neighbour);
                    }
                }
            }
            clusters.push_back(std::move(cluster));
        }
        return clusters;
    }

}
