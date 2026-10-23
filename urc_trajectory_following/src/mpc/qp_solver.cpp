#include "urc_trajectory_following/mpc/qp_solver.hpp"

#include <osqp.h>

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

namespace mpc
{
namespace
{
using SparseMatrix = Eigen::SparseMatrix<double>;

struct WorkspaceDeleter
{
  void operator()(OSQPWorkspace * workspace) const {osqp_cleanup(workspace);}
};

// Compressed-column structure of a matrix, fixed for the lifetime of the solver.
struct SparsityPattern
{
  c_int rows = 0;
  c_int cols = 0;
  std::vector<c_int> outer;
  std::vector<c_int> inner;
};

void requireCompressed(const SparseMatrix & matrix, const std::string & name)
{
  if (!matrix.isCompressed()) {
    throw std::invalid_argument(name + " must be in compressed storage");
  }
}

void requireUpperTriangular(const SparseMatrix & matrix)
{
  for (int col = 0; col < matrix.outerSize(); ++col) {
    for (SparseMatrix::InnerIterator it(matrix, col); it; ++it) {
      if (it.row() > it.col()) {
        throw std::invalid_argument("hessian must be upper triangular");
      }
    }
  }
}

SparsityPattern patternOf(const SparseMatrix & matrix)
{
  SparsityPattern pattern;
  pattern.rows = matrix.rows();
  pattern.cols = matrix.cols();
  pattern.outer.assign(matrix.outerIndexPtr(), matrix.outerIndexPtr() + matrix.outerSize() + 1);
  pattern.inner.assign(matrix.innerIndexPtr(), matrix.innerIndexPtr() + matrix.nonZeros());
  return pattern;
}

bool samePattern(const SparsityPattern & pattern, const SparseMatrix & matrix)
{
  return pattern.rows == matrix.rows() && pattern.cols == matrix.cols() &&
         pattern.inner.size() == static_cast<size_t>(matrix.nonZeros()) &&
         std::equal(pattern.outer.begin(), pattern.outer.end(), matrix.outerIndexPtr()) &&
         std::equal(pattern.inner.begin(), pattern.inner.end(), matrix.innerIndexPtr());
}

std::vector<c_float> valuesOf(const SparseMatrix & matrix)
{
  return std::vector<c_float>(matrix.valuePtr(), matrix.valuePtr() + matrix.nonZeros());
}

std::vector<c_float> toOsqpVector(const Eigen::VectorXd & vector)
{
  return std::vector<c_float>(vector.data(), vector.data() + vector.size());
}

csc viewAsCsc(SparsityPattern & pattern, std::vector<c_float> & values)
{
  return csc{
    static_cast<c_int>(values.size()), pattern.rows, pattern.cols,
    pattern.outer.data(), pattern.inner.data(), values.data(), -1};
}

QpStatus toStatus(c_int osqp_status)
{
  switch (osqp_status) {
    case OSQP_SOLVED:
      return QpStatus::kSolved;
    case OSQP_SOLVED_INACCURATE:
      return QpStatus::kSolvedInaccurate;
    case OSQP_MAX_ITER_REACHED:
      return QpStatus::kMaxIterationsReached;
    case OSQP_PRIMAL_INFEASIBLE:
    case OSQP_PRIMAL_INFEASIBLE_INACCURATE:
      return QpStatus::kInfeasible;
    default:
      return QpStatus::kFailed;
  }
}

Eigen::VectorXd toEigen(const c_float * data, c_int size)
{
  return Eigen::Map<const Eigen::Matrix<c_float, Eigen::Dynamic, 1>>(data, size).cast<double>();
}
}  // namespace

class QpSolver::Impl
{
public:
  Impl(
    const SparseMatrix & upper_hessian, const Eigen::VectorXd & linear_cost,
    const SparseMatrix & constraints, const Eigen::VectorXd & lower_bound,
    const Eigen::VectorXd & upper_bound, const QpSolverSettings & settings)
  {
    validate(upper_hessian, linear_cost, constraints, lower_bound, upper_bound);
    hessian_pattern_ = patternOf(upper_hessian);
    constraint_pattern_ = patternOf(constraints);

    auto hessian_values = valuesOf(upper_hessian);
    auto constraint_values = valuesOf(constraints);
    auto cost = toOsqpVector(linear_cost);
    auto lower = toOsqpVector(lower_bound);
    auto upper = toOsqpVector(upper_bound);
    csc hessian = viewAsCsc(hessian_pattern_, hessian_values);
    csc constraint = viewAsCsc(constraint_pattern_, constraint_values);

    OSQPData data{
      static_cast<c_int>(upper_hessian.rows()), static_cast<c_int>(constraints.rows()),
      &hessian, &constraint, cost.data(), lower.data(), upper.data()};

    OSQPSettings osqp_settings;
    osqp_set_default_settings(&osqp_settings);
    osqp_settings.max_iter = settings.max_iterations;
    osqp_settings.eps_abs = settings.absolute_tolerance;
    osqp_settings.eps_rel = settings.relative_tolerance;
    osqp_settings.verbose = 0;

    OSQPWorkspace * workspace = nullptr;
    if (osqp_setup(&workspace, &data, &osqp_settings) != 0) {
      throw std::runtime_error("OSQP rejected the problem during setup");
    }
    workspace_.reset(workspace);
  }

