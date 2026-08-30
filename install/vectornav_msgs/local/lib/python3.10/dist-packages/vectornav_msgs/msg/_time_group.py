# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/TimeGroup.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TimeGroup(type):
    """Metaclass of message 'TimeGroup'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'TIMEGROUP_TIMESTARTUP': 1,
        'TIMEGROUP_TIMEGPS': 2,
        'TIMEGROUP_GPSTOW': 4,
        'TIMEGROUP_GPSWEEK': 8,
        'TIMEGROUP_TIMESYNCIN': 16,
        'TIMEGROUP_TIMEGPSPPS': 32,
        'TIMEGROUP_TIMEUTC': 64,
        'TIMEGROUP_SYNCINCNT': 128,
        'TIMEGROUP_SYNCOUTCNT': 256,
        'TIMEGROUP_TIMESTATUS': 512,
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
                'vectornav_msgs.msg.TimeGroup')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__time_group
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__time_group
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__time_group
            cls._TYPE_SUPPORT = module.type_support_msg__msg__time_group
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__time_group

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

            from vectornav_msgs.msg import TimeStatus
            if TimeStatus.__class__._TYPE_SUPPORT is None:
                TimeStatus.__class__.__import_type_support__()

            from vectornav_msgs.msg import TimeUTC
            if TimeUTC.__class__._TYPE_SUPPORT is None:
                TimeUTC.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'TIMEGROUP_TIMESTARTUP': cls.__constants['TIMEGROUP_TIMESTARTUP'],
            'TIMEGROUP_TIMEGPS': cls.__constants['TIMEGROUP_TIMEGPS'],
            'TIMEGROUP_GPSTOW': cls.__constants['TIMEGROUP_GPSTOW'],
            'TIMEGROUP_GPSWEEK': cls.__constants['TIMEGROUP_GPSWEEK'],
            'TIMEGROUP_TIMESYNCIN': cls.__constants['TIMEGROUP_TIMESYNCIN'],
            'TIMEGROUP_TIMEGPSPPS': cls.__constants['TIMEGROUP_TIMEGPSPPS'],
            'TIMEGROUP_TIMEUTC': cls.__constants['TIMEGROUP_TIMEUTC'],
            'TIMEGROUP_SYNCINCNT': cls.__constants['TIMEGROUP_SYNCINCNT'],
            'TIMEGROUP_SYNCOUTCNT': cls.__constants['TIMEGROUP_SYNCOUTCNT'],
            'TIMEGROUP_TIMESTATUS': cls.__constants['TIMEGROUP_TIMESTATUS'],
        }

    @property
    def TIMEGROUP_TIMESTARTUP(self):
        """Message constant 'TIMEGROUP_TIMESTARTUP'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_TIMESTARTUP']

    @property
    def TIMEGROUP_TIMEGPS(self):
        """Message constant 'TIMEGROUP_TIMEGPS'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_TIMEGPS']

    @property
    def TIMEGROUP_GPSTOW(self):
        """Message constant 'TIMEGROUP_GPSTOW'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_GPSTOW']

    @property
    def TIMEGROUP_GPSWEEK(self):
        """Message constant 'TIMEGROUP_GPSWEEK'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_GPSWEEK']

    @property
    def TIMEGROUP_TIMESYNCIN(self):
        """Message constant 'TIMEGROUP_TIMESYNCIN'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_TIMESYNCIN']

    @property
    def TIMEGROUP_TIMEGPSPPS(self):
        """Message constant 'TIMEGROUP_TIMEGPSPPS'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_TIMEGPSPPS']

    @property
    def TIMEGROUP_TIMEUTC(self):
        """Message constant 'TIMEGROUP_TIMEUTC'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_TIMEUTC']

    @property
    def TIMEGROUP_SYNCINCNT(self):
        """Message constant 'TIMEGROUP_SYNCINCNT'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_SYNCINCNT']

    @property
    def TIMEGROUP_SYNCOUTCNT(self):
        """Message constant 'TIMEGROUP_SYNCOUTCNT'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_SYNCOUTCNT']

    @property
    def TIMEGROUP_TIMESTATUS(self):
        """Message constant 'TIMEGROUP_TIMESTATUS'."""
        return Metaclass_TimeGroup.__constants['TIMEGROUP_TIMESTATUS']


