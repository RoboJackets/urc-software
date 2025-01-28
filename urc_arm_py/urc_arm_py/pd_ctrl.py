import numpy as np


class PDController:
    def __init__(self, joint_names: list[str]):
        self.joint_names = joint_names
        self.num = len(joint_names)

        # in layout of (n joints, <kp, kd>)
        self.pd_values = np.zeros((self.num, 2))  # Initialize gains as zeros
        self.torque_limit_lb = np.ones(self.num) * -np.inf
        self.torque_limit_ub = np.ones(self.num) * np.inf

    def set_gains(self, kp: np.array, kd: np.array):
        """
        Set proportional and derivative gains for each joint.
        """
        if kp.shape[0] != self.num or kd.shape[0] != self.num:
            raise ValueError(
                "Gains dimensions must match the number of joints.")
        self.pd_values[:, 0] = kp
        self.pd_values[:, 1] = kd

    def set_gain(self, joint_name: str, kp: float, kd: float):
        """
        Set proportional and derivative gains for a single joint by the name of the joint.
        """
        if joint_name not in self.joint_names:
            raise ValueError(f"Joint '{joint_name}' not found in joint names.")
        joint_index = self.joint_names.index(joint_name)
        self.pd_values[joint_index, 0] = kp
        self.pd_values[joint_index, 1] = kd

    def set_torque_limit(self, joint_name: str, torque_limit: list[float]):
        """
        Set torque limits for a single joint by the name of the joint.
        """
        if joint_name not in self.joint_names:
            raise ValueError(f"Joint '{joint_name}' not found in joint names.")
        if len(torque_limit) != 2 or torque_limit[0] > torque_limit[1]:
            raise ValueError(f"Torquel limit must be in the format [lb, ub].")
        joint_index = self.joint_names.index(joint_name)
        self.torque_limit_lb[joint_index] = torque_limit[0]
        self.torque_limit_ub[joint_index] = torque_limit[1]

    def compute_torque(self, q_ref: np.array, qd_ref: np.array, q_curr: np.array, qd_curr: np.array) -> np.array:
        """
        Compute the control torque for each joint based on PD control.
        """
        if any(len(arr) != self.num for arr in [q_ref, qd_ref, q_curr, qd_curr]):
            raise ValueError(
                "Input dimensions must match the number of joints.")

        q_delta = q_ref - q_curr  # Position error
        qd_delta = qd_ref - qd_curr  # Velocity error

        kp = self.pd_values[:, 0]
        kd = self.pd_values[:, 1]

        torque = kp * q_delta + kd * qd_delta
        torque = np.clip(torque, self.torque_limit_lb, self.torque_limit_ub)
        return torque