  void updateMatrices(const SparseMatrix & upper_hessian, const SparseMatrix & constraints)
  {
    requireCompressed(upper_hessian, "hessian");
    requireCompressed(constraints, "constraints");
    if (!samePattern(hessian_pattern_, upper_hessian) ||
      !samePattern(constraint_pattern_, constraints))
    {
      throw std::invalid_argument("matrix sparsity pattern changed after construction");
    }

    const auto hessian_values = valuesOf(upper_hessian);
    const auto constraint_values = valuesOf(constraints);
    const c_int status = osqp_update_P_A(
      workspace_.get(), hessian_values.data(), nullptr, hessian_values.size(),
      constraint_values.data(), nullptr, constraint_values.size());
    if (status != 0) {
      throw std::runtime_error("OSQP failed to update matrices");
    }
  }

  void updateVectors(
    const Eigen::VectorXd & linear_cost, const Eigen::VectorXd & lower_bound,
    const Eigen::VectorXd & upper_bound)
  {
    requireSize(linear_cost, hessian_pattern_.cols, "linear cost");
    requireSize(lower_bound, constraint_pattern_.rows, "lower bound");
    requireSize(upper_bound, constraint_pattern_.rows, "upper bound");

    const auto cost = toOsqpVector(linear_cost);
    const auto lower = toOsqpVector(lower_bound);
    const auto upper = toOsqpVector(upper_bound);
    if (osqp_update_lin_cost(workspace_.get(), cost.data()) != 0 ||
      osqp_update_bounds(workspace_.get(), lower.data(), upper.data()) != 0)
    {
      throw std::runtime_error("OSQP failed to update vectors");
    }
  }

  void warmStart(const Eigen::VectorXd & primal, const Eigen::VectorXd & dual)
  {
    requireSize(primal, hessian_pattern_.cols, "primal warm start");
    requireSize(dual, constraint_pattern_.rows, "dual warm start");

    const auto primal_values = toOsqpVector(primal);
    const auto dual_values = toOsqpVector(dual);
    if (osqp_warm_start(workspace_.get(), primal_values.data(), dual_values.data()) != 0) {
      throw std::runtime_error("OSQP failed to apply warm start");
    }
  }

  QpSolution solve()
  {
    QpSolution solution;
    if (osqp_solve(workspace_.get()) != 0) {
      return solution;
    }
    solution.status = toStatus(workspace_->info->status_val);
    solution.iterations = static_cast<int>(workspace_->info->iter);
    if (solution.usable()) {
      solution.primal = toEigen(workspace_->solution->x, hessian_pattern_.cols);
      solution.dual = toEigen(workspace_->solution->y, constraint_pattern_.rows);
    }
    return solution;
  }

private:
  static void requireSize(const Eigen::VectorXd & vector, c_int expected, const char * name)
  {
    if (vector.size() != expected) {
      throw std::invalid_argument(std::string(name) + " has the wrong size");
    }
  }

  static void validate(
    const SparseMatrix & upper_hessian, const Eigen::VectorXd & linear_cost,
    const SparseMatrix & constraints, const Eigen::VectorXd & lower_bound,
    const Eigen::VectorXd & upper_bound)
  {
    requireCompressed(upper_hessian, "hessian");
    requireCompressed(constraints, "constraints");
    requireUpperTriangular(upper_hessian);
    if (upper_hessian.rows() != upper_hessian.cols() ||
      constraints.cols() != upper_hessian.cols())
    {
      throw std::invalid_argument("hessian and constraint dimensions are inconsistent");
    }
    requireSize(linear_cost, upper_hessian.cols(), "linear cost");
    requireSize(lower_bound, constraints.rows(), "lower bound");
    requireSize(upper_bound, constraints.rows(), "upper bound");
  }

  SparsityPattern hessian_pattern_;
  SparsityPattern constraint_pattern_;
  std::unique_ptr<OSQPWorkspace, WorkspaceDeleter> workspace_;
};

QpSolver::QpSolver(
  const Eigen::SparseMatrix<double> & upper_hessian, const Eigen::VectorXd & linear_cost,
  const Eigen::SparseMatrix<double> & constraints, const Eigen::VectorXd & lower_bound,
  const Eigen::VectorXd & upper_bound, const QpSolverSettings & settings)
: impl_(
    std::make_unique<Impl>(
      upper_hessian, linear_cost, constraints, lower_bound, upper_bound, settings))
{
}

QpSolver::~QpSolver() = default;

void QpSolver::updateMatrices(
  const Eigen::SparseMatrix<double> & upper_hessian,
  const Eigen::SparseMatrix<double> & constraints)
{
  impl_->updateMatrices(upper_hessian, constraints);
}

void QpSolver::updateVectors(
  const Eigen::VectorXd & linear_cost, const Eigen::VectorXd & lower_bound,
  const Eigen::VectorXd & upper_bound)
{
  impl_->updateVectors(linear_cost, lower_bound, upper_bound);
}

void QpSolver::warmStart(const Eigen::VectorXd & primal, const Eigen::VectorXd & dual)
{
  impl_->warmStart(primal, dual);
}

QpSolution QpSolver::solve() {return impl_->solve();}
}  // namespace mpc
