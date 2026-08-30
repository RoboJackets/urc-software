# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/InsStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_InsStatus(type):
    """Metaclass of message 'InsStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'MODE_NOT_TRACKING': 0,
        'MODE_ALIGNING': 1,
        'MODE_TRACKING': 2,
        'MODE_NO_GPS': 3,
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
                'vectornav_msgs.msg.InsStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__ins_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__ins_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__ins_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__ins_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__ins_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'MODE_NOT_TRACKING': cls.__constants['MODE_NOT_TRACKING'],
            'MODE_ALIGNING': cls.__constants['MODE_ALIGNING'],
            'MODE_TRACKING': cls.__constants['MODE_TRACKING'],
            'MODE_NO_GPS': cls.__constants['MODE_NO_GPS'],
        }

    @property
    def MODE_NOT_TRACKING(self):
        """Message constant 'MODE_NOT_TRACKING'."""
        return Metaclass_InsStatus.__constants['MODE_NOT_TRACKING']

    @property
    def MODE_ALIGNING(self):
        """Message constant 'MODE_ALIGNING'."""
        return Metaclass_InsStatus.__constants['MODE_ALIGNING']

    @property
    def MODE_TRACKING(self):
        """Message constant 'MODE_TRACKING'."""
        return Metaclass_InsStatus.__constants['MODE_TRACKING']

    @property
    def MODE_NO_GPS(self):
        """Message constant 'MODE_NO_GPS'."""
        return Metaclass_InsStatus.__constants['MODE_NO_GPS']


class InsStatus(metaclass=Metaclass_InsStatus):
    """
    Message class 'InsStatus'.

    Constants:
      MODE_NOT_TRACKING
      MODE_ALIGNING
      MODE_TRACKING
      MODE_NO_GPS
    """

    __slots__ = [
        '_mode',
        '_gps_fix',
        '_time_error',
        '_imu_error',
        '_mag_pres_error',
        '_gps_error',
        '_gps_heading_ins',
        '_gps_compass',
    ]

    _fields_and_field_types = {
        'mode': 'uint8',
        'gps_fix': 'boolean',
        'time_error': 'boolean',
        'imu_error': 'boolean',
        'mag_pres_error': 'boolean',
        'gps_error': 'boolean',
        'gps_heading_ins': 'boolean',
        'gps_compass': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.mode = kwargs.get('mode', int())
        self.gps_fix = kwargs.get('gps_fix', bool())
        self.time_error = kwargs.get('time_error', bool())
        self.imu_error = kwargs.get('imu_error', bool())
        self.mag_pres_error = kwargs.get('mag_pres_error', bool())
        self.gps_error = kwargs.get('gps_error', bool())
        self.gps_heading_ins = kwargs.get('gps_heading_ins', bool())
        self.gps_compass = kwargs.get('gps_compass', bool())

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
        if self.mode != other.mode:
            return False
        if self.gps_fix != other.gps_fix:
            return False
        if self.time_error != other.time_error:
            return False
        if self.imu_error != other.imu_error:
            return False
        if self.mag_pres_error != other.mag_pres_error:
            return False
        if self.gps_error != other.gps_error:
            return False
        if self.gps_heading_ins != other.gps_heading_ins:
            return False
        if self.gps_compass != other.gps_compass:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def mode(self):
        """Message field 'mode'."""
        return self._mode

    @mode.setter
    def mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode' field must be an unsigned integer in [0, 255]"
        self._mode = value

    @builtins.property
    def gps_fix(self):
        """Message field 'gps_fix'."""
        return self._gps_fix

    @gps_fix.setter
    def gps_fix(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'gps_fix' field must be of type 'bool'"
        self._gps_fix = value

    @builtins.property
    def time_error(self):
        """Message field 'time_error'."""
        return self._time_error

    @time_error.setter
    def time_error(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'time_error' field must be of type 'bool'"
        self._time_error = value

    @builtins.property
    def imu_error(self):
        """Message field 'imu_error'."""
        return self._imu_error

    @imu_error.setter
    def imu_error(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'imu_error' field must be of type 'bool'"
        self._imu_error = value

    @builtins.property
    def mag_pres_error(self):
        """Message field 'mag_pres_error'."""
        return self._mag_pres_error

    @mag_pres_error.setter
    def mag_pres_error(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'mag_pres_error' field must be of type 'bool'"
        self._mag_pres_error = value

    @builtins.property
    def gps_error(self):
        """Message field 'gps_error'."""
        return self._gps_error

    @gps_error.setter
    def gps_error(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'gps_error' field must be of type 'bool'"
        self._gps_error = value

    @builtins.property
    def gps_heading_ins(self):
        """Message field 'gps_heading_ins'."""
        return self._gps_heading_ins

    @gps_heading_ins.setter
    def gps_heading_ins(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'gps_heading_ins' field must be of type 'bool'"
        self._gps_heading_ins = value

    @builtins.property
    def gps_compass(self):
        """Message field 'gps_compass'."""
        return self._gps_compass

    @gps_compass.setter
    def gps_compass(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'gps_compass' field must be of type 'bool'"
        self._gps_compass = value
