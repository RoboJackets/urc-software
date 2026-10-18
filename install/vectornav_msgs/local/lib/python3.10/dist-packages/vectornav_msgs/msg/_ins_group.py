# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/InsGroup.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_InsGroup(type):
    """Metaclass of message 'InsGroup'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'INSGROUP_INSSTATUS': 1,
        'INSGROUP_POSLLA': 2,
        'INSGROUP_POSECEF': 4,
        'INSGROUP_VELBODY': 8,
        'INSGROUP_VELNED': 16,
        'INSGROUP_VELECEF': 32,
        'INSGROUP_MAGECEF': 64,
        'INSGROUP_ACCELECEF': 128,
        'INSGROUP_LINEARACCELECEF': 256,
        'INSGROUP_POSU': 512,
        'INSGROUP_VELU': 1024,
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
                'vectornav_msgs.msg.InsGroup')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__ins_group
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__ins_group
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__ins_group
            cls._TYPE_SUPPORT = module.type_support_msg__msg__ins_group
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__ins_group

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

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
            'INSGROUP_INSSTATUS': cls.__constants['INSGROUP_INSSTATUS'],
            'INSGROUP_POSLLA': cls.__constants['INSGROUP_POSLLA'],
            'INSGROUP_POSECEF': cls.__constants['INSGROUP_POSECEF'],
            'INSGROUP_VELBODY': cls.__constants['INSGROUP_VELBODY'],
            'INSGROUP_VELNED': cls.__constants['INSGROUP_VELNED'],
            'INSGROUP_VELECEF': cls.__constants['INSGROUP_VELECEF'],
            'INSGROUP_MAGECEF': cls.__constants['INSGROUP_MAGECEF'],
            'INSGROUP_ACCELECEF': cls.__constants['INSGROUP_ACCELECEF'],
            'INSGROUP_LINEARACCELECEF': cls.__constants['INSGROUP_LINEARACCELECEF'],
            'INSGROUP_POSU': cls.__constants['INSGROUP_POSU'],
            'INSGROUP_VELU': cls.__constants['INSGROUP_VELU'],
        }

    @property
    def INSGROUP_INSSTATUS(self):
        """Message constant 'INSGROUP_INSSTATUS'."""
        return Metaclass_InsGroup.__constants['INSGROUP_INSSTATUS']

    @property
    def INSGROUP_POSLLA(self):
        """Message constant 'INSGROUP_POSLLA'."""
        return Metaclass_InsGroup.__constants['INSGROUP_POSLLA']

    @property
    def INSGROUP_POSECEF(self):
        """Message constant 'INSGROUP_POSECEF'."""
        return Metaclass_InsGroup.__constants['INSGROUP_POSECEF']

    @property
    def INSGROUP_VELBODY(self):
        """Message constant 'INSGROUP_VELBODY'."""
        return Metaclass_InsGroup.__constants['INSGROUP_VELBODY']

    @property
    def INSGROUP_VELNED(self):
        """Message constant 'INSGROUP_VELNED'."""
        return Metaclass_InsGroup.__constants['INSGROUP_VELNED']

    @property
    def INSGROUP_VELECEF(self):
        """Message constant 'INSGROUP_VELECEF'."""
        return Metaclass_InsGroup.__constants['INSGROUP_VELECEF']

    @property
    def INSGROUP_MAGECEF(self):
        """Message constant 'INSGROUP_MAGECEF'."""
        return Metaclass_InsGroup.__constants['INSGROUP_MAGECEF']

    @property
    def INSGROUP_ACCELECEF(self):
        """Message constant 'INSGROUP_ACCELECEF'."""
        return Metaclass_InsGroup.__constants['INSGROUP_ACCELECEF']

    @property
    def INSGROUP_LINEARACCELECEF(self):
        """Message constant 'INSGROUP_LINEARACCELECEF'."""
        return Metaclass_InsGroup.__constants['INSGROUP_LINEARACCELECEF']

    @property
    def INSGROUP_POSU(self):
        """Message constant 'INSGROUP_POSU'."""
        return Metaclass_InsGroup.__constants['INSGROUP_POSU']

    @property
    def INSGROUP_VELU(self):
        """Message constant 'INSGROUP_VELU'."""
        return Metaclass_InsGroup.__constants['INSGROUP_VELU']


class InsGroup(metaclass=Metaclass_InsGroup):
    """
    Message class 'InsGroup'.

    Constants:
      INSGROUP_INSSTATUS
      INSGROUP_POSLLA
      INSGROUP_POSECEF
      INSGROUP_VELBODY
      INSGROUP_VELNED
      INSGROUP_VELECEF
      INSGROUP_MAGECEF
      INSGROUP_ACCELECEF
      INSGROUP_LINEARACCELECEF
      INSGROUP_POSU
      INSGROUP_VELU
    """

    __slots__ = [
        '_header',
        '_group_fields',
        '_insstatus',
        '_poslla',
        '_posecef',
        '_velbody',
        '_velned',
        '_velecef',
        '_magecef',
        '_accelecef',
        '_linearaccelecef',
        '_posu',
        '_velu',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'group_fields': 'uint16',
        'insstatus': 'vectornav_msgs/InsStatus',
        'poslla': 'geometry_msgs/Point',
        'posecef': 'geometry_msgs/Point',
        'velbody': 'geometry_msgs/Vector3',
        'velned': 'geometry_msgs/Vector3',
        'velecef': 'geometry_msgs/Vector3',
        'magecef': 'geometry_msgs/Vector3',
        'accelecef': 'geometry_msgs/Vector3',
        'linearaccelecef': 'geometry_msgs/Vector3',
        'posu': 'float',
        'velu': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vectornav_msgs', 'msg'], 'InsStatus'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.group_fields = kwargs.get('group_fields', int())
        from vectornav_msgs.msg import InsStatus
        self.insstatus = kwargs.get('insstatus', InsStatus())
        from geometry_msgs.msg import Point
        self.poslla = kwargs.get('poslla', Point())
        from geometry_msgs.msg import Point
        self.posecef = kwargs.get('posecef', Point())
        from geometry_msgs.msg import Vector3
        self.velbody = kwargs.get('velbody', Vector3())
        from geometry_msgs.msg import Vector3
        self.velned = kwargs.get('velned', Vector3())
        from geometry_msgs.msg import Vector3
        self.velecef = kwargs.get('velecef', Vector3())
        from geometry_msgs.msg import Vector3
        self.magecef = kwargs.get('magecef', Vector3())
        from geometry_msgs.msg import Vector3
        self.accelecef = kwargs.get('accelecef', Vector3())
        from geometry_msgs.msg import Vector3
        self.linearaccelecef = kwargs.get('linearaccelecef', Vector3())
        self.posu = kwargs.get('posu', float())
        self.velu = kwargs.get('velu', float())

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
        if self.insstatus != other.insstatus:
            return False
        if self.poslla != other.poslla:
            return False
        if self.posecef != other.posecef:
            return False
        if self.velbody != other.velbody:
            return False
        if self.velned != other.velned:
            return False
        if self.velecef != other.velecef:
            return False
        if self.magecef != other.magecef:
            return False
        if self.accelecef != other.accelecef:
            return False
        if self.linearaccelecef != other.linearaccelecef:
            return False
        if self.posu != other.posu:
            return False
        if self.velu != other.velu:
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
    def velbody(self):
        """Message field 'velbody'."""
        return self._velbody

    @velbody.setter
    def velbody(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'velbody' field must be a sub message of type 'Vector3'"
        self._velbody = value

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
    def magecef(self):
        """Message field 'magecef'."""
        return self._magecef

    @magecef.setter
    def magecef(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'magecef' field must be a sub message of type 'Vector3'"
        self._magecef = value

    @builtins.property
    def accelecef(self):
        """Message field 'accelecef'."""
        return self._accelecef

    @accelecef.setter
    def accelecef(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'accelecef' field must be a sub message of type 'Vector3'"
        self._accelecef = value

    @builtins.property
    def linearaccelecef(self):
        """Message field 'linearaccelecef'."""
        return self._linearaccelecef

    @linearaccelecef.setter
    def linearaccelecef(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'linearaccelecef' field must be a sub message of type 'Vector3'"
        self._linearaccelecef = value

    @builtins.property
    def posu(self):
        """Message field 'posu'."""
        return self._posu

    @posu.setter
    def posu(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'posu' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'posu' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
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
