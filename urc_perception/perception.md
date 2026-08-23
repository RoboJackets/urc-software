# urc_perception

## Overview

The `urc_perception` package provides the rover’s perception stack for mapping, environment filtering, and traversability analysis.

This system includes the following modules:

1.  **Gaussian Filter**
- Applies smoothing on elevation maps to reduce sensor noise.  
- Outputs filtered elevation maps suitable for mapping and traversability analysis.  

2.  **Traversability Mapping**
- Analyzes elevation maps for terrain hazards and drivability.  
- Outputs traversability costmaps for motion planning.  

---

## Features

- **Gaussian Filtering**: Smooths noisy elevation data using configurable kernels.  
- **Traversability Analysis**: Computes cost layers (flat, rough, steep) for safe navigation.  
- **ROS 2 Integration**: Implements publishers, subscribers, and parameters compatible with Nav2 and the rover’s navigation system.  

---

## Package Structure

```
├── CMakeLists.txt
├── config
│   ├── pcl_grid_map_params.yaml
│   └── traversability_params.yaml
├── filter_plugins.xml
├── include
│   ├── urc_perception/gaussian_filter.hpp
│   └── traversability_mapping.hpp
├── launch
│   ├── d435i.launch.py
│   ├── mapping.launch.py
│   └── perception.launch.py
├── package.xml
└── src
    ├── gaussian_filter.cpp
    └── traversability_mapping.cpp

```

---

## Components

### Gaussian Filter
- **GaussianFilter** (`gaussian_filter.hpp/cpp`)
  - Applies a Gaussian kernel to smooth elevation data.  
  - **Input**: Raw elevation grid layers.  
  - **Output**: Smoothed elevation maps.  
  - Configurable kernel size and variance parameters.  

### Traversability Mapping
- **TraversabilityMapping** (`TraversabilityMapping.hpp/cpp`)  
  - Computes terrain traversability from elevation maps.  
  - **Input**: Filtered elevation map layers.  
  - **Output**: Traversability grid or costmap (safe, rough, hazardous).  

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

Run traversability mapping

```bash
ros2 launch urc_perception mapping.launch.py
```

Launch the depth camera driver (Intel D435i example):

```bash
ros2 launch urc_perception d435i.launch.py
```
