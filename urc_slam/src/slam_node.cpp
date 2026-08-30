#include "slam_node.hpp"
#include <functional>
#include <gtsam/geometry/Rot3.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/NavState.h>

#include <pcl_conversions/pcl_conversions.h>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>

namespace urc_slam {
    SlamNode::SlamNode(const rclcpp::NodeOptions &options)
        :   rclcpp::Node("slam_node", options),   
            lidar_frontend(
                declare_parameter<double>("lidar_frontend.voxel_size_m", 0.2),
                declare_parameter<double>("lidar_frontend.minimum_range_m", 1.0),
                declare_parameter<double>("lidar_frontend.maximum_range_m", 80.0),
                declare_parameter<double>("lidar_frontend.maximum_correspondence_distance_m", 2.0),
                declare_parameter<int>("lidar_frontend.maximum_iterations", 64),
                declare_parameter<double>("lidar_frontend.transformation_epsilon", 1e-6),
                declare_parameter<double>("lidar_frontend.fitness_epsilon", 1e-6),
                gtsam::Pose3()
                
            ),
            previous_keyframe_cloud(nullptr),
            maximum_fitness_score(
                declare_parameter<double>("lidar_frontend.maximum_fitness_score", 0.5)
            ),
            backend(
                declare_parameter<double>("keyframe.translation_threshold_m", 0.5),
                declare_parameter<double>("keyframe.rotation_threshold_rad", 0.174533),
                gtsam::Vector6::Constant(0.1),
                gtsam::Vector3::Constant(1.0),
                gtsam::Vector6::Constant(1.0),
                gtsam::Vector6::Constant(0.2),
                gtsam::Vector6::Constant(1e-3),
                gtsam::Vector6::Constant(1e-4)
            ),
            previous_imu_stamp(std::nullopt),
            latest_keyframe_index(0)
    {
        imu_topic = declare_parameter<std::string>("imu_topic", "/imu/data");
        lidar_topic = declare_parameter<std::string>("lidar_topic", "/points");
        slam_odom_topic = declare_parameter<std::string>("slam_odom_topic", "/slam/odometry");
        map_frame = declare_parameter<std::string>("map_frame", "map");
        base_link_frame = declare_parameter<std::string>("base_link_frame", "base_link");

        backend.initialize(
            gtsam::NavState(
                gtsam::Pose3(),
                gtsam::Vector3::Zero()
            ),
            gtsam::imuBias::ConstantBias()
        );

        imu_sub = create_subscription<sensor_msgs::msg::Imu>(
            imu_topic,
            rclcpp::SensorDataQoS(),
            std::bind(
                &SlamNode::imuCallback,
                this,
                std::placeholders::_1
            )
        );

        lidar_sub = create_subscription<sensor_msgs::msg::PointCloud2>(
            lidar_topic,
            rclcpp::SensorDataQoS(),
            std::bind(
                &SlamNode::lidarCallback,
                this,
                std::placeholders::_1
            )
        );

        slam_odom_pub = create_publisher<nav_msgs::msg::Odometry>(
            slam_odom_topic,
            10
        );

        path_pub = create_publisher<nav_msgs::msg::Path>(
            "/slam/path",
            10
        );

        tf_broadcaster = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

        path_msg.header.frame_id = map_frame;

    }

    void SlamNode::imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
        const rclcpp::Time current_stamp(msg->header.stamp);

        const gtsam::Vector3 acceleration(
            msg->linear_acceleration.x,
            msg->linear_acceleration.y,
            msg->linear_acceleration.z
        );

        const gtsam::Vector3 angular_velocity(
            msg->angular_velocity.x,
            msg->angular_velocity.y,
            msg->angular_velocity.z
        );

        if (!previous_imu_stamp.has_value()) {
            previous_imu_stamp = current_stamp;
            return;
        }

        const double dt = (current_stamp - previous_imu_stamp.value()).seconds();
        previous_imu_stamp = current_stamp;

        if (dt <= 0.0 || dt > 0.1) {
            return;
        }

        if (!previous_keyframe_cloud) {
            return;
        }

        backend.integrateImuMeasurement(
            acceleration,
            angular_velocity,
            dt
        );

