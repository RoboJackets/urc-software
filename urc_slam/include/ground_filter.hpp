#ifndef GROUND_FILTER_HPP_
#define GROUND_FILTER_HPP_

#include <vector>

#include "rock_types.hpp"

namespace urc_slam {

    struct ElevatedPoint {
        Eigen::Vector3d point;
        // Height above the local ground estimate, always >= 0.
        double height_m;
    };

    // Keeps points that stand more than `clearance_m` above the local ground.
    //
    // Local ground = the lowest z in the point's grid cell or any of its 8
    // neighbours (cells are `cell_size_m` wide). Searching the neighbours
    // matters: a rock wider than one cell has no bare ground inside its own cell.
    // Weakness: on a slope the uphill cell's "ground" is taken from the lower
    // neighbour, so slope * cell_size_m should stay below clearance_m. Rougher
    // terrain needs a real ground model.
    std::vector<ElevatedPoint> removeGround(
        const PointCloud3d &cloud, double cell_size_m, double clearance_m);

}

#endif
