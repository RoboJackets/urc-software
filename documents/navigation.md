# URC Navigation

## Overview

The navigation stack provides autonomous rover navigation through four focused ROS 2 packages:

1. **Path Planning (`urc_path_planning`)**  
   - Implements a global planner using the A* algorithm.  
   - Provides plans as a sequence of poses (`nav_msgs/Path`).  
   - Integrated with Nav2 as an external planner service.  

2. **Trajectory Following (`urc_trajectory_following`)**  
   - Consumes planned paths and generates smooth velocity commands.  
   - Ensures accurate and safe tracking of the planned trajectory.  
   - Bridges the gap between high-level plans and rover motion control.  

3. **State Machine (`urc_state_machine`)**
   - Coordinates navigation goals and action results.

4. **Navigation Common (`urc_nav_common`)**
   - Provides shared grid-map access utilities.

Together these packages form a lightweight navigation stack for the University Rover Challenge.

---

## Features

- **Custom Path Planning (A\*)**: Grid-based A* planner that generates collision-free paths on occupancy grid costmaps.  
- **Trajectory Following**: Executes smooth and precise motion along planned paths.  
- **ROS 2 Integration**: Implements standard ROS 2 publishers, subscribers, and services.  
- **Simulation & Hardware Support**: Works in both Gazebo simulation and real rover hardware environments.  


## Package Structure

```
├── urc_path_planning
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── astar.hpp
│   │   └── planner_server.hpp
│   ├── launch
│   │   └── planning.launch.py
│   ├── package.xml
│   └── src
│       ├── astar.cpp
│       └── planner_server.cpp
├── urc_trajectory_following
│   ├── CMakeLists.txt
│   ├── config
│   │   └── pure_pursuit_config.yaml
│   ├── include
│   │   └── urc_trajectory_following
│   ├── launch
│   │   └── trajectory_following.launch.py
│   ├── package.xml
│   ├── README.md
│   └── src
├── urc_state_machine
│   ├── include
│   └── src
└── urc_nav_common
    ├── include
    └── src

```

### Components

#### Path Planning (`urc_path_planning`)

- **AStar (`astar.hpp/cpp`)**
  - Implements the grid-based A* search algorithm
  - Operates directly on `OccupancyGrid` costmaps
  - Produces a vector of poses (waypoints) forming the global path  

- **PlannerServer (`planner_server.hpp/cpp`)**
  - Wraps the A* planner in a ROS 2 node
  - Provides a service interface for plan generation
  - Subscribes to a costmap and publishes computed paths  

#### Trajectory Following (`urc_trajectory_following`)

- **FollowerActionServer (`follower_action_server.hpp/cpp`)**
  - Implements a ROS 2 Action Server for trajectory following  
  - Consumes planned paths (`nav_msgs/Path`) and generates velocity commands (`geometry_msgs/Twist`)  
  - Interfaces with rover control to execute trajectories reliably  

- **Pure Pursuit (`pure_pursuit/pure_pursuit.hpp/cpp`)**
  - Implements the Pure Pursuit path tracking algorithm  
  - Selects lookahead points along the path for smooth velocity generation  
  - Configurable via `pure_pursuit_config.yaml`  

- **Geometry Util (`geometry_util.hpp/cpp`)**
  - Provides reusable geometric helper functions
  - Supports Pure Pursuit calculations and general path-following logic

---
## Planner_Server | Node

### Subscriptions
- `/costmap` (`nav_msgs/OccupancyGrid`)  
  Costmap input used for planning.

### Publishers
- `/path` (`nav_msgs/Path`)  
  Planned path published for visualization and debugging.

### Services
- `/plan` (`urc_msgs/srv/GeneratePlan`)  
  - **Request**: Start pose and goal pose (`geometry_msgs/PoseStamped`)  
  - **Response**: Path (`nav_msgs/Path`) and success/error code

---

## Trajectory_Follower | Node

### Subscriptions
- `/trajectory` (`nav_msgs/Path`)  
  Planned trajectory to follow.

- `/odom` (`nav_msgs/Odometry`)  
  Current robot pose and velocity feedback.

### Publishers
- `/cmd_vel` (`geometry_msgs/Twist`)  
  Velocity commands for trajectory execution.

### Actions
- `follow_trajectory` (`urc_msgs/action/FollowTrajectory`)  
  - **Goal**: Trajectory to follow (`nav_msgs/Path`)  
  - **Feedback**: Progress along trajectory, current target pose  
  - **Result**: Success/failure and error code

### Parameters
- `lookahead_distance` (double) – distance ahead on trajectory for control.  
- `max_linear_speed` (double)  
- `max_angular_speed` (double)  

---

## Launch

Start the planner server with:

```bash
ros2 launch urc_path_planning planning.launch.py
```


Start the trajectory_follower with:

```bash
ros2 launch urc_trajectory_following trajectory_following.launch.py
```
