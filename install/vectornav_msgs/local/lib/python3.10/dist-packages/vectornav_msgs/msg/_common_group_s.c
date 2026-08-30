// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/CommonGroup.idl
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
#include "vectornav_msgs/msg/detail/common_group__struct.h"
#include "vectornav_msgs/msg/detail/common_group__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__quaternion__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__quaternion__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
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
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__vector3__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__vector3__convert_to_py(void * raw_ros_message);
bool vectornav_msgs__msg__ins_status__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * vectornav_msgs__msg__ins_status__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__common_group__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[45];
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
    assert(strncmp("vectornav_msgs.msg._common_group.CommonGroup", full_classname_dest, 44) == 0);
  }
  vectornav_msgs__msg__CommonGroup * ros_message = _ros_message;
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
  {  // timesyncin
    PyObject * field = PyObject_GetAttrString(_pymsg, "timesyncin");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timesyncin = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // yawpitchroll
    PyObject * field = PyObject_GetAttrString(_pymsg, "yawpitchroll");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->yawpitchroll)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // quaternion
    PyObject * field = PyObject_GetAttrString(_pymsg, "quaternion");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__quaternion__convert_from_py(field, &ros_message->quaternion)) {
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
  {  // position
    PyObject * field = PyObject_GetAttrString(_pymsg, "position");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__point__convert_from_py(field, &ros_message->position)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // velocity
    PyObject * field = PyObject_GetAttrString(_pymsg, "velocity");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->velocity)) {
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
  {  // imu_accel
    PyObject * field = PyObject_GetAttrString(_pymsg, "imu_accel");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->imu_accel)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // imu_rate
    PyObject * field = PyObject_GetAttrString(_pymsg, "imu_rate");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->imu_rate)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // magpres_mag
    PyObject * field = PyObject_GetAttrString(_pymsg, "magpres_mag");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->magpres_mag)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // magpres_temp
    PyObject * field = PyObject_GetAttrString(_pymsg, "magpres_temp");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->magpres_temp = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // magpres_pres
    PyObject * field = PyObject_GetAttrString(_pymsg, "magpres_pres");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->magpres_pres = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // deltatheta_dtime
    PyObject * field = PyObject_GetAttrString(_pymsg, "deltatheta_dtime");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->deltatheta_dtime = (float)PyFloat_AS_DOUBLE(field);
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
  {  // deltatheta_dvel
    PyObject * field = PyObject_GetAttrString(_pymsg, "deltatheta_dvel");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__vector3__convert_from_py(field, &ros_message->deltatheta_dvel)) {
      Py_DECREF(field);
      return false;
    }
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
  {  // syncincnt
    PyObject * field = PyObject_GetAttrString(_pymsg, "syncincnt");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->syncincnt = PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // timegpspps
    PyObject * field = PyObject_GetAttrString(_pymsg, "timegpspps");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timegpspps = (uint16_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__common_group__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of CommonGroup */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._common_group");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "CommonGroup");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__CommonGroup * ros_message = (vectornav_msgs__msg__CommonGroup *)raw_ros_message;
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
  {  // yawpitchroll
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->yawpitchroll);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "yawpitchroll", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // quaternion
    PyObject * field = NULL;
    field = geometry_msgs__msg__quaternion__convert_to_py(&ros_message->quaternion);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "quaternion", field);
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
  {  // position
    PyObject * field = NULL;
    field = geometry_msgs__msg__point__convert_to_py(&ros_message->position);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "position", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // velocity
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->velocity);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "velocity", field);
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
  {  // imu_accel
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->imu_accel);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "imu_accel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // imu_rate
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->imu_rate);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "imu_rate", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // magpres_mag
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->magpres_mag);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "magpres_mag", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // magpres_temp
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->magpres_temp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "magpres_temp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // magpres_pres
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->magpres_pres);
    {
      int rc = PyObject_SetAttrString(_pymessage, "magpres_pres", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // deltatheta_dtime
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->deltatheta_dtime);
    {
      int rc = PyObject_SetAttrString(_pymessage, "deltatheta_dtime", field);
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
  {  // deltatheta_dvel
    PyObject * field = NULL;
    field = geometry_msgs__msg__vector3__convert_to_py(&ros_message->deltatheta_dvel);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "deltatheta_dvel", field);
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
  {  // timegpspps
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->timegpspps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timegpspps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
