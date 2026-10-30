cmake_minimum_required(VERSION 3.16)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project(urc_slam_rock_landmark_tests CXX)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

find_package(GTSAM REQUIRED)
find_package(Eigen3 REQUIRED)

set(SLAM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

if(TARGET urc_slam)
  set(ROCK_LANDMARK_LIBRARY urc_slam)
else()
  add_library(rock_landmarks STATIC
    ${SLAM_DIR}/src/rock_landmark_params.cpp
    ${SLAM_DIR}/src/rock_extractor.cpp
    ${SLAM_DIR}/src/ground_filter.cpp
    ${SLAM_DIR}/src/point_clustering.cpp
    ${SLAM_DIR}/src/sphere_fit.cpp
    ${SLAM_DIR}/src/jcbb_search.cpp
    ${SLAM_DIR}/src/loop_closure_screening.cpp
    ${SLAM_DIR}/src/landmark_associator.cpp
    ${SLAM_DIR}/src/landmark_manager.cpp
    ${SLAM_DIR}/src/wheel_odometry_factors.cpp
  )
  target_include_directories(rock_landmarks PUBLIC ${SLAM_DIR}/include)
  target_link_libraries(rock_landmarks PUBLIC gtsam Eigen3::Eigen)
  set(ROCK_LANDMARK_LIBRARY rock_landmarks)
endif()

enable_testing()
foreach(test_name
    test_wheel_odometry_factors
    test_rock_extractor
    test_jcbb_search
    test_loop_closure_screening
    test_jcbb_vs_nearest_neighbor
    test_ambiguity
    test_loop_closure_graph)
  add_executable(${test_name} ${test_name}.cpp)
  target_link_libraries(${test_name} ${ROCK_LANDMARK_LIBRARY})
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
