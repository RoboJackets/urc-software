from setuptools import setup
import os
from glob import glob

package_name = "urc_test"

setup(
    name=package_name,
    version="0.0.0",
    packages=[package_name],
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join("share", package_name, "launch"), glob("launch/*.py")),
        (os.path.join("share", package_name, "config"), glob("config/*.yaml")),
    ],
    package_dir={
        "": "src",
    },
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="nvidia",
    maintainer_email="rbansal66@gatech.edu",
    description="TODO: Package description",
    license="TODO: License declaration",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "urc_test = urc_test.urc_test:main",
            "costmap_generator = urc_test.costmap_generator:main",
            "imu_rpy = urc_test.pub_imu_rpy:main",
            "odom_to_map_pose = urc_test.odom_to_map_pose:main",
        ],
    },
)
