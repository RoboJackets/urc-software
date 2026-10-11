#ifndef URC_STATE_MACHINE__DETECTION_CONFIRMATION_HPP_
#define URC_STATE_MACHINE__DETECTION_CONFIRMATION_HPP_

#include <cstddef>
#include <deque>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

namespace urc_state_machine
{

struct DetectionCandidate
{
  std::string class_name;
  double confidence{0.0};
  double center_x{0.0};
  double center_y{0.0};
  double width{0.0};
  double height{0.0};
};

struct DetectionConfirmationConfig
{
  
  std::vector<std::string> target_classes;
  double min_confidence{0.5};
  int required_hits{3};
  int window_frames{5};
};


class DetectionConfirmation
{
public:
  
  explicit DetectionConfirmation(const DetectionConfirmationConfig & config);

  void reset();

  std::optional<DetectionCandidate> update(const std::vector<DetectionCandidate> & frame);

private:
  std::optional<DetectionCandidate> bestTarget(
    const std::vector<DetectionCandidate> & frame) const;
  bool isTargetClass(const std::string & class_name) const;
  int hitsInWindow(const std::string & class_name) const;

  std::unordered_set<std::string> target_classes_;
  double min_confidence_;
  int required_hits_;
  std::size_t window_frames_;

  // Best target class per recent frame; an empty string marks a frame without a target.
  std::deque<std::string> recent_frames_;
};

}  

#endif  