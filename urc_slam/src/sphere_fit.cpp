#include "sphere_fit.hpp"

#include <cmath>
#include <Eigen/Dense>

namespace urc_slam {

    namespace {

        // The algebraic guess is already close for rock-sized caps, so a few
        // iterations normally suffice; the cap bounds worst-case work per cluster.
        constexpr int kMaxIterations = 20;
        constexpr double kInitialDamping = 1e-3;
        constexpr double kDampingIncrease = 10.0;
        constexpr double kDampingDecrease = 0.1;
        constexpr double kConvergedStepM = 1e-7;

        struct Sphere {
            Eigen::Vector3d center;
            double radius_m;
        };

        // Gauss-Newton system J^T J, J^T r of the geometric residuals
        // r_i = |p_i - c| - radius over the parameters (c, radius).
        struct NormalEquations {
            Eigen::Matrix4d information = Eigen::Matrix4d::Zero();
            Eigen::Vector4d gradient = Eigen::Vector4d::Zero();
        };

        std::optional<Sphere> algebraicFit(const std::vector<Eigen::Vector3d> &points) {

            //calculate mean position of points
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
            return Sphere{centered_center + mean, std::sqrt(radius_sq)};
        }

        double squaredGeometricError(const std::vector<Eigen::Vector3d> &points, const Sphere &sphere) {
            double squared_error = 0.0;
            for (const Eigen::Vector3d &point : points) {
                const double miss = (point - sphere.center).norm() - sphere.radius_m;
                squared_error += miss * miss;
            }
            return squared_error;
        }

        NormalEquations linearize(const std::vector<Eigen::Vector3d> &points, const Sphere &sphere) {
            NormalEquations equations;
            for (const Eigen::Vector3d &point : points) {
                const Eigen::Vector3d offset = point - sphere.center;
                const double distance = offset.norm();
                // The residual is not differentiable at the centre; such a
                // point carries no information about the centre's direction.
                if (distance <= 0.0) {
                    continue;
                }
                Eigen::Vector4d jacobian;
                jacobian << -offset / distance, -1.0;
                equations.information += jacobian * jacobian.transpose();
                equations.gradient += jacobian * (distance - sphere.radius_m);
            }
            return equations;
        }

        // Levenberg-Marquardt with Marquardt's diagonal scaling. Only steps
        // that reduce the geometric error are accepted, so the result is never
        // worse than the initial guess.
        Sphere refineGeometric(const std::vector<Eigen::Vector3d> &points, Sphere sphere) {
            double error = squaredGeometricError(points, sphere);
            double damping = kInitialDamping;
            //find the hessian and gradient matrices
            NormalEquations equations = linearize(points, sphere);
            for (int iteration = 0; iteration < kMaxIterations; ++iteration) {
                Eigen::Matrix4d damped = equations.information;
                damped.diagonal() *= 1.0 + damping;
                const Eigen::Vector4d step = damped.ldlt().solve(-equations.gradient);
                if (!step.allFinite() || step.norm() < kConvergedStepM) {
                    break;
                }

                const Sphere candidate{sphere.center + step.head<3>(), sphere.radius_m + step(3)};
                const double candidate_error = squaredGeometricError(points, candidate);

                //if guess overshot increase the damping factor
                if (candidate.radius_m <= 0.0 || !(candidate_error < error)) {
                    damping *= kDampingIncrease;
                    continue;
                }
                sphere = candidate;
                error = candidate_error;

                //if guess is good decrease damping factor

                damping *= kDampingDecrease;
                equations = linearize(points, sphere);
            }
            return sphere;
        }

    }

    std::optional<SphereFit> fitSphere(const std::vector<Eigen::Vector3d> &points) {
        if (points.size() < 4) {
            return std::nullopt;
        }
        const std::optional<Sphere> initial_guess = algebraicFit(points);
        if (!initial_guess) {
            return std::nullopt;
        }
        const Sphere sphere = refineGeometric(points, *initial_guess);
        
        
        
        SphereFit fit;
        fit.center = sphere.center;
        fit.radius_m = sphere.radius_m;
        fit.rms_residual_m =
            std::sqrt(squaredGeometricError(points, sphere) / static_cast<double>(points.size()));
        return fit;
    }

}
