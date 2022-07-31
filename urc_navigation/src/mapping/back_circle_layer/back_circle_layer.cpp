#include "back_circle_layer.h"
#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(back_circle_layer::BackCircleLayer, costmap_2d::Layer)

namespace back_circle_layer
{
BackCircleLayer::BackCircleLayer(const rclcpp::NodeOptions & options)
: rclcpp::Node("joystick_driver", options)
{
}

// Get a subscriber in here that subscribes to a topic published to in the back_circle_server.cpp

void BackCircleLayer::onInitialize()
{
  matchSize();

  back_circle_sub_ = create_subscription<urc_msgs::msg::BackCircleResponse>(
    "/back_circle_response", rclcpp::SystemDefaultsQoS(), [this](const urc_msgs::msg::BackCircleResponse msg) {
      costmapCallback(msg);
  });

  current_ = true;
}

void BackCircleLayer::updateBounds(double robot_x, double robot_y, double robot_yaw, double *min_x, double *min_y,
                                   double *max_x, double *max_y)
{
  updateOrigin(robot_x - getSizeInMetersX() / 2, robot_y - getSizeInMetersY() / 2);

  *min_x = getOriginX();
  *max_x = getOriginX() + getSizeInMetersX();
  *min_y = getOriginY();
  *max_y = getOriginY() + getSizeInMetersY();
}

void BackCircleLayer::updateCosts(costmap_2d::Costmap2D &master_grid, int min_i, int min_j, int max_i, int max_j)
{
  for (size_t i = 0; i < xVals.size(); ++i)
  {
    // If costmap contains the back circle point, add it to the costmap
    unsigned int mx;
    unsigned int my;
    if (master_grid.worldToMap(xVals.at(i), yVals.at(i), mx, my))
    {
      master_grid.setCost(mx, my, costmap_2d::LETHAL_OBSTACLE);
    }
  }
}

void BackCircleLayer::costmapCallback(const urc_msgs::msg::BackCircleResponse &msg)
{
  xVals = msg->x;
  yVals = msg->y;
  RCLCPP_INFO_STREAM(this->get_logger(), msg);
}

}  // namespace back_circle_layer