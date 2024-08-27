# External  

This folder consists of Git Submodules which are pulled in through the setup instructions. If you are missing any of the packages, run `git submodule --update` to pull then in again.  
Here is a list of the submodules:  
* BehaviorTree.ROS2: provides a set of C++ interfaces for BT.CPP to connect to ROS2.  
* Articubot One: an example project by [Articulated Robotics](https://www.youtube.com/@ArticulatedRobotics) which contains a URDF robot and navigation implementation.
* Aruco ROS: a package designed for reading ARUCO tags and providing the transform to them relative to the robot.
* NanoPB: a package which allow us to implement [Protocol Buffers](https://protobuf.dev/), a protocol for message transmission which allows us to communicate with our firmware.  
