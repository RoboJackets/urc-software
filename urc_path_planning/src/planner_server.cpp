#include <cstdint>
#include <stdexcept>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

#include "urc_path_planning/planner_server.hpp"
#include "urc_path_planning/astar.hpp"
#include "urc_path_planning/gradient_descent_smoother.hpp"

namespace planner_server
{
PlannerServer::PlannerServer(const rclcpp::NodeOptions & options)
: rclcpp::Node("planner_server", options)
{
  RCLCPP_INFO(get_logger(), "Planner server started.");

  declare_parameter<double>("smoothing.data_weight", 0.5);
  declare_parameter<double>("smoothing.smoothness_weight", 0.1);
  declare_parameter<double>("smoothing.tolerance", 0.001);
  declare_parameter<int64_t>("smoothing.maximum_iterations", 1000);

  // Create the service
  plan_service_ = create_service<urc_msgs::srv::GeneratePlan>(
    "plan",
    std::bind(&PlannerServer::generatePlan, this, std::placeholders::_1, std::placeholders::_2));

  // Create the publisher
  plan_publisher_ = create_publisher<nav_msgs::msg::Path>(
    "/path",
    rclcpp::SystemDefaultsQoS());

  // Setup the costmap
  costmap_subscriber_ = create_subscription<grid_map_msgs::msg::GridMap>(
    "/costmap",
    rclcpp::SystemDefaultsQoS(),
    std::bind(&PlannerServer::handleCostmap, this, std::placeholders::_1));
}

void PlannerServer::handleCostmap(const grid_map_msgs::msg::GridMap::SharedPtr msg)
{
  // RCLCPP_INFO(get_logger(), "Received Costmap!");
  current_costmap_ = *msg;
}

PlannerServer::~PlannerServer() {}

void PlannerServer::generatePlan(
  const std::shared_ptr<urc_msgs::srv::GeneratePlan::Request> request,
  std::shared_ptr<urc_msgs::srv::GeneratePlan::Response> response)
{
  try {
    astar::AStar astar;
    astar.setCostmapLayer("traversability_inflated");
    astar.setMap(current_costmap_);

    auto start = request->start.pose;
    auto goal = request->goal.pose;

    astar.createPlan(start, goal);

    const double data_weight = get_parameter("smoothing.data_weight").as_double();
    const double smoothness_weight = get_parameter("smoothing.smoothness_weight").as_double();
    const double tolerance = get_parameter("smoothing.tolerance").as_double();
    const int64_t maximum_iterations = get_parameter("smoothing.maximum_iterations").as_int();

    if (maximum_iterations <= 0) {
      throw std::invalid_argument("smoothing.maximum_iterations must be positive");
    }

    std::vector<astar::AStarNode> path = astar.getPath();

    std::vector<geometry_msgs::msg::PoseStamped> poses;

    for (auto & node : path) {
      geometry_msgs::msg::PoseStamped pose;

      pose.header.frame_id = "map";
      pose.header.stamp = get_clock()->now();
      pose.pose = node.getPose();

      poses.push_back(pose);
    }

    nav_msgs::msg::Path plan;
    plan.header.frame_id = "map";
    plan.header.stamp = get_clock()->now();
    plan.poses = poses;

    urc_path_planning::SmoothingParameters smoothing_parameters {
      data_weight,
      smoothness_weight,
      tolerance,
      static_cast<std::size_t>(maximum_iterations)
    };

    const urc_path_planning::GradientDescentSmoother smoother(smoothing_parameters);

    plan = smoother.smooth(plan);

    response->path = plan;
    response->error_code = urc_msgs::srv::GeneratePlan::Response::SUCCESS;

    RCLCPP_INFO(get_logger(), "Returning plan with %ld poses", plan.poses.size());

    publishPlan(plan);
  } catch (const std::exception & e) {
    RCLCPP_ERROR(get_logger(), "Error generating plan: %s", e.what());
    response->error_code = urc_msgs::srv::GeneratePlan::Response::FAILURE;
  }
}

void PlannerServer::publishPlan(const nav_msgs::msg::Path & plan)
{
  auto msg = std::make_unique<nav_msgs::msg::Path>(plan);
  if (plan_publisher_->get_subscription_count() > 0) {
    plan_publisher_->publish(std::move(msg));
  }
}
} // namespace planner_server

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(planner_server::PlannerServer)
