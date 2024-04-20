#include <gtest/gtest.h>
#include "geometry_util.hpp"
#include <geometry_msgs/msg/point.hpp>

TEST(trajectory_following, circle_segment_intersection_test)
{
  geometry_msgs::msg::Point a;
  a.x = 0.0;
  a.y = 0.0;

  geometry_msgs::msg::Point b;
  b.x = -0.8;
  b.y = 0.0;

  auto intersection = geometry_util::circleSegmentIntersection(a, b, 0.5);
  EXPECT_NEAR(intersection.x, -0.5, 1e-6);
  EXPECT_NEAR(intersection.y, 0.0, 1e-6);
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
