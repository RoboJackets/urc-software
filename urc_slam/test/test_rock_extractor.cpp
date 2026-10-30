#include <cmath>
#include <iostream>
#include <random>

#include "mini_check.hpp"
#include "rock_extractor.hpp"

namespace {

    struct Rock {
        Eigen::Vector3d center;
        double radius;
    };

    // Flat ground at z = 0 sampled on a grid, then a sphere's surface as seen
    // from the origin: only the hemisphere facing the sensor is generated,
    // which is what a real sweep would hit.
    urc_slam::PointCloud3d syntheticSweep(const std::vector<Rock> &rocks, double sensor_height_m) {
        std::mt19937 rng(7);
        std::normal_distribution<double> noise(0.0, 0.005);
        urc_slam::PointCloud3d cloud;
        const Eigen::Vector3d sensor(0.0, 0.0, sensor_height_m);

        for (double x = 1.0; x <= 12.0; x += 0.1) {
            for (double y = -6.0; y <= 6.0; y += 0.1) {
                cloud.emplace_back(x, y, noise(rng));
            }
        }
        for (const Rock &rock : rocks) {
            for (double polar = 0.0; polar < M_PI; polar += 0.04) {
                for (double azimuth = 0.0; azimuth < 2.0 * M_PI; azimuth += 0.04) {
                    const Eigen::Vector3d normal(std::sin(polar) * std::cos(azimuth),
                                                 std::sin(polar) * std::sin(azimuth),
                                                 std::cos(polar));
                    const Eigen::Vector3d surface = rock.center + rock.radius * normal;
                    // Facing the sensor and above the ground plane.
                    if (normal.dot(sensor - surface) > 0.0 && surface.z() > 0.02) {
                        cloud.push_back(surface + Eigen::Vector3d::Constant(noise(rng)));
                    }
                }
            }
        }
        // Sensor frame is the origin here, so shift by the mounting height.
        for (Eigen::Vector3d &point : cloud) {
            point.z() -= sensor_height_m;
        }
        return cloud;
    }

    bool matches(const urc_slam::RockObservation &rock, const Eigen::Vector3d &truth, double tolerance_m) {
        return (rock.sensor_point - truth).norm() < tolerance_m;
    }

}

int main() {
    const double sensor_height_m = 1.0;
    const std::vector<Rock> rocks{{{4.0, 1.5, 0.3}, 0.35}, {{7.0, -2.0, 0.4}, 0.45}};
    const urc_slam::RockExtractor extractor{urc_slam::RockExtractorParams{}};

    // Two spherical rocks on flat ground give two observations whose fitted
    // centres land close to the true centres, in the sensor frame (z is
    // relative to the sensor, hence the -sensor_height_m).
    const auto found = extractor.extract(syntheticSweep(rocks, sensor_height_m));
    CHECK(found.size() == 2);

    for (const Rock &rock : rocks) {
        const Eigen::Vector3d truth = rock.center - Eigen::Vector3d(0.0, 0.0, sensor_height_m);
        bool matched = false;
        for (const auto &observation : found) {
            if (matches(observation, truth, 0.08)) {
                matched = true;
                CHECK_NEAR(observation.radius_m, rock.radius, 0.08);
                std::cout << "rock r=" << rock.radius << ": centre error sphere fit "
                          << (observation.sensor_point - truth).norm() << " m" << std::endl;
            }
        }
        CHECK(matched);
    }

    // A rejected sphere fit yields no observation rather than a centroid
    // biased toward the sensor.
    urc_slam::RockExtractorParams no_fit;
    no_fit.max_sphere_rms_m = 0.0;
    CHECK(urc_slam::RockExtractor(no_fit).extract(syntheticSweep(rocks, sensor_height_m)).empty());

    // Bare ground produces nothing.
    CHECK(extractor.extract(syntheticSweep({}, sensor_height_m)).empty());

    // A wall-sized object (radius 3) is rejected by the size filter.
    CHECK(extractor.extract(syntheticSweep({{{8.0, 0.0, 1.0}, 3.0}}, sensor_height_m)).empty());

    std::cout << "test_rock_extractor passed" << std::endl;
    return 0;
}
