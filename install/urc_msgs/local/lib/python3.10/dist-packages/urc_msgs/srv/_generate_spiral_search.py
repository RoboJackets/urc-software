# generated from rosidl_generator_py/resource/_idl.py.em
# with input from urc_msgs:srv/GenerateSpiralSearch.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GenerateSpiralSearch_Request(type):
    """Metaclass of message 'GenerateSpiralSearch_Request'."""

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
                'urc_msgs.srv.GenerateSpiralSearch_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__generate_spiral_search__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__generate_spiral_search__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__generate_spiral_search__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__generate_spiral_search__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__generate_spiral_search__request

            from geometry_msgs.msg import PoseStamped
            if PoseStamped.__class__._TYPE_SUPPORT is None:
                PoseStamped.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GenerateSpiralSearch_Request(metaclass=Metaclass_GenerateSpiralSearch_Request):
    """Message class 'GenerateSpiralSearch_Request'."""

    __slots__ = [
        '_center',
        '_search_radius',
        '_track_spacing',
        '_waypoint_spacing',
    ]

    _fields_and_field_types = {
        'center': 'geometry_msgs/PoseStamped',
        'search_radius': 'double',
        'track_spacing': 'double',
        'waypoint_spacing': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseStamped'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from geometry_msgs.msg import PoseStamped
        self.center = kwargs.get('center', PoseStamped())
        self.search_radius = kwargs.get('search_radius', float())
        self.track_spacing = kwargs.get('track_spacing', float())
        self.waypoint_spacing = kwargs.get('waypoint_spacing', float())

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
        if self.center != other.center:
            return False
        if self.search_radius != other.search_radius:
            return False
        if self.track_spacing != other.track_spacing:
            return False
        if self.waypoint_spacing != other.waypoint_spacing:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def center(self):
        """Message field 'center'."""
        return self._center

    @center.setter
    def center(self, value):
        if __debug__:
            from geometry_msgs.msg import PoseStamped
            assert \
                isinstance(value, PoseStamped), \
                "The 'center' field must be a sub message of type 'PoseStamped'"
        self._center = value

    @builtins.property
    def search_radius(self):
        """Message field 'search_radius'."""
        return self._search_radius

    @search_radius.setter
    def search_radius(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'search_radius' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'search_radius' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._search_radius = value

    @builtins.property
    def track_spacing(self):
        """Message field 'track_spacing'."""
        return self._track_spacing

    @track_spacing.setter
    def track_spacing(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'track_spacing' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'track_spacing' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._track_spacing = value

    @builtins.property
    def waypoint_spacing(self):
        """Message field 'waypoint_spacing'."""
        return self._waypoint_spacing

    @waypoint_spacing.setter
    def waypoint_spacing(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'waypoint_spacing' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'waypoint_spacing' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._waypoint_spacing = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import math

# already imported above
# import rosidl_parser.definition


class Metaclass_GenerateSpiralSearch_Response(type):
    """Metaclass of message 'GenerateSpiralSearch_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'SUCCESS': 0,
        'INVALID_REQUEST': 1,
        'FAILURE': 2,
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
                'urc_msgs.srv.GenerateSpiralSearch_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__generate_spiral_search__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__generate_spiral_search__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__generate_spiral_search__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__generate_spiral_search__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__generate_spiral_search__response

            from nav_msgs.msg import Path
            if Path.__class__._TYPE_SUPPORT is None:
                Path.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'SUCCESS': cls.__constants['SUCCESS'],
            'INVALID_REQUEST': cls.__constants['INVALID_REQUEST'],
            'FAILURE': cls.__constants['FAILURE'],
        }

    @property
    def SUCCESS(self):
        """Message constant 'SUCCESS'."""
        return Metaclass_GenerateSpiralSearch_Response.__constants['SUCCESS']

    @property
    def INVALID_REQUEST(self):
        """Message constant 'INVALID_REQUEST'."""
        return Metaclass_GenerateSpiralSearch_Response.__constants['INVALID_REQUEST']

    @property
    def FAILURE(self):
        """Message constant 'FAILURE'."""
        return Metaclass_GenerateSpiralSearch_Response.__constants['FAILURE']


class GenerateSpiralSearch_Response(metaclass=Metaclass_GenerateSpiralSearch_Response):
    """
    Message class 'GenerateSpiralSearch_Response'.

    Constants:
      SUCCESS
      INVALID_REQUEST
      FAILURE
    """

    __slots__ = [
        '_path',
        '_track_spacing',
        '_path_length',
        '_error_code',
    ]

    _fields_and_field_types = {
        'path': 'nav_msgs/Path',
        'track_spacing': 'double',
        'path_length': 'double',
        'error_code': 'uint16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['nav_msgs', 'msg'], 'Path'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from nav_msgs.msg import Path
        self.path = kwargs.get('path', Path())
        self.track_spacing = kwargs.get('track_spacing', float())
        self.path_length = kwargs.get('path_length', float())
        self.error_code = kwargs.get('error_code', int())

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
        if self.path != other.path:
            return False
        if self.track_spacing != other.track_spacing:
            return False
        if self.path_length != other.path_length:
            return False
        if self.error_code != other.error_code:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def path(self):
        """Message field 'path'."""
        return self._path

    @path.setter
    def path(self, value):
        if __debug__:
            from nav_msgs.msg import Path
            assert \
                isinstance(value, Path), \
                "The 'path' field must be a sub message of type 'Path'"
        self._path = value

    @builtins.property
    def track_spacing(self):
        """Message field 'track_spacing'."""
        return self._track_spacing

    @track_spacing.setter
    def track_spacing(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'track_spacing' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'track_spacing' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._track_spacing = value

    @builtins.property
    def path_length(self):
        """Message field 'path_length'."""
        return self._path_length

    @path_length.setter
    def path_length(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'path_length' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'path_length' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._path_length = value

    @builtins.property
    def error_code(self):
        """Message field 'error_code'."""
        return self._error_code

    @error_code.setter
    def error_code(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'error_code' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'error_code' field must be an unsigned integer in [0, 65535]"
        self._error_code = value


class Metaclass_GenerateSpiralSearch(type):
    """Metaclass of service 'GenerateSpiralSearch'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('urc_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'urc_msgs.srv.GenerateSpiralSearch')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__generate_spiral_search

            from urc_msgs.srv import _generate_spiral_search
            if _generate_spiral_search.Metaclass_GenerateSpiralSearch_Request._TYPE_SUPPORT is None:
                _generate_spiral_search.Metaclass_GenerateSpiralSearch_Request.__import_type_support__()
            if _generate_spiral_search.Metaclass_GenerateSpiralSearch_Response._TYPE_SUPPORT is None:
                _generate_spiral_search.Metaclass_GenerateSpiralSearch_Response.__import_type_support__()


class GenerateSpiralSearch(metaclass=Metaclass_GenerateSpiralSearch):
    from urc_msgs.srv._generate_spiral_search import GenerateSpiralSearch_Request as Request
    from urc_msgs.srv._generate_spiral_search import GenerateSpiralSearch_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
