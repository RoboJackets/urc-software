from glob import glob
import os
from setuptools import setup

PACKAGE_NAME = "imu_driver"
SHARE_DIR = os.path.join("share", PACKAGE_NAME)

setup(
    name=PACKAGE_NAME,
    version='2.0.1',
    packages=["libimu_driver", "libimu_driver.nodes"],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + PACKAGE_NAME]),
        ('share/' + PACKAGE_NAME, ['package.xml']),
        (os.path.join(SHARE_DIR, "launch"),
         glob(os.path.join("launch", "*.launch.py"))),
        (os.path.join(SHARE_DIR, "config"),
         glob(os.path.join("config", "*.yaml")))],
    package_dir={'': 'src', },
    py_modules=[],
    zip_safe=True,
    install_requires=['setuptools',
                      'pyserial',
                      'numpy',
                      'pyyaml'],
    author='Eric Perko',
    maintainer='Ed Venator',
    keywords=['ROS2'],
    description='Package to parse IMU strings' +
    'and publish a very simple GPS message.',
    license='BSD',
    entry_points={
        'console_scripts': [
            'imu_serial_driver = libimu_driver.nodes.imu_serial_driver:main',
            'imu_topic_driver = libimu_driver.nodes.imu_topic_driver:main',
            'imu_topic_serial_reader = libimu_driver.nodes.' +
            'imu_topic_serial_reader:main'],
    }
)
