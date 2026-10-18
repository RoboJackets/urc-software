// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/ImuGroup.idl
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
#include "vectornav_msgs/msg/detail/imu_group__struct.h"
#include "vectornav_msgs/msg/detail/imu_group__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
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
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__imu_group__convert_from_py(PyObject * _pymsg, void * _ros_message)
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
    assert(strncmp("vectornav_msgs.msg._imu_group.ImuGroup", full_classname_dest, 38) == 0);
  }
  vectornav_msgs__msg__ImuGroup * ros_message = _ros_message;
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
  {  // imustatus
    PyObject * field = PyObject_GetAttrString(_pymsg, "imustatus");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->imustatus = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // uncompmag
    PyObject * field = PyObject_GetAttrString(_pymsg, "uncompmag");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->uncompmag)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // uncompaccel
    PyObject * field = PyObject_GetAttrString(_pymsg, "uncompaccel");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->uncompaccel)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // uncompgyro
    PyObject * field = PyObject_GetAttrString(_pymsg, "uncompgyro");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->uncompgyro)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // temp
    PyObject * field = PyObject_GetAttrString(_pymsg, "temp");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->temp = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // pres
    PyObject * field = PyObject_GetAttrString(_pymsg, "pres");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pres = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // deltatheta_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "deltatheta_time");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->deltatheta_time = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // deltatheta_dtheta
    PyObject * field = PyObject_GetAttrString(_pymsg, "deltatheta_dtheta");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->deltatheta_dtheta)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // deltavel
    PyObject * field = PyObject_GetAttrString(_pymsg, "deltavel");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->deltavel)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // mag
    PyObject * field = PyObject_GetAttrString(_pymsg, "mag");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->mag)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // accel
    PyObject * field = PyObject_GetAttrString(_pymsg, "accel");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->accel)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // angularrate
    PyObject * field = PyObject_GetAttrString(_pymsg, "angularrate");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->angularrate)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // sensat
    PyObject * field = PyObject_GetAttrString(_pymsg, "sensat");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->sensat = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__imu_group__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ImuGroup */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._imu_group");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ImuGroup");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__ImuGroup * ros_message = (vectornav_msgs__msg__ImuGroup *)raw_ros_message;
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
  {  // imustatus
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->imustatus);
    {
      int rc = PyObject_SetAttrString(_pymessage, "imustatus", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // uncompmag
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->uncompmag);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "uncompmag", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // uncompaccel
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->uncompaccel);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "uncompaccel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // uncompgyro
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->uncompgyro);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "uncompgyro", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // temp
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->temp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "temp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pres
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pres);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pres", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // deltatheta_time
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->deltatheta_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "deltatheta_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // deltatheta_dtheta
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->deltatheta_dtheta);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "deltatheta_dtheta", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // deltavel
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->deltavel);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "deltavel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mag
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->mag);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "mag", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // accel
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->accel);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "accel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // angularrate
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->angularrate);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "angularrate", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sensat
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->sensat);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sensat", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
