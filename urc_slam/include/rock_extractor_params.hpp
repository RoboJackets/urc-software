#ifndef ROCK_EXTRACTOR_PARAMS_HPP_
#define ROCK_EXTRACTOR_PARAMS_HPP_

#include <cstddef>

namespace urc_slam {

    struct RockExtractorParams {
        // First gate on every point. Beyond 2 m the 16-beam LiDAR puts too
        // few rings on a rock for a reliable sphere fit.
        double min_range_m = 1.0;
        double max_range_m = 2.0;
        // Points more than this far above the sensor's horizontal plane are
        // dropped: upward beams hit overhangs and distant terrain, never the
        // near side of a rock on the ground. Assumes the LiDAR is mounted
        // level on the rover, so sensor horizontal is robot horizontal.
        double max_elevation_rad = 0.2618;  // 15 deg
        // A cluster with any point closer than this to the range or elevation
        // limits is cut off by the window. The fit then sees a partial cap
        // whose centre and radius trade off along the line of sight, so the
        // cluster is dropped. Several times the LiDAR range noise.
        double window_edge_margin_m = 0.05;
        // See removeGround(). Terrain steeper than ground_max_slope (rise/run)
        // leaks (slope - ground_max_slope) * cell into rock candidates.
        double ground_cell_size_m = 0.5;
        double ground_clearance_m = 0.10;
        double ground_max_slope = 0.55;
        // Max gap between neighbouring points of one cluster. Must exceed the
        // LiDAR point spacing at max_range_m or far rocks shatter.
        double cluster_tolerance_m = 0.15;
        std::size_t min_points = 20;
        std::size_t max_points = 20000;
        // Plausible rock radii; also bound the sphere fit and, doubled, the
        // horizontal extent of a cluster.
        double min_radius_m = 0.1;
        double max_radius_m = 0.5;
        // Taller candidates are people, poles or walls, not rocks.
        double max_height_m = 1.5;
        // A sphere fit rougher than this is not a round rock; the cluster is dropped.
        double max_sphere_rms_m = 0.05;
    };

}

#endif
