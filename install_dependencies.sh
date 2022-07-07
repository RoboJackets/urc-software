#!/bin/bash

rosdep update
rosdep install -iy --from-paths ../../src
sudo apt-get install python3-protobuf