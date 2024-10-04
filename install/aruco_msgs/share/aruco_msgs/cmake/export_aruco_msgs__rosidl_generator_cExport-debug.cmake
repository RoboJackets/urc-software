#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "aruco_msgs::aruco_msgs__rosidl_generator_c" for configuration "Debug"
set_property(TARGET aruco_msgs::aruco_msgs__rosidl_generator_c APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(aruco_msgs::aruco_msgs__rosidl_generator_c PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libaruco_msgs__rosidl_generator_c.so"
  IMPORTED_SONAME_DEBUG "libaruco_msgs__rosidl_generator_c.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS aruco_msgs::aruco_msgs__rosidl_generator_c )
list(APPEND _IMPORT_CHECK_FILES_FOR_aruco_msgs::aruco_msgs__rosidl_generator_c "${_IMPORT_PREFIX}/lib/libaruco_msgs__rosidl_generator_c.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
