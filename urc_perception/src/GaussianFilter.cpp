#include "GaussianFilter.hpp"
#include <pluginlib/class_list_macros.hpp>
#include <rclcpp/rclcpp.hpp>

#include <grid_map_core/grid_map_core.hpp>

#include <string>
#include <vector>

#include <grid_map_cv/utilities.hpp>

#define EPSILON 0.001

namespace urc_perception
{

    template <typename T>
    GaussianFilter<T>::GaussianFilter()
        : radius_(5.0)
    {
    }

    template <typename T>
    GaussianFilter<T>::~GaussianFilter()
    {
    }

    template <typename T>
    bool GaussianFilter<T>::configure()
    {
        grid_map::ParameterReader param_reader(this->param_prefix_, this->params_interface_);

        if (!param_reader.get(std::string("radius"), radius_))
        {
            RCLCPP_ERROR(
                this->logging_interface_->get_logger(), "Gaussian filter did not find param radius.");
            return false;
        }

        if (radius_ < 0.0)
        {
            RCLCPP_ERROR(this->logging_interface_->get_logger(), "Radius must be greater than zero.");
            return false;
        }

        RCLCPP_DEBUG(this->logging_interface_->get_logger(), "Radius = %f.", radius_);

        if (!param_reader.get(std::string("input_layer"), inputLayer_))
        {
            RCLCPP_ERROR(
                this->logging_interface_->get_logger(),
                "Gaussian filter did not find parameter `input_layer`.");
            return false;
        }

        RCLCPP_DEBUG(
            this->logging_interface_->get_logger(), "Gaussian input layer is = %s.", inputLayer_.c_str());

        if (!param_reader.get(std::string("output_layer"), outputLayer_))
        {
            RCLCPP_ERROR(
                this->logging_interface_->get_logger(),
                "Gaussian filter did not find parameter `output_layer`.");
            return false;
        }

        RCLCPP_DEBUG(
            this->logging_interface_->get_logger(), "Gaussian output layer = %s.", outputLayer_.c_str());

        return true;
    }

    template <typename T>
    bool GaussianFilter<T>::update(const T &mapIn, T &mapOut)
    {
        mapOut = mapIn;
        mapOut.add(outputLayer_, 0.0);

        double value;

        for (grid_map::GridMapIterator iterator(mapOut); !iterator.isPastEnd(); ++iterator)
        {
            if (!mapOut.isValid(*iterator, inputLayer_))
                continue;

            Eigen::Vector2d center;
            mapOut.getPosition(*iterator, center);
            double center_cost = mapOut.at(inputLayer_, *iterator);

            if (center_cost < EPSILON)
                continue;

            for (grid_map::CircleIterator submapIterator(mapOut, center, radius_); !submapIterator.isPastEnd(); ++submapIterator)
            {
                Eigen::Vector2d pos;
                mapOut.getPosition(*submapIterator, pos);

                double distance = (center - pos).norm();
                value = std::exp(-0.5 * distance * distance / radius_) * center_cost;

                if (value > mapOut.at(outputLayer_, *submapIterator))
                {
                    mapOut.at(outputLayer_, *submapIterator) = value;
                }
            }
        }

        return true;
    }
} // namespace urc_perception

PLUGINLIB_EXPORT_CLASS(urc_perception::GaussianFilter<grid_map::GridMap>, filters::FilterBase<grid_map::GridMap>)