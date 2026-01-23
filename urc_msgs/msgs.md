# urc_msgs

## Overview

The `urc_msgs` package provides ROS 2 message (`msg`) and service (`srv`) definitions for rover perception, navigation, battery monitoring, and subsystem control.

This system includes the following modules:

### Aruco & Navigation Messages
- Defines messages for ArUco marker detection, localization, and navigation status.  
- **Key features:** Marker IDs, positions, angles, and navigation messages for rover perception and guidance.

### Battery & Status Messages
- Defines messages for battery monitoring and status lights.  
- **Key features:** Reports cell voltages, charge, current, temperature, and status light states.

### Motion & Waypoint Messages
- Defines messages for wheel velocities, waypoints, and grid locations.  
- **Key features:** Supports motion commands and mapping for autonomous navigation.

### Services
- Provides service definitions for path planning and behavior tree updates.  
- **Key features:** Request/response patterns for planning and behavior management.

---

## Features

- **Aruco Marker Detection:** Detect and locate markers in rover environment with camera identification.  
- **Battery Monitoring:** Access detailed battery status including voltages, charge, and temperature.  
- **Navigation Support:** Provides waypoints, grid, and landing location messages for navigation.  
- **Status Control:** Supports RGB LED control for rover status feedback.  
- **Path Planning Services:** Generate navigation plans between start and goal poses.  
- **Behavior Tree Updates:** Dynamically update behavior trees for rover autonomy.

---

## Package Structure

```
├── action
├── CMakeLists.txt
├── msg
│   ├── ArucoDetection.msg
│   ├── ArucoLocation.msg
│   ├── BatteryInfo.msg
│   ├── GridLocation.msg
│   ├── LandingLocations.msg
│   ├── NavigationStatus.msg
│   ├── StatusLightCommand.msg
│   ├── VelocityPair.msg
│   └── Waypoint.msg
├── package.xml
├── README.md
└── srv
    ├── GeneratePlan.srv
    └── UpdateBehaviorTree.srv
```

## Components

### Aruco & Navigation Messages

- **ArucoDetection (`.msg`)**  
  - Provides detected marker ID, x/y angles, distance, and camera source.  
  - **Inputs:** Camera detection  
  - **Outputs:** Serialized ROS 2 message  

- **ArucoLocation (`.msg`)**  
  - Provides marker longitude, latitude, ID, and camera source.  
  - **Inputs:** Marker detection  
  - **Outputs:** Localization data  

- **NavigationStatus (`.msg`)**  
  - Publishes status messages related to navigation.  
  - **Outputs:** Human-readable string message  

- **LandingLocation (`.msg`)**  
  - Provides multiple possible landing site coordinates.  
  - **Outputs:** Up to 100 latitude/longitude pairs  

- **GridLocation (`.msg`)**  
  - Provides X/Y location on a grid map.  
  - **Outputs:** Grid coordinates  

---

### Battery & Status Messages

- **BatteryInfo (`.msg`)**  
  - Reports voltage, charge, current, temperature, and all cell voltages.  
  - **Outputs:** Battery monitoring data  

- **StatusLightCommand (`.msg`)**  
  - Controls RGB LED lights on the rover with OFF, ON, or BLINK states.  
  - **Inputs:** Desired color and state  
  - **Outputs:** Light control command  

---

### Motion & Waypoint Messages

- **VelocityPair (`.msg`)**  
  - Provides left/right wheel velocities and duration for motion commands.  
  - **Inputs:** Desired wheel velocities  
  - **Outputs:** Serialized ROS 2 message  

- **Waypoint (`.msg`)**  
  - Defines a GPS waypoint with latitude and longitude.  
  - **Outputs:** Navigation waypoint  

---

### Services

- **GeneratePlan (`.srv`)**  
  - **Request:** Start and goal poses (`geometry_msgs/PoseStamped`)  
  - **Response:** Navigation path (`nav_msgs/Path`) and error code (`SUCCESS`/`FAILURE`)  

- **UpdateBehaviorTree (`.srv`)**  
  - **Request:** Behavior tree content, directory, and `use_dir` flag  
  - **Response:** Success boolean  

---

## Notes

This package provides **message and service definitions only**; it does not include runtime nodes.  

Generated headers (`.hpp`) and source files (`.cpp`) from these messages/services are used by ROS 2 nodes for communication.

