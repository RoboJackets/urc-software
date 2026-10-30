#ifndef URC_PERCEPTION__TRAVERSABILITY_COST_FILTER_HPP_
#define URC_PERCEPTION__TRAVERSABILITY_COST_FILTER_HPP_

#include <string>

#include <filters/filter_base.hpp>
#include <grid_map_core/GridMap.hpp>

namespace urc_perception
{
// Scores each cell from 0 (easy) to 1 (lethal) as the worst of three terms,
// each divided by the rover's limit: slope (rad), roughness (m) and step
// height (m). Step height is the largest height change to a neighboring cell
// beyond what the cell's own slope explains, so a planar slope adds no step.
// Cells where no term can be computed stay NaN, meaning unobserved.
class TraversabilityCostFilter : public filters::FilterBase<grid_map::GridMap>
{
public:
  bool configure() override;
  bool update(const grid_map::GridMap & map_in, grid_map::GridMap & map_out) override;

private:
  std::string elevation_layer_;
  std::string slope_layer_;
  std::string roughness_layer_;
  std::string step_layer_;
  std::string output_layer_;
  double max_slope_rad_ = 0.0;
  double max_roughness_m_ = 0.0;
  double max_step_height_m_ = 0.0;
};
}  // namespace urc_perception

#endif  // URC_PERCEPTION__TRAVERSABILITY_COST_FILTER_HPP_
