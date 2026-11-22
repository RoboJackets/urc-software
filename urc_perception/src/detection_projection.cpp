#include "urc_perception/detection_projection.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

namespace urc_perception {

    namespace {

        cv::Rect coreRegion(
            const PixelBox &box,
            double core_fraction,
            const cv::Size &image_size
        ) {
            const double margin_x = (box.x_max - box.x_min) * (1.0 - core_fraction) / 2.0;
            const double margin_y = (box.y_max - box.y_min) * (1.0 - core_fraction) / 2.0;

            const cv::Rect core(
                cv::Point(static_cast<int>(box.x_min + margin_x), static_cast<int>(box.y_min + margin_y)),
                cv::Point(
                    static_cast<int>(std::ceil(box.x_max - margin_x)),
                    static_cast<int>(std::ceil(box.y_max - margin_y))
                )
            );

            return core & cv::Rect(cv::Point(0, 0), image_size);
        }
    }

    std::optional<double> medianCoreDepth(
        const cv::Mat &depth_m,
        const PixelBox &box,
        double core_fraction
    ) {
        const cv::Rect core = coreRegion(box, core_fraction, depth_m.size());
        if (core.empty()) {
            return std::nullopt;
        }

        std::vector<float> valid_depths;
        valid_depths.reserve(static_cast<size_t>(core.area()));
        for (int row = core.y; row < core.y + core.height; ++row) {
            const float * depths = depth_m.ptr<float>(row);
            for (int col = core.x; col < core.x + core.width; ++col) {
                if (std::isfinite(depths[col]) && depths[col] > 0.0F) {
                    valid_depths.push_back(depths[col]);
                }
            }
        }
        if (valid_depths.empty()) {
            return std::nullopt;
        }

        const auto middle = valid_depths.begin() + valid_depths.size() / 2;

        std::nth_element(valid_depths.begin(), middle, valid_depths.end());

        return static_cast<double>(*middle);
    }

    cv::Point3d deprojectBoxCenter(
        const PinholeIntrinsics &intrinsics,
        const PixelBox &box,
        double depth_m
    ) {
        const double u = (box.x_min + box.x_max) / 2.0;
        const double v = (box.y_min + box.y_max) / 2.0;

        return {
            (u - intrinsics.cx) * depth_m / intrinsics.fx,
            (v - intrinsics.cy) * depth_m / intrinsics.fy,
            depth_m};
    }
}