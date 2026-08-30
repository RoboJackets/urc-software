#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "urc_hw::urc_hw" for configuration ""
set_property(TARGET urc_hw::urc_hw APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(urc_hw::urc_hw PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liburc_hw.so"
  IMPORTED_SONAME_NOCONFIG "liburc_hw.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS urc_hw::urc_hw )
list(APPEND _IMPORT_CHECK_FILES_FOR_urc_hw::urc_hw "${_IMPORT_PREFIX}/lib/liburc_hw.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
