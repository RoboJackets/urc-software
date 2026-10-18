# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/ImuGroup.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ImuGroup(type):
    """Metaclass of message 'ImuGroup'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'IMUGROUP_IMUSTATUS': 1,
        'IMUGROUP_UNCOMPMAG': 2,
        'IMUGROUP_UNCOMPACCEL': 4,
        'IMUGROUP_UNCOMPGYRO': 8,
        'IMUGROUP_TEMP': 16,
        'IMUGROUP_PRES': 32,
        'IMUGROUP_DELTATHETA': 64,
        'IMUGROUP_DELTAVEL': 128,
        'IMUGROUP_MAG': 256,
        'IMUGROUP_ACCEL': 512,
        'IMUGROUP_ANGULARRATE': 1024,
        'IMUGROUP_SENSSAT': 2048,
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
                'vectornav_msgs.msg.ImuGroup')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__imu_group
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__imu_group
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__imu_group
            cls._TYPE_SUPPORT = module.type_support_msg__msg__imu_group
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__imu_group

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'IMUGROUP_IMUSTATUS': cls.__constants['IMUGROUP_IMUSTATUS'],
            'IMUGROUP_UNCOMPMAG': cls.__constants['IMUGROUP_UNCOMPMAG'],
            'IMUGROUP_UNCOMPACCEL': cls.__constants['IMUGROUP_UNCOMPACCEL'],
            'IMUGROUP_UNCOMPGYRO': cls.__constants['IMUGROUP_UNCOMPGYRO'],
            'IMUGROUP_TEMP': cls.__constants['IMUGROUP_TEMP'],
            'IMUGROUP_PRES': cls.__constants['IMUGROUP_PRES'],
            'IMUGROUP_DELTATHETA': cls.__constants['IMUGROUP_DELTATHETA'],
            'IMUGROUP_DELTAVEL': cls.__constants['IMUGROUP_DELTAVEL'],
            'IMUGROUP_MAG': cls.__constants['IMUGROUP_MAG'],
            'IMUGROUP_ACCEL': cls.__constants['IMUGROUP_ACCEL'],
            'IMUGROUP_ANGULARRATE': cls.__constants['IMUGROUP_ANGULARRATE'],
            'IMUGROUP_SENSSAT': cls.__constants['IMUGROUP_SENSSAT'],
        }

    @property
    def IMUGROUP_IMUSTATUS(self):
        """Message constant 'IMUGROUP_IMUSTATUS'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_IMUSTATUS']

    @property
    def IMUGROUP_UNCOMPMAG(self):
        """Message constant 'IMUGROUP_UNCOMPMAG'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_UNCOMPMAG']

    @property
    def IMUGROUP_UNCOMPACCEL(self):
        """Message constant 'IMUGROUP_UNCOMPACCEL'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_UNCOMPACCEL']

    @property
    def IMUGROUP_UNCOMPGYRO(self):
        """Message constant 'IMUGROUP_UNCOMPGYRO'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_UNCOMPGYRO']

    @property
    def IMUGROUP_TEMP(self):
        """Message constant 'IMUGROUP_TEMP'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_TEMP']

    @property
    def IMUGROUP_PRES(self):
        """Message constant 'IMUGROUP_PRES'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_PRES']

    @property
    def IMUGROUP_DELTATHETA(self):
        """Message constant 'IMUGROUP_DELTATHETA'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_DELTATHETA']

    @property
    def IMUGROUP_DELTAVEL(self):
        """Message constant 'IMUGROUP_DELTAVEL'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_DELTAVEL']

    @property
    def IMUGROUP_MAG(self):
        """Message constant 'IMUGROUP_MAG'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_MAG']

    @property
    def IMUGROUP_ACCEL(self):
        """Message constant 'IMUGROUP_ACCEL'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_ACCEL']

    @property
    def IMUGROUP_ANGULARRATE(self):
        """Message constant 'IMUGROUP_ANGULARRATE'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_ANGULARRATE']

    @property
    def IMUGROUP_SENSSAT(self):
        """Message constant 'IMUGROUP_SENSSAT'."""
        return Metaclass_ImuGroup.__constants['IMUGROUP_SENSSAT']


