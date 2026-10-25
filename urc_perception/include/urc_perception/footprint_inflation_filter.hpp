#ifndef URC_PERCEPTION__FOOTPRINT_INFLATION_FILTER_HPP_
#define URC_PERCEPTION__FOOTPRINT_INFLATION_FILTER_HPP_

#include <string>

#include <filters/filter_base.hpp>
#include <grid_map_core/GridMap.hpp>

namespace urc_perception
{
// Inflates lethal cells for a rover planned as a point. Cells within
// inscribed_radius_m of a lethal cell are lethal, because any rover heading
// would touch it. Out to inflation_radius_m, cost decays exponentially and
// stays below lethal. Non-lethal costs are kept but not spread.
class FootprintInflationFilter : public filters::FilterBase<grid_map::GridMap>
{
public:
  bool configure() override;
  bool update(const grid_map::GridMap & map_in, grid_map::GridMap & map_out) override;

private:
  float inflatedCost(double distance_m) const;

  std::string input_layer_;
  std::string output_layer_;
  double lethal_cost_ = 1.0;
  double inscribed_radius_m_ = 0.0;
  double inflation_radius_m_ = 0.0;
  double cost_scaling_per_m_ = 0.0;
};
}  // namespace urc_perception

#endif  // URC_PERCEPTION__FOOTPRINT_INFLATION_FILTER_HPP_
