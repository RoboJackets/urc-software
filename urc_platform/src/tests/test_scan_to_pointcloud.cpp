#include <gtest/gtest.h>
#include <pcl/point_types.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <ros/publisher.h>
#include <ros/ros.h>
#include <mocking_utils/mock_subscriber.h>

class TestScanToPointCloud : public rclcpp::Node, public testing::Test
{
public:
  TestScanToPointCloud() 
  : rclcpp::Node("test_scan_to_pointcloud", options)
  {
    getParam("min_dist", min_dist);
    getParam("neighbor_dist", neighbor_dist);
    getParam("offset", offset);
    
    mock_pub = create_publisher<pcl::PointCloud<pcl::PointXYZ>>
    ("/pc2", rclcpp::SystemDefaultsQoS()));

    mock_sub = create_subscription<pcl::PointCloud<pcl::PointXYZ>>
    ("/scan", rclcpp::SystemDefaultsQoS(), [this](pcl::PointCloud<pcl::PointXYZ> input)
    {
      sub_data = input;
    });
  }

  pcl::PointCloud<pcl::PointXYZ> createPointCloudMsg()
  {
    pcl::PointCloud<pcl::PointXYZ> cloud;
    pcl::PointXYZ point(1, 1, 1);
    cloud.points.push_back(point);
    cloud.header.frame_id = "/lidar";

    tf::Quaternion quaternion_mag;
    quaternion_mag.setRPY(0, 0, offset);
    tf::Transform trans;
    trans.setRotation(quaternion_mag);
    pcl_ros::transformPointCloud(cloud, cloud, trans);
    return cloud;
  }

protected:
  rclcpp::Publisher<pcl::PointCloud<pcl::PointXYZ>> mock_pub;
  rclcpp::Subscription<pcl::PointCloud<pcl::PointXYZ> mock_sub;
  pcl::PointCloud<pcl::PointXYZ> sub_data;

private:
  double min_dist;
  double neighbor_dist;
  double offset;
};

TEST_F(TestScanToPointCloud, ParameterTest)
{
  ASSERT_TRUE(min_dist == 0.1);
  ASSERT_TRUE(neighbor_dist == 0.2);
  ASSERT_TRUE(offset == 2.35619449019);
}

TEST_F(TestScanToPointCloud, ComparisonTest)
{
  auto future = std::future<pcl::PointCloud<pcl::PointXYZ>>(mock_sub.get_future());
  mock_pub.publish(createPointCloudMsg());

  auto cloudComparer = [](const pcl::PointCloud<pcl::PointXYZ>& p1, const pcl::PointCloud<pcl::PointXYZ>& p2) {
    double difference =
        (p1.points[0].x - p2.points[0].x) + (p1.points[0].y - p2.points[0].y) + (p1.points[0].z - p2.points[0].z);
    return (abs(difference) < .01);
  };

  pcl::PointCloud<pcl::PointXYZ> test_cloud;
  pcl::PointXYZ point(-1.4142136, 0, 1);
  test_cloud.points.push_back(point);
  test_cloud.header.frame_id = "/lidar";

  try
  {
    auto published_cloud = future.get();
  }
  catch(const std::exception&)
  {
    ASSERT_TRUE(false);
  }
  
  ASSERT_TRUE(cloudComparer(published_cloud, test_cloud)); 
}

int main(int argc, char** argv)
{
  rclcpp::init(argc, argc, "scan_to_pointcloud");
  rclcpp::spin(std::make_shared<TestScanToPointCloud>());
  testing::InitGoogleTest(&argc, argv);
  
  int result = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return result;
}