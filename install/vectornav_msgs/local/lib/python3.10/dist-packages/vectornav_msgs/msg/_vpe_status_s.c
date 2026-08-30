// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/VpeStatus.idl
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
#include "vectornav_msgs/msg/detail/vpe_status__struct.h"
#include "vectornav_msgs/msg/detail/vpe_status__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__vpe_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
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
    assert(strncmp("vectornav_msgs.msg._vpe_status.VpeStatus", full_classname_dest, 40) == 0);
  }
  vectornav_msgs__msg__VpeStatus * ros_message = _ros_message;
  {  // attitude_quality
    PyObject * field = PyObject_GetAttrString(_pymsg, "attitude_quality");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->attitude_quality = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // gyro_saturation
    PyObject * field = PyObject_GetAttrString(_pymsg, "gyro_saturation");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->gyro_saturation = (Py_True == field);
    Py_DECREF(field);
  }
  {  // gyro_saturation_recovery
    PyObject * field = PyObject_GetAttrString(_pymsg, "gyro_saturation_recovery");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->gyro_saturation_recovery = (Py_True == field);
    Py_DECREF(field);
  }
  {  // mag_disturbance
    PyObject * field = PyObject_GetAttrString(_pymsg, "mag_disturbance");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->mag_disturbance = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // mag_saturation
    PyObject * field = PyObject_GetAttrString(_pymsg, "mag_saturation");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->mag_saturation = (Py_True == field);
    Py_DECREF(field);
  }
  {  // acc_disturbance
    PyObject * field = PyObject_GetAttrString(_pymsg, "acc_disturbance");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->acc_disturbance = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // acc_saturation
    PyObject * field = PyObject_GetAttrString(_pymsg, "acc_saturation");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->acc_saturation = (Py_True == field);
    Py_DECREF(field);
  }
  {  // known_mag_disturbance
    PyObject * field = PyObject_GetAttrString(_pymsg, "known_mag_disturbance");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->known_mag_disturbance = (Py_True == field);
    Py_DECREF(field);
  }
  {  // known_accel_disturbance
    PyObject * field = PyObject_GetAttrString(_pymsg, "known_accel_disturbance");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->known_accel_disturbance = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__vpe_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of VpeStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._vpe_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "VpeStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__VpeStatus * ros_message = (vectornav_msgs__msg__VpeStatus *)raw_ros_message;
  {  // attitude_quality
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->attitude_quality);
    {
      int rc = PyObject_SetAttrString(_pymessage, "attitude_quality", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gyro_saturation
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->gyro_saturation ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gyro_saturation", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // gyro_saturation_recovery
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->gyro_saturation_recovery ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "gyro_saturation_recovery", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mag_disturbance
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->mag_disturbance);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mag_disturbance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mag_saturation
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->mag_saturation ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mag_saturation", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // acc_disturbance
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->acc_disturbance);
    {
      int rc = PyObject_SetAttrString(_pymessage, "acc_disturbance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // acc_saturation
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->acc_saturation ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "acc_saturation", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // known_mag_disturbance
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->known_mag_disturbance ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "known_mag_disturbance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // known_accel_disturbance
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->known_accel_disturbance ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "known_accel_disturbance", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
