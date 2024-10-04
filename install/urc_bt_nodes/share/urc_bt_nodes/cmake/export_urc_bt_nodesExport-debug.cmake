#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "urc_bt_nodes::urc_bt_nodes" for configuration "Debug"
set_property(TARGET urc_bt_nodes::urc_bt_nodes APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(urc_bt_nodes::urc_bt_nodes PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/liburc_bt_nodes.so"
  IMPORTED_SONAME_DEBUG "liburc_bt_nodes.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS urc_bt_nodes::urc_bt_nodes )
list(APPEND _IMPORT_CHECK_FILES_FOR_urc_bt_nodes::urc_bt_nodes "${_IMPORT_PREFIX}/lib/liburc_bt_nodes.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
