// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/InsGroup.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "vectornav_msgs/msg/detail/ins_group__struct.h"
#include "vectornav_msgs/msg/detail/ins_group__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
bool vectornav_msgs__msg__ins_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vectornav_msgs__msg__ins_status__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__point__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__point__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__point__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__point__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__ins_group__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[39];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("vectornav_msgs.msg._ins_group.InsGroup", full_classname_dest, 38) == 0);
  }
  vectornav_msgs__msg__InsGroup * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // group_fields
    PyObject * field = PyObject_GetAttrString(_pymsg, "group_fields");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->group_fields = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // insstatus
    PyObject * field = PyObject_GetAttrString(_pymsg, "insstatus");
    if (!field) {
      return false;
    }
    if (!vectornav_msgs__msg__ins_status__convert_from_py(field, &ros_message->insstatus)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // poslla
    PyObject * field = PyObject_GetAttrString(_pymsg, "poslla");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__point__convert_from_py(field, &ros_message->poslla)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // posecef
    PyObject * field = PyObject_GetAttrString(_pymsg, "posecef");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__point__convert_from_py(field, &ros_message->posecef)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // velbody
    PyObject * field = PyObject_GetAttrString(_pymsg, "velbody");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->velbody)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // velned
    PyObject * field = PyObject_GetAttrString(_pymsg, "velned");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->velned)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // velecef
    PyObject * field = PyObject_GetAttrString(_pymsg, "velecef");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->velecef)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // magecef
    PyObject * field = PyObject_GetAttrString(_pymsg, "magecef");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->magecef)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // accelecef
    PyObject * field = PyObject_GetAttrString(_pymsg, "accelecef");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->accelecef)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // linearaccelecef
    PyObject * field = PyObject_GetAttrString(_pymsg, "linearaccelecef");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->linearaccelecef)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // posu
    PyObject * field = PyObject_GetAttrString(_pymsg, "posu");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->posu = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // velu
    PyObject * field = PyObject_GetAttrString(_pymsg, "velu");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->velu = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__ins_group__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of InsGroup */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._ins_group");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "InsGroup");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__InsGroup * ros_message = (vectornav_msgs__msg__InsGroup *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // group_fields
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->group_fields);
    {
      int rc = PyObject_SetAttrString(_pymessage, "group_fields", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // insstatus
    PyObject * field = NULL;
    field = vectornav_msgs__msg__ins_status__convert_to_py(&ros_message->insstatus);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "insstatus", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // poslla
    PyObject * field = NULL;
    field = geometry_msgs__msg__point__convert_to_py(&ros_message->poslla);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "poslla", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // posecef
    PyObject * field = NULL;
    field = geometry_msgs__msg__point__convert_to_py(&ros_message->posecef);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "posecef", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // velbody
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->velbody);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "velbody", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // velned
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->velned);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "velned", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // velecef
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->velecef);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "velecef", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // magecef
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->magecef);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "magecef", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // accelecef
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->accelecef);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "accelecef", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // linearaccelecef
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->linearaccelecef);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "linearaccelecef", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // posu
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->posu);
    {
      int rc = PyObject_SetAttrString(_pymessage, "posu", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // velu
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->velu);
    {
      int rc = PyObject_SetAttrString(_pymessage, "velu", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
