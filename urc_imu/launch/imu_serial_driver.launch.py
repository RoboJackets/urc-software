# Copyright 2018 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

""" A simple launch file for the imu_serial_driver node. """

import os
import sys

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription, LaunchService
from launch_ros import actions


def generate_launch_description():
    """Generate a launch description for a single serial driver."""
    config_file = os.path.join(
        get_package_share_directory("imu_driver"),
        "config", "imu_serial_driver.yaml")
    driver_node = actions.Node(
        package='imu_driver',
        executable='imu_serial_driver',
        output='screen',
        parameters=[config_file])

    return LaunchDescription([driver_node])


def main(argv):
    ld = generate_launch_description()
    ls = LaunchService()
    ls.include_launch_description(ld)
    return ls.run()


if __name__ == '__main__':
    main(sys.argv)
