#include "urc_trajectory_following/lqr/discrete_lqr.hpp"

namespace lqr
{
namespace
{
constexpr int kMaxIterations = 10000;
constexpr double kConvergenceTolerance = 1e-9;

Eigen::MatrixXd optimalGain(
  const LinearModel & model, const QuadraticCost & cost, const Eigen::MatrixXd & cost_to_go)
{
  const Eigen::MatrixXd & a = model.state_matrix;
  const Eigen::MatrixXd & b = model.input_matrix;
  return (cost.input_weight + b.transpose() * cost_to_go * b)
         .ldlt()
         .solve(b.transpose() * cost_to_go * a);
}
}  // namespace

std::optional<Eigen::MatrixXd> solveDiscreteLqr(
  const LinearModel & model, const QuadraticCost & cost)
{
  const Eigen::MatrixXd & a = model.state_matrix;
  const Eigen::MatrixXd & b = model.input_matrix;
  Eigen::MatrixXd cost_to_go = cost.state_weight;

  for (int iteration = 0; iteration < kMaxIterations; ++iteration) {
    const Eigen::MatrixXd gain = optimalGain(model, cost, cost_to_go);
    const Eigen::MatrixXd next_cost_to_go =
      cost.state_weight + a.transpose() * cost_to_go * (a - b * gain);
    const double change = (next_cost_to_go - cost_to_go).cwiseAbs().maxCoeff();
    cost_to_go = next_cost_to_go;
    if (change < kConvergenceTolerance) {
      return optimalGain(model, cost, cost_to_go);
    }
  }
  return std::nullopt;
}
}  // namespace lqr
