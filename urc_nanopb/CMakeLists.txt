cmake_minimum_required(VERSION 3.5)
project(urc_nanopb)

include(../cmake/default_settings.cmake)

find_package(ament_cmake REQUIRED)
find_package(Protobuf REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../external/nanopb/extra)
find_package(Nanopb REQUIRED)

nanopb_generate_cpp(
  PROTO_GENERATED_SRCS
  PROTO_HDRS
  proto/urc.proto
)

add_library(${PROJECT_NAME} SHARED
  ${PROTO_HDRS}
  ${PROTO_GENERATED_SRCS}
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${NANOPB_INCLUDE_DIRS}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>
)

ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)

install(
  DIRECTORY ${CMAKE_BINARY_DIR}
  DESTINATION include
)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the copyright linker
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()