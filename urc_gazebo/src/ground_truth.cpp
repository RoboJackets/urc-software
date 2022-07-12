#include "ground_truth.hpp"

namespace ground_truth
{
  GroundTruth::GroundTruth(const rclcpp::NodeOptions &options)
      : rclcpp::Node("ground_truth", options)
  {
    // Other variables that need to be defined go here (noise variables?)
    RobotLocalization::NavsatConversions::UTM(latitude, longitude, &utm_x, &utm_y);

    _ground_truth_sub = create_subscription<nav_msgs::Odometry>("~/ground_truth/state_raw", rclcpp::SystemDefaultsQoS(), [this](const nav_msgs::Odometry msg));

    _estimate_sub = create_subscription<nav_msgs::Odometry>("~/odometry/filtered", rclcpp::SystemDefaultsQoS(), [this](const nav_msgs::Odometry msg))

        _ground_truth_pub = create_publisher<nav_msgs::Odometry>("~/ground_truth", rclcpp::SystemDefaultsQoS());

    utm_to_odom.setOrigin(
        tf::Vector3(utm_x - g_og_pose.pose.pose.position.x, utm_y - g_og_pose.pose.pose.position.y, 0.0));
    utm_to_odom.setRotation(tf::createQuaternionFromYaw(M_PI));

    // this will probably error
    utm_timer = rclcpp::create_timer(ros::Duration(1.0), boost::bind(utm_callback, _1, utm_to_odom.inverse()));
  }

  void GroundTruth::groundTruthCallback(const nav_msgs::Odometry::ConstPtr &msg)
  {
  }

  void GroundTruth::odomCallback(const nav_msgs::Odometry::ConstPtr &msg)
  {
    _last_estimate = msg->header.stamp;
  }

  void GroundTruth::utmCallback(const ros::TimerEvent &event, const tf::Transform &odom_to_utm)
  {
    static tf::TransformBroadcaster br;
    static tf::TransformListener tf_listener;
    tf::StampedTransform transform;
    static bool enabled = true;

    if (enabled)
    {
      bool found = true;
      try
      {
        tf_listener.lookupTransform("odom", "utm", ros::Time(0), transform);
      }
      catch (const tf::TransformException &ex)
      {
        found = false;
      }

      if (found && transform.getRotation() != odom_to_utm.getRotation() &&
          transform.getOrigin() != odom_to_utm.getOrigin())
      {
        ROS_WARN_STREAM("Anther odom -> utm tf broadcast detected. Disabling ground_truth odom -> utm tf broadcast.");
        enabled = false;
        return;
      }
      br.sendTransform(tf::StampedTransform(odom_to_utm, event.current_real, "odom", "utm"));
    }
  }

} // namespace ground_truth

RCLCPP_COMPONENTS_REGISTER_NODE(ground_truth::GroundTruth)

/*
int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ground_truth::groundTruth>());
  rclcpp::shutdown();

  return 0;
}
*/
