#ifndef GRID_MAP_UTILS_HPP_
#define GRID_MAP_UTILS_HPP_
#include <string>

#include <grid_map_msgs/msg/grid_map.hpp>

namespace grid_map_utils
{
    class GridMapUtils
    {
        public:
            GridMapUtils();

            void setMap(const grid_map_msgs::msg::GridMap & grid_map);
            void setLayer(const std::string & layer_name);

            int getLayerIndex() const;
            bool getMapDimensions(int & width, int & height) const;
            bool worldToGrid(double x, double y, int & map_x, int & map_y) const;
            bool tryGetCellCost(double x, double y, float & cost) const;

        private:
            grid_map_msgs::msg::GridMap grid_map_;
            std::string layer_name_;
    };
}
#endif