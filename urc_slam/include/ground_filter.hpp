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
    // Ground references are the lowest point of the point's grid cell and of its
    // 8 neighbours (cells are `cell_size_m` wide), so a rock wider than one cell
    // still sees bare ground. Height above a reference q is
    //   p.z - q.z - s * |p.xy - q.xy|
    // where s is the local terrain slope (rise/run) from a plane fit through
    // those lowest points, capped at `max_slope`. The point's height is the
    // largest over its references. `max_slope` = 0 gives plain lowest-neighbour
    // filtering.
    std::vector<ElevatedPoint> removeGround(
        const PointCloud3d &cloud, double cell_size_m, double clearance_m, double max_slope);

}

#endif
