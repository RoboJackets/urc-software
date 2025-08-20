# urc_perception

## Overview

The `urc_perception` package provides the rover’s perception stack for mapping, environment filtering, and traversability analysis.

This system includes the following modules:

1.  **Gaussian Filter**
- Applies smoothing on elevation maps to reduce sensor noise.  
- Outputs filtered elevation maps suitable for mapping and traversability analysis.  

2.  **Elevation Mapping**
- Builds a 2.5D elevation map from sensor data (e.g., depth camera, LiDAR).  
- Produces elevation grid layers for further processing.  

3.  **Traversability Mapping**
- Analyzes elevation maps for terrain hazards and drivability.  
- Outputs traversability costmaps for motion planning.  

---

## Features

- **Gaussian Filtering**: Smooths noisy elevation data using configurable kernels.  
- **Elevation Mapping**: Maintains a rolling elevation grid map aligned to the robot’s frame.  
- **Traversability Analysis**: Computes cost layers (flat, rough, steep) for safe navigation.  
- **ROS 2 Integration**: Implements publishers, subscribers, and parameters compatible with Nav2 and the rover’s navigation system.  

---

## Package Structure

```
├── CMakeLists.txt
├── config
│   ├── mapping_params.yaml
│   ├── pcl_grid_map_params.yaml
│   └── traversability_params.yaml
├── filter_plugins.xml
├── include
│   ├── elevation_mapping.hpp
│   ├── GaussianFilter.hpp
│   └── traversability_mapping.hpp
├── launch
│   ├── d435i.launch.py
│   ├── mapping.launch.py
│   └── perception.launch.py
├── package.xml
└── src
    ├── elevation_mapping.cpp
    ├── GaussianFilter.cpp
    └── traversability_mapping.cpp

```

---

## Components

### Gaussian Filter
- **GaussianFilter** (`GaussianFilter.hpp/cpp`)  
  - Applies a Gaussian kernel to smooth elevation data.  
  - **Input**: Raw elevation grid layers.  
  - **Output**: Smoothed elevation maps.  
  - Configurable kernel size and variance parameters.  

### Elevation Mapping
- **ElevationMapping** (`ElevationMapping.hpp/cpp`)  
  - Maintains a 2.5D elevation map using depth or LiDAR sensors.  
  - **Input**: Depth images, LiDAR point clouds, and odometry transforms.  
  - **Output**: Elevation grid layers with height and variance data.  

### Traversability Mapping
- **TraversabilityMapping** (`TraversabilityMapping.hpp/cpp`)  
  - Computes terrain traversability from elevation maps.  
  - **Input**: Filtered elevation map layers.  
  - **Output**: Traversability grid or costmap (safe, rough, hazardous).  

---

## ElevationMapping | Node

### Subscriptions
- `/camera/depth/points` (`sensor_msgs/msg/PointCloud2`)  
  Depth point cloud input from RGB-D camera.  

- `/odom` (`nav_msgs/msg/Odometry`)  
  Robot pose for map alignment.  

### Publishers
- `/elevation_map` (`grid_map_msgs/msg/GridMap`)  
  Published elevation grid layers.  

### Parameters
- `map_resolution` (`double`) – Resolution of the elevation map (m/cell).  
- `map_length` (`double`) – Size of the local map window.  
- `robot_base_frame` (`string`) – Frame used to align the map to the robot.  

---

## TraversabilityMapping | Node

### Subscriptions
- `/elevation_map` (`grid_map_msgs/msg/GridMap`)  
  Filtered elevation map input.  

### Publishers
- `/traversability_map` (`grid_map_msgs/msg/GridMap`)  
  Traversability costmap output.  

### Parameters
- `slope_threshold` (`double`) – Maximum slope allowed for traversability.  
- `roughness_threshold` (`double`) – Threshold for terrain roughness.  

---

## Launching the Package

Start the perception stack with:

```bash
ros2 launch urc_perception perception.launch.py
```

Run elevation and traversability mapping together

```bash
ros2 launch urc_perception mapping.launch.py
```

Launch the depth camera driver (Intel D435i example):

```bash
ros2 launch urc_perception d435i.launch.py
```



