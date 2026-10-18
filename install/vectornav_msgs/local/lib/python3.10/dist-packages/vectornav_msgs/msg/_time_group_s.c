// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/TimeGroup.idl
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
#include "vectornav_msgs/msg/detail/time_group__struct.h"
#include "vectornav_msgs/msg/detail/time_group__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
bool vectornav_msgs__msg__time_utc__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vectornav_msgs__msg__time_utc__convert_to_py(void * raw_ros_message);
bool vectornav_msgs__msg__time_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vectornav_msgs__msg__time_status__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__time_group__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[41];
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
    assert(strncmp("vectornav_msgs.msg._time_group.TimeGroup", full_classname_dest, 40) == 0);
  }
  vectornav_msgs__msg__TimeGroup * ros_message = _ros_message;
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
  {  // timestartup
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestartup");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timestartup = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // timegps
    PyObject * field = PyObject_GetAttrString(_pymsg, "timegps");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timegps = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // gpstow
    PyObject * field = PyObject_GetAttrString(_pymsg, "gpstow");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->gpstow = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // gpsweek
    PyObject * field = PyObject_GetAttrString(_pymsg, "gpsweek");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->gpsweek = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // timesyncin
    PyObject * field = PyObject_GetAttrString(_pymsg, "timesyncin");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timesyncin = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // timegpspps
    PyObject * field = PyObject_GetAttrString(_pymsg, "timegpspps");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timegpspps = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // timeutc
    PyObject * field = PyObject_GetAttrString(_pymsg, "timeutc");
    if (!field) {
      return false;
    }
    if (!vectornav_msgs__msg__time_utc__convert_from_py(field, &ros_message->timeutc)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // syncincnt
    PyObject * field = PyObject_GetAttrString(_pymsg, "syncincnt");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->syncincnt = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // syncoutcnt
    PyObject * field = PyObject_GetAttrString(_pymsg, "syncoutcnt");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->syncoutcnt = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // timestatus
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestatus");
    if (!field) {
      return false;
    }
    if (!vectornav_msgs__msg__time_status__convert_from_py(field, &ros_message->timestatus)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__time_group__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of TimeGroup */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._time_group");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "TimeGroup");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__TimeGroup * ros_message = (vectornav_msgs__msg__TimeGroup *)raw_ros_message;
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
  {  // timestartup
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->timestartup);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestartup", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timegps
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->timegps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timegps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gpstow
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->gpstow);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gpstow", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gpsweek
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->gpsweek);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gpsweek", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timesyncin
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->timesyncin);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timesyncin", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timegpspps
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->timegpspps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timegpspps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timeutc
    PyObject * field = NULL;
    field = vectornav_msgs__msg__time_utc__convert_to_py(&ros_message->timeutc);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "timeutc", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // syncincnt
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->syncincnt);
    {
      int rc = PyObject_SetAttrString(_pymessage, "syncincnt", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // syncoutcnt
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->syncoutcnt);
    {
      int rc = PyObject_SetAttrString(_pymessage, "syncoutcnt", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timestatus
    PyObject * field = NULL;
    field = vectornav_msgs__msg__time_status__convert_to_py(&ros_message->timestatus);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestatus", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
