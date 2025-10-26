#include <cmath>
#include <memory>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "urc_msgs/msg/swerve.hpp"

class SwerveModule {
public:
    SwerveModule(double x, double y, const std::string& name)
        : x_(x), y_(y), name_(name), angle_(0.0), speed_(0.0) {}

    void calculateKinematics(double vx, double vy, double omega) {
        // Calculate wheel velocity components
        // vx, vy: desired robot velocity in x, y
        // omega: desired robot angular velocity

        // Velocity due to translation
        double wheel_vx = vx;
        double wheel_vy = vy;

        // Velocity due to rotation around robot center
        wheel_vx += -omega * y_;
        wheel_vy += omega * x_;

        // Calculate wheel angle and speed
        speed_ = std::sqrt(wheel_vx * wheel_vx + wheel_vy * wheel_vy);
        if (speed_ > 0) {
            angle_ = std::atan2(wheel_vy, wheel_vx);
        }
    }

    double getSpeed() const { return speed_; }
    double getAngle() const { return angle_; }
    std::string getName() const { return name_; }

private:
    double x_;  // Position relative to robot center
    double y_;
    std::string name_;
    double angle_;  // Wheel orientation angle (radians)
    double speed_;  // Wheel speed
};

class ControlTestNode : public rclcpp::Node {
public:
    ControlTestNode() : Node("control_test_node") {
        // TODO: read in module positions from config file
        // Module positions (meters from robot center)
        // These values should match your actual robot dimensions
        const double module_x = 0.3;  // Distance in x-direction (front/back)
        const double module_y = 0.3;  // Distance in y-direction (left/right)

        modules_.emplace_back(module_x, module_y, "FL");    // Front Left
        modules_.emplace_back(-module_x, module_y, "FR");   // Front Right
        modules_.emplace_back(-module_x, -module_y, "BL");  // Back Left
        modules_.emplace_back(module_x, -module_y, "BR");   // Back Right

        // Create subscriber to cmd_vel
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            10,
            std::bind(&ControlTestNode::directionCallback, this, std::placeholders::_1));

        // Create publisher for swerve commands
        swerve_publisher_ = this->create_publisher<urc_msgs::msg::Swerve>(
            "/swerve/command",
            10);

        RCLCPP_INFO(this->get_logger(), "Control Test Node Started");
    }

private:
    void directionCallback(const geometry_msgs::msg::Twist::SharedPtr msg) {
        // Control inputs
        double desired_vx = msg->linear.x;
        double desired_vy = msg->linear.y;
        double desired_omega = msg->angular.z;

        // Calculate kinematics for each module
        for (auto& module : modules_) {
            module.calculateKinematics(desired_vx, desired_vy, desired_omega);
        }

        // Create and publish swerve message
        auto swerve_msg = urc_msgs::msg::Swerve();
        swerve_msg.fl_drive_ang_vel = static_cast<float>(modules_[0].getSpeed());
        swerve_msg.fl_steer_ang = static_cast<float>(modules_[0].getAngle());
        swerve_msg.fr_drive_ang_vel = static_cast<float>(modules_[1].getSpeed());
        swerve_msg.fr_steer_ang = static_cast<float>(modules_[1].getAngle());
        swerve_msg.bl_drive_ang_vel = static_cast<float>(modules_[2].getSpeed());
        swerve_msg.bl_steer_ang = static_cast<float>(modules_[2].getAngle());
        swerve_msg.br_drive_ang_vel = static_cast<float>(modules_[3].getSpeed());
        swerve_msg.br_steer_ang = static_cast<float>(modules_[3].getAngle());

        swerve_publisher_->publish(swerve_msg);
    }

    std::vector<SwerveModule> modules_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<urc_msgs::msg::Swerve>::SharedPtr swerve_publisher_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ControlTestNode>());
    rclcpp::shutdown();
    return 0;
}
