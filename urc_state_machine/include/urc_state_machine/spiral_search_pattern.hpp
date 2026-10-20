#ifndef URC_STATE_MACHINE__SPIRAL_SEARCH_PATTERN_HPP_
#define URC_STATE_MACHINE__SPIRAL_SEARCH_PATTERN_HPP_

#include <vector>

namespace urc_state_machine
{

// Distances are in meters in the frame of the search center
struct SpiralSearchConfig
{
  double radius_m{20.0};
  double ring_spacing_m{4.0};
  double point_spacing_m{4.0};
};

struct PlanarPose
{
  double x{0.0};
  double y{0.0};
  double yaw{0.0};
};

void validateSpiralSearchConfig(const SpiralSearchConfig & config);

// Archimedean spiral starting one ring out from the center. Each pose faces along
// the spiral tangent so a forward camera sweeps the area as the rover drives it.

std::vector<PlanarPose> generateSpiralSearch(
  double center_x, double center_y, const SpiralSearchConfig & config);

}  

#endif  