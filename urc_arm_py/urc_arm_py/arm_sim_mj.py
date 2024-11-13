import mujoco
import glfw
import rclpy
from rclpy.node import Node
import numpy as np
from sensor_msgs.msg import JointState


class MjSimNode(Node):
    def __init__(self):
        super().__init__("arm_mj_sim")

        self.declare_parameter("model_dir", "")
        model_dir = self.get_parameter("model_dir").get_parameter_value().string_value
        self.get_logger().warn(f"Loading model from: {model_dir}")
        # Load the MuJoCo model
        self.model = mujoco.MjModel.from_xml_path(model_dir)
        self.data = mujoco.MjData(self.model)

        # Initialize GLFW
        if not glfw.init():
            raise Exception("Failed to initialize GLFW")

        # Create the MuJoCo rendering context and window
        self.window = glfw.create_window(1280, 720, "MuJoCo Simulation", None, None)
        if not self.window:
            glfw.terminate()
            raise Exception("Failed to create GLFW window")

        glfw.make_context_current(self.window)
        glfw.set_key_callback(self.window, self.key_callback)
        glfw.set_cursor_pos_callback(self.window, self.mouse_move_callback)
        glfw.set_mouse_button_callback(self.window, self.mouse_button_callback)
        glfw.set_scroll_callback(self.window, self.scroll_callback)

        # Initialize required rendering components
        self.scene = mujoco.MjvScene(self.model, maxgeom=1000)
        self.ctx = mujoco.MjrContext(self.model, mujoco.mjtFontScale.mjFONTSCALE_150)
        self.cam = mujoco.MjvCamera()
        self.opt = mujoco.MjvOption()
        self.pert = mujoco.MjvPerturb()

        # Set up the camera
        self.cam.azimuth = 90.0
        self.cam.elevation = -20.0
        self.cam.distance = 2.0
        self.cam.lookat = np.array([0.0, 0.0, 0.5])

        # Start simulation loop
        self.get_logger().info(
            f"Start simulation with dt = {self.model.opt.timestep}s."
        )
        self.create_timer(self.model.opt.timestep, self.mj_update)

        # Joint states publisher
        self.joint_state_pub = self.create_publisher(
            JointState, "/arm_joint_states", 10
        )
        self.joint_names = [
            mujoco.mj_id2name(self.model, mujoco.mjtObj.mjOBJ_JOINT, i)
            for i in range(self.model.njnt)
        ]

        # Interaction state
        self.is_paused = False
        self.mouse_last_x, self.mouse_last_y = None, None
        self.mouse_left_button = False

    def key_callback(self, window, key, scancode, action, mods):
        """Handle keyboard input for simulation control."""
        if action == glfw.PRESS:
            if key == glfw.KEY_P:
                self.is_paused = not self.is_paused  # Toggle pause
                self.get_logger().info(f"Simulation paused: {self.is_paused}")
            elif key == glfw.KEY_R:
                mujoco.mj_resetData(self.model, self.data)  # Reset simulation
                self.get_logger().info("Simulation reset")

    def mouse_button_callback(self, window, button, action, mods):
        """Handle mouse button events for dragging the camera."""
        if button == glfw.MOUSE_BUTTON_LEFT:
            self.mouse_left_button = action == glfw.PRESS

    def mouse_move_callback(self, window, xpos, ypos):
        """Handle mouse motion to rotate the camera when the left button is held."""
        if self.mouse_left_button:
            if self.mouse_last_x is not None and self.mouse_last_y is not None:
                dx = xpos - self.mouse_last_x
                dy = ypos - self.mouse_last_y
                self.cam.azimuth -= dx * 0.2
                self.cam.elevation -= dy * 0.2
            self.mouse_last_x, self.mouse_last_y = xpos, ypos
        else:
            self.mouse_last_x, self.mouse_last_y = None, None

    def scroll_callback(self, window, xoffset, yoffset):
        """Handle scroll input to zoom in/out."""
        self.cam.distance -= yoffset * 0.1
        if self.cam.distance < 0.1:
            self.cam.distance = 0.1

    def mj_update(self):
        if not glfw.window_should_close(self.window) and rclpy.ok():
            if not self.is_paused:
                mujoco.mj_step(self.model, self.data)

            # Get the viewport dimensions
            viewport_width, viewport_height = glfw.get_framebuffer_size(self.window)
            viewport = mujoco.MjrRect(0, 0, viewport_width, viewport_height)

            # Update the scene and render
            mujoco.mjv_updateScene(
                self.model,
                self.data,
                self.opt,
                self.pert,
                self.cam,
                mujoco.mjtCatBit.mjCAT_ALL,
                self.scene,
            )
            mujoco.mjr_render(viewport, self.scene, self.ctx)

            # Swap buffers and poll events
            glfw.swap_buffers(self.window)
            glfw.poll_events()

            # Publish joint states
            jnt_state = JointState()
            jnt_state.position = self.data.qpos.tolist()
            jnt_state.velocity = self.data.qvel.tolist()
            jnt_state.name = self.joint_names
            jnt_state.header.frame_id = "base_link"
            current_time = self.get_clock().now()
            jnt_state.header.stamp.sec, jnt_state.header.stamp.nanosec = (
                current_time.seconds_nanoseconds()
            )

            self.joint_state_pub.publish(jnt_state)


def main():
    rclpy.init()
    node = MjSimNode()
    rclpy.spin(node)
    glfw.terminate()
    rclpy.shutdown()
