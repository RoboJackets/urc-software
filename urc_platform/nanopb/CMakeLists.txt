find_package(ament_cmake REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../external/nanopb/extra)
find_package(Nanopb REQUIRED)

nanopb_generate_cpp(
  PROTO_GENERATED_SRCS
  PROTO_HDRS
  proto/urc.proto
)

add_library(${urc_nanopb} SHARED
  ${PROTO_HDRS}
  ${PROTO_GENERATED_SRCS}
)
target_link_libraries(${urc_nanopb}
  nanopb::libnanopb
)
target_include_directories(${urc_nanopb}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)

ament_export_targets(${urc_nanopb} HAS_LIBRARY_TARGET)
ament_export_dependencies(Nanopb)

install(
  DIRECTORY ${CMAKE_BINARY_DIR}
  DESTINATION include
)

install(TARGETS ${urc_nanopb}
        EXPORT ${urc_nanopb}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

ament_package()