        imu_integrated_since_keyframe = true;
    }  

    void SlamNode::lidarCallback(
        const sensor_msgs::msg::PointCloud2::SharedPtr msg
    ) {


        LidarFrontend::Cloud::Ptr raw_cloud(
            new LidarFrontend::Cloud
        );

        pcl::fromROSMsg(*msg, *raw_cloud);

        const LidarFrontend::Cloud::Ptr current_cloud = lidar_frontend.preprocess(raw_cloud);

        if (!current_cloud || current_cloud->empty()) {
            RCLCPP_WARN(get_logger(), "Discarding empty LiDAR cloud");
            return;
        }

        // First cloud is keyframe zero
        if (!previous_keyframe_cloud) {
            previous_keyframe_cloud = current_cloud;
            latest_keyframe_index = 0;
            imu_integrated_since_keyframe = false;
            publishOutputs(rclcpp::Time(msg->header.stamp));
            return;
        }

        if (!imu_integrated_since_keyframe) {
            return;
        }

        // Use accumulated IMU motion as ICP initial guess
        const gtsam::Pose3 imu_relative_guess = backend.predictedRelativePose();
        const gtsam::Pose3 predicted_global_pose = backend.latestEstimate().pose().compose(
            imu_relative_guess
        );

        if (!backend.shouldCreateKeyframe(predicted_global_pose)) {
            return;
        }

        const LidarRegistrationResult registration = lidar_frontend.registerClouds(
            previous_keyframe_cloud,
            current_cloud,
            //imu_relative_guess
            gtsam::Pose3()
        );

        if (!registration.converged) {
            RCLCPP_WARN(get_logger(), "LiDAR registration did not converge");
            return;
        }

        if (registration.fitness_score > maximum_fitness_score) {
            RCLCPP_WARN(get_logger(), "Rejected LiDAR registration with fitness score  %.3f",
                registration.fitness_score
            );
            return;
        }

        const std::size_t previous_index = latest_keyframe_index;
        const std::size_t current_index = previous_index + 1;

        // Convert icp relative transform to global pose
        const gtsam::Pose3 current_global_pose = backend.latestEstimate().pose().compose(
            registration.relative_pose
        );

        // Stage imu state, then optimize with LiDAR constraint
        backend.addKeyframe(current_global_pose);
        backend.addLidarFactor(
            previous_index,
            current_index,
            registration.relative_pose
        );

        latest_keyframe_index = current_index;
        previous_keyframe_cloud = current_cloud;
        imu_integrated_since_keyframe = false;

        publishOutputs(rclcpp::Time(msg->header.stamp));
    }

    void SlamNode::publishOutputs(const rclcpp::Time &stamp) {
        const gtsam::NavState state = backend.latestEstimate();
        const gtsam::Pose3 pose = state.pose();
        const gtsam::Point3 position = pose.translation();
        const auto orientation = pose.rotation().toQuaternion();

        // gtsam velocity is in the map frame, odometry twist uses base link
        const gtsam::Vector3 body_velocity = pose.rotation().unrotate(state.v());

        nav_msgs::msg::Odometry odometry_msg;
        odometry_msg.header.stamp = stamp;
        odometry_msg.header.frame_id = map_frame;
        odometry_msg.child_frame_id = base_link_frame;

        odometry_msg.pose.pose.position.x = position.x();
        odometry_msg.pose.pose.position.y = position.y();
        odometry_msg.pose.pose.position.z = position.z();

        odometry_msg.pose.pose.orientation.w = orientation.w();
        odometry_msg.pose.pose.orientation.x = orientation.x();
        odometry_msg.pose.pose.orientation.y = orientation.y();
        odometry_msg.pose.pose.orientation.z = orientation.z();

        odometry_msg.twist.twist.linear.x = body_velocity.x();
        odometry_msg.twist.twist.linear.y = body_velocity.y();
        odometry_msg.twist.twist.linear.z = body_velocity.z();

        slam_odom_pub->publish(odometry_msg);

        geometry_msgs::msg::PoseStamped pose_msg;
        pose_msg.header = odometry_msg.header;
        pose_msg.pose = odometry_msg.pose.pose;

        path_msg.header.stamp = stamp;
        path_msg.poses.push_back(pose_msg);
        path_pub->publish(path_msg);
        
        geometry_msgs::msg::TransformStamped transform_msg;
        transform_msg.header.stamp = stamp;
        transform_msg.header.frame_id = map_frame;
        transform_msg.child_frame_id = base_link_frame;

        transform_msg.transform.translation.x = position.x();
        transform_msg.transform.translation.y = position.y();
        transform_msg.transform.translation.z = position.z();

        transform_msg.transform.rotation = odometry_msg.pose.pose.orientation;
        tf_broadcaster->sendTransform(transform_msg);
    }
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_slam::SlamNode)