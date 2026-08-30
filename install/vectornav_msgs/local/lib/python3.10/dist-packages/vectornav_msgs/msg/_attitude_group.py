# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vectornav_msgs:msg/AttitudeGroup.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'dcm'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_AttitudeGroup(type):
    """Metaclass of message 'AttitudeGroup'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'ATTITUDEGROUP_VPESTATUS': 1,
        'ATTITUDEGROUP_YAWPITCHROLL': 2,
        'ATTITUDEGROUP_QUATERNION': 4,
        'ATTITUDEGROUP_DCM': 8,
        'ATTITUDEGROUP_MAGNED': 16,
        'ATTITUDEGROUP_ACCELNED': 32,
        'ATTITUDEGROUP_LINEARACCELBODY': 64,
        'ATTITUDEGROUP_LINEARACCELNED': 128,
        'ATTITUDEGROUP_YPRU': 256,
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
                'vectornav_msgs.msg.AttitudeGroup')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__attitude_group
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__attitude_group
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__attitude_group
            cls._TYPE_SUPPORT = module.type_support_msg__msg__attitude_group
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__attitude_group

            from geometry_msgs.msg import Quaternion
            if Quaternion.__class__._TYPE_SUPPORT is None:
                Quaternion.__class__.__import_type_support__()

            from geometry_msgs.msg import Vector3
            if Vector3.__class__._TYPE_SUPPORT is None:
                Vector3.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

            from vectornav_msgs.msg import VpeStatus
            if VpeStatus.__class__._TYPE_SUPPORT is None:
                VpeStatus.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'ATTITUDEGROUP_VPESTATUS': cls.__constants['ATTITUDEGROUP_VPESTATUS'],
            'ATTITUDEGROUP_YAWPITCHROLL': cls.__constants['ATTITUDEGROUP_YAWPITCHROLL'],
            'ATTITUDEGROUP_QUATERNION': cls.__constants['ATTITUDEGROUP_QUATERNION'],
            'ATTITUDEGROUP_DCM': cls.__constants['ATTITUDEGROUP_DCM'],
            'ATTITUDEGROUP_MAGNED': cls.__constants['ATTITUDEGROUP_MAGNED'],
            'ATTITUDEGROUP_ACCELNED': cls.__constants['ATTITUDEGROUP_ACCELNED'],
            'ATTITUDEGROUP_LINEARACCELBODY': cls.__constants['ATTITUDEGROUP_LINEARACCELBODY'],
            'ATTITUDEGROUP_LINEARACCELNED': cls.__constants['ATTITUDEGROUP_LINEARACCELNED'],
            'ATTITUDEGROUP_YPRU': cls.__constants['ATTITUDEGROUP_YPRU'],
        }

    @property
    def ATTITUDEGROUP_VPESTATUS(self):
        """Message constant 'ATTITUDEGROUP_VPESTATUS'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_VPESTATUS']

    @property
    def ATTITUDEGROUP_YAWPITCHROLL(self):
        """Message constant 'ATTITUDEGROUP_YAWPITCHROLL'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_YAWPITCHROLL']

    @property
    def ATTITUDEGROUP_QUATERNION(self):
        """Message constant 'ATTITUDEGROUP_QUATERNION'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_QUATERNION']

    @property
    def ATTITUDEGROUP_DCM(self):
        """Message constant 'ATTITUDEGROUP_DCM'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_DCM']

    @property
    def ATTITUDEGROUP_MAGNED(self):
        """Message constant 'ATTITUDEGROUP_MAGNED'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_MAGNED']

    @property
    def ATTITUDEGROUP_ACCELNED(self):
        """Message constant 'ATTITUDEGROUP_ACCELNED'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_ACCELNED']

    @property
    def ATTITUDEGROUP_LINEARACCELBODY(self):
        """Message constant 'ATTITUDEGROUP_LINEARACCELBODY'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_LINEARACCELBODY']

    @property
    def ATTITUDEGROUP_LINEARACCELNED(self):
        """Message constant 'ATTITUDEGROUP_LINEARACCELNED'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_LINEARACCELNED']

    @property
    def ATTITUDEGROUP_YPRU(self):
        """Message constant 'ATTITUDEGROUP_YPRU'."""
        return Metaclass_AttitudeGroup.__constants['ATTITUDEGROUP_YPRU']


class AttitudeGroup(metaclass=Metaclass_AttitudeGroup):
    """
    Message class 'AttitudeGroup'.

    Constants:
      ATTITUDEGROUP_VPESTATUS
      ATTITUDEGROUP_YAWPITCHROLL
      ATTITUDEGROUP_QUATERNION
      ATTITUDEGROUP_DCM
      ATTITUDEGROUP_MAGNED
      ATTITUDEGROUP_ACCELNED
      ATTITUDEGROUP_LINEARACCELBODY
      ATTITUDEGROUP_LINEARACCELNED
      ATTITUDEGROUP_YPRU
    """

    __slots__ = [
        '_header',
        '_group_fields',
        '_vpestatus',
        '_yawpitchroll',
        '_quaternion',
        '_dcm',
        '_magned',
        '_accelned',
        '_linearaccelbody',
        '_linearaccelned',
        '_ypru',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'group_fields': 'uint16',
        'vpestatus': 'vectornav_msgs/VpeStatus',
        'yawpitchroll': 'geometry_msgs/Vector3',
        'quaternion': 'geometry_msgs/Quaternion',
        'dcm': 'float[9]',
        'magned': 'geometry_msgs/Vector3',
        'accelned': 'geometry_msgs/Vector3',
        'linearaccelbody': 'geometry_msgs/Vector3',
        'linearaccelned': 'geometry_msgs/Vector3',
        'ypru': 'geometry_msgs/Vector3',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['vectornav_msgs', 'msg'], 'VpeStatus'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Quaternion'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 9),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Vector3'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.group_fields = kwargs.get('group_fields', int())
        from vectornav_msgs.msg import VpeStatus
        self.vpestatus = kwargs.get('vpestatus', VpeStatus())
        from geometry_msgs.msg import Vector3
        self.yawpitchroll = kwargs.get('yawpitchroll', Vector3())
        from geometry_msgs.msg import Quaternion
        self.quaternion = kwargs.get('quaternion', Quaternion())
        if 'dcm' not in kwargs:
            self.dcm = numpy.zeros(9, dtype=numpy.float32)
        else:
            self.dcm = kwargs.get('dcm')
        from geometry_msgs.msg import Vector3
        self.magned = kwargs.get('magned', Vector3())
        from geometry_msgs.msg import Vector3
        self.accelned = kwargs.get('accelned', Vector3())
        from geometry_msgs.msg import Vector3
        self.linearaccelbody = kwargs.get('linearaccelbody', Vector3())
        from geometry_msgs.msg import Vector3
        self.linearaccelned = kwargs.get('linearaccelned', Vector3())
        from geometry_msgs.msg import Vector3
        self.ypru = kwargs.get('ypru', Vector3())

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
        if self.vpestatus != other.vpestatus:
            return False
        if self.yawpitchroll != other.yawpitchroll:
            return False
        if self.quaternion != other.quaternion:
            return False
        if any(self.dcm != other.dcm):
            return False
        if self.magned != other.magned:
            return False
        if self.accelned != other.accelned:
            return False
        if self.linearaccelbody != other.linearaccelbody:
            return False
        if self.linearaccelned != other.linearaccelned:
            return False
        if self.ypru != other.ypru:
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
    def vpestatus(self):
        """Message field 'vpestatus'."""
        return self._vpestatus

    @vpestatus.setter
    def vpestatus(self, value):
        if __debug__:
            from vectornav_msgs.msg import VpeStatus
            assert \
                isinstance(value, VpeStatus), \
                "The 'vpestatus' field must be a sub message of type 'VpeStatus'"
        self._vpestatus = value

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
    def dcm(self):
        """Message field 'dcm'."""
        return self._dcm

    @dcm.setter
    def dcm(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'dcm' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 9, \
                "The 'dcm' numpy.ndarray() must have a size of 9"
            self._dcm = value
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
                 len(value) == 9 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'dcm' field must be a set or sequence with length 9 and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._dcm = numpy.array(value, dtype=numpy.float32)

    @builtins.property
    def magned(self):
        """Message field 'magned'."""
        return self._magned

    @magned.setter
    def magned(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'magned' field must be a sub message of type 'Vector3'"
        self._magned = value

    @builtins.property
    def accelned(self):
        """Message field 'accelned'."""
        return self._accelned

    @accelned.setter
    def accelned(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'accelned' field must be a sub message of type 'Vector3'"
        self._accelned = value

    @builtins.property
    def linearaccelbody(self):
        """Message field 'linearaccelbody'."""
        return self._linearaccelbody

    @linearaccelbody.setter
    def linearaccelbody(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'linearaccelbody' field must be a sub message of type 'Vector3'"
        self._linearaccelbody = value

    @builtins.property
    def linearaccelned(self):
        """Message field 'linearaccelned'."""
        return self._linearaccelned

    @linearaccelned.setter
    def linearaccelned(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'linearaccelned' field must be a sub message of type 'Vector3'"
        self._linearaccelned = value

    @builtins.property
    def ypru(self):
        """Message field 'ypru'."""
        return self._ypru

    @ypru.setter
    def ypru(self, value):
        if __debug__:
            from geometry_msgs.msg import Vector3
            assert \
                isinstance(value, Vector3), \
                "The 'ypru' field must be a sub message of type 'Vector3'"
        self._ypru = value
