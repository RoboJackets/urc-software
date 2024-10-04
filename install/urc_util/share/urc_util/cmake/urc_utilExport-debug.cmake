#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "urc_util::urc_util" for configuration "Debug"
set_property(TARGET urc_util::urc_util APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(urc_util::urc_util PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/liburc_util.so"
  IMPORTED_SONAME_DEBUG "liburc_util.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS urc_util::urc_util )
list(APPEND _IMPORT_CHECK_FILES_FOR_urc_util::urc_util "${_IMPORT_PREFIX}/lib/liburc_util.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
