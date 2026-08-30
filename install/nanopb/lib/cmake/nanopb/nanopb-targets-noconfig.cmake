#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "nanopb::protobuf-nanopb-static" for configuration ""
set_property(TARGET nanopb::protobuf-nanopb-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(nanopb::protobuf-nanopb-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libprotobuf-nanopb.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS nanopb::protobuf-nanopb-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_nanopb::protobuf-nanopb-static "${_IMPORT_PREFIX}/lib/libprotobuf-nanopb.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
