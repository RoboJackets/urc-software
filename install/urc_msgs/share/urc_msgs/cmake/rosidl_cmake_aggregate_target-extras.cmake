# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target urc_msgs::urc_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${urc_msgs_TARGETS}.
if(urc_msgs_TARGETS AND NOT TARGET urc_msgs::urc_msgs)
  add_library(urc_msgs::urc_msgs INTERFACE IMPORTED)
  set_target_properties(urc_msgs::urc_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${urc_msgs_TARGETS}")
endif()
