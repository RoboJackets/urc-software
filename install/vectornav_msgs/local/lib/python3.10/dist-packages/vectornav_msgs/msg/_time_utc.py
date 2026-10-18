# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/TimeUTC.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TimeUTC(type):
    """Metaclass of message 'TimeUTC'."""

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
                'vectornav_msgs.msg.TimeUTC')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__time_utc
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__time_utc
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__time_utc
            cls._TYPE_SUPPORT = module.type_support_msg__msg__time_utc
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__time_utc

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class TimeUTC(metaclass=Metaclass_TimeUTC):
    """Message class 'TimeUTC'."""

    __slots__ = [
        '_year',
        '_month',
        '_day',
        '_hour',
        '_min',
        '_sec',
        '_ms',
    ]

    _fields_and_field_types = {
        'year': 'uint8',
        'month': 'uint8',
        'day': 'uint8',
        'hour': 'uint8',
        'min': 'uint8',
        'sec': 'uint8',
        'ms': 'uint16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.year = kwargs.get('year', int())
        self.month = kwargs.get('month', int())
        self.day = kwargs.get('day', int())
        self.hour = kwargs.get('hour', int())
        self.min = kwargs.get('min', int())
        self.sec = kwargs.get('sec', int())
        self.ms = kwargs.get('ms', int())

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
        if self.year != other.year:
            return False
        if self.month != other.month:
            return False
        if self.day != other.day:
            return False
        if self.hour != other.hour:
            return False
        if self.min != other.min:
            return False
        if self.sec != other.sec:
            return False
        if self.ms != other.ms:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def year(self):
        """Message field 'year'."""
        return self._year

    @year.setter
    def year(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'year' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'year' field must be an unsigned integer in [0, 255]"
        self._year = value

    @builtins.property
    def month(self):
        """Message field 'month'."""
        return self._month

    @month.setter
    def month(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'month' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'month' field must be an unsigned integer in [0, 255]"
        self._month = value

    @builtins.property
    def day(self):
        """Message field 'day'."""
        return self._day

    @day.setter
    def day(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'day' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'day' field must be an unsigned integer in [0, 255]"
        self._day = value

    @builtins.property
    def hour(self):
        """Message field 'hour'."""
        return self._hour

    @hour.setter
    def hour(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'hour' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'hour' field must be an unsigned integer in [0, 255]"
        self._hour = value

    @builtins.property  # noqa: A003
    def min(self):  # noqa: A003
        """Message field 'min'."""
        return self._min

    @min.setter  # noqa: A003
    def min(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'min' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'min' field must be an unsigned integer in [0, 255]"
        self._min = value

    @builtins.property
    def sec(self):
        """Message field 'sec'."""
        return self._sec

    @sec.setter
    def sec(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sec' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'sec' field must be an unsigned integer in [0, 255]"
        self._sec = value

    @builtins.property
    def ms(self):
        """Message field 'ms'."""
        return self._ms

    @ms.setter
    def ms(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ms' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'ms' field must be an unsigned integer in [0, 65535]"
        self._ms = value
