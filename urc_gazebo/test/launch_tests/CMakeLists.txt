find_package(launch_testing_ament_cmake REQUIRED)

add_launch_test(scan_to_pointcloud_test.py
    APPEND_ENV PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/test
    TIMEOUT 10
)