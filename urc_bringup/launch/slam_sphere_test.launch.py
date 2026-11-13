"""SLAM-vs-ground-truth check: flat world with one sphere, scripted route, RViz.

Starts sim.launch.py on sphere_test.sdf with the rover 8 m behind the sphere,
SLAM with its RViz layout (SLAM pose red, ground truth green), and the sphere
route from urc_slam/testing/route_trial.py. The route waits until SLAM and
ground truth both publish, then prints SLAM error after each leg.

Run from source so the world and route script need no reinstall:
  ros2 launch ~/urc_container/rover_ws/src/urc_bringup/launch/slam_sphere_test.launch.py
"""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import ExecuteProcess, GroupAction, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

# Resolve the source tree through any install symlink
SRC = os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
WORLD = os.path.join(SRC, "urc_hw_description", "world", "sphere_test.sdf")
ROUTE = os.path.join(SRC, "urc_slam", "testing", "route_trial.py")
# route_trial.py SPHERE_AHEAD_M: the sphere sits at the world origin
SPAWN_X = "-8.0"


def generate_launch_description():
    bringup_share = get_package_share_directory("urc_bringup")
    slam_share = get_package_share_directory("urc_slam")

    simulation = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(bringup_share, "launch", "sim.launch.py")),
        launch_arguments={"world": WORLD, "spawn_x": SPAWN_X}.items(),
    )
    # Scoped so SLAM's launch arguments do not leak into the rest of this file
    slam = GroupAction([
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(slam_share, "launch", "slam.launch.py")),
            launch_arguments={"rviz": "true"}.items(),
        )
    ])
    route = ExecuteProcess(cmd=["python3", ROUTE, "sphere"], output="screen")

    return LaunchDescription([simulation, slam, route])
