// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/InsStatus.idl
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
#include "vectornav_msgs/msg/detail/ins_status__struct.h"
#include "vectornav_msgs/msg/detail/ins_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__ins_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
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
    assert(strncmp("vectornav_msgs.msg._ins_status.InsStatus", full_classname_dest, 40) == 0);
  }
  vectornav_msgs__msg__InsStatus * ros_message = _ros_message;
  {  // mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "mode");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->mode = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // gps_fix
    PyObject * field = PyObject_GetAttrString(_pymsg, "gps_fix");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->gps_fix = (Py_True == field);
    Py_DECREF(field);
  }
  {  // time_error
    PyObject * field = PyObject_GetAttrString(_pymsg, "time_error");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->time_error = (Py_True == field);
    Py_DECREF(field);
  }
  {  // imu_error
    PyObject * field = PyObject_GetAttrString(_pymsg, "imu_error");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->imu_error = (Py_True == field);
    Py_DECREF(field);
  }
  {  // mag_pres_error
    PyObject * field = PyObject_GetAttrString(_pymsg, "mag_pres_error");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->mag_pres_error = (Py_True == field);
    Py_DECREF(field);
  }
  {  // gps_error
    PyObject * field = PyObject_GetAttrString(_pymsg, "gps_error");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->gps_error = (Py_True == field);
    Py_DECREF(field);
  }
  {  // gps_heading_ins
    PyObject * field = PyObject_GetAttrString(_pymsg, "gps_heading_ins");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->gps_heading_ins = (Py_True == field);
    Py_DECREF(field);
  }
  {  // gps_compass
    PyObject * field = PyObject_GetAttrString(_pymsg, "gps_compass");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->gps_compass = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__ins_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of InsStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._ins_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "InsStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__InsStatus * ros_message = (vectornav_msgs__msg__InsStatus *)raw_ros_message;
  {  // mode
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->mode);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gps_fix
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->gps_fix ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gps_fix", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // time_error
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->time_error ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "time_error", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // imu_error
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->imu_error ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "imu_error", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mag_pres_error
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->mag_pres_error ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mag_pres_error", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gps_error
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->gps_error ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gps_error", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gps_heading_ins
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->gps_heading_ins ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gps_heading_ins", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gps_compass
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->gps_compass ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gps_compass", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
