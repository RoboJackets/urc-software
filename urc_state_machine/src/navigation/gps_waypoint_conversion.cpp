#include "urc_state_machine/gps_waypoint_conversion.hpp"

// Humble's geodesy headers require global math declarations before inclusion.
#include <math.h>

#include <geographic_msgs/msg/geo_point.hpp>
#include <geodesy/utm.h>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <stdexcept>
#include <tf2/exceptions.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_ros/buffer.h>

namespace nav_coordinator
{
geometry_msgs::msg::PoseStamped convertGpsToMapWaypoint(
  const urc_msgs::msg::Waypoint & waypoint,
  tf2_ros::Buffer & tf_buffer,
  const std::string & map_frame,
  const std::string & utm_frame,
  const builtin_interfaces::msg::Time & stamp)
{
  geographic_msgs::msg::GeoPoint geo_point;
  geo_point.latitude = waypoint.latitude;
  geo_point.longitude = waypoint.longitude;
  geo_point.altitude = 0.0;

  geodesy::UTMPoint waypoint_utm;
  geodesy::fromMsg(geo_point, waypoint_utm);

  geometry_msgs::msg::PointStamped utm_point;
  utm_point.header.stamp = stamp;
  utm_point.header.frame_id = utm_frame;
  utm_point.point.x = waypoint_utm.easting;
  utm_point.point.y = waypoint_utm.northing;
  utm_point.point.z = 0.0;

  geometry_msgs::msg::PointStamped map_point;
  try {
    tf_buffer.transform(utm_point, map_point, map_frame);
  } catch (const tf2::TransformException & ex) {
    throw std::runtime_error(
            "Failed to transform waypoint from '" + utm_frame + "' to '" + map_frame + "': " +
            ex.what());
  }

  geometry_msgs::msg::PoseStamped pose;
  pose.header = map_point.header;
  pose.pose.position.x = map_point.point.x;
  pose.pose.position.y = map_point.point.y;
  pose.pose.position.z = map_point.point.z;
  pose.pose.orientation.w = 1.0;

  return pose;
}

}
