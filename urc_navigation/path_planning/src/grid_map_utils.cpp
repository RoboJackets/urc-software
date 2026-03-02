#include "grid_map_utils.hpp"

#include <algorithm>

namespace grid_map_utils {
    GridMapUtils::GridMapUtils() {}

    void GridMapUtils::setMap(const grid_map_msgs::msg::GridMap & grid_map) {
        grid_map_ = grid_map;
    }

    void GridMapUtils::setLayer(const std::string & layer_name) {
        layer_name_ = layer_name;
    }

    int GridMapUtils::getLayerIndex() const {
        auto it = std::find(grid_map_.layers.begin(), grid_map_.layers.end(), layer_name_);
        if (it == grid_map_.layers.end()) {
            return -1;
        }
        return static_cast<int>(std::distance(grid_map_.layers.begin(), it));
    }

    bool GridMapUtils::getMapDimensions(int &width, int &height) const {
        int idx = getLayerIndex();
        if (idx < 0) {
            return false;
        }
        if (grid_map_.data.empty() || idx >= static_cast<int>(grid_map_.data.size())) {
            return false;
        }
        if (grid_map_.data[idx].layout.dim.size() < 2) {
            return false;
        }

        height = grid_map_.data[idx].layout.dim[0].size;
        width = grid_map_.data[idx].layout.dim[1].size;
        return true;
    }

    bool GridMapUtils::worldToGrid(double x, double y, int &map_x, int &map_y) const {
        int width, height;
        if (!getMapDimensions(width, height)) {
            return false;
        }

        double resolution = grid_map_.info.resolution;
        if (resolution <= 0.0) {
            return false;
        }

        double origin_x = grid_map_.info.pose.position.x;
        double origin_y = grid_map_.info.pose.position.y;
        double rel_x = x - origin_x;
        double rel_y = y - origin_y;

        map_x = static_cast<int>(rel_x / resolution + width / 2.0);
        map_y = static_cast<int>(rel_y / resolution + height / 2.0);

        if (map_x < 0 || map_x >= width || map_y < 0 || map_y >= height) {
            return false;
        }

        return true;
    }

    bool GridMapUtils::tryGetCellCost(double x, double y, float &cost) const {
        int idx = getLayerIndex();
        if (idx < 0) {
            return false;
        }
        if (grid_map_.data.empty() || idx >= static_cast<int>(grid_map_.data.size())) {
            return false;
        }

        int width, height;
        if (!getMapDimensions(width, height)) {
            return false;
        }

        int map_x, map_y;
        if (!worldToGrid(x, y, map_x, map_y)) {
            return false;
        }

        size_t index = static_cast<size_t>(map_y * width + map_x);
        if (index >= grid_map_.data[idx].data.size()) {
            return false;
        }

        cost = grid_map_.data[idx].data[index];
        return true;
    }

}
