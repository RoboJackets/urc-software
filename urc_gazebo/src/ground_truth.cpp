#include "ground_truth.hpp"

namespace ground_truth
{

  GroundTruth::GroundTruth(const rclcpp::NodeOptions &options)
  : rclcpp::Node("ground_truth", options),
    tfBuffer_(this->get_clock()),
    tfListener_(tfBuffer_)
  {
    longitude = declare_parameter<double>("longitude");
    latitude = declare_parameter<double>("latitude");
    
    // Other variables that need to be defined go here (noise variables?)
    //RobotLocalization::NavsatConversions::UTM(latitude, longitude, &utm_x, &utm_y);
    nav_msgs::msg::Odometry og_pose;
    rclcpp::Time last_estimate;
    
    //noise variables
    x_noise_std_dev = declare_parameter<double>("x_noise_std_dev", 0.0);
    y_noise_std_dev = declare_parameter<double>("y_noise_std_dev", 0.0);
    z_noise_std_dev = declare_parameter<double>("z_noise_std_dev", 0.0);
    roll_noise_std_dev = declare_parameter<double>("roll_noise_std_dev", 0.0);
    pitch_noise_std_dev = declare_parameter<double>("pitch_noise_std_dev", 0.0);
    yaw_noise_std_dev = declare_parameter<double>("yaw_noise_std_dev", 0.0);
    std::default_random_engine engine(std::random_device{}());
    x_distribution = std::normal_distribution<double>(0, x_noise_std_dev);
    y_distribution = std::normal_distribution<double>(0, y_noise_std_dev);
    z_distribution = std::normal_distribution<double>(0, z_noise_std_dev);
    roll_distribution = std::normal_distribution<double>(0, roll_noise_std_dev);
    pitch_distribution = std::normal_distribution<double>(0, pitch_noise_std_dev);
    yaw_distribution = std::normal_distribution<double>(0, yaw_noise_std_dev);


    _ground_truth_sub = create_subscription<nav_msgs::msg::Odometry>(
      "~/ground_truth/state_raw", rclcpp::SensorDataQoS(), [this](const nav_msgs::msg::Odometry msg) {
        groundTruthCallback(msg);
      });

    _estimate_sub = create_subscription<nav_msgs::msg::Odometry>(
      "~/odometry/filtered", rclcpp::SystemDefaultsQoS(), [this](const nav_msgs::msg::Odometry msg){
        odomCallback(msg);
      });

    _ground_truth_pub = create_publisher<nav_msgs::msg::Odometry>(
      "~/ground_truth",
      rclcpp::SystemDefaultsQoS());
      
    _banana_pub = create_publisher<std_msgs::msg::Float64>(
      "~/banana",
      rclcpp::SystemDefaultsQoS());

    utm_to_odom.setOrigin(
         tf2::Vector3(utm_x - og_pose.pose.pose.position.x, utm_y - og_pose.pose.pose.position.y, 0.0));
    utm_to_odom.setRotation(createQuaternionMsgFromYaw(M_PI));
  }
  
  tf2::Quaternion GroundTruth::createQuaternionMsgFromYaw(double yaw)
  {
    tf2::Quaternion q;
    q.setRPY(0,0,yaw);
    return q;
  }

  void GroundTruth::groundTruthCallback(const nav_msgs::msg::Odometry & msg)
  {

    // get the starting location as the origin
    if (og_pose.header.stamp.sec == 0)
    {
      og_pose.pose = msg.pose;
      og_pose.header = msg.header;
      og_pose.pose.pose.position.x = msg.pose.pose.position.x + x_distribution(engine);
      og_pose.pose.pose.position.y = msg.pose.pose.position.y + y_distribution(engine);
      og_pose.pose.pose.position.z = msg.pose.pose.position.z + z_distribution(engine);
      RCLCPP_INFO(this->get_logger(), "setting og_pose to %f,%f,%f", og_pose.pose.pose.position.x,og_pose.pose.pose.position.y,og_pose.pose.pose.position.z);
    }
    else
    {
      nav_msgs::msg::Odometry result;
      result.pose = msg.pose;

      // use the initial location as an offset (makes the starting location 0, 0)
      result.pose.pose.position.x = msg.pose.pose.position.x - og_pose.pose.pose.position.x + x_distribution(engine);
      result.pose.pose.position.y = msg.pose.pose.position.y - og_pose.pose.pose.position.y + y_distribution(engine);
      result.pose.pose.position.z = msg.pose.pose.position.z - og_pose.pose.pose.position.z + z_distribution(engine);
      result.twist = msg.twist;

      // set up the correct header
      result.header = msg.header;
      result.child_frame_id = "base_footprint";
      result.header.frame_id = "odom";

      tf2::Quaternion quat(msg.pose.pose.orientation.x, msg.pose.pose.orientation.y, msg.pose.pose.orientation.z,
                          msg.pose.pose.orientation.w);
      tf2::Matrix3x3 m(quat);
      double roll, pitch, yaw;
      m.getRPY(roll, pitch, yaw);

      tf2::Quaternion tempQuat;
      tempQuat.setRPY(roll + roll_distribution(engine), pitch + pitch_distribution(engine), yaw + yaw_distribution(engine));
      
      result.pose.pose.orientation = toMsg(tempQuat);
      quat.setRPY(roll,pitch,yaw);

      tf2::Vector3 pos;
      tf2::fromMsg(msg.pose.pose.orientation, quat);
      tf2::fromMsg(result.pose.pose.position, pos);

      // publish odom message
      _ground_truth_pub->publish(result);
      
      
      // publish transform for tf if there has not been a update from the localization node in the last second
      // since it also publishes the same transform
      if (std::fabs(msg.header.stamp.sec - last_estimate.seconds()) > 1.0)
      {
        geometry_msgs::msg::TransformStamped transformMsg;
        transformMsg.header.frame_id = "odom";
        transformMsg.child_frame_id = "base_footprint";
        transformMsg.header.stamp = this->get_clock()->now();
        transformMsg.transform.translation = toMsg(pos);
        transformMsg.transform.rotation = toMsg(quat);
	      
        br->sendTransform(transformMsg);

        //tf2::Transform utm_to_odom;
      }
    }
  }
      
/*
   void GroundTruth::utmCallback(const rclcpp::TimerEvent & event, const tf2::Transform & odom_to_utm)
   {
     static tf::TransformBroadcaster br;
     static tf::TransformListener tf_listener;
     geometry_msgs::msg::TransformStamped transform_stamped;
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
*/

} // namespace ground_truth
RCLCPP_COMPONENTS_REGISTER_NODE(ground_truth::GroundTruth)
