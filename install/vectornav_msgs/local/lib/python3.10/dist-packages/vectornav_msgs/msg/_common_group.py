# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/CommonGroup.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_CommonGroup(type):
    """Metaclass of message 'CommonGroup'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'COMMONGROUP_TIMESTARTUP': 1,
        'COMMONGROUP_TIMEGPS': 2,
        'COMMONGROUP_TIMESYNCIN': 4,
        'COMMONGROUP_YAWPITCHROLL': 8,
        'COMMONGROUP_QUATERNION': 16,
        'COMMONGROUP_ANGULARRATE': 32,
        'COMMONGROUP_POSITION': 64,
        'COMMONGROUP_VELOCITY': 128,
        'COMMONGROUP_ACCEL': 256,
        'COMMONGROUP_IMU': 512,
        'COMMONGROUP_MAGPRES': 1024,
        'COMMONGROUP_DELTATHETA': 2048,
        'COMMONGROUP_INSSTATUS': 4096,
        'COMMONGROUP_SYNCINCNT': 8192,
        'COMMONGROUP_TIMEGPSPPS': 16384,
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
                'vectornav_msgs.msg.CommonGroup')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__common_group
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__common_group
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__common_group
            cls._TYPE_SUPPORT = module.type_support_msg__msg__common_group
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__common_group

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from geometry_msgs.msg import Quaternion
            if Quaternion.__class__._TYPE_SUPPORT is None:
                Quaternion.__class__.__import_type_support__()

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

            from vectornav_msgs.msg import InsStatus
            if InsStatus.__class__._TYPE_SUPPORT is None:
                InsStatus.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'COMMONGROUP_TIMESTARTUP': cls.__constants['COMMONGROUP_TIMESTARTUP'],
            'COMMONGROUP_TIMEGPS': cls.__constants['COMMONGROUP_TIMEGPS'],
            'COMMONGROUP_TIMESYNCIN': cls.__constants['COMMONGROUP_TIMESYNCIN'],
            'COMMONGROUP_YAWPITCHROLL': cls.__constants['COMMONGROUP_YAWPITCHROLL'],
            'COMMONGROUP_QUATERNION': cls.__constants['COMMONGROUP_QUATERNION'],
            'COMMONGROUP_ANGULARRATE': cls.__constants['COMMONGROUP_ANGULARRATE'],
            'COMMONGROUP_POSITION': cls.__constants['COMMONGROUP_POSITION'],
            'COMMONGROUP_VELOCITY': cls.__constants['COMMONGROUP_VELOCITY'],
            'COMMONGROUP_ACCEL': cls.__constants['COMMONGROUP_ACCEL'],
            'COMMONGROUP_IMU': cls.__constants['COMMONGROUP_IMU'],
            'COMMONGROUP_MAGPRES': cls.__constants['COMMONGROUP_MAGPRES'],
            'COMMONGROUP_DELTATHETA': cls.__constants['COMMONGROUP_DELTATHETA'],
            'COMMONGROUP_INSSTATUS': cls.__constants['COMMONGROUP_INSSTATUS'],
            'COMMONGROUP_SYNCINCNT': cls.__constants['COMMONGROUP_SYNCINCNT'],
            'COMMONGROUP_TIMEGPSPPS': cls.__constants['COMMONGROUP_TIMEGPSPPS'],
        }

    @property
    def COMMONGROUP_TIMESTARTUP(self):
        """Message constant 'COMMONGROUP_TIMESTARTUP'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_TIMESTARTUP']

    @property
    def COMMONGROUP_TIMEGPS(self):
        """Message constant 'COMMONGROUP_TIMEGPS'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_TIMEGPS']

    @property
    def COMMONGROUP_TIMESYNCIN(self):
        """Message constant 'COMMONGROUP_TIMESYNCIN'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_TIMESYNCIN']

    @property
    def COMMONGROUP_YAWPITCHROLL(self):
        """Message constant 'COMMONGROUP_YAWPITCHROLL'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_YAWPITCHROLL']

    @property
    def COMMONGROUP_QUATERNION(self):
        """Message constant 'COMMONGROUP_QUATERNION'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_QUATERNION']

    @property
    def COMMONGROUP_ANGULARRATE(self):
        """Message constant 'COMMONGROUP_ANGULARRATE'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_ANGULARRATE']

    @property
    def COMMONGROUP_POSITION(self):
        """Message constant 'COMMONGROUP_POSITION'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_POSITION']

    @property
    def COMMONGROUP_VELOCITY(self):
        """Message constant 'COMMONGROUP_VELOCITY'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_VELOCITY']

    @property
    def COMMONGROUP_ACCEL(self):
        """Message constant 'COMMONGROUP_ACCEL'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_ACCEL']

    @property
    def COMMONGROUP_IMU(self):
        """Message constant 'COMMONGROUP_IMU'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_IMU']

    @property
    def COMMONGROUP_MAGPRES(self):
        """Message constant 'COMMONGROUP_MAGPRES'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_MAGPRES']

    @property
    def COMMONGROUP_DELTATHETA(self):
        """Message constant 'COMMONGROUP_DELTATHETA'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_DELTATHETA']

    @property
    def COMMONGROUP_INSSTATUS(self):
        """Message constant 'COMMONGROUP_INSSTATUS'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_INSSTATUS']

    @property
    def COMMONGROUP_SYNCINCNT(self):
        """Message constant 'COMMONGROUP_SYNCINCNT'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_SYNCINCNT']

    @property
    def COMMONGROUP_TIMEGPSPPS(self):
        """Message constant 'COMMONGROUP_TIMEGPSPPS'."""
        return Metaclass_CommonGroup.__constants['COMMONGROUP_TIMEGPSPPS']


class CommonGroup(metaclass=Metaclass_CommonGroup):
    """
    Message class 'CommonGroup'.

    Constants:
      COMMONGROUP_TIMESTARTUP
      COMMONGROUP_TIMEGPS
      COMMONGROUP_TIMESYNCIN
      COMMONGROUP_YAWPITCHROLL
      COMMONGROUP_QUATERNION
      COMMONGROUP_ANGULARRATE
      COMMONGROUP_POSITION
      COMMONGROUP_VELOCITY
      COMMONGROUP_ACCEL
      COMMONGROUP_IMU
      COMMONGROUP_MAGPRES
      COMMONGROUP_DELTATHETA
      COMMONGROUP_INSSTATUS
      COMMONGROUP_SYNCINCNT
      COMMONGROUP_TIMEGPSPPS
    """

    __slots__ = [
        '_header',
        '_group_fields',
        '_timestartup',
        '_timegps',
        '_timesyncin',
        '_yawpitchroll',
        '_quaternion',
        '_angularrate',
        '_position',
        '_velocity',
        '_accel',
        '_imu_accel',
        '_imu_rate',
        '_magpres_mag',
        '_magpres_temp',
        '_magpres_pres',
        '_deltatheta_dtime',
        '_deltatheta_dtheta',
        '_deltatheta_dvel',
        '_insstatus',
        '_syncincnt',
        '_timegpspps',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'group_fields': 'uint16',
        'timestartup': 'uint64',
        'timegps': 'uint64',
        'timesyncin': 'uint64',
        'yawpitchroll': 'geometry_msgs/Vector3',
        'quaternion': 'geometry_msgs/Quaternion',
        'angularrate': 'geometry_msgs/Vector3',
        'position': 'geometry_msgs/Point',
        'velocity': 'geometry_msgs/Vector3',
        'accel': 'geometry_msgs/Vector3',
        'imu_accel': 'geometry_msgs/Vector3',
        'imu_rate': 'geometry_msgs/Vector3',
        'magpres_mag': 'geometry_msgs/Vector3',
        'magpres_temp': 'float',
        'magpres_pres': 'float',
        'deltatheta_dtime': 'float',
        'deltatheta_dtheta': 'geometry_msgs/Vector3',
        'deltatheta_dvel': 'geometry_msgs/Vector3',
        'insstatus': 'vectornav_msgs/InsStatus',
        'syncincnt': 'uint32',
        'timegpspps': 'uint16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Quaternion'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vectornav_msgs', 'msg'], 'InsStatus'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
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
        self.timesyncin = kwargs.get('timesyncin', int())
        from geometry_msgs.msg import Vector3
        self.yawpitchroll = kwargs.get('yawpitchroll', Vector3())
        from geometry_msgs.msg import Quaternion
        self.quaternion = kwargs.get('quaternion', Quaternion())
        from geometry_msgs.msg import Vector3
        self.angularrate = kwargs.get('angularrate', Vector3())
        from geometry_msgs.msg import Point
        self.position = kwargs.get('position', Point())
        from geometry_msgs.msg import Vector3
        self.velocity = kwargs.get('velocity', Vector3())
        from geometry_msgs.msg import Vector3
        self.accel = kwargs.get('accel', Vector3())
        from geometry_msgs.msg import Vector3
        self.imu_accel = kwargs.get('imu_accel', Vector3())
        from geometry_msgs.msg import Vector3
        self.imu_rate = kwargs.get('imu_rate', Vector3())
        from geometry_msgs.msg import Vector3
        self.magpres_mag = kwargs.get('magpres_mag', Vector3())
        self.magpres_temp = kwargs.get('magpres_temp', float())
        self.magpres_pres = kwargs.get('magpres_pres', float())
        self.deltatheta_dtime = kwargs.get('deltatheta_dtime', float())
        from geometry_msgs.msg import Vector3
        self.deltatheta_dtheta = kwargs.get('deltatheta_dtheta', Vector3())
        from geometry_msgs.msg import Vector3
        self.deltatheta_dvel = kwargs.get('deltatheta_dvel', Vector3())
        from vectornav_msgs.msg import InsStatus
        self.insstatus = kwargs.get('insstatus', InsStatus())
        self.syncincnt = kwargs.get('syncincnt', int())
        self.timegpspps = kwargs.get('timegpspps', int())

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
        if self.timesyncin != other.timesyncin:
            return False
        if self.yawpitchroll != other.yawpitchroll:
            return False
        if self.quaternion != other.quaternion:
            return False
        if self.angularrate != other.angularrate:
            return False
        if self.position != other.position:
            return False
        if self.velocity != other.velocity:
            return False
        if self.accel != other.accel:
            return False
        if self.imu_accel != other.imu_accel:
            return False
        if self.imu_rate != other.imu_rate:
            return False
        if self.magpres_mag != other.magpres_mag:
            return False
        if self.magpres_temp != other.magpres_temp:
            return False
        if self.magpres_pres != other.magpres_pres:
            return False
        if self.deltatheta_dtime != other.deltatheta_dtime:
            return False
        if self.deltatheta_dtheta != other.deltatheta_dtheta:
            return False
        if self.deltatheta_dvel != other.deltatheta_dvel:
            return False
        if self.insstatus != other.insstatus:
            return False
        if self.syncincnt != other.syncincnt:
            return False
        if self.timegpspps != other.timegpspps:
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
    def yawpitchroll(self):
        """Message field 'yawpitchroll'."""
        return self._yawpitchroll

    @yawpitchroll.setter
    def yawpitchroll(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'yawpitchroll' field must be a sub message of type 'Vector3'"
        self._yawpitchroll = value

    @builtins.property
    def quaternion(self):
        """Message field 'quaternion'."""
        return self._quaternion

    @quaternion.setter
    def quaternion(self, value):
        if __debug__:
            from geometry_msgs.msg import Quaternion
            assert \
                isinstance(value, Quaternion), \
                "The 'quaternion' field must be a sub message of type 'Quaternion'"
        self._quaternion = value

    @builtins.property
    def angularrate(self):
        """Message field 'angularrate'."""
        return self._angularrate

    @angularrate.setter
    def angularrate(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'angularrate' field must be a sub message of type 'Vector3'"
        self._angularrate = value

    @builtins.property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'position' field must be a sub message of type 'Point'"
        self._position = value

    @builtins.property
    def velocity(self):
        """Message field 'velocity'."""
        return self._velocity

    @velocity.setter
    def velocity(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'velocity' field must be a sub message of type 'Vector3'"
        self._velocity = value

    @builtins.property
    def accel(self):
        """Message field 'accel'."""
        return self._accel

    @accel.setter
    def accel(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'accel' field must be a sub message of type 'Vector3'"
        self._accel = value

    @builtins.property
    def imu_accel(self):
        """Message field 'imu_accel'."""
        return self._imu_accel

    @imu_accel.setter
    def imu_accel(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'imu_accel' field must be a sub message of type 'Vector3'"
        self._imu_accel = value

    @builtins.property
    def imu_rate(self):
        """Message field 'imu_rate'."""
        return self._imu_rate

    @imu_rate.setter
    def imu_rate(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'imu_rate' field must be a sub message of type 'Vector3'"
        self._imu_rate = value

    @builtins.property
    def magpres_mag(self):
        """Message field 'magpres_mag'."""
        return self._magpres_mag

    @magpres_mag.setter
    def magpres_mag(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'magpres_mag' field must be a sub message of type 'Vector3'"
        self._magpres_mag = value

    @builtins.property
    def magpres_temp(self):
        """Message field 'magpres_temp'."""
        return self._magpres_temp

    @magpres_temp.setter
    def magpres_temp(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'magpres_temp' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'magpres_temp' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._magpres_temp = value

    @builtins.property
    def magpres_pres(self):
        """Message field 'magpres_pres'."""
        return self._magpres_pres

    @magpres_pres.setter
    def magpres_pres(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'magpres_pres' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'magpres_pres' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._magpres_pres = value

    @builtins.property
    def deltatheta_dtime(self):
        """Message field 'deltatheta_dtime'."""
        return self._deltatheta_dtime

    @deltatheta_dtime.setter
    def deltatheta_dtime(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'deltatheta_dtime' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'deltatheta_dtime' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._deltatheta_dtime = value

    @builtins.property
    def deltatheta_dtheta(self):
        """Message field 'deltatheta_dtheta'."""
        return self._deltatheta_dtheta

    @deltatheta_dtheta.setter
    def deltatheta_dtheta(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'deltatheta_dtheta' field must be a sub message of type 'Vector3'"
        self._deltatheta_dtheta = value

    @builtins.property
    def deltatheta_dvel(self):
        """Message field 'deltatheta_dvel'."""
        return self._deltatheta_dvel

    @deltatheta_dvel.setter
    def deltatheta_dvel(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'deltatheta_dvel' field must be a sub message of type 'Vector3'"
        self._deltatheta_dvel = value

    @builtins.property
    def insstatus(self):
        """Message field 'insstatus'."""
        return self._insstatus

    @insstatus.setter
    def insstatus(self, value):
        if __debug__:
            from vectornav_msgs.msg import InsStatus
            assert \
                isinstance(value, InsStatus), \
                "The 'insstatus' field must be a sub message of type 'InsStatus'"
        self._insstatus = value

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
    def timegpspps(self):
        """Message field 'timegpspps'."""
        return self._timegpspps

    @timegpspps.setter
    def timegpspps(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timegpspps' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'timegpspps' field must be an unsigned integer in [0, 65535]"
        self._timegpspps = value
