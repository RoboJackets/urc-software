// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vectornav_msgs:msg/DOP.idl
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
#include "vectornav_msgs/msg/detail/dop__struct.h"
#include "vectornav_msgs/msg/detail/dop__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool vectornav_msgs__msg__dop__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[28];
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
    assert(strncmp("vectornav_msgs.msg._dop.DOP", full_classname_dest, 27) == 0);
  }
  vectornav_msgs__msg__DOP * ros_message = _ros_message;
  {  // g
    PyObject * field = PyObject_GetAttrString(_pymsg, "g");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->g = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // p
    PyObject * field = PyObject_GetAttrString(_pymsg, "p");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->p = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // t
    PyObject * field = PyObject_GetAttrString(_pymsg, "t");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->t = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // v
    PyObject * field = PyObject_GetAttrString(_pymsg, "v");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->v = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // h
    PyObject * field = PyObject_GetAttrString(_pymsg, "h");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->h = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // n
    PyObject * field = PyObject_GetAttrString(_pymsg, "n");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->n = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // e
    PyObject * field = PyObject_GetAttrString(_pymsg, "e");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->e = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vectornav_msgs__msg__dop__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of DOP */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vectornav_msgs.msg._dop");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "DOP");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vectornav_msgs__msg__DOP * ros_message = (vectornav_msgs__msg__DOP *)raw_ros_message;
  {  // g
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->g);
    {
      int rc = PyObject_SetAttrString(_pymessage, "g", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // p
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->p);
    {
      int rc = PyObject_SetAttrString(_pymessage, "p", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // t
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->t);
    {
      int rc = PyObject_SetAttrString(_pymessage, "t", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // v
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->v);
    {
      int rc = PyObject_SetAttrString(_pymessage, "v", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // h
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->h);
    {
      int rc = PyObject_SetAttrString(_pymessage, "h", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // n
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->n);
    {
      int rc = PyObject_SetAttrString(_pymessage, "n", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // e
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->e);
    {
      int rc = PyObject_SetAttrString(_pymessage, "e", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
