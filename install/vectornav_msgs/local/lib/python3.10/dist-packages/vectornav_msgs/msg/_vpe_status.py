# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/VpeStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VpeStatus(type):
    """Metaclass of message 'VpeStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('vectornav_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vectornav_msgs.msg.VpeStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vpe_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vpe_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vpe_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vpe_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vpe_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class VpeStatus(metaclass=Metaclass_VpeStatus):
    """Message class 'VpeStatus'."""

    __slots__ = [
        '_attitude_quality',
        '_gyro_saturation',
        '_gyro_saturation_recovery',
        '_mag_disturbance',
        '_mag_saturation',
        '_acc_disturbance',
        '_acc_saturation',
        '_known_mag_disturbance',
        '_known_accel_disturbance',
    ]

    _fields_and_field_types = {
        'attitude_quality': 'uint8',
        'gyro_saturation': 'boolean',
        'gyro_saturation_recovery': 'boolean',
        'mag_disturbance': 'uint8',
        'mag_saturation': 'boolean',
        'acc_disturbance': 'uint8',
        'acc_saturation': 'boolean',
        'known_mag_disturbance': 'boolean',
        'known_accel_disturbance': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.attitude_quality = kwargs.get('attitude_quality', int())
        self.gyro_saturation = kwargs.get('gyro_saturation', bool())
        self.gyro_saturation_recovery = kwargs.get('gyro_saturation_recovery', bool())
        self.mag_disturbance = kwargs.get('mag_disturbance', int())
        self.mag_saturation = kwargs.get('mag_saturation', bool())
        self.acc_disturbance = kwargs.get('acc_disturbance', int())
        self.acc_saturation = kwargs.get('acc_saturation', bool())
        self.known_mag_disturbance = kwargs.get('known_mag_disturbance', bool())
        self.known_accel_disturbance = kwargs.get('known_accel_disturbance', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.attitude_quality != other.attitude_quality:
            return False
        if self.gyro_saturation != other.gyro_saturation:
            return False
        if self.gyro_saturation_recovery != other.gyro_saturation_recovery:
            return False
        if self.mag_disturbance != other.mag_disturbance:
            return False
        if self.mag_saturation != other.mag_saturation:
            return False
        if self.acc_disturbance != other.acc_disturbance:
            return False
        if self.acc_saturation != other.acc_saturation:
            return False
        if self.known_mag_disturbance != other.known_mag_disturbance:
            return False
        if self.known_accel_disturbance != other.known_accel_disturbance:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def attitude_quality(self):
        """Message field 'attitude_quality'."""
        return self._attitude_quality

    @attitude_quality.setter
    def attitude_quality(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'attitude_quality' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'attitude_quality' field must be an unsigned integer in [0, 255]"
        self._attitude_quality = value

    @builtins.property
    def gyro_saturation(self):
        """Message field 'gyro_saturation'."""
        return self._gyro_saturation

    @gyro_saturation.setter
    def gyro_saturation(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'gyro_saturation' field must be of type 'bool'"
        self._gyro_saturation = value

    @builtins.property
    def gyro_saturation_recovery(self):
        """Message field 'gyro_saturation_recovery'."""
        return self._gyro_saturation_recovery

    @gyro_saturation_recovery.setter
    def gyro_saturation_recovery(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'gyro_saturation_recovery' field must be of type 'bool'"
        self._gyro_saturation_recovery = value

    @builtins.property
    def mag_disturbance(self):
        """Message field 'mag_disturbance'."""
        return self._mag_disturbance

    @mag_disturbance.setter
    def mag_disturbance(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mag_disturbance' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mag_disturbance' field must be an unsigned integer in [0, 255]"
        self._mag_disturbance = value

    @builtins.property
    def mag_saturation(self):
        """Message field 'mag_saturation'."""
        return self._mag_saturation

    @mag_saturation.setter
    def mag_saturation(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'mag_saturation' field must be of type 'bool'"
        self._mag_saturation = value

    @builtins.property
    def acc_disturbance(self):
        """Message field 'acc_disturbance'."""
        return self._acc_disturbance

    @acc_disturbance.setter
    def acc_disturbance(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'acc_disturbance' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'acc_disturbance' field must be an unsigned integer in [0, 255]"
        self._acc_disturbance = value

    @builtins.property
    def acc_saturation(self):
        """Message field 'acc_saturation'."""
        return self._acc_saturation

    @acc_saturation.setter
    def acc_saturation(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'acc_saturation' field must be of type 'bool'"
        self._acc_saturation = value

    @builtins.property
    def known_mag_disturbance(self):
        """Message field 'known_mag_disturbance'."""
        return self._known_mag_disturbance

    @known_mag_disturbance.setter
    def known_mag_disturbance(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'known_mag_disturbance' field must be of type 'bool'"
        self._known_mag_disturbance = value

    @builtins.property
    def known_accel_disturbance(self):
        """Message field 'known_accel_disturbance'."""
        return self._known_accel_disturbance

    @known_accel_disturbance.setter
    def known_accel_disturbance(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'known_accel_disturbance' field must be of type 'bool'"
        self._known_accel_disturbance = value
