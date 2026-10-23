#ifndef ROCK_EXTRACTOR_PARAMS_HPP_
#define ROCK_EXTRACTOR_PARAMS_HPP_

#include <cstddef>

namespace urc_slam {

    struct RockExtractorParams {
        // Points outside this range band are ignored (self-hits, sparse far returns).
        double min_range_m = 1.0;
        double max_range_m = 30.0;
        // See removeGround(): slope * ground_cell_size_m should stay below
        // ground_clearance_m or uphill ground leaks into the rock candidates.
        double ground_cell_size_m = 0.5;
        double ground_clearance_m = 0.10;
        // Max gap between neighbouring points of one cluster. Must exceed the
        // LiDAR point spacing at max_range_m or far rocks shatter.
        double cluster_tolerance_m = 0.15;
        std::size_t min_points = 20;
        std::size_t max_points = 20000;
        // Plausible rock radii; also bound the sphere fit and, doubled, the
        // horizontal extent of a cluster.
        double min_radius_m = 0.1;
        double max_radius_m = 1.0;
        // Taller candidates are people, poles or walls, not rocks.
        double max_height_m = 1.5;
        // A sphere fit rougher than this is not a round rock; fall back to centroid.
        double max_sphere_rms_m = 0.05;
    };

}

#endif
