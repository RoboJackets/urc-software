# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/GpsGroup.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GpsGroup(type):
    """Metaclass of message 'GpsGroup'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'GPSGROUP_UTC': 1,
        'GPSGROUP_TOW': 2,
        'GPSGROUP_WEEK': 4,
        'GPSGROUP_NUMSATS': 8,
        'GPSGROUP_FIX': 16,
        'GPSGROUP_POSLLA': 32,
        'GPSGROUP_POSECEF': 64,
        'GPSGROUP_VELNED': 128,
        'GPSGROUP_VELECEF': 256,
        'GPSGROUP_POSU': 512,
        'GPSGROUP_VELU': 1024,
        'GPSGROUP_TIMEU': 2048,
        'GPSGROUP_TIMEINFO': 4096,
        'GPSGROUP_DOP': 8192,
        'GPSFIX_NOFIX': 0,
        'GPSFIX_TIMEONLY': 1,
        'GPSFIX_2D': 2,
        'GPSFIX_3D': 3,
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
                'vectornav_msgs.msg.GpsGroup')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__gps_group
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__gps_group
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__gps_group
            cls._TYPE_SUPPORT = module.type_support_msg__msg__gps_group
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__gps_group

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

            from vectornav_msgs.msg import DOP
            if DOP.__class__._TYPE_SUPPORT is None:
                DOP.__class__.__import_type_support__()

            from vectornav_msgs.msg import TimeUTC
            if TimeUTC.__class__._TYPE_SUPPORT is None:
                TimeUTC.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'GPSGROUP_UTC': cls.__constants['GPSGROUP_UTC'],
            'GPSGROUP_TOW': cls.__constants['GPSGROUP_TOW'],
            'GPSGROUP_WEEK': cls.__constants['GPSGROUP_WEEK'],
            'GPSGROUP_NUMSATS': cls.__constants['GPSGROUP_NUMSATS'],
            'GPSGROUP_FIX': cls.__constants['GPSGROUP_FIX'],
            'GPSGROUP_POSLLA': cls.__constants['GPSGROUP_POSLLA'],
            'GPSGROUP_POSECEF': cls.__constants['GPSGROUP_POSECEF'],
            'GPSGROUP_VELNED': cls.__constants['GPSGROUP_VELNED'],
            'GPSGROUP_VELECEF': cls.__constants['GPSGROUP_VELECEF'],
            'GPSGROUP_POSU': cls.__constants['GPSGROUP_POSU'],
            'GPSGROUP_VELU': cls.__constants['GPSGROUP_VELU'],
            'GPSGROUP_TIMEU': cls.__constants['GPSGROUP_TIMEU'],
            'GPSGROUP_TIMEINFO': cls.__constants['GPSGROUP_TIMEINFO'],
            'GPSGROUP_DOP': cls.__constants['GPSGROUP_DOP'],
            'GPSFIX_NOFIX': cls.__constants['GPSFIX_NOFIX'],
            'GPSFIX_TIMEONLY': cls.__constants['GPSFIX_TIMEONLY'],
            'GPSFIX_2D': cls.__constants['GPSFIX_2D'],
            'GPSFIX_3D': cls.__constants['GPSFIX_3D'],
        }

    @property
    def GPSGROUP_UTC(self):
        """Message constant 'GPSGROUP_UTC'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_UTC']

    @property
    def GPSGROUP_TOW(self):
        """Message constant 'GPSGROUP_TOW'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_TOW']

    @property
    def GPSGROUP_WEEK(self):
        """Message constant 'GPSGROUP_WEEK'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_WEEK']

    @property
    def GPSGROUP_NUMSATS(self):
        """Message constant 'GPSGROUP_NUMSATS'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_NUMSATS']

    @property
    def GPSGROUP_FIX(self):
        """Message constant 'GPSGROUP_FIX'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_FIX']

    @property
    def GPSGROUP_POSLLA(self):
        """Message constant 'GPSGROUP_POSLLA'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_POSLLA']

    @property
    def GPSGROUP_POSECEF(self):
        """Message constant 'GPSGROUP_POSECEF'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_POSECEF']

    @property
    def GPSGROUP_VELNED(self):
        """Message constant 'GPSGROUP_VELNED'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_VELNED']

    @property
    def GPSGROUP_VELECEF(self):
        """Message constant 'GPSGROUP_VELECEF'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_VELECEF']

    @property
    def GPSGROUP_POSU(self):
        """Message constant 'GPSGROUP_POSU'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_POSU']

    @property
    def GPSGROUP_VELU(self):
        """Message constant 'GPSGROUP_VELU'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_VELU']

    @property
    def GPSGROUP_TIMEU(self):
        """Message constant 'GPSGROUP_TIMEU'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_TIMEU']

    @property
    def GPSGROUP_TIMEINFO(self):
        """Message constant 'GPSGROUP_TIMEINFO'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_TIMEINFO']

    @property
    def GPSGROUP_DOP(self):
        """Message constant 'GPSGROUP_DOP'."""
        return Metaclass_GpsGroup.__constants['GPSGROUP_DOP']

    @property
    def GPSFIX_NOFIX(self):
        """Message constant 'GPSFIX_NOFIX'."""
        return Metaclass_GpsGroup.__constants['GPSFIX_NOFIX']

    @property
    def GPSFIX_TIMEONLY(self):
        """Message constant 'GPSFIX_TIMEONLY'."""
        return Metaclass_GpsGroup.__constants['GPSFIX_TIMEONLY']

    @property
    def GPSFIX_2D(self):
        """Message constant 'GPSFIX_2D'."""
        return Metaclass_GpsGroup.__constants['GPSFIX_2D']

    @property
    def GPSFIX_3D(self):
        """Message constant 'GPSFIX_3D'."""
        return Metaclass_GpsGroup.__constants['GPSFIX_3D']


