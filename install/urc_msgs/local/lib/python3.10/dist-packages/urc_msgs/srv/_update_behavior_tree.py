# generated from rosidl_generator_py/resource/_idl.py.em
# with input from urc_msgs:srv/UpdateBehaviorTree.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_UpdateBehaviorTree_Request(type):
    """Metaclass of message 'UpdateBehaviorTree_Request'."""

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
                'urc_msgs.srv.UpdateBehaviorTree_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__update_behavior_tree__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__update_behavior_tree__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__update_behavior_tree__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__update_behavior_tree__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__update_behavior_tree__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class UpdateBehaviorTree_Request(metaclass=Metaclass_UpdateBehaviorTree_Request):
    """Message class 'UpdateBehaviorTree_Request'."""

    __slots__ = [
        '_tree_content',
        '_tree_dir',
        '_use_dir',
    ]

    _fields_and_field_types = {
        'tree_content': 'string',
        'tree_dir': 'string',
        'use_dir': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.tree_content = kwargs.get('tree_content', str())
        self.tree_dir = kwargs.get('tree_dir', str())
        self.use_dir = kwargs.get('use_dir', bool())

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
        if self.tree_content != other.tree_content:
            return False
        if self.tree_dir != other.tree_dir:
            return False
        if self.use_dir != other.use_dir:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def tree_content(self):
        """Message field 'tree_content'."""
        return self._tree_content

    @tree_content.setter
    def tree_content(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'tree_content' field must be of type 'str'"
        self._tree_content = value

    @builtins.property
    def tree_dir(self):
        """Message field 'tree_dir'."""
        return self._tree_dir

    @tree_dir.setter
    def tree_dir(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'tree_dir' field must be of type 'str'"
        self._tree_dir = value

    @builtins.property
    def use_dir(self):
        """Message field 'use_dir'."""
        return self._use_dir

    @use_dir.setter
    def use_dir(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'use_dir' field must be of type 'bool'"
        self._use_dir = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_UpdateBehaviorTree_Response(type):
    """Metaclass of message 'UpdateBehaviorTree_Response'."""

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
                'urc_msgs.srv.UpdateBehaviorTree_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__update_behavior_tree__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__update_behavior_tree__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__update_behavior_tree__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__update_behavior_tree__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__update_behavior_tree__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class UpdateBehaviorTree_Response(metaclass=Metaclass_UpdateBehaviorTree_Response):
    """Message class 'UpdateBehaviorTree_Response'."""

    __slots__ = [
        '_success',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.success = kwargs.get('success', bool())

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
        if self.success != other.success:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value


class Metaclass_UpdateBehaviorTree(type):
    """Metaclass of service 'UpdateBehaviorTree'."""

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
                'urc_msgs.srv.UpdateBehaviorTree')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__update_behavior_tree

            from urc_msgs.srv import _update_behavior_tree
            if _update_behavior_tree.Metaclass_UpdateBehaviorTree_Request._TYPE_SUPPORT is None:
                _update_behavior_tree.Metaclass_UpdateBehaviorTree_Request.__import_type_support__()
            if _update_behavior_tree.Metaclass_UpdateBehaviorTree_Response._TYPE_SUPPORT is None:
                _update_behavior_tree.Metaclass_UpdateBehaviorTree_Response.__import_type_support__()


class UpdateBehaviorTree(metaclass=Metaclass_UpdateBehaviorTree):
    from urc_msgs.srv._update_behavior_tree import UpdateBehaviorTree_Request as Request
    from urc_msgs.srv._update_behavior_tree import UpdateBehaviorTree_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
