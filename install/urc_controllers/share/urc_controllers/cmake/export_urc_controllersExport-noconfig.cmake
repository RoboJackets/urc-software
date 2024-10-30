#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "urc_controllers::urc_controllers" for configuration ""
set_property(TARGET urc_controllers::urc_controllers APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(urc_controllers::urc_controllers PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liburc_controllers.so"
  IMPORTED_SONAME_NOCONFIG "liburc_controllers.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS urc_controllers::urc_controllers )
list(APPEND _IMPORT_CHECK_FILES_FOR_urc_controllers::urc_controllers "${_IMPORT_PREFIX}/lib/liburc_controllers.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
