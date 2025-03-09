from setuptools import find_packages, setup
from generate_parameter_library_py.setup_helper import generate_parameter_module
import sys
import os
from glob import glob

package_name = "urc_arm_py"

if len(sys.argv) >= 2 and sys.argv[1] != "clean":
    from generate_parameter_library_py.setup_helper import generate_parameter_module

    # set module_name and yaml file
    module_name = "arm_qp_control_parameters"
    yaml_file = "urc_arm_py/arm_qp_control_parameters.yaml"
    generate_parameter_module(module_name, yaml_file)

setup(
    name=package_name,
    version="0.0.0",
    packages=find_packages(exclude=["test"]),
    data_files=[
        ("share/ament_index/resource_index/packages",
         ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join('share', package_name, 'launch'), glob('launch/*')),
        (os.path.join('share', package_name, 'config'), glob('config/*')),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="Zimeng Chai",
    maintainer_email="zimeng.chai@gatech.edu",
    description="TODO: Package description",
    license="TODO: License declaration",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "arm_qp_control = urc_arm_py.arm_qp_control:main",
            "twist_sender = urc_arm_py.twist_sender:main",
        ],
    },
)
