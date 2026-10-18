// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/TimeStatus.idl
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
#include "vectornav_msgs/msg/detail/time_status__struct.h"
#include "vectornav_msgs/msg/detail/time_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__time_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[43];
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
    assert(strncmp("vectornav_msgs.msg._time_status.TimeStatus", full_classname_dest, 42) == 0);
  }
  vectornav_msgs__msg__TimeStatus * ros_message = _ros_message;
  {  // time_ok
    PyObject * field = PyObject_GetAttrString(_pymsg, "time_ok");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->time_ok = (Py_True == field);
    Py_DECREF(field);
  }
  {  // date_ok
    PyObject * field = PyObject_GetAttrString(_pymsg, "date_ok");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->date_ok = (Py_True == field);
    Py_DECREF(field);
  }
  {  // utctime_ok
    PyObject * field = PyObject_GetAttrString(_pymsg, "utctime_ok");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->utctime_ok = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__time_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of TimeStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._time_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "TimeStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__TimeStatus * ros_message = (vectornav_msgs__msg__TimeStatus *)raw_ros_message;
  {  // time_ok
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->time_ok ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "time_ok", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // date_ok
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->date_ok ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "date_ok", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // utctime_ok
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->utctime_ok ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "utctime_ok", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
