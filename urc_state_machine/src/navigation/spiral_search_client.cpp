#include "urc_state_machine/spiral_search_client.hpp"

#include <algorithm>
#include <cstddef>
#include <utility>
#include <rclcpp/exceptions/exceptions.hpp>
#include "urc_state_machine/mission_geometry.hpp"

namespace urc_state_machine
{
namespace
{
constexpr std::size_t kMaximumPathPoses = 2000;

bool usablePath(const nav_msgs::msg::Path & path, const std::string & frame)
{
  return path.header.frame_id == frame && path.poses.size() >= 2 &&
         path.poses.size() <= kMaximumPathPoses &&
         std::all_of(
    path.poses.begin(), path.poses.end(), [&frame](const auto & pose) {
      return pose.header.frame_id == frame && validPose(pose);
    });
}
}  // namespace

SpiralSearchClient::SpiralSearchClient(rclcpp::Node & node, const std::string & service_name)
: client_(node.create_client<Service>(service_name))
{
}

bool SpiralSearchClient::request(const geometry_msgs::msg::PoseStamped & center, double radius)
{
  if (request_id_ || !client_->service_is_ready()) {
    return false;
  }
  path_.reset();
  failed_ = false;
  const auto generation = ++generation_;
  auto request = std::make_shared<Service::Request>();
  request->center = center;
  request->search_radius = radius;
  try {
    auto pending = client_->async_send_request(
      request, [this, generation, frame = center.header.frame_id](
        rclcpp::Client<Service>::SharedFuture future) {
        if (generation != generation_) {
          return;
        }
        request_id_.reset();
        const auto response = future.get();
        failed_ = response->error_code != Service::Response::SUCCESS ||
        !response->traversability_checked || !usablePath(response->path, frame);
        if (!failed_) {
          path_ = response->path;
        }
      });
    request_id_ = pending.request_id;
  } catch (const rclcpp::exceptions::RCLError &) {
    failed_ = true;
  }
  return true;
}

void SpiralSearchClient::cancel()
{
  ++generation_;
  if (request_id_) {
    client_->remove_pending_request(*request_id_);
    request_id_.reset();
  }
  path_.reset();
  failed_ = false;
}

bool SpiralSearchClient::failed() const
{
  return failed_;
}

std::optional<nav_msgs::msg::Path> SpiralSearchClient::takePath()
{
  return std::exchange(path_, std::nullopt);
}
}  // namespace urc_state_machine
