#include "slam_node.hpp"

#include <functional>
#include <limits>


#include <cmath>
#include <Eigen/Cholesky>

#include <gtsam/geometry/Rot3.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/NavState.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/transforms.h>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>

namespace {
    //About 5 s of imu history at 100 Hz
    constexpr std::size_t kMaximumImuBufferSize = 500;
    constexpr double kUnitQuaternionTolerance = 1e-3;
}

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
                gtsam::Pose3()
                
            ),
            previous_keyframe_cloud(nullptr),
            maximum_fitness_score(
                declare_parameter<double>("lidar_frontend.maximum_fitness_score", 0.3)
            ),
            backend(
                declare_parameter<double>("keyframe.translation_threshold_m", 0.5),
                declare_parameter<double>("keyframe.rotation_threshold_rad", 0.174533),
                gtsam::Vector6::Constant(0.1),
                gtsam::Vector3::Constant(1.0),
                gtsam::Vector6::Constant(0.2),
                gtsam::Vector6::Constant(1e-3),
                gtsam::Vector6::Constant(1e-4)
            ),
            previous_imu_stamp(std::nullopt),
            latest_keyframe_index(0),
            accumulated_map(new LidarFrontend::Cloud)

    {
        imu_topic = declare_parameter<std::string>("imu_topic", "/imu/data");
        lidar_topic = declare_parameter<std::string>("lidar_topic", "/points");
        gps_topic = declare_parameter<std::string>("gps_topic", "/slam/gps_odometry");
        slam_odom_topic = declare_parameter<std::string>("slam_odom_topic", "/slam/odometry");
        map_frame = declare_parameter<std::string>("map_frame", "map");
        base_link_frame = declare_parameter<std::string>("base_link_frame", "base_link");

        // Identity initialization disabled: the backend is now initialized at the
        // first keyframe from the IMU's roll and pitch, so gravity does not leak
        // into the IMU prediction when the rover starts tilted.
        // backend.initialize(
        //     gtsam::NavState(
        //         gtsam::Pose3(),
        //         gtsam::Vector3::Zero()
        //     ),
        //     gtsam::imuBias::ConstantBias()
        // );

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

        gps_sub = create_subscription<nav_msgs::msg::Odometry>(
            gps_topic,
            rclcpp::SensorDataQoS(),
            std::bind(
                &SlamNode::gpsCallback,
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

        map_pub = create_publisher<sensor_msgs::msg::PointCloud2>(
            "/slam/map_points",
            rclcpp::QoS(1).reliable().transient_local()
        );
    }

    void SlamNode::imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg) {
        imu_buffer.push_back({
            rclcpp::Time(msg->header.stamp),
            gtsam::Vector3(
                msg->linear_acceleration.x,
                msg->linear_acceleration.y,
                msg->linear_acceleration.z
            ),
            gtsam::Vector3(
                msg->angular_velocity.x,
                msg->angular_velocity.y,
                msg->angular_velocity.z
            )
        });

        while (imu_buffer.size() > kMaximumImuBufferSize) {
            imu_buffer.pop_front();
        }

        // Stored to initialize the starting orientation from gravity
        const gtsam::Quaternion orientation(
            msg->orientation.w,
            msg->orientation.x,
            msg->orientation.y,
            msg->orientation.z
        );
        if (std::abs(orientation.norm() - 1.0) < kUnitQuaternionTolerance) {
            latest_imu_orientation = gtsam::Rot3(orientation.normalized());
        }

    }

    bool SlamNode::integrateImuUntil(const rclcpp::Time &stamp) {
        if (imu_buffer.empty() || imu_buffer.back().stamp < stamp) {
            return false;
        }

        while (!imu_buffer.empty() && imu_buffer.front().stamp <= stamp) {
            const ImuSample sample = imu_buffer.front();
            imu_buffer.pop_front();

            const double dt = (sample.stamp - previous_imu_stamp.value()).seconds();
            previous_imu_stamp = sample.stamp;

            if (dt <= 0 || dt > 0.1) {
                continue;
            }
            backend.integrateImuMeasurement(
                sample.acceleration, sample.angular_velocity, dt
            );
        }


        const double remaining_dt = (stamp - previous_imu_stamp.value()).seconds();
        if (remaining_dt > 0.0) {
            const ImuSample &next = imu_buffer.front();
            backend.integrateImuMeasurement(
                next.acceleration, next.angular_velocity, remaining_dt
            );
        }
        previous_imu_stamp = stamp;


        return true;
    }

    void SlamNode::discardImuUntil(const rclcpp::Time &stamp) {
        while (!imu_buffer.empty() && imu_buffer.front().stamp <= stamp) {
            imu_buffer.pop_front();
        }
        previous_imu_stamp = stamp;
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
        const rclcpp::Time scan_stamp(msg->header.stamp);

        // First cloud is keyframe zero
        if (!previous_keyframe_cloud) {
            // Initialize from IMU roll and pitch instead of identity so the
            // starting orientation is gravity-aligned. Yaw stays zero to keep
            // the map frame anchored to the starting heading.
            if (!latest_imu_orientation) {
                RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 1000,
                    "Waiting for IMU orientation to initialize SLAM");
                return;
            }
            const gtsam::Rot3 initial_rotation = gtsam::Rot3::Ypr(
                0.0,
                latest_imu_orientation->pitch(),
                latest_imu_orientation->roll()
            );
            backend.initialize(
                gtsam::NavState(
                    gtsam::Pose3(initial_rotation, gtsam::Point3::Zero()),
                    gtsam::Vector3::Zero()
                ),
                gtsam::imuBias::ConstantBias()
            );

            previous_keyframe_cloud = current_cloud;
            latest_keyframe_index = 0;
            discardImuUntil(scan_stamp);

            keyframe_clouds.push_back(current_cloud);
            keyframe_stamps.push_back({
                0, rclcpp::Time(msg->header.stamp)
            });
            addKeyframeToMap(current_cloud, rclcpp::Time(msg->header.stamp));
            processGPSMeasurements();
            publishOutputs(rclcpp::Time(msg->header.stamp));
            return;
        }

        if (!integrateImuUntil(scan_stamp)) {
            RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 1000,
                "Waiting for IMU data to reach the LiDAR scan stamp");
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
            imu_relative_guess
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


        // Stage imu state, then optimize with LiDAR constraint
        backend.addImuKeyframe();
        backend.addLidarFactor(
            previous_index,
            current_index,
            registration.relative_pose
        );
        backend.optimize();

        latest_keyframe_index = current_index;
        previous_keyframe_cloud = current_cloud;

        keyframe_clouds.push_back(current_cloud);
        keyframe_stamps.push_back({
            current_index, scan_stamp
        });
        addKeyframeToMap(current_cloud, scan_stamp);
        processGPSMeasurements();
        publishOutputs(scan_stamp);
    }

    void SlamNode::gpsCallback(nav_msgs::msg::Odometry::SharedPtr msg) {
        if (msg->header.frame_id != map_frame) {
            return;
        }

        const auto &p = msg->pose.pose.position;
        if (!std::isfinite(p.x) ||
            !std::isfinite(p.y) ||
            !std::isfinite(p.z)) {
            return;
        }

        // Extract position block from 6x6 pose covariance
        Eigen::Matrix3d covariance;
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                covariance(row, col) = msg->pose.covariance[row * 6 + col];
            }
        }

        if (!covariance.allFinite() || !covariance.isApprox(covariance.transpose())) {
            return;
        }

        Eigen::LLT<Eigen::Matrix3d> decomposition(covariance);
        if (decomposition.info() != Eigen::Success) {
            return;
        }

        // Keep timestamps strictly increasing; discard duplicates
        const rclcpp::Time stamp(msg->header.stamp);
        if (last_accepted_gps_stamp && stamp <= *last_accepted_gps_stamp) {
            return;
        }

        gps_buffer.push_back(*msg);
        last_accepted_gps_stamp = stamp;
        while (gps_buffer.size() > 200) {
            gps_buffer.pop_front();
        }

        processGPSMeasurements();

    }

    void SlamNode::processGPSMeasurements() {
        if (keyframe_stamps.empty()) {
            return;
        }

        while (!gps_buffer.empty()) {
            const auto &gps = gps_buffer.front();
            const rclcpp::Time gps_stamp(gps.header.stamp);

            // Wait until keyframes bracket this measurement's time
            if (gps_stamp > keyframe_stamps.back().stamp) {
                break;
            }

            double best_dt = std::numeric_limits<double>::infinity();
            std::size_t best_index = 0;

            for (const auto &keyframe : keyframe_stamps) {
                const double dt = std::abs((keyframe.stamp - gps_stamp).seconds());

                if (dt < best_dt) {
                    best_dt = dt;
                    best_index = keyframe.index;
                }
            }

            if (best_dt <= gps_time_tolerance_sec) {
                matched_gps.push_back({best_index, gps});
            }

            // Consume matched fixes and discard those outside tolerance
            gps_buffer.pop_front();
        }

        const bool has_gps_updates = !matched_gps.empty();
        while (!matched_gps.empty()) {
            const auto &match = matched_gps.front();
            const auto &p = match.measurement.pose.pose.position;

            gtsam::Matrix3 covariance;
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    covariance(row, col) = match.measurement.pose.covariance[row*6 + col];
                }
            }

            backend.addGpsFactor(
                match.keyframe_index,
                gtsam::Point3(p.x, p.y, p.z),
                covariance
            );

            matched_gps.pop_front();

        }
        if (has_gps_updates) {
            backend.optimize();
            rebuildMap();
            publishOutputs(keyframe_stamps.back().stamp);

        }
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
        path_msg.poses.resize(latest_keyframe_index + 1);
        path_msg.poses.at(latest_keyframe_index) = pose_msg;
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

    void SlamNode::rebuildMap() {
        if (keyframe_stamps.empty()) {
            return;
        }

        accumulated_map->clear();
        path_msg.poses.clear();
        path_msg.header.frame_id = map_frame;
        path_msg.header.stamp = keyframe_stamps.back().stamp;
        path_msg.poses.reserve(keyframe_stamps.size());

        for (const auto &keyframe : keyframe_stamps) {
            const gtsam::Pose3 pose = backend.poseAt(keyframe.index);

            // Match the frontend's current identity base_T_lidar assumption.
            LidarFrontend::Cloud transformed;
            pcl::transformPointCloud(
                *keyframe_clouds.at(keyframe.index),
                transformed,
                pose.matrix()
            );
            *accumulated_map += transformed;

            geometry_msgs::msg::PoseStamped pose_msg;
            pose_msg.header.frame_id = map_frame;
            pose_msg.header.stamp = keyframe.stamp;
            const auto &position = pose.translation();
            const auto rotation = pose.rotation().toQuaternion();
            pose_msg.pose.position.x = position.x();
            pose_msg.pose.position.y = position.y();
            pose_msg.pose.position.z = position.z();
            pose_msg.pose.orientation.x = rotation.x();
            pose_msg.pose.orientation.y = rotation.y();
            pose_msg.pose.orientation.z = rotation.z();
            pose_msg.pose.orientation.w = rotation.w();
            path_msg.poses.push_back(pose_msg);
        }

        sensor_msgs::msg::PointCloud2 map_msg;
        pcl::toROSMsg(*accumulated_map, map_msg);
        map_msg.header = path_msg.header;
        map_pub->publish(map_msg);
        path_pub->publish(path_msg);
    }

    void SlamNode::addKeyframeToMap(
        const LidarFrontend::Cloud::ConstPtr &cloud,
        const rclcpp::Time &stamp
    ) {
        const gtsam::Pose3 map_T_base = backend.latestEstimate().pose();

        // FIX FOR ACTUAL - base_T_lidar is identity rn
        const gtsam::Pose3 map_T_lidar = map_T_base;

        LidarFrontend::Cloud transformed_cloud;
        pcl::transformPointCloud(*cloud, transformed_cloud, map_T_lidar.matrix());

        *accumulated_map += transformed_cloud;

        sensor_msgs::msg::PointCloud2 map_msg;
        pcl::toROSMsg(*accumulated_map, map_msg);
        map_msg.header.stamp = stamp;
        map_msg.header.frame_id = map_frame;
        map_pub->publish(map_msg);
    }
    
}

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(urc_slam::SlamNode)