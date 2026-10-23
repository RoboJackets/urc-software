# Standalone build for the rock-landmark tests. Deliberately NOT referenced
# from urc_slam/CMakeLists.txt (existing files are untouched on this branch),
# and needs only GTSAM + Eigen: no ROS, PCL, or hardware.
#
#   cmake -S urc_slam/test -B /tmp/rock_tests && cmake --build /tmp/rock_tests
#   ctest --test-dir /tmp/rock_tests --output-on-failure
cmake_minimum_required(VERSION 3.16)
project(urc_slam_rock_landmark_tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

find_package(GTSAM REQUIRED)
find_package(Eigen3 REQUIRED)

set(SLAM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(rock_landmarks STATIC
  ${SLAM_DIR}/src/rock_landmark_params.cpp
  ${SLAM_DIR}/src/rock_extractor.cpp
  ${SLAM_DIR}/src/ground_filter.cpp
  ${SLAM_DIR}/src/point_clustering.cpp
  ${SLAM_DIR}/src/sphere_fit.cpp
  ${SLAM_DIR}/src/jcbb_search.cpp
  ${SLAM_DIR}/src/landmark_associator.cpp
  ${SLAM_DIR}/src/landmark_manager.cpp
)
target_include_directories(rock_landmarks PUBLIC ${SLAM_DIR}/include)
target_link_libraries(rock_landmarks PUBLIC gtsam Eigen3::Eigen)

enable_testing()
foreach(test_name
    test_rock_extractor
    test_jcbb_search
    test_jcbb_vs_nearest_neighbor
    test_ambiguity
    test_loop_closure_graph)
  add_executable(${test_name} ${test_name}.cpp)
  target_link_libraries(${test_name} rock_landmarks)
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
