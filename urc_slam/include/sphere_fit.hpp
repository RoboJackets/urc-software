#ifndef SPHERE_FIT_HPP_
#define SPHERE_FIT_HPP_

#include <optional>
#include <vector>
#include <Eigen/Core>

namespace urc_slam {

    struct SphereFit {
        Eigen::Vector3d center;
        double radius_m;
        // Root-mean-square distance of the points from the fitted surface.
        double rms_residual_m;
    };

    // Geometric least-squares sphere fit: minimises the sum of squared
    // point-to-surface distances (|p - c| - r)^2 by Levenberg-Marquardt,
    // starting from the linear algebraic fit |p|^2 = 2 c.p + (r^2 - |c|^2).
    // The refinement removes the algebraic fit's small-cap bias; iterations
    // are capped, so the cost stays bounded per call.
    // Returns nullopt for fewer than 4 points or a degenerate (planar or
    // collinear) set.
    std::optional<SphereFit> fitSphere(const std::vector<Eigen::Vector3d> &points);

}

#endif
