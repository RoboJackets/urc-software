find_package(ament_cmake REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../external/nanopb/extra)
find_package(Nanopb REQUIRED)

nanopb_generate_cpp(
  PROTO_GENERATED_SRCS
  PROTO_HDRS
  proto/urc.proto
)
include_directories(${NANOPB_INCLUDE_DIRS})

ament_export_dependencies(Nanopb)
