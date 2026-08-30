# generated from rosidl_generator_py/resource/_idl.py.em
# with input from urc_msgs:msg/BatteryInfo.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'cell_voltages'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_BatteryInfo(type):
    """Metaclass of message 'BatteryInfo'."""

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
                'urc_msgs.msg.BatteryInfo')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__battery_info
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__battery_info
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__battery_info
            cls._TYPE_SUPPORT = module.type_support_msg__msg__battery_info
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__battery_info

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class BatteryInfo(metaclass=Metaclass_BatteryInfo):
    """Message class 'BatteryInfo'."""

    __slots__ = [
        '_cell_voltage',
        '_cell_charge_percentage',
        '_cell_discharge_current',
        '_cell_temperature',
        '_cell_voltages',
    ]

    _fields_and_field_types = {
        'cell_voltage': 'float',
        'cell_charge_percentage': 'float',
        'cell_discharge_current': 'float',
        'cell_temperature': 'float',
        'cell_voltages': 'sequence<float>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.cell_voltage = kwargs.get('cell_voltage', float())
        self.cell_charge_percentage = kwargs.get('cell_charge_percentage', float())
        self.cell_discharge_current = kwargs.get('cell_discharge_current', float())
        self.cell_temperature = kwargs.get('cell_temperature', float())
        self.cell_voltages = array.array('f', kwargs.get('cell_voltages', []))

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
        if self.cell_voltage != other.cell_voltage:
            return False
        if self.cell_charge_percentage != other.cell_charge_percentage:
            return False
        if self.cell_discharge_current != other.cell_discharge_current:
            return False
        if self.cell_temperature != other.cell_temperature:
            return False
        if self.cell_voltages != other.cell_voltages:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def cell_voltage(self):
        """Message field 'cell_voltage'."""
        return self._cell_voltage

    @cell_voltage.setter
    def cell_voltage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'cell_voltage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'cell_voltage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._cell_voltage = value

    @builtins.property
    def cell_charge_percentage(self):
        """Message field 'cell_charge_percentage'."""
        return self._cell_charge_percentage

    @cell_charge_percentage.setter
    def cell_charge_percentage(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'cell_charge_percentage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'cell_charge_percentage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._cell_charge_percentage = value

    @builtins.property
    def cell_discharge_current(self):
        """Message field 'cell_discharge_current'."""
        return self._cell_discharge_current

    @cell_discharge_current.setter
    def cell_discharge_current(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'cell_discharge_current' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'cell_discharge_current' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._cell_discharge_current = value

    @builtins.property
    def cell_temperature(self):
        """Message field 'cell_temperature'."""
        return self._cell_temperature

    @cell_temperature.setter
    def cell_temperature(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'cell_temperature' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'cell_temperature' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._cell_temperature = value

    @builtins.property
    def cell_voltages(self):
        """Message field 'cell_voltages'."""
        return self._cell_voltages

    @cell_voltages.setter
    def cell_voltages(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'cell_voltages' array.array() must have the type code of 'f'"
            self._cell_voltages = value
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
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'cell_voltages' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._cell_voltages = array.array('f', value)
