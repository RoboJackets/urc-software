#ifndef SWERVE_MODEL_HPP_
#define SWERVE_MODEL_HPP_

#include <Eigen/Dense>

#include <vector>

namespace mpc
{
/**
 * Planar kinematics of a holonomic swerve base, discretized with forward Euler.
 *
 * State  [x, y, yaw]: position (m) and heading (rad) in the map frame. Yaw is continuous and
 *                     never wrapped, so linearizations stay valid across the +-pi cut.
 * Input  [vx, vy, wz]: body-frame forward velocity (m/s), sideways velocity (m/s) and turn
 *                      rate (rad/s), as commanded on cmd_vel.
 */
using State = Eigen::Vector3d;
using Input = Eigen::Vector3d;

/** First-order model of one step around a nominal point: dx+ = A dx + B du. */
struct LinearizedStep
{
  Eigen::Matrix3d state_jacobian;
  Eigen::Matrix3d input_jacobian;
};

State step(const State & state, const Input & input, double dt);

/** @return inputs.size() + 1 states, starting with initial_state. */
std::vector<State> rollout(
  const State & initial_state, const std::vector<Input> & inputs, double dt);

LinearizedStep linearize(const State & nominal_state, const Input & nominal_input, double dt);
}  // namespace mpc

#endif  // SWERVE_MODEL_HPP_
