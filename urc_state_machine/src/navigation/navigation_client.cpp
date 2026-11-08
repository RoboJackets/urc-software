#include "urc_state_machine/navigation_client.hpp"

#include <limits>
#include <utility>
#include <rclcpp/exceptions/exceptions.hpp>

namespace urc_state_machine
{
NavigationClient::NavigationClient(rclcpp::Node & node, const std::string & action_name)
: client_(rclcpp_action::create_client<Action>(&node, action_name))
{
}

bool NavigationClient::ready() const
{
  return client_->action_server_is_ready();
}
bool NavigationClient::busy() const
{
  return sending_ || static_cast<bool>(handle_);
}
float NavigationClient::distance() const
{
  return distance_;
}
uint16_t NavigationClient::replans() const
{
  return replans_;
}

void NavigationClient::replace(const geometry_msgs::msg::PoseStamped & pose)
{
  Action::Goal goal;
  goal.goal = pose;
  goal.has_goal = true;
  replaceGoal(std::move(goal));
}

void NavigationClient::follow(const nav_msgs::msg::Path & path)
{
  Action::Goal goal;
  goal.path = path;
  goal.has_path = true;
  replaceGoal(std::move(goal));
}

void NavigationClient::replaceGoal(Action::Goal goal)
{
  result_.reset();
  if (!busy()) {
    send(std::move(goal));
    return;
  }
  pending_ = std::move(goal);
  stopping_ = true;
  cancelAcceptedGoal();
}

void NavigationClient::cancel()
{
  pending_.reset();
  result_.reset();
  stopping_ = true;
  cancelAcceptedGoal();
}

void NavigationClient::cancelAcceptedGoal()
{
  if (handle_ && !cancel_sent_) {
    client_->async_cancel_goal(handle_);
    cancel_sent_ = true;
  }
}

std::optional<NavigationResult> NavigationClient::takeResult()
{
  auto result = result_;
  result_.reset();
  return result;
}

void NavigationClient::send(Action::Goal goal)
{
  stopping_ = false;
  cancel_sent_ = false;
  distance_ = std::numeric_limits<float>::infinity();
  replans_ = 0;
  if (!ready()) {
    finish(NavigationResult::FAILED);
    return;
  }
  sending_ = true;
  // Late callbacks from an older goal must not mutate the current leg.
  const auto generation = ++generation_;
  rclcpp_action::Client<Action>::SendGoalOptions options;
  options.goal_response_callback = [this, generation](Handle::SharedPtr handle) {
      accepted(generation, handle);
    };
  options.feedback_callback = [this, generation](
    Handle::SharedPtr, const std::shared_ptr<const Action::Feedback> feedback) {
      if (generation == generation_) {
        distance_ = feedback->distance_to_goal;
        replans_ = feedback->replan_count;
      }
    };
  options.result_callback = [this, generation](const Handle::WrappedResult & result) {
      completed(generation, result);
    };
  try {
    client_->async_send_goal(goal, options);
  } catch (const rclcpp::exceptions::RCLError &) {
    finish(NavigationResult::FAILED);
  }
}

void NavigationClient::accepted(uint64_t generation, Handle::SharedPtr handle)
{
  if (generation != generation_) {
    if (handle) {
      client_->async_cancel_goal(handle);
    }
    return;
  }
  sending_ = false;
  handle_ = handle;
  if (!handle_) {
    finish(stopping_ ? NavigationResult::STOPPED : NavigationResult::FAILED);
  } else if (stopping_) {
    cancelAcceptedGoal();
  }
}

void NavigationClient::completed(uint64_t generation, const Handle::WrappedResult & result)
{
  if (generation != generation_) {
    return;
  }
  if (stopping_) {
    finish(NavigationResult::STOPPED);
  } else if (result.code == rclcpp_action::ResultCode::CANCELED) {
    finish(NavigationResult::CANCELED);
  } else if (result.code == rclcpp_action::ResultCode::SUCCEEDED && result.result &&
    result.result->error_code == Action::Result::SUCCESS)
  {
    finish(NavigationResult::REACHED);
  } else {
    finish(NavigationResult::FAILED);
  }
}

void NavigationClient::finish(NavigationResult result)
{
  handle_.reset();
  sending_ = false;
  if (pending_) {
    auto next = std::move(*pending_);
    pending_.reset();
    send(std::move(next));
    return;
  }
  result_ = result;
}
}  // namespace urc_state_machine
