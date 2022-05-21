find_package(ament_cmake REQUIRED)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(
  PROTOBUF_SRCS
  PROTOBUF_HDRS
  proto/urc.proto
)

add_library(${PROJECT_NAME} SHARED
  ${PROTOBUF_HDRS}
  ${PROTOBUF_SRCS}
)

target_link_libraries(${PROJECT_NAME}
  protobuf::libprotobuf
)

target_include_directories(${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)

ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(Protobuf)
