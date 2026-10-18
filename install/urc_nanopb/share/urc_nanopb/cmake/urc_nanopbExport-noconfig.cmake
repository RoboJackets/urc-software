#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "urc_nanopb::urc_nanopb" for configuration ""
set_property(TARGET urc_nanopb::urc_nanopb APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(urc_nanopb::urc_nanopb PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/liburc_nanopb.so"
  IMPORTED_SONAME_NOCONFIG "liburc_nanopb.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS urc_nanopb::urc_nanopb )
list(APPEND _IMPORT_CHECK_FILES_FOR_urc_nanopb::urc_nanopb "${_IMPORT_PREFIX}/lib/liburc_nanopb.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
