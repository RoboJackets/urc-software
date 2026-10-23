#include "urc_trajectory_following/mpc/swerve_model.hpp"

#include <cmath>

namespace mpc
{
namespace
{
Eigen::Matrix2d bodyToMapRotation(double yaw)
{
  Eigen::Matrix2d rotation;
  rotation << std::cos(yaw), -std::sin(yaw),
    std::sin(yaw), std::cos(yaw);
  return rotation;
}
}  // namespace

State step(const State & state, const Input & input, double dt)
{
  State next = state;
  next.head<2>() += dt * (bodyToMapRotation(state.z()) * input.head<2>());
  next.z() += dt * input.z();
  return next;
}

std::vector<State> rollout(
  const State & initial_state, const std::vector<Input> & inputs, double dt)
{
  std::vector<State> states;
  states.reserve(inputs.size() + 1);
  states.push_back(initial_state);
  for (const Input & input : inputs) {
    states.push_back(step(states.back(), input, dt));
  }
  return states;
}

LinearizedStep linearize(const State & nominal_state, const Input & nominal_input, double dt)
{
  const double yaw = nominal_state.z();
  const Eigen::Matrix2d rotation = bodyToMapRotation(yaw);
  Eigen::Matrix2d rotation_derivative;
  rotation_derivative << -std::sin(yaw), -std::cos(yaw),
    std::cos(yaw), -std::sin(yaw);

  LinearizedStep linearized;
  linearized.state_jacobian.setIdentity();
  linearized.state_jacobian.block<2, 1>(0, 2) =
    dt * (rotation_derivative * nominal_input.head<2>());

  linearized.input_jacobian.setZero();
  linearized.input_jacobian.block<2, 2>(0, 0) = dt * rotation;
  linearized.input_jacobian(2, 2) = dt;
  return linearized;
}
}  // namespace mpc
