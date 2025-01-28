#include <GLFW/glfw3.h>
#include <mujoco/mujoco.h>

#include <chrono>
#include <geometry_msgs/msg/detail/pose__struct.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <mutex>
#include <rclcpp/qos.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <string>
#include <thread>

#include "mujoco/mjdata.h"
#include "mujoco/mjmodel.h"
#include "mujoco/mjrender.h"

int main(int argc, char** argv)
{
  // Initialize ROS
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("arm_mjsim");
  auto logger = node->get_logger();

  // Publishers
  auto joint_state_pub = node->create_publisher<sensor_msgs::msg::JointState>("~/joint_states", rclcpp::QoS(10));
  auto base_pose_pub = node->create_publisher<geometry_msgs::msg::Pose>("~/base_pose", rclcpp::QoS(10));

  // Parameters
  node->declare_parameter("model_path", "");
  node->declare_parameter("fps", 60.0);
  node->declare_parameter("policy_rate_hz", 120.0);

  std::string model_path = node->get_parameter("model_path").as_string();
  double fps = node->get_parameter("fps").as_double();
  double policy_rate_hz = node->get_parameter("policy_rate_hz").as_double();

  // Load model
  char error[1000] = "Could not load model";
  mjModel* m = mj_loadXML(model_path.c_str(), nullptr, error, sizeof(error));
  if (!m)
  {
    RCLCPP_ERROR(logger, "Error loading model:\n%s", error);
    rclcpp::shutdown();
    return 1;
  }

  // Create mjData
  mjData* d = mj_makeData(m);
  if (!d)
  {
    RCLCPP_ERROR(logger, "Could not create mjData.");
    mj_deleteModel(m);
    rclcpp::shutdown();
    return 1;
  }

  // Initialize GLFW
  if (!glfwInit())
  {
    RCLCPP_ERROR(logger, "Could not initialize GLFW.");
    mj_deleteData(d);
    mj_deleteModel(m);
    rclcpp::shutdown();
    return 1;
  }

  // Create window
  GLFWwindow* window = glfwCreateWindow(1200, 900, "MuJoCo", nullptr, nullptr);
  if (!window)
  {
    RCLCPP_ERROR(logger, "Could not create GLFW window.");
    glfwTerminate();
    mj_deleteData(d);
    mj_deleteModel(m);
    rclcpp::shutdown();
    return 1;
  }
  glfwMakeContextCurrent(window);

  // MuJoCo visualization
  mjvCamera cam;
  mjvOption opt;
  mjvScene scn;
  mjrContext con;
  mjv_defaultCamera(&cam);
  cam.trackbodyid = 0;
  mjv_defaultOption(&opt);
  mjv_defaultScene(&scn);
  mjr_defaultContext(&con);
  mjv_makeScene(m, &scn, 2000);
  mjr_makeContext(m, &con, mjFONTSCALE_150);

  // Camera
  cam.azimuth = 0.0f;
  cam.elevation = -20.0f;
  cam.distance = 2.0f;
  cam.lookat[0] = 0.0f;
  cam.lookat[1] = 0.0f;
  cam.lookat[2] = 0.5f;

  // Timings
  double sim_dt = m->opt.timestep;
  double render_dt = 1.0 / fps;
  double sim_accum = 0.0;
  double render_accum = 0.0;
  auto last_time = std::chrono::steady_clock::now();

  // Mutex
  std::mutex data_mutex;

  // JointState template
  sensor_msgs::msg::JointState joint_state_msg;
  joint_state_msg.header.frame_id = "base_link";

  // Publisher thread
  int floating_base_pos_id = mj_name2id(m, mjOBJ_SENSOR, "floating_base_pos");
  int floating_base_ori_id = mj_name2id(m, mjOBJ_SENSOR, "floating_base_ori");

  // Sensor address offsets
  geometry_msgs::msg::Pose pose_msg;
  std::thread([&]() {
    rclcpp::Rate rate(policy_rate_hz);
    while (rclcpp::ok())
    {
      sensor_msgs::msg::JointState msg;

      {
        std::lock_guard<std::mutex> lock(data_mutex);

        // 1) --- Fill JointState (your existing code) ---
        msg.header.stamp = node->now();
        msg.name.reserve(m->njnt);
        msg.position.reserve(m->njnt);
        msg.velocity.reserve(m->njnt);
        msg.effort.reserve(m->njnt);
        for (int i = 0; i < m->njnt; i++)
        {
          const char* name = mj_id2name(m, mjOBJ_JOINT, i);
          if (name)
          {
            msg.name.emplace_back(std::string(name));
            int qpos_addr = m->jnt_qposadr[i];
            int qvel_addr = m->jnt_dofadr[i];
            if (qpos_addr < m->nq && qvel_addr < m->nv)
            {
              msg.position.emplace_back(d->qpos[qpos_addr]);
              msg.velocity.emplace_back(d->qvel[qvel_addr]);
              msg.effort.emplace_back(d->qfrc_applied[qvel_addr]);
            }
            else
            {
              msg.position.emplace_back(0.0);
              msg.velocity.emplace_back(0.0);
              msg.effort.emplace_back(0.0);
            }
          }
        }

        if (floating_base_pos_id != -1 && floating_base_ori_id != -1)
        {
          int floating_base_pos_adr = m->sensor_adr[floating_base_pos_id];
          int floating_base_ori_adr = m->sensor_adr[floating_base_ori_id];

          // Retrieve position
          double x = d->sensordata[floating_base_pos_adr + 0];
          double y = d->sensordata[floating_base_pos_adr + 1];
          double z = d->sensordata[floating_base_pos_adr + 2];

          // Retrieve orientation: MuJoCo's <framequat> is (qw, qx, qy, qz)
          double qw = d->sensordata[floating_base_ori_adr + 0];
          double qx = d->sensordata[floating_base_ori_adr + 1];
          double qy = d->sensordata[floating_base_ori_adr + 2];
          double qz = d->sensordata[floating_base_ori_adr + 3];

          pose_msg.position.x = x;
          pose_msg.position.y = y;
          pose_msg.position.z = z;

          pose_msg.orientation.w = qw;
          pose_msg.orientation.x = qx;
          pose_msg.orientation.y = qy;
          pose_msg.orientation.z = qz;
        }
      }

      joint_state_pub->publish(msg);
      base_pose_pub->publish(pose_msg);

      rate.sleep();
    }
  }).detach();

  // For real-time factor
  double simulation_time = 0.0;
  double wall_time = 0.0;

  // Mouse interaction
  bool mouse_left = false;
  double last_x = 0.0, last_y = 0.0;

  // Callbacks
  struct Callbacks
  {
    std::function<void(GLFWwindow*, int, int, int, int)> key_callback;
    std::function<void(GLFWwindow*, int, int, int)> mouse_button_callback;
    std::function<void(GLFWwindow*, double, double)> cursor_position_callback;
    std::function<void(GLFWwindow*, double, double)> scroll_callback;
  } callbacks;

  callbacks.key_callback = [&](GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
    {
      if (key == GLFW_KEY_R)
      {
        std::lock_guard<std::mutex> lock(data_mutex);
        mj_resetData(m, d);
      }
    }
  };

  callbacks.mouse_button_callback = [&](GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT)
      mouse_left = (action == GLFW_PRESS);
  };

  callbacks.cursor_position_callback = [&](GLFWwindow* window, double xpos, double ypos) {
    if (mouse_left)
    {
      double dx = xpos - last_x;
      double dy = ypos - last_y;
      cam.azimuth -= dx * 0.1;
      cam.elevation -= dy * 0.1;
    }
    last_x = xpos;
    last_y = ypos;
  };

  callbacks.scroll_callback = [&](GLFWwindow* window, double xoffset, double yoffset) {
    cam.distance -= yoffset * 0.1;
    if (cam.distance < 0.1f)
      cam.distance = 0.1f;
  };

  glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto user_pointer = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
    user_pointer->key_callback(window, key, scancode, action, mods);
  });
  glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
    auto user_pointer = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
    user_pointer->mouse_button_callback(window, button, action, mods);
  });
  glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
    auto user_pointer = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
    user_pointer->cursor_position_callback(window, xpos, ypos);
  });
  glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
    auto user_pointer = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
    user_pointer->scroll_callback(window, xoffset, yoffset);
  });
  glfwSetWindowUserPointer(window, &callbacks);

  // Subscriber for control
  auto joint_pos_cmd_sub = node->create_subscription<std_msgs::msg::Float64MultiArray>(
      "~/torque_ctrl",
      rclcpp::SystemDefaultsQoS(),
      [&](const std_msgs::msg::Float64MultiArray& msg) {
        std::lock_guard<std::mutex> lock(data_mutex);
        int i = 0;
        for (auto eff : msg.data)
        {
          const int qvel_addr = m->jnt_dofadr[i++];
          d->qfrc_applied[qvel_addr] = eff;
        }
      }
  );

  // Simulation control flags
  bool simulation_paused = false;

  // Services to start/pause simulation
  auto start_service = node->create_service<std_srvs::srv::Trigger>(
      "~/start_simulation",
      [&](const std::shared_ptr<std_srvs::srv::Trigger::Request>,
          std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        RCLCPP_INFO(logger, "Simulation started.");
        simulation_time = 0.0;
        sim_accum = 0.0;
        wall_time = 0.0;
        simulation_paused = false;
        res->success = true;
      }
  );

  auto pause_service = node->create_service<std_srvs::srv::Trigger>(
      "~/pause_simulation",
      [&](const std::shared_ptr<std_srvs::srv::Trigger::Request>,
          std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        RCLCPP_INFO(logger, "Simulation paused.");
        simulation_paused = true;
        res->success = true;
      }
  );

  auto reset_service = node->create_service<std_srvs::srv::Trigger>(
      "~/reset_simulation",
      [&](const std::shared_ptr<std_srvs::srv::Trigger::Request>,
          std::shared_ptr<std_srvs::srv::Trigger::Response> res) {
        RCLCPP_INFO(logger, "Simulation reset.");
        std::lock_guard<std::mutex> lock(data_mutex);
        mj_resetData(m, d);
        simulation_time = 0.0;
        sim_accum = 0.0;
        mj_step(m, d);
        res->success = true;
      }
  );

  // Main loop
  mj_step(m, d);
  while (!glfwWindowShouldClose(window) && rclcpp::ok())
  {
    auto now_time = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(now_time - last_time).count();
    last_time = now_time;

    sim_accum += elapsed;
    wall_time += elapsed;

    // Step simulation if not paused
    if (!simulation_paused)
    {
      while (sim_accum >= sim_dt)
      {
        mj_step(m, d);
        sim_accum -= sim_dt;
        simulation_time += sim_dt;
      }
    }

    // Rendering
    render_accum += elapsed;
    if (render_accum >= render_dt)
    {
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      mjrRect viewport = { 0, 0, width, height };

      {
        std::lock_guard<std::mutex> lock(data_mutex);
        mjv_updateScene(m, d, &opt, nullptr, &cam, mjCAT_ALL, &scn);
      }

      double real_time_factor = wall_time > 0.0 ? simulation_time / wall_time : 0.0;
      std::string rt_text = "Real Time Factor: " + std::to_string(real_time_factor).substr(0, 5);
      mjr_render(viewport, &scn, &con);
      mjr_overlay(mjFONTSCALE_50, mjGRID_TOPRIGHT, viewport, rt_text.c_str(), nullptr, &con);
      mjr_overlay(mjFONT_NORMAL, mjGRID_TOPLEFT, viewport, "ROS2 Mujoco Simulator\nV0.1.0", nullptr, &con);
      mjr_overlay(mjFONT_NORMAL, mjGRID_BOTTOMLEFT, viewport, simulation_paused ? "Paused" : "Active", nullptr, &con);

      glfwSwapBuffers(window);
      glfwPollEvents();

      render_accum = 0.0;
    }

    // Spin ROS
    rclcpp::spin_some(node);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  // Cleanup
  mjv_freeScene(&scn);
  mjr_freeContext(&con);
  glfwDestroyWindow(window);
  glfwTerminate();
  mj_deleteData(d);
  mj_deleteModel(m);
  rclcpp::shutdown();

  return 0;
}