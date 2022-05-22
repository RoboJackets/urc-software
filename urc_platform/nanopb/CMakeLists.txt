find_package(ament_cmake REQUIRED)
find_package(Protobuf REQUIRED)

set(NANOPB_SRC_ROOT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/external/nanopb)
set(CMAKE_MODULE_PATH ${NANOPB_SRC_ROOT_FOLDER}/extra)
find_package(Nanopb REQUIRED)

nanopb_generate_cpp(
  PROTO_GENERATED_SRCS
  PROTO_HDRS
  proto/urc.proto
)
include_directories(${NANOPB_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED
  ${PROTO_HDRS}
  ${PROTO_GENERATED_SRCS}
)

target_link_libraries(${PROJECT_NAME})

ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(Nanopb)
