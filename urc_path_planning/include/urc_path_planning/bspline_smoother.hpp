#ifndef URC_PATH_PLANNING__BSPLINE_SMOOTHER_HPP_
#define URC_PATH_PLANNING__BSPLINE_SMOOTHER_HPP_

#include <nav_msgs/msg/path.hpp>

namespace urc_path_planning
{
struct BSplineParameters
{
  double sample_spacing;
};

class BSplineSmoother
{
public:
  explicit BSplineSmoother(BSplineParameters parameters);

  nav_msgs::msg::Path smooth(const nav_msgs::msg::Path & control_path) const;

private:
  BSplineParameters parameters_;
};
}  // namespace urc_path_planning

#endif  // URC_PATH_PLANNING__BSPLINE_SMOOTHER_HPP_
