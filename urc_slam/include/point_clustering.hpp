#ifndef POINT_CLUSTERING_HPP_
#define POINT_CLUSTERING_HPP_

#include <cstddef>
#include <vector>

#include "ground_filter.hpp"

namespace urc_slam {

    // Euclidean clustering: two points share a cluster if a chain of points,
    // each within `tolerance_m` of the next, links them. Uses a voxel hash so
    // the cost is roughly linear in the number of points.
    // Returns, per cluster, indices into `points`.
    std::vector<std::vector<std::size_t>> clusterPoints(
        const std::vector<ElevatedPoint> &points, double tolerance_m);

}

#endif
