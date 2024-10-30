# generated from rosidl_generator_py/resource/_idl.py.em
# with input from urc_msgs:msg/LandingLocations.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'latitudes'
# Member 'longitudes'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LandingLocations(type):
    """Metaclass of message 'LandingLocations'."""

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
            module = import_type_support('urc_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'urc_msgs.msg.LandingLocations')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__landing_locations
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__landing_locations
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__landing_locations
            cls._TYPE_SUPPORT = module.type_support_msg__msg__landing_locations
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__landing_locations

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class LandingLocations(metaclass=Metaclass_LandingLocations):
    """Message class 'LandingLocations'."""

    __slots__ = [
        '_header',
        '_num_locations',
        '_latitudes',
        '_longitudes',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'num_locations': 'int32',
        'latitudes': 'double[100]',
        'longitudes': 'double[100]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 100),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 100),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.num_locations = kwargs.get('num_locations', int())
        if 'latitudes' not in kwargs:
            self.latitudes = numpy.zeros(100, dtype=numpy.float64)
        else:
            self.latitudes = numpy.array(kwargs.get('latitudes'), dtype=numpy.float64)
            assert self.latitudes.shape == (100, )
        if 'longitudes' not in kwargs:
            self.longitudes = numpy.zeros(100, dtype=numpy.float64)
        else:
            self.longitudes = numpy.array(kwargs.get('longitudes'), dtype=numpy.float64)
            assert self.longitudes.shape == (100, )

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
        if self.header != other.header:
            return False
        if self.num_locations != other.num_locations:
            return False
        if all(self.latitudes != other.latitudes):
            return False
        if all(self.longitudes != other.longitudes):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def num_locations(self):
        """Message field 'num_locations'."""
        return self._num_locations

    @num_locations.setter
    def num_locations(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_locations' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'num_locations' field must be an integer in [-2147483648, 2147483647]"
        self._num_locations = value

    @builtins.property
    def latitudes(self):
        """Message field 'latitudes'."""
        return self._latitudes

    @latitudes.setter
    def latitudes(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'latitudes' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 100, \
                "The 'latitudes' numpy.ndarray() must have a size of 100"
            self._latitudes = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 100 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'latitudes' field must be a set or sequence with length 100 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._latitudes = numpy.array(value, dtype=numpy.float64)

    @builtins.property
    def longitudes(self):
        """Message field 'longitudes'."""
        return self._longitudes

    @longitudes.setter
    def longitudes(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'longitudes' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 100, \
                "The 'longitudes' numpy.ndarray() must have a size of 100"
            self._longitudes = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 100 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'longitudes' field must be a set or sequence with length 100 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._longitudes = numpy.array(value, dtype=numpy.float64)
