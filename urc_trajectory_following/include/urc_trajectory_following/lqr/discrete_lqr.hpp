#ifndef DISCRETE_LQR_HPP_
#define DISCRETE_LQR_HPP_

#include <Eigen/Dense>

#include <optional>

namespace lqr
{
/** Discrete-time linear model x[k+1] = A x[k] + B u[k]. */
struct LinearModel
{
  Eigen::MatrixXd state_matrix;
  Eigen::MatrixXd input_matrix;
};

/** Quadratic cost: sum of x' Q x + u' R u over all future steps. */
struct QuadraticCost
{
  Eigen::MatrixXd state_weight;
  Eigen::MatrixXd input_weight;
};

/**
 * Solves the discrete algebraic Riccati equation by fixed-point iteration.
 * @return Gain K for the control law u = -K x, or nullopt if the iteration does not converge.
 */
std::optional<Eigen::MatrixXd> solveDiscreteLqr(
  const LinearModel & model, const QuadraticCost & cost);
}  // namespace lqr

#endif  // DISCRETE_LQR_HPP_