class TimeGroup(metaclass=Metaclass_TimeGroup):
    """
    Message class 'TimeGroup'.

    Constants:
      TIMEGROUP_TIMESTARTUP
      TIMEGROUP_TIMEGPS
      TIMEGROUP_GPSTOW
      TIMEGROUP_GPSWEEK
      TIMEGROUP_TIMESYNCIN
      TIMEGROUP_TIMEGPSPPS
      TIMEGROUP_TIMEUTC
      TIMEGROUP_SYNCINCNT
      TIMEGROUP_SYNCOUTCNT
      TIMEGROUP_TIMESTATUS
    """

    __slots__ = [
        '_header',
        '_group_fields',
        '_timestartup',
        '_timegps',
        '_gpstow',
        '_gpsweek',
        '_timesyncin',
        '_timegpspps',
        '_timeutc',
        '_syncincnt',
        '_syncoutcnt',
        '_timestatus',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'group_fields': 'uint16',
        'timestartup': 'uint64',
        'timegps': 'uint64',
        'gpstow': 'uint64',
        'gpsweek': 'uint16',
        'timesyncin': 'uint64',
        'timegpspps': 'uint64',
        'timeutc': 'vectornav_msgs/TimeUTC',
        'syncincnt': 'uint32',
        'syncoutcnt': 'uint32',
        'timestatus': 'vectornav_msgs/TimeStatus',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vectornav_msgs', 'msg'], 'TimeUTC'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vectornav_msgs', 'msg'], 'TimeStatus'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.group_fields = kwargs.get('group_fields', int())
        self.timestartup = kwargs.get('timestartup', int())
        self.timegps = kwargs.get('timegps', int())
        self.gpstow = kwargs.get('gpstow', int())
        self.gpsweek = kwargs.get('gpsweek', int())
        self.timesyncin = kwargs.get('timesyncin', int())
        self.timegpspps = kwargs.get('timegpspps', int())
        from vectornav_msgs.msg import TimeUTC
        self.timeutc = kwargs.get('timeutc', TimeUTC())
        self.syncincnt = kwargs.get('syncincnt', int())
        self.syncoutcnt = kwargs.get('syncoutcnt', int())
        from vectornav_msgs.msg import TimeStatus
        self.timestatus = kwargs.get('timestatus', TimeStatus())

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
        if self.group_fields != other.group_fields:
            return False
        if self.timestartup != other.timestartup:
            return False
        if self.timegps != other.timegps:
            return False
        if self.gpstow != other.gpstow:
            return False
        if self.gpsweek != other.gpsweek:
            return False
        if self.timesyncin != other.timesyncin:
            return False
        if self.timegpspps != other.timegpspps:
            return False
        if self.timeutc != other.timeutc:
            return False
        if self.syncincnt != other.syncincnt:
            return False
        if self.syncoutcnt != other.syncoutcnt:
            return False
        if self.timestatus != other.timestatus:
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
    def group_fields(self):
        """Message field 'group_fields'."""
        return self._group_fields

    @group_fields.setter
    def group_fields(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'group_fields' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'group_fields' field must be an unsigned integer in [0, 65535]"
        self._group_fields = value

    @builtins.property
    def timestartup(self):
        """Message field 'timestartup'."""
        return self._timestartup

    @timestartup.setter
    def timestartup(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timestartup' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestartup' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestartup = value

    @builtins.property
    def timegps(self):
        """Message field 'timegps'."""
        return self._timegps

    @timegps.setter
    def timegps(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timegps' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timegps' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timegps = value

    @builtins.property
    def gpstow(self):
        """Message field 'gpstow'."""
        return self._gpstow

    @gpstow.setter
    def gpstow(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'gpstow' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'gpstow' field must be an unsigned integer in [0, 18446744073709551615]"
        self._gpstow = value

    @builtins.property
    def gpsweek(self):
        """Message field 'gpsweek'."""
        return self._gpsweek

    @gpsweek.setter
    def gpsweek(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'gpsweek' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'gpsweek' field must be an unsigned integer in [0, 65535]"
        self._gpsweek = value

    @builtins.property
    def timesyncin(self):
        """Message field 'timesyncin'."""
        return self._timesyncin

    @timesyncin.setter
    def timesyncin(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timesyncin' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timesyncin' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timesyncin = value

    @builtins.property
    def timegpspps(self):
        """Message field 'timegpspps'."""
        return self._timegpspps

    @timegpspps.setter
    def timegpspps(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timegpspps' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timegpspps' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timegpspps = value

    @builtins.property
    def timeutc(self):
        """Message field 'timeutc'."""
        return self._timeutc

    @timeutc.setter
    def timeutc(self, value):
        if __debug__:
            from vectornav_msgs.msg import TimeUTC
            assert \
                isinstance(value, TimeUTC), \
                "The 'timeutc' field must be a sub message of type 'TimeUTC'"
        self._timeutc = value

    @builtins.property
    def syncincnt(self):
        """Message field 'syncincnt'."""
        return self._syncincnt

    @syncincnt.setter
    def syncincnt(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'syncincnt' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'syncincnt' field must be an unsigned integer in [0, 4294967295]"
        self._syncincnt = value

    @builtins.property
    def syncoutcnt(self):
        """Message field 'syncoutcnt'."""
        return self._syncoutcnt

    @syncoutcnt.setter
    def syncoutcnt(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'syncoutcnt' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'syncoutcnt' field must be an unsigned integer in [0, 4294967295]"
        self._syncoutcnt = value

    @builtins.property
    def timestatus(self):
        """Message field 'timestatus'."""
        return self._timestatus

    @timestatus.setter
    def timestatus(self, value):
        if __debug__:
            from vectornav_msgs.msg import TimeStatus
            assert \
                isinstance(value, TimeStatus), \
                "The 'timestatus' field must be a sub message of type 'TimeStatus'"
        self._timestatus = value
