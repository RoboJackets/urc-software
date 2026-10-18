// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/GpsGroup.idl
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
#include "vectornav_msgs/msg/detail/gps_group__struct.h"
#include "vectornav_msgs/msg/detail/gps_group__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
bool vectornav_msgs__msg__time_utc__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vectornav_msgs__msg__time_utc__convert_to_py(void * raw_ros_message);
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
bool vectornav_msgs__msg__dop__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vectornav_msgs__msg__dop__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__gps_group__convert_from_py(PyObject * _pymsg, void * _ros_message)
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
    assert(strncmp("vectornav_msgs.msg._gps_group.GpsGroup", full_classname_dest, 38) == 0);
  }
  vectornav_msgs__msg__GpsGroup * ros_message = _ros_message;
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
  {  // utc
    PyObject * field = PyObject_GetAttrString(_pymsg, "utc");
    if (!field) {
      return false;
    }
    if (!vectornav_msgs__msg__time_utc__convert_from_py(field, &ros_message->utc)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // tow
    PyObject * field = PyObject_GetAttrString(_pymsg, "tow");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->tow = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // week
    PyObject * field = PyObject_GetAttrString(_pymsg, "week");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->week = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // numsats
    PyObject * field = PyObject_GetAttrString(_pymsg, "numsats");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->numsats = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // fix
    PyObject * field = PyObject_GetAttrString(_pymsg, "fix");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->fix = (uint8_t)PyLong_AsUnsignedLong(field);
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
  {  // posu
    PyObject * field = PyObject_GetAttrString(_pymsg, "posu");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->posu)) {
      Py_DECREF(field);
      return false;
    }
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
  {  // timeu
    PyObject * field = PyObject_GetAttrString(_pymsg, "timeu");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timeu = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // timeinfo_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "timeinfo_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timeinfo_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // timeinfo_leapseconds
    PyObject * field = PyObject_GetAttrString(_pymsg, "timeinfo_leapseconds");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timeinfo_leapseconds = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // dop
    PyObject * field = PyObject_GetAttrString(_pymsg, "dop");
    if (!field) {
      return false;
    }
    if (!vectornav_msgs__msg__dop__convert_from_py(field, &ros_message->dop)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__gps_group__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GpsGroup */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._gps_group");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GpsGroup");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__GpsGroup * ros_message = (vectornav_msgs__msg__GpsGroup *)raw_ros_message;
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
  {  // utc
    PyObject * field = NULL;
    field = vectornav_msgs__msg__time_utc__convert_to_py(&ros_message->utc);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "utc", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // tow
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->tow);
    {
      int rc = PyObject_SetAttrString(_pymessage, "tow", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // week
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->week);
    {
      int rc = PyObject_SetAttrString(_pymessage, "week", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // numsats
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->numsats);
    {
      int rc = PyObject_SetAttrString(_pymessage, "numsats", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fix
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->fix);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fix", field);
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
  {  // posu
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->posu);
    if (!field) {
      return NULL;
    }
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
  {  // timeu
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->timeu);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timeu", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timeinfo_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->timeinfo_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timeinfo_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timeinfo_leapseconds
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->timeinfo_leapseconds);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timeinfo_leapseconds", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // dop
    PyObject * field = NULL;
    field = vectornav_msgs__msg__dop__convert_to_py(&ros_message->dop);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "dop", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
