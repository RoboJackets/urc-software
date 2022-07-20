#include "ground_truth.hpp"

namespace ground_truth
{
  GroundTruth::GroundTruth(const rclcpp::NodeOptions &options)
  : rclcpp::Node("ground_truth", options)
  {
    // Other variables that need to be defined go here (noise variables?)
    RobotLocalization::NavsatConversions::UTM(latitude, longitude, &utm_x, &utm_y);

    //noise variables
    x_noise_std_dev = declare_parameter<double>("x_noise_std_dev", 0.0);
    y_noise_std_dev = declare_parameter<double>("y_noise_std_dev", 0.0);
    z_noise_std_dev = declare_parameter<double>("z_noise_std_dev", 0.0);
    roll_noise_std_dev = declare_parameter<double>("roll_noise_std_dev", 0.0);
    pitch_noise_std_dev = declare_parameter<double>("pitch_noise_std_dev", 0.0);
    yaw_noise_std_dev = declare_parameter<double>("yaw_noise_std_dev", 0.0);

    x_distribution = std::normal_distribution<double>(0, x_noise_std_dev);
    y_distribution = std::normal_distribution<double>(0, y_noise_std_dev);
    z_distribution = std::normal_distribution<double>(0, z_noise_std_dev);
    roll_distribution = std::normal_distribution<double>(0, roll_noise_std_dev);
    pitch_distribution = std::normal_distribution<double>(0, pitch_noise_std_dev);
    yaw_distribution = std::normal_distribution<double>(0, yaw_noise_std_dev);


    _ground_truth_sub = create_subscription<nav_msgs::Odometry>(
      "~/ground_truth/state_raw", rclcpp::SystemDefaultsQoS(), [this](const nav_msgs::Odometry msg){
        groundTruthCallback(msg);
      });

    _estimate_sub = create_subscription<nav_msgs::Odometry>(
      "~/odometry/filtered", rclcpp::SystemDefaultsQoS(), [this](const nav_msgs::Odometry msg){
        odomCallback(msg);
      })

    _ground_truth_pub = create_publisher<nav_msgs::Odometry>(
      "~/ground_truth",
      rclcpp::SystemDefaultsQoS());

    utm_to_odom.setOrigin(
        tf::Vector3(utm_x - g_og_pose.pose.pose.position.x, utm_y - g_og_pose.pose.pose.position.y, 0.0));
    utm_to_odom.setRotation(tf::createQuaternionFromYaw(M_PI));

    // this will probably error
    utm_timer = rclcpp::create_timer(ros::Duration(1.0), boost::bind(utm_callback, _1, utm_to_odom.inverse()));
  }

  void GroundTruth::groundTruthCallback(const nav_msgs::Odometry::ConstPtr &msg)
  {
    // get the starting location as the origin
    if (g_og_pose.header.stamp.toSec() == 0)
    {
      g_og_pose.pose = msg->pose;
      g_og_pose.header = msg->header;
      g_og_pose.pose.pose.position.x = msg->pose.pose.position.x + x_distribution(engine);
      g_og_pose.pose.pose.position.y = msg->pose.pose.position.y + y_distribution(engine);
      g_og_pose.pose.pose.position.z = msg->pose.pose.position.z + z_distribution(engine);
      RCLCPP_INFO(this->get_logger(), "setting g_og_pose to " << g_og_pose.pose.pose.position.x << ", "
                  << g_og_pose.pose.pose.position.y << ", " << g_og_pose.pose.pose.position.z);
    }
    else
    {
      nav_msgs::Odometry result;
      result.pose = msg->pose;

      // use the initial location as an offset (makes the starting location 0, 0)
      result.pose.pose.position.x = msg->pose.pose.position.x - g_og_pose.pose.pose.position.x + x_distribution(engine);
      result.pose.pose.position.y = msg->pose.pose.position.y - g_og_pose.pose.pose.position.y + y_distribution(engine);
      result.pose.pose.position.z = msg->pose.pose.position.z - g_og_pose.pose.pose.position.z + z_distribution(engine);
      result.twist = msg->twist;

      // set up the correct header
      result.header = msg->header;
      result.child_frame_id = "base_footprint";
      result.header.frame_id = "odom";

      tf::Quaternion quat(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z,
                          msg->pose.pose.orientation.w);
      tf::Matrix3x3 m(quat);
      double roll, pitch, yaw;
      m.getRPY(roll, pitch, yaw);
      result.pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(
          roll + roll_distribution(engine), pitch + pitch_distribution(engine), yaw + yaw_distribution(engine));
      quat = tf::createQuaternionFromRPY(roll, pitch, yaw);

      tf::Vector3 pos;
      tf::quaternionMsgToTF(msg->pose.pose.orientation, quat);
      tf::pointMsgToTF(result.pose.pose.position, pos);

      // publish odom message
      _ground_truth_pub.publish(result);

      // publish transform for tf if there has not been a update from the localization node in the last second
      // since it also publishes the same transform
      if (std::fabs(msg->header.stamp.toSec() - g_last_estimate.toSec()) > 1.0)
      {
        static tf::TransformBroadcaster br;
        tf::Transform transform{ quat, pos };
        br.sendTransform(tf::StampedTransform(transform, msg->header.stamp, "odom", "base_footprint"));

        tf::Transform utm_to_odom;
      }
    }
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
        RCLCPP_WARN(this->get_logger(), "Another odom -> utm tf broadcast detected. Disabling ground_truth odom -> utm tf broadcast.");
        enabled = false;
        return;
      }
      br.sendTransform(tf::StampedTransform(odom_to_utm, event.current_real, "odom", "utm"));
    }
  }
} // namespace ground_truth

RCLCPP_COMPONENTS_REGISTER_NODE(ground_truth::GroundTruth)
