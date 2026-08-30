# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/TimeStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TimeStatus(type):
    """Metaclass of message 'TimeStatus'."""

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
                'vectornav_msgs.msg.TimeStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__time_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__time_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__time_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__time_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__time_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class TimeStatus(metaclass=Metaclass_TimeStatus):
    """Message class 'TimeStatus'."""

    __slots__ = [
        '_time_ok',
        '_date_ok',
        '_utctime_ok',
    ]

    _fields_and_field_types = {
        'time_ok': 'boolean',
        'date_ok': 'boolean',
        'utctime_ok': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.time_ok = kwargs.get('time_ok', bool())
        self.date_ok = kwargs.get('date_ok', bool())
        self.utctime_ok = kwargs.get('utctime_ok', bool())

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
        if self.time_ok != other.time_ok:
            return False
        if self.date_ok != other.date_ok:
            return False
        if self.utctime_ok != other.utctime_ok:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def time_ok(self):
        """Message field 'time_ok'."""
        return self._time_ok

    @time_ok.setter
    def time_ok(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'time_ok' field must be of type 'bool'"
        self._time_ok = value

    @builtins.property
    def date_ok(self):
        """Message field 'date_ok'."""
        return self._date_ok

    @date_ok.setter
    def date_ok(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'date_ok' field must be of type 'bool'"
        self._date_ok = value

    @builtins.property
    def utctime_ok(self):
        """Message field 'utctime_ok'."""
        return self._utctime_ok

    @utctime_ok.setter
    def utctime_ok(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'utctime_ok' field must be of type 'bool'"
        self._utctime_ok = value