class GpsGroup(metaclass=Metaclass_GpsGroup):
    """
    Message class 'GpsGroup'.

    Constants:
      GPSGROUP_UTC
      GPSGROUP_TOW
      GPSGROUP_WEEK
      GPSGROUP_NUMSATS
      GPSGROUP_FIX
      GPSGROUP_POSLLA
      GPSGROUP_POSECEF
      GPSGROUP_VELNED
      GPSGROUP_VELECEF
      GPSGROUP_POSU
      GPSGROUP_VELU
      GPSGROUP_TIMEU
      GPSGROUP_TIMEINFO
      GPSGROUP_DOP
      GPSFIX_NOFIX
      GPSFIX_TIMEONLY
      GPSFIX_2D
      GPSFIX_3D
    """

    __slots__ = [
        '_header',
        '_group_fields',
        '_utc',
        '_tow',
        '_week',
        '_numsats',
        '_fix',
        '_poslla',
        '_posecef',
        '_velned',
        '_velecef',
        '_posu',
        '_velu',
        '_timeu',
        '_timeinfo_status',
        '_timeinfo_leapseconds',
        '_dop',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'group_fields': 'uint16',
        'utc': 'vectornav_msgs/TimeUTC',
        'tow': 'uint64',
        'week': 'uint16',
        'numsats': 'uint8',
        'fix': 'uint8',
        'poslla': 'geometry_msgs/Point',
        'posecef': 'geometry_msgs/Point',
        'velned': 'geometry_msgs/Vector3',
        'velecef': 'geometry_msgs/Vector3',
        'posu': 'geometry_msgs/Vector3',
        'velu': 'float',
        'timeu': 'uint32',
        'timeinfo_status': 'uint8',
        'timeinfo_leapseconds': 'int8',
        'dop': 'vectornav_msgs/DOP',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vectornav_msgs', 'msg'], 'TimeUTC'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vectornav_msgs', 'msg'], 'DOP'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.group_fields = kwargs.get('group_fields', int())
        from vectornav_msgs.msg import TimeUTC
        self.utc = kwargs.get('utc', TimeUTC())
        self.tow = kwargs.get('tow', int())
        self.week = kwargs.get('week', int())
        self.numsats = kwargs.get('numsats', int())
        self.fix = kwargs.get('fix', int())
        from geometry_msgs.msg import Point
        self.poslla = kwargs.get('poslla', Point())
        from geometry_msgs.msg import Point
        self.posecef = kwargs.get('posecef', Point())
        from geometry_msgs.msg import Vector3
        self.velned = kwargs.get('velned', Vector3())
        from geometry_msgs.msg import Vector3
        self.velecef = kwargs.get('velecef', Vector3())
        from geometry_msgs.msg import Vector3
        self.posu = kwargs.get('posu', Vector3())
        self.velu = kwargs.get('velu', float())
        self.timeu = kwargs.get('timeu', int())
        self.timeinfo_status = kwargs.get('timeinfo_status', int())
        self.timeinfo_leapseconds = kwargs.get('timeinfo_leapseconds', int())
        from vectornav_msgs.msg import DOP
        self.dop = kwargs.get('dop', DOP())

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
        if self.utc != other.utc:
            return False
        if self.tow != other.tow:
            return False
        if self.week != other.week:
            return False
        if self.numsats != other.numsats:
            return False
        if self.fix != other.fix:
            return False
        if self.poslla != other.poslla:
            return False
        if self.posecef != other.posecef:
            return False
        if self.velned != other.velned:
            return False
        if self.velecef != other.velecef:
            return False
        if self.posu != other.posu:
            return False
        if self.velu != other.velu:
            return False
        if self.timeu != other.timeu:
            return False
        if self.timeinfo_status != other.timeinfo_status:
            return False
        if self.timeinfo_leapseconds != other.timeinfo_leapseconds:
            return False
        if self.dop != other.dop:
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
    def utc(self):
        """Message field 'utc'."""
        return self._utc

    @utc.setter
    def utc(self, value):
        if __debug__:
            from vectornav_msgs.msg import TimeUTC
            assert \
                isinstance(value, TimeUTC), \
                "The 'utc' field must be a sub message of type 'TimeUTC'"
        self._utc = value

    @builtins.property
    def tow(self):
        """Message field 'tow'."""
        return self._tow

    @tow.setter
    def tow(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'tow' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'tow' field must be an unsigned integer in [0, 18446744073709551615]"
        self._tow = value

    @builtins.property
    def week(self):
        """Message field 'week'."""
        return self._week

    @week.setter
    def week(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'week' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'week' field must be an unsigned integer in [0, 65535]"
        self._week = value

    @builtins.property
    def numsats(self):
        """Message field 'numsats'."""
        return self._numsats

    @numsats.setter
    def numsats(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'numsats' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'numsats' field must be an unsigned integer in [0, 255]"
        self._numsats = value

    @builtins.property
    def fix(self):
        """Message field 'fix'."""
        return self._fix

    @fix.setter
    def fix(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'fix' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'fix' field must be an unsigned integer in [0, 255]"
        self._fix = value

    @builtins.property
    def poslla(self):
        """Message field 'poslla'."""
        return self._poslla

    @poslla.setter
    def poslla(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'poslla' field must be a sub message of type 'Point'"
        self._poslla = value

    @builtins.property
    def posecef(self):
        """Message field 'posecef'."""
        return self._posecef

    @posecef.setter
    def posecef(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'posecef' field must be a sub message of type 'Point'"
        self._posecef = value

    @builtins.property
    def velned(self):
        """Message field 'velned'."""
        return self._velned

    @velned.setter
    def velned(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'velned' field must be a sub message of type 'Vector3'"
        self._velned = value

    @builtins.property
    def velecef(self):
        """Message field 'velecef'."""
        return self._velecef

    @velecef.setter
    def velecef(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'velecef' field must be a sub message of type 'Vector3'"
        self._velecef = value

    @builtins.property
    def posu(self):
        """Message field 'posu'."""
        return self._posu

    @posu.setter
    def posu(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'posu' field must be a sub message of type 'Vector3'"
        self._posu = value

    @builtins.property
    def velu(self):
        """Message field 'velu'."""
        return self._velu

    @velu.setter
    def velu(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'velu' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'velu' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._velu = value

    @builtins.property
    def timeu(self):
        """Message field 'timeu'."""
        return self._timeu

    @timeu.setter
    def timeu(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timeu' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'timeu' field must be an unsigned integer in [0, 4294967295]"
        self._timeu = value

    @builtins.property
    def timeinfo_status(self):
        """Message field 'timeinfo_status'."""
        return self._timeinfo_status

    @timeinfo_status.setter
    def timeinfo_status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timeinfo_status' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'timeinfo_status' field must be an unsigned integer in [0, 255]"
        self._timeinfo_status = value

    @builtins.property
    def timeinfo_leapseconds(self):
        """Message field 'timeinfo_leapseconds'."""
        return self._timeinfo_leapseconds

    @timeinfo_leapseconds.setter
    def timeinfo_leapseconds(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timeinfo_leapseconds' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'timeinfo_leapseconds' field must be an integer in [-128, 127]"
        self._timeinfo_leapseconds = value

    @builtins.property
    def dop(self):
        """Message field 'dop'."""
        return self._dop

    @dop.setter
    def dop(self, value):
        if __debug__:
            from vectornav_msgs.msg import DOP
            assert \
                isinstance(value, DOP), \
                "The 'dop' field must be a sub message of type 'DOP'"
        self._dop = value
