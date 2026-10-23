#include "sphere_fit.hpp"

#include <cmath>
#include <Eigen/Dense>

namespace urc_slam {

    std::optional<SphereFit> fitSphere(const std::vector<Eigen::Vector3d> &points) {
        if (points.size() < 4) {
            return std::nullopt;
        }

        Eigen::Vector3d mean = Eigen::Vector3d::Zero();
        for (const Eigen::Vector3d &point : points) {
            mean += point;
        }
        mean /= static_cast<double>(points.size());

        const Eigen::Index n = static_cast<Eigen::Index>(points.size());
        Eigen::MatrixXd design(n, 4);
        Eigen::VectorXd target(n);
        for (Eigen::Index i = 0; i < n; ++i) {
            const Eigen::Vector3d p = points[static_cast<std::size_t>(i)] - mean;
            design.row(i) << 2.0 * p.transpose(), 1.0;
            target(i) = p.squaredNorm();
        }

        // SVD (not normal equations) so near-planar caps degrade gracefully
        // instead of squaring the condition number.
        Eigen::JacobiSVD<Eigen::MatrixXd> svd(design, Eigen::ComputeThinU | Eigen::ComputeThinV);
        // A planar or collinear point set makes the sphere unobservable.
        if (svd.singularValues()(3) < 1e-6 * svd.singularValues()(0)) {
            return std::nullopt;
        }
        const Eigen::Vector4d solution = svd.solve(target);

        const Eigen::Vector3d centered_center = solution.head<3>();
        const double radius_sq = solution(3) + centered_center.squaredNorm();
        if (radius_sq <= 0.0) {
            return std::nullopt;
        }

        SphereFit fit;
        fit.center = centered_center + mean;
        fit.radius_m = std::sqrt(radius_sq);
        double squared_error = 0.0;
        for (const Eigen::Vector3d &point : points) {
            const double miss = (point - fit.center).norm() - fit.radius_m;
            squared_error += miss * miss;
        }
        fit.rms_residual_m = std::sqrt(squared_error / static_cast<double>(points.size()));
        return fit;
    }

}
