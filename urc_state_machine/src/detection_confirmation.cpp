#include "urc_state_machine/detection_confirmation.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace urc_state_machine
{

DetectionConfirmation::DetectionConfirmation(const DetectionConfirmationConfig & config)
: target_classes_(config.target_classes.begin(), config.target_classes.end()),
  min_confidence_(config.min_confidence),
  required_hits_(config.required_hits),
  window_frames_(0)
{
  if (!std::isfinite(config.min_confidence) || config.min_confidence < 0.0 ||
    config.min_confidence > 1.0)
  {
    throw std::invalid_argument("yolo_min_confidence must be within [0, 1]");
  }
  if (config.required_hits < 1 || config.window_frames < config.required_hits) {
    throw std::invalid_argument(
            "yolo_confirmation_hits must be >= 1 and <= yolo_confirmation_window");
  }
  window_frames_ = static_cast<std::size_t>(config.window_frames);
}

void DetectionConfirmation::reset()
{
  recent_frames_.clear();
}

std::optional<DetectionCandidate> DetectionConfirmation::update(
  const std::vector<DetectionCandidate> & frame)
{
  const auto best = bestTarget(frame);
  recent_frames_.push_back(best ? best->class_name : std::string{});
  if (recent_frames_.size() > window_frames_) {
    recent_frames_.pop_front();
  }

  if (!best || hitsInWindow(best->class_name) < required_hits_) {
    return std::nullopt;
  }
  return best;
}

std::optional<DetectionCandidate> DetectionConfirmation::bestTarget(
  const std::vector<DetectionCandidate> & frame) const
{
  std::optional<DetectionCandidate> best;
  for (const auto & candidate : frame) {
    if (candidate.class_name.empty() || candidate.confidence < min_confidence_ ||
      !isTargetClass(candidate.class_name))
    {
      continue;
    }
    if (!best || candidate.confidence > best->confidence) {
      best = candidate;
    }
  }
  return best;
}

bool DetectionConfirmation::isTargetClass(const std::string & class_name) const
{
  return target_classes_.empty() || target_classes_.count(class_name) > 0;
}

int DetectionConfirmation::hitsInWindow(const std::string & class_name) const
{
  return static_cast<int>(std::count(recent_frames_.begin(), recent_frames_.end(), class_name));
}

}  // namespace urc_state_machine