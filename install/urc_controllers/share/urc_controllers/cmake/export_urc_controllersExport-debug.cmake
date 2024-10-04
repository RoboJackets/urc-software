#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "urc_controllers::urc_controllers" for configuration "Debug"
set_property(TARGET urc_controllers::urc_controllers APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(urc_controllers::urc_controllers PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/liburc_controllers.so"
  IMPORTED_SONAME_DEBUG "liburc_controllers.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS urc_controllers::urc_controllers )
list(APPEND _IMPORT_CHECK_FILES_FOR_urc_controllers::urc_controllers "${_IMPORT_PREFIX}/lib/liburc_controllers.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
