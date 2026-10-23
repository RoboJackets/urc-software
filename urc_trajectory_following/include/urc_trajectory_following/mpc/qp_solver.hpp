#ifndef QP_SOLVER_HPP_
#define QP_SOLVER_HPP_

#include <Eigen/Sparse>

#include <memory>

namespace mpc
{
enum class QpStatus
{
  kSolved,
  kSolvedInaccurate,
  kMaxIterationsReached,
  kInfeasible,
  kFailed
};

struct QpSolverSettings
{
  int max_iterations = 200;
  double absolute_tolerance = 1e-4;
  double relative_tolerance = 1e-4;
};

struct QpSolution
{
  Eigen::VectorXd primal;
  Eigen::VectorXd dual;
  QpStatus status = QpStatus::kFailed;
  int iterations = 0;

  bool usable() const
  {
    return status == QpStatus::kSolved || status == QpStatus::kSolvedInaccurate;
  }
};

/**
 * @brief Convex QP  min 0.5 x'Px + q'x  s.t.  l <= Ax <= u, solved with OSQP.
 *
 * The sparsity patterns of P and A are fixed at construction. Later updates may only
 * change values, which lets OSQP reuse its symbolic factorization every control cycle.
 * Matrices must be compressed. P is given as its upper triangle.
 */
class QpSolver
{
public:
  /**
   * @throws std::invalid_argument if the dimensions or matrix storage are inconsistent
   * @throws std::runtime_error if OSQP rejects the problem
   */
  QpSolver(
    const Eigen::SparseMatrix<double> & upper_hessian,
    const Eigen::VectorXd & linear_cost,
    const Eigen::SparseMatrix<double> & constraints,
    const Eigen::VectorXd & lower_bound,
    const Eigen::VectorXd & upper_bound,
    const QpSolverSettings & settings);
  ~QpSolver();

  QpSolver(const QpSolver &) = delete;
  QpSolver & operator=(const QpSolver &) = delete;

  /**
   * @throws std::invalid_argument if a sparsity pattern differs from the constructed one
   */
  void updateMatrices(
    const Eigen::SparseMatrix<double> & upper_hessian,
    const Eigen::SparseMatrix<double> & constraints);

  void updateVectors(
    const Eigen::VectorXd & linear_cost,
    const Eigen::VectorXd & lower_bound,
    const Eigen::VectorXd & upper_bound);

  void warmStart(const Eigen::VectorXd & primal, const Eigen::VectorXd & dual);

  QpSolution solve();

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};
}  // namespace mpc

#endif  // QP_SOLVER_HPP_
