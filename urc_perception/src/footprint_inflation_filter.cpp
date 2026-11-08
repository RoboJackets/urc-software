#include "urc_perception/footprint_inflation_filter.hpp"

#include <cmath>

#include <grid_map_core/iterators/CircleIterator.hpp>
#include <grid_map_core/iterators/GridMapIterator.hpp>
#include <grid_map_cv/utilities.hpp>
#include <pluginlib/class_list_macros.hpp>
#include <rclcpp/rclcpp.hpp>

namespace urc_perception
{
namespace
{
// Keeps decayed cost strictly below lethal, so only the inscribed disk blocks
constexpr double kDecayedCostCeiling = 0.99;
}  // namespace

bool FootprintInflationFilter::configure()
{
  grid_map::ParameterReader reader(this->param_prefix_, this->params_interface_);
  const auto logger = this->logging_interface_->get_logger();

  if (!reader.get("input_layer", input_layer_) || !reader.get("output_layer", output_layer_) ||
    !reader.get("lethal_cost", lethal_cost_) ||
    !reader.get("inscribed_radius_m", inscribed_radius_m_) ||
    !reader.get("inflation_radius_m", inflation_radius_m_) ||
    !reader.get("cost_scaling_per_m", cost_scaling_per_m_))
  {
    RCLCPP_ERROR(
      logger, "FootprintInflationFilter needs input_layer, output_layer, lethal_cost, "
      "inscribed_radius_m, inflation_radius_m and cost_scaling_per_m");
    return false;
  }
  if (lethal_cost_ <= 0.0 || inscribed_radius_m_ < 0.0 ||
    inflation_radius_m_ < inscribed_radius_m_ || cost_scaling_per_m_ <= 0.0)
  {
    RCLCPP_ERROR(
      logger, "FootprintInflationFilter needs lethal_cost > 0, cost_scaling_per_m > 0 and "
      "0 <= inscribed_radius_m <= inflation_radius_m");
    return false;
  }
  return true;
}

float FootprintInflationFilter::inflatedCost(double distance_m) const
{
  if (distance_m <= inscribed_radius_m_) {
    return static_cast<float>(lethal_cost_);
  }
  return static_cast<float>(
    lethal_cost_ * kDecayedCostCeiling *
    std::exp(-cost_scaling_per_m_ * (distance_m - inscribed_radius_m_)));
}

bool FootprintInflationFilter::update(
  const grid_map::GridMap & map_in,
  grid_map::GridMap & map_out)
{
  if (!map_in.exists(input_layer_)) {
    RCLCPP_ERROR(
      this->logging_interface_->get_logger(),
      "FootprintInflationFilter input layer '%s' is missing", input_layer_.c_str());
    return false;
  }

  map_out = map_in;
  map_out.add(output_layer_, map_in[input_layer_]);
  const grid_map::Matrix & input = map_in[input_layer_];
  grid_map::Matrix & output = map_out[output_layer_];

  for (grid_map::GridMapIterator it(map_in); !it.isPastEnd(); ++it) {
    const grid_map::Index lethal_index = *it;
    if (!(input(lethal_index(0), lethal_index(1)) >= lethal_cost_)) {
      continue;
    }
    grid_map::Position center;
    map_in.getPosition(lethal_index, center);
    for (grid_map::CircleIterator circle(map_in, center, inflation_radius_m_);
      !circle.isPastEnd(); ++circle)
    {
      const grid_map::Index index = *circle;
      grid_map::Position position;
      map_in.getPosition(index, position);
      const float inflated = inflatedCost((position - center).norm());
      float & cell = output(index(0), index(1));
      if (std::isnan(cell) || inflated > cell) {
        cell = inflated;
      }
    }
  }
  return true;
}
}  // namespace urc_perception

PLUGINLIB_EXPORT_CLASS(
  urc_perception::FootprintInflationFilter,
  filters::FilterBase<grid_map::GridMap>)
