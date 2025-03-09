# flake8: noqa

# auto-generated DO NOT EDIT

from rcl_interfaces.msg import ParameterDescriptor
from rcl_interfaces.msg import SetParametersResult
from rcl_interfaces.msg import FloatingPointRange, IntegerRange
from rclpy.clock import Clock
from rclpy.exceptions import InvalidParameterValueException
from rclpy.time import Time
import copy
import rclpy
import rclpy.parameter
from generate_parameter_library_py.python_validators import ParameterValidators



class arm_qp_control_parameters:

    class Params:
        # for detecting if the parameter struct has been updated
        stamp_ = Time()

        joints = ["default_joint"]
        class __RobotConfig:
            model_path = None
            use_visualization = True
        robot_config = __RobotConfig()
        class __ControlConfig:
            rate_hz = 200
            pos_threshold = 1e-05
            ori_threshold = 1e-05
            max_iters = 20
            solver = "osqp"
        control_config = __ControlConfig()
        class __Gains:
            class __MapJoints:
                kp = None
                kd = None
                torque_limit = None
            __map_type = __MapJoints
            def add_entry(self, name):
                if not hasattr(self, name):
                    setattr(self, name, self.__map_type())
                return getattr(self, name)
            def get_entry(self, name):
                return getattr(self, name)
        gains = __Gains()



    class ParamListener:
        def __init__(self, node, prefix=""):
            self.prefix_ = prefix
            self.params_ = arm_qp_control_parameters.Params()
            self.node_ = node
            self.logger_ = rclpy.logging.get_logger("arm_qp_control_parameters." + prefix)

            self.declare_params()

            self.node_.add_on_set_parameters_callback(self.update)
            self.clock_ = Clock()

        def get_params(self):
            tmp = self.params_.stamp_
            self.params_.stamp_ = None
            paramCopy = copy.deepcopy(self.params_)
            paramCopy.stamp_ = tmp
            self.params_.stamp_ = tmp
            return paramCopy

        def is_old(self, other_param):
            return self.params_.stamp_ != other_param.stamp_

        def unpack_parameter_dict(self, namespace: str, parameter_dict: dict):
            """
            Flatten a parameter dictionary recursively.

            :param namespace: The namespace to prepend to the parameter names.
            :param parameter_dict: A dictionary of parameters keyed by the parameter names
            :return: A list of rclpy Parameter objects
            """
            parameters = []
            for param_name, param_value in parameter_dict.items():
                full_param_name = namespace + param_name
                # Unroll nested parameters
                if isinstance(param_value, dict):
                    nested_params = self.unpack_parameter_dict(
                            namespace=full_param_name + rclpy.parameter.PARAMETER_SEPARATOR_STRING,
                            parameter_dict=param_value)
                    parameters.extend(nested_params)
                else:
                    parameters.append(rclpy.parameter.Parameter(full_param_name, value=param_value))
            return parameters

        def set_params_from_dict(self, param_dict):
            params_to_set = self.unpack_parameter_dict('', param_dict)
            self.update(params_to_set)

        def refresh_dynamic_parameters(self):
            updated_params = self.get_params()
            # TODO remove any destroyed dynamic parameters

            # declare any new dynamic parameters

            for value_1 in updated_params.joints:

                updated_params.gains.add_entry(value_1)
                entry = updated_params.gains.get_entry(value_1)
                param_name = f"{self.prefix_}gains.{value_1}.kp"
                if not self.node_.has_parameter(self.prefix_ + param_name):
                    descriptor = ParameterDescriptor(description="", read_only = False)
                    parameter = rclpy.Parameter.Type.DOUBLE
                    self.node_.declare_parameter(param_name, parameter, descriptor)
                param = self.node_.get_parameter(param_name)
                self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
                entry.kp = param.value

            for value_1 in updated_params.joints:

                updated_params.gains.add_entry(value_1)
                entry = updated_params.gains.get_entry(value_1)
                param_name = f"{self.prefix_}gains.{value_1}.kd"
                if not self.node_.has_parameter(self.prefix_ + param_name):
                    descriptor = ParameterDescriptor(description="", read_only = False)
                    parameter = rclpy.Parameter.Type.DOUBLE
                    self.node_.declare_parameter(param_name, parameter, descriptor)
                param = self.node_.get_parameter(param_name)
                self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
                entry.kd = param.value

            for value_1 in updated_params.joints:

                updated_params.gains.add_entry(value_1)
                entry = updated_params.gains.get_entry(value_1)
                param_name = f"{self.prefix_}gains.{value_1}.torque_limit"
                if not self.node_.has_parameter(self.prefix_ + param_name):
                    descriptor = ParameterDescriptor(description="", read_only = False)
                    parameter = rclpy.Parameter.Type.DOUBLE_ARRAY
                    self.node_.declare_parameter(param_name, parameter, descriptor)
                param = self.node_.get_parameter(param_name)
                self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
                validation_result = ParameterValidators.fixed_size(param, 2)
                if validation_result:
                    raise InvalidParameterValueException('gains.__map_joints.torque_limit',param.value, 'Invalid value set during initialization for parameter gains.__map_joints.torque_limit: ' + validation_result)
                entry.torque_limit = param.value

        def update(self, parameters):
            updated_params = self.get_params()

            for param in parameters:
                if param.name == self.prefix_ + "robot_config.model_path":
                    updated_params.robot_config.model_path = param.value
                    self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))

                if param.name == self.prefix_ + "robot_config.use_visualization":
                    updated_params.robot_config.use_visualization = param.value
                    self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))

                if param.name == self.prefix_ + "control_config.rate_hz":
                    updated_params.control_config.rate_hz = param.value
                    self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))

                if param.name == self.prefix_ + "control_config.pos_threshold":
                    updated_params.control_config.pos_threshold = param.value
                    self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))

                if param.name == self.prefix_ + "control_config.ori_threshold":
                    updated_params.control_config.ori_threshold = param.value
                    self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))

                if param.name == self.prefix_ + "control_config.max_iters":
                    updated_params.control_config.max_iters = param.value
                    self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))

                if param.name == self.prefix_ + "control_config.solver":
                    updated_params.control_config.solver = param.value
                    self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))

                if param.name == self.prefix_ + "joints":
                    updated_params.joints = param.value
                    self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))


            # update dynamic parameters
            for param in parameters:

                    for value_1 in updated_params.joints:

                        param_name = f"{self.prefix_}gains.{value_1}.kp"
                        if param.name == param_name:

                            updated_params.gains.get_entry(value_1).kp = param.value
                            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))


                    for value_1 in updated_params.joints:

                        param_name = f"{self.prefix_}gains.{value_1}.kd"
                        if param.name == param_name:

                            updated_params.gains.get_entry(value_1).kd = param.value
                            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))


                    for value_1 in updated_params.joints:

                        param_name = f"{self.prefix_}gains.{value_1}.torque_limit"
                        if param.name == param_name:
                            validation_result = ParameterValidators.fixed_size(param, 2)
                            if validation_result:
                                return SetParametersResult(successful=False, reason=validation_result)

                            updated_params.gains.get_entry(value_1).torque_limit = param.value
                            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))


            updated_params.stamp_ = self.clock_.now()
            self.update_internal_params(updated_params)
            return SetParametersResult(successful=True)

        def update_internal_params(self, updated_params):
            self.params_ = updated_params

        def declare_params(self):
            updated_params = self.get_params()
            # declare all parameters and give default values to non-required ones
            if not self.node_.has_parameter(self.prefix_ + "robot_config.model_path"):
                descriptor = ParameterDescriptor(description="Model path to urdf.", read_only = True)
                parameter = rclpy.Parameter.Type.STRING
                self.node_.declare_parameter(self.prefix_ + "robot_config.model_path", parameter, descriptor)

            if not self.node_.has_parameter(self.prefix_ + "robot_config.use_visualization"):
                descriptor = ParameterDescriptor(description="Whether start visualization.", read_only = False)
                parameter = updated_params.robot_config.use_visualization
                self.node_.declare_parameter(self.prefix_ + "robot_config.use_visualization", parameter, descriptor)

            if not self.node_.has_parameter(self.prefix_ + "control_config.rate_hz"):
                descriptor = ParameterDescriptor(description="Control frequency. Default to 120Hz.", read_only = False)
                parameter = updated_params.control_config.rate_hz
                self.node_.declare_parameter(self.prefix_ + "control_config.rate_hz", parameter, descriptor)

            if not self.node_.has_parameter(self.prefix_ + "control_config.pos_threshold"):
                descriptor = ParameterDescriptor(description="", read_only = False)
                parameter = updated_params.control_config.pos_threshold
                self.node_.declare_parameter(self.prefix_ + "control_config.pos_threshold", parameter, descriptor)

            if not self.node_.has_parameter(self.prefix_ + "control_config.ori_threshold"):
                descriptor = ParameterDescriptor(description="", read_only = False)
                parameter = updated_params.control_config.ori_threshold
                self.node_.declare_parameter(self.prefix_ + "control_config.ori_threshold", parameter, descriptor)

            if not self.node_.has_parameter(self.prefix_ + "control_config.max_iters"):
                descriptor = ParameterDescriptor(description="", read_only = False)
                parameter = updated_params.control_config.max_iters
                self.node_.declare_parameter(self.prefix_ + "control_config.max_iters", parameter, descriptor)

            if not self.node_.has_parameter(self.prefix_ + "control_config.solver"):
                descriptor = ParameterDescriptor(description="", read_only = False)
                parameter = updated_params.control_config.solver
                self.node_.declare_parameter(self.prefix_ + "control_config.solver", parameter, descriptor)

            if not self.node_.has_parameter(self.prefix_ + "joints"):
                descriptor = ParameterDescriptor(description="Specifies which joints will be used.", read_only = False)
                parameter = updated_params.joints
                self.node_.declare_parameter(self.prefix_ + "joints", parameter, descriptor)

            # TODO: need validation
            # get parameters and fill struct fields
            param = self.node_.get_parameter(self.prefix_ + "robot_config.model_path")
            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
            updated_params.robot_config.model_path = param.value
            param = self.node_.get_parameter(self.prefix_ + "robot_config.use_visualization")
            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
            updated_params.robot_config.use_visualization = param.value
            param = self.node_.get_parameter(self.prefix_ + "control_config.rate_hz")
            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
            updated_params.control_config.rate_hz = param.value
            param = self.node_.get_parameter(self.prefix_ + "control_config.pos_threshold")
            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
            updated_params.control_config.pos_threshold = param.value
            param = self.node_.get_parameter(self.prefix_ + "control_config.ori_threshold")
            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
            updated_params.control_config.ori_threshold = param.value
            param = self.node_.get_parameter(self.prefix_ + "control_config.max_iters")
            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
            updated_params.control_config.max_iters = param.value
            param = self.node_.get_parameter(self.prefix_ + "control_config.solver")
            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
            updated_params.control_config.solver = param.value
            param = self.node_.get_parameter(self.prefix_ + "joints")
            self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
            updated_params.joints = param.value


            # declare and set all dynamic parameters

            for value_1 in updated_params.joints:

                updated_params.gains.add_entry(value_1)
                entry = updated_params.gains.get_entry(value_1)
                param_name = f"{self.prefix_}gains.{value_1}.kp"
                if not self.node_.has_parameter(self.prefix_ + param_name):
                    descriptor = ParameterDescriptor(description="", read_only = False)
                    parameter = rclpy.Parameter.Type.DOUBLE
                    self.node_.declare_parameter(param_name, parameter, descriptor)
                param = self.node_.get_parameter(param_name)
                self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
                entry.kp = param.value

            for value_1 in updated_params.joints:

                updated_params.gains.add_entry(value_1)
                entry = updated_params.gains.get_entry(value_1)
                param_name = f"{self.prefix_}gains.{value_1}.kd"
                if not self.node_.has_parameter(self.prefix_ + param_name):
                    descriptor = ParameterDescriptor(description="", read_only = False)
                    parameter = rclpy.Parameter.Type.DOUBLE
                    self.node_.declare_parameter(param_name, parameter, descriptor)
                param = self.node_.get_parameter(param_name)
                self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
                entry.kd = param.value

            for value_1 in updated_params.joints:

                updated_params.gains.add_entry(value_1)
                entry = updated_params.gains.get_entry(value_1)
                param_name = f"{self.prefix_}gains.{value_1}.torque_limit"
                if not self.node_.has_parameter(self.prefix_ + param_name):
                    descriptor = ParameterDescriptor(description="", read_only = False)
                    parameter = rclpy.Parameter.Type.DOUBLE_ARRAY
                    self.node_.declare_parameter(param_name, parameter, descriptor)
                param = self.node_.get_parameter(param_name)
                self.logger_.debug(param.name + ": " + param.type_.name + " = " + str(param.value))
                validation_result = ParameterValidators.fixed_size(param, 2)
                if validation_result:
                    raise InvalidParameterValueException('gains.__map_joints.torque_limit',param.value, 'Invalid value set during initialization for parameter gains.__map_joints.torque_limit: ' + validation_result)
                entry.torque_limit = param.value

            self.update_internal_params(updated_params)