class ImuGroup(metaclass=Metaclass_ImuGroup):
    """
    Message class 'ImuGroup'.

    Constants:
      IMUGROUP_IMUSTATUS
      IMUGROUP_UNCOMPMAG
      IMUGROUP_UNCOMPACCEL
      IMUGROUP_UNCOMPGYRO
      IMUGROUP_TEMP
      IMUGROUP_PRES
      IMUGROUP_DELTATHETA
      IMUGROUP_DELTAVEL
      IMUGROUP_MAG
      IMUGROUP_ACCEL
      IMUGROUP_ANGULARRATE
      IMUGROUP_SENSSAT
    """

    __slots__ = [
        '_header',
        '_group_fields',
        '_imustatus',
        '_uncompmag',
        '_uncompaccel',
        '_uncompgyro',
        '_temp',
        '_pres',
        '_deltatheta_time',
        '_deltatheta_dtheta',
        '_deltavel',
        '_mag',
        '_accel',
        '_angularrate',
        '_sensat',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'group_fields': 'uint16',
        'imustatus': 'uint16',
        'uncompmag': 'geometry_msgs/Vector3',
        'uncompaccel': 'geometry_msgs/Vector3',
        'uncompgyro': 'geometry_msgs/Vector3',
        'temp': 'float',
        'pres': 'float',
        'deltatheta_time': 'float',
        'deltatheta_dtheta': 'geometry_msgs/Vector3',
        'deltavel': 'geometry_msgs/Vector3',
        'mag': 'geometry_msgs/Vector3',
        'accel': 'geometry_msgs/Vector3',
        'angularrate': 'geometry_msgs/Vector3',
        'sensat': 'uint16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.group_fields = kwargs.get('group_fields', int())
        self.imustatus = kwargs.get('imustatus', int())
        from geometry_msgs.msg import Vector3
        self.uncompmag = kwargs.get('uncompmag', Vector3())
        from geometry_msgs.msg import Vector3
        self.uncompaccel = kwargs.get('uncompaccel', Vector3())
        from geometry_msgs.msg import Vector3
        self.uncompgyro = kwargs.get('uncompgyro', Vector3())
        self.temp = kwargs.get('temp', float())
        self.pres = kwargs.get('pres', float())
        self.deltatheta_time = kwargs.get('deltatheta_time', float())
        from geometry_msgs.msg import Vector3
        self.deltatheta_dtheta = kwargs.get('deltatheta_dtheta', Vector3())
        from geometry_msgs.msg import Vector3
        self.deltavel = kwargs.get('deltavel', Vector3())
        from geometry_msgs.msg import Vector3
        self.mag = kwargs.get('mag', Vector3())
        from geometry_msgs.msg import Vector3
        self.accel = kwargs.get('accel', Vector3())
        from geometry_msgs.msg import Vector3
        self.angularrate = kwargs.get('angularrate', Vector3())
        self.sensat = kwargs.get('sensat', int())

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
        if self.imustatus != other.imustatus:
            return False
        if self.uncompmag != other.uncompmag:
            return False
        if self.uncompaccel != other.uncompaccel:
            return False
        if self.uncompgyro != other.uncompgyro:
            return False
        if self.temp != other.temp:
            return False
        if self.pres != other.pres:
            return False
        if self.deltatheta_time != other.deltatheta_time:
            return False
        if self.deltatheta_dtheta != other.deltatheta_dtheta:
            return False
        if self.deltavel != other.deltavel:
            return False
        if self.mag != other.mag:
            return False
        if self.accel != other.accel:
            return False
        if self.angularrate != other.angularrate:
            return False
        if self.sensat != other.sensat:
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
    def imustatus(self):
        """Message field 'imustatus'."""
        return self._imustatus

    @imustatus.setter
    def imustatus(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'imustatus' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'imustatus' field must be an unsigned integer in [0, 65535]"
        self._imustatus = value

    @builtins.property
    def uncompmag(self):
        """Message field 'uncompmag'."""
        return self._uncompmag

    @uncompmag.setter
    def uncompmag(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'uncompmag' field must be a sub message of type 'Vector3'"
        self._uncompmag = value

    @builtins.property
    def uncompaccel(self):
        """Message field 'uncompaccel'."""
        return self._uncompaccel

    @uncompaccel.setter
    def uncompaccel(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'uncompaccel' field must be a sub message of type 'Vector3'"
        self._uncompaccel = value

    @builtins.property
    def uncompgyro(self):
        """Message field 'uncompgyro'."""
        return self._uncompgyro

    @uncompgyro.setter
    def uncompgyro(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'uncompgyro' field must be a sub message of type 'Vector3'"
        self._uncompgyro = value

    @builtins.property
    def temp(self):
        """Message field 'temp'."""
        return self._temp

    @temp.setter
    def temp(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'temp' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'temp' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._temp = value

    @builtins.property
    def pres(self):
        """Message field 'pres'."""
        return self._pres

    @pres.setter
    def pres(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pres' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pres' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pres = value

    @builtins.property
    def deltatheta_time(self):
        """Message field 'deltatheta_time'."""
        return self._deltatheta_time

    @deltatheta_time.setter
    def deltatheta_time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'deltatheta_time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'deltatheta_time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._deltatheta_time = value

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
    def deltavel(self):
        """Message field 'deltavel'."""
        return self._deltavel

    @deltavel.setter
    def deltavel(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'deltavel' field must be a sub message of type 'Vector3'"
        self._deltavel = value

    @builtins.property
    def mag(self):
        """Message field 'mag'."""
        return self._mag

    @mag.setter
    def mag(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'mag' field must be a sub message of type 'Vector3'"
        self._mag = value

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
    def sensat(self):
        """Message field 'sensat'."""
        return self._sensat

    @sensat.setter
    def sensat(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sensat' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'sensat' field must be an unsigned integer in [0, 65535]"
        self._sensat = value
