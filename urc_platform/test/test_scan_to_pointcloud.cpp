#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include <laser_geometry/laser_geometry.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <rclcpp_components/register_node_macro.hpp>

class TestScanToPointCloud : public rclcpp::Node, public testing::Test
{
public:
  TestScanToPointCloud() 
  : rclcpp::Node("test_scan_to_pointcloud", options)
  {
    getParam("min_dist", min_dist);
    getParam("neighbor_dist", neighbor_dist);
    getParam("offset", offset);
    
    mock_pub = create_publisher<sensor_msgs::msg::PointCloud2>
    ("/pc2", rclcpp::SystemDefaultsQoS()));

    mock_sub = create_subscription<sensor_msgs::msg::PointCloud2>
    ("/scan", rclcpp::SystemDefaultsQoS(), [this](sensor_msgs::msg::PointCloud2 input)
    {
      sub_data = input;
    });
  }

  sensor_msgs::msg::PointCloud2 createPointCloudMsg()
  {
    sensor_msgs::msg::PointCloud2 output;
    output.header.height = 1;
    output.header.width = 3;
    output.header.frame_id = "/lidar";

    output.fields.data = {1, 0, 0};
    projection.projectLaser(filteredScan, output);
    return output;
  }

private:
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2> mock_pub;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2> mock_sub;
  sensor_msgs::msg::PointCloud2 sub_data;

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
  auto future = std::future<sensor_msgs::msg::PointCloud2>(mock_sub.get_future());
  mock_pub.publish(createPointCloudMsg());

  auto cloudComparer = [](uint8_t msg_data[], uint8_t test_data[]){
    for (size_t i{0}; i < (sizeof(uint8_t)/sizeof(test_data)); ++i)
    {
      if (msg_data[i] != test_data[i])
      {
        return false;
      }
      return true;
    }
  }
  
  try
  {
    auto published_cloud_msg = future.get();
  }
  catch(const std::exception&)
  {
    ASSERT_TRUE(false);
  }

  uint8_t msg_data[published_cloud_msg.header.row_step * published_cloud_msg.header.height] = published_cloud_msg.fields.data;
  unit8_t test_data[3] = {-1.4142136, 0, 1};
  ASSERT_TRUE(cloudComparer(msg_data, test_data));
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