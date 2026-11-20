#include "urc_perception/traversability_cost_filter.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

#include <grid_map_core/GridMapMath.hpp>
#include <grid_map_core/iterators/GridMapIterator.hpp>
#include <grid_map_cv/utilities.hpp>
#include <pluginlib/class_list_macros.hpp>
#include <rclcpp/rclcpp.hpp>

namespace urc_perception
{
namespace
{
constexpr float kUnknown = std::numeric_limits<float>::quiet_NaN();
// Caps tan(slope) so a near-vertical normal cannot explain away any step
constexpr float kMaxSlopeForStepRad = 1.4f;

// Largest neighbor height change not explained by the cell's slope. Returns
// NaN when the cell or all of its neighbors lack elevation.
float stepHeight(
  const grid_map::GridMap & map, const grid_map::Matrix & elevation,
  const grid_map::Index & buffer_index, float slope_rad)
{
  const float center = elevation(buffer_index(0), buffer_index(1));
  if (!std::isfinite(center)) {
    return kUnknown;
  }

  const grid_map::Size size = map.getSize();
  const grid_map::Index start = map.getStartIndex();
  const grid_map::Index index = grid_map::getIndexFromBufferIndex(buffer_index, size, start);
  const double tan_slope =
    std::isfinite(slope_rad) ? std::tan(std::min(slope_rad, kMaxSlopeForStepRad)) : 0.0;

  float step = kUnknown;
  for (int di = -1; di <= 1; ++di) {
    for (int dj = -1; dj <= 1; ++dj) {
      const grid_map::Index neighbor = index + grid_map::Index(di, dj);
      if ((di == 0 && dj == 0) || !grid_map::checkIfIndexInRange(neighbor, size)) {
        continue;
      }
      const grid_map::Index neighbor_buffer =
        grid_map::getBufferIndexFromIndex(neighbor, size, start);
      const float height = elevation(neighbor_buffer(0), neighbor_buffer(1));
      if (!std::isfinite(height)) {
        continue;
      }
      const double distance = map.getResolution() * std::hypot(di, dj);
      const float excess = static_cast<float>(std::abs(height - center) - distance * tan_slope);
      step = std::isnan(step) ? std::max(excess, 0.0f) : std::max(step, excess);
    }
  }
  return step;
}
}  // namespace

bool TraversabilityCostFilter::configure()
{
  grid_map::ParameterReader reader(this->param_prefix_, this->params_interface_);
  const auto logger = this->logging_interface_->get_logger();

  if (!reader.get("elevation_layer", elevation_layer_) ||
    !reader.get("slope_layer", slope_layer_) ||
    !reader.get("roughness_layer", roughness_layer_) ||
    !reader.get("step_layer", step_layer_) ||
    !reader.get("output_layer", output_layer_))
  {
    RCLCPP_ERROR(
      logger, "TraversabilityCostFilter needs elevation_layer, slope_layer, roughness_layer, "
      "step_layer and output_layer");
    return false;
  }
  if (!reader.get("max_slope_rad", max_slope_rad_) ||
    !reader.get("max_roughness_m", max_roughness_m_) ||
    !reader.get("max_step_height_m", max_step_height_m_))
  {
    RCLCPP_ERROR(
      logger,
      "TraversabilityCostFilter needs max_slope_rad, max_roughness_m and max_step_height_m");
    return false;
  }
  if (max_slope_rad_ <= 0.0 || max_slope_rad_ >= M_PI_2 || max_roughness_m_ <= 0.0 ||
    max_step_height_m_ <= 0.0)
  {
    RCLCPP_ERROR(
      logger, "TraversabilityCostFilter limits must be positive, with max_slope_rad below pi/2");
    return false;
  }
  return true;
}

bool TraversabilityCostFilter::update(
  const grid_map::GridMap & map_in,
  grid_map::GridMap & map_out)
{
  if (!map_in.exists(elevation_layer_) || !map_in.exists(slope_layer_) ||
    !map_in.exists(roughness_layer_))
  {
    RCLCPP_ERROR(
      this->logging_interface_->get_logger(),
      "TraversabilityCostFilter input layers '%s', '%s' or '%s' are missing",
      elevation_layer_.c_str(), slope_layer_.c_str(), roughness_layer_.c_str());
    return false;
  }

  map_out = map_in;
  map_out.add(step_layer_, kUnknown);
  map_out.add(output_layer_, kUnknown);
  const grid_map::Matrix & elevation = map_in[elevation_layer_];
  const grid_map::Matrix & slope = map_in[slope_layer_];
  const grid_map::Matrix & roughness = map_in[roughness_layer_];
  grid_map::Matrix & step = map_out[step_layer_];
  grid_map::Matrix & cost = map_out[output_layer_];

  for (grid_map::GridMapIterator it(map_in); !it.isPastEnd(); ++it) {
    const grid_map::Index index = *it;
    const int i = index(0);
    const int j = index(1);
    step(i, j) = stepHeight(map_in, elevation, index, slope(i, j));

    float worst = kUnknown;
    const float terms[] = {
      static_cast<float>(slope(i, j) / max_slope_rad_),
      static_cast<float>(roughness(i, j) / max_roughness_m_),
      static_cast<float>(step(i, j) / max_step_height_m_)};
    for (const float term : terms) {
      if (std::isfinite(term)) {
        worst = std::isnan(worst) ? term : std::max(worst, term);
      }
    }
    cost(i, j) = std::isnan(worst) ? kUnknown : std::min(worst, 1.0f);
  }
  return true;
}
}  // namespace urc_perception

PLUGINLIB_EXPORT_CLASS(
  urc_perception::TraversabilityCostFilter,
  filters::FilterBase<grid_map::GridMap>)
