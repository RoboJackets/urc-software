# generated from rosidl_generator_py/resource/_idl.py.em
# with input from urc_msgs:msg/StatusLightCommand.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_StatusLightCommand(type):
    """Metaclass of message 'StatusLightCommand'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'RED': 0,
        'GREEN': 1,
        'BLUE': 2,
        'OFF': 0,
        'ON': 1,
        'BLINK': 2,
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
                'urc_msgs.msg.StatusLightCommand')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__status_light_command
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__status_light_command
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__status_light_command
            cls._TYPE_SUPPORT = module.type_support_msg__msg__status_light_command
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__status_light_command

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'RED': cls.__constants['RED'],
            'GREEN': cls.__constants['GREEN'],
            'BLUE': cls.__constants['BLUE'],
            'OFF': cls.__constants['OFF'],
            'ON': cls.__constants['ON'],
            'BLINK': cls.__constants['BLINK'],
        }

    @property
    def RED(self):
        """Message constant 'RED'."""
        return Metaclass_StatusLightCommand.__constants['RED']

    @property
    def GREEN(self):
        """Message constant 'GREEN'."""
        return Metaclass_StatusLightCommand.__constants['GREEN']

    @property
    def BLUE(self):
        """Message constant 'BLUE'."""
        return Metaclass_StatusLightCommand.__constants['BLUE']

    @property
    def OFF(self):
        """Message constant 'OFF'."""
        return Metaclass_StatusLightCommand.__constants['OFF']

    @property
    def ON(self):
        """Message constant 'ON'."""
        return Metaclass_StatusLightCommand.__constants['ON']

    @property
    def BLINK(self):
        """Message constant 'BLINK'."""
        return Metaclass_StatusLightCommand.__constants['BLINK']


class StatusLightCommand(metaclass=Metaclass_StatusLightCommand):
    """
    Message class 'StatusLightCommand'.

    Constants:
      RED
      GREEN
      BLUE
      OFF
      ON
      BLINK
    """

    __slots__ = [
        '_color',
        '_state',
    ]

    _fields_and_field_types = {
        'color': 'uint8',
        'state': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.color = kwargs.get('color', int())
        self.state = kwargs.get('state', int())

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
        if self.color != other.color:
            return False
        if self.state != other.state:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def color(self):
        """Message field 'color'."""
        return self._color

    @color.setter
    def color(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'color' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'color' field must be an unsigned integer in [0, 255]"
        self._color = value

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'state' field must be an unsigned integer in [0, 255]"
        self._state = value
