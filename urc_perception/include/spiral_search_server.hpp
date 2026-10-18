#ifndef SPIRAL_SEARCH_SERVER_HPP_
#define SPIRAL_SEARCH_SERVER_HPP_

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>

#include <memory>
#include <string>
#include <vector>

#include "urc_msgs/srv/generate_spiral_search.hpp"
#include "spiral_search.hpp"

namespace urc_perception
{

/**
 * @brief Serves outward Archimedean spiral search paths around a requested center.
 *
 * The rover follows the returned path to sweep its forward-facing detection camera over the
 * area around a GNSS target whose exact location is uncertain.
 */
class SpiralSearchServer : public rclcpp::Node
{
public:
  explicit SpiralSearchServer(const rclcpp::NodeOptions & options);

private:
  /**
   * @brief Generate the spiral requested by the caller.
   *
   * Invalid geometry is reported as INVALID_REQUEST rather than raised, so a caller polling
   * with an unreachable radius does not take the server down.
   */
  void generateSpiralSearch(
    const std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch::Request> request,
    std::shared_ptr<urc_msgs::srv::GenerateSpiralSearch::Response> response);

  /// Combine the request with the configured defaults it leaves unset.
  SpiralSearchParameters resolveParameters(
    const urc_msgs::srv::GenerateSpiralSearch::Request & request) const;

  /// Place center-relative waypoints into the center's frame, oriented along the spiral tangent.
  nav_msgs::msg::Path toPath(
    const std::vector<SpiralWaypoint> & waypoints,
    const geometry_msgs::msg::PoseStamped & center) const;

  /**
   * @brief Publish the spiral for *visualization*. The path is returned through the service.
   */
  void publishPath(const nav_msgs::msg::Path & path);

  rclcpp::Service<urc_msgs::srv::GenerateSpiralSearch>::SharedPtr spiral_service_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_publisher_;

  CameraCoverage camera_coverage_;
  double default_track_spacing_ = 0.0;
  double default_waypoint_spacing_ = 0.0;
  double start_radius_ = 0.0;
  std::size_t max_waypoints_ = 0;
  std::string map_frame_;
};

} // namespace urc_perception

#endif // SPIRAL_SEARCH_SERVER_HPP_
