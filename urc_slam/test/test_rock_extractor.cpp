#include <cmath>
#include <iostream>

#include "mini_check.hpp"
#include "rock_extractor.hpp"

namespace {

    struct Circle {
        double x;
        double y;
        double radius;
    };

    // Distance along a ray from the origin to the circle's near side, or -1.
    double rayHit(double angle, const Circle &circle) {
        const double dx = std::cos(angle);
        const double dy = std::sin(angle);
        const double along = circle.x * dx + circle.y * dy;
        const double closest_sq = circle.x * circle.x + circle.y * circle.y - along * along;
        const double depth_sq = circle.radius * circle.radius - closest_sq;
        if (along <= 0.0 || depth_sq < 0.0) {
            return -1.0;
        }
        return along - std::sqrt(depth_sq);
    }

    urc_slam::PlanarScan syntheticScan(const std::vector<Circle> &circles) {
        urc_slam::PlanarScan scan;
        scan.angle_min_rad = -M_PI / 2.0;
        scan.angle_increment_rad = 0.25 * M_PI / 180.0;
        scan.range_min_m = 0.1;
        scan.range_max_m = 30.0;
        const int beams = static_cast<int>(M_PI / scan.angle_increment_rad) + 1;
        for (int i = 0; i < beams; ++i) {
            const double angle = scan.angle_min_rad + i * scan.angle_increment_rad;
            float range = std::numeric_limits<float>::infinity();
            for (const Circle &circle : circles) {
                const double hit = rayHit(angle, circle);
                if (hit > 0.0 && hit < range) {
                    range = static_cast<float>(hit);
                }
            }
            scan.ranges_m.push_back(range);
        }
        return scan;
    }

    bool near(const urc_slam::RockObservation &rock, const Circle &circle) {
        const double true_range = std::hypot(circle.x, circle.y);
        const double true_bearing = std::atan2(circle.y, circle.x);
        // The centroid of the visible near arc lies between the near surface and
        // the true centre (see the TODO in rock_extractor.cpp), so the range is
        // only guaranteed to land within one radius short of the centre.
        return rock.range_m < true_range &&
               rock.range_m > true_range - circle.radius &&
               std::abs(rock.bearing_rad - true_bearing) < 0.03;
    }

}

int main() {
    const std::vector<Circle> circles{{3.0, 1.0, 0.3}, {5.0, -1.5, 0.4}};

    urc_slam::RockExtractor extractor{urc_slam::RockExtractorParams{}};
    const auto rocks = extractor.extract(syntheticScan(circles));

    CHECK(rocks.size() == 2);
    // Output is ordered by beam angle: the -1.5 m rock is swept first.
    CHECK(near(rocks[0], circles[1]));
    CHECK(near(rocks[1], circles[0]));
    CHECK(rocks[0].size_m > 0.3 && rocks[0].size_m < 0.9);

    // Empty scan and a wall-sized object must not produce rocks.
    CHECK(extractor.extract(syntheticScan({})).empty());
    CHECK(extractor.extract(syntheticScan({{4.0, 0.0, 3.0}})).empty());

    std::cout << "test_rock_extractor passed" << std::endl;
    return 0;
}
