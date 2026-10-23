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

    // Algebraic least-squares sphere fit: |p|^2 = 2 c.p + (r^2 - |c|^2) is
    // linear in (c, r^2 - |c|^2). Minimises an algebraic, not geometric,
    // error, which is biased for very small caps but needs no iteration.
    // Returns nullopt for fewer than 4 points or a degenerate (planar or
    // collinear) set. Points are centred internally for conditioning.
    std::optional<SphereFit> fitSphere(const std::vector<Eigen::Vector3d> &points);

}

#endif
