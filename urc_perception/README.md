# URC Perception

This package is a collection of nodes focused on detecting and mapping ARURO tags and costmap generation based on obstacle detection

## Aruco Detector

Focuses on detecting aruco tags if they are found, and then determining basic data about the found tag.
- Subscribes to an image publisher
- Uses callback method when any image is received:
    - Uses image_msg and info_msg
    - Uses cv::aruco package methods: detectMarkers and estimatePoseSingleMarkers to determine distance, angles, and marker id.
    - Publishes this info continually to the aruco topic. 

## Aruco Location
- Focuses on using info from Aruco Detector (to which this node publishes) to determine GPS coordinates of the drone.

## Costmpa Generator
- Will store and publish a `nav_msgs/msg/OccupancyGrid` message. This is a 100x100 grid.

- Smaller visual representation:
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 y 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 x 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0  

- Where 'x' indicates the position of the base station and 'y' indicates the postion of the rover. The costmap is always stored, visualizsed, etc. with everything facing north.
