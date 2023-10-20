# URC Perception

This package is a collection of nodes focused on detecting and mapping ARUCO tags.

## Aruco Detector

Focuses on detecting aruco tags if they are found, and then determining basic data about the found tag.
- Subscribes to an image publisher
- Uses callback method when any image is received:
    - Uses image_msg and info_msg
    - Uses cv::aruco package methods: detectMarkers and estimatePoseSingleMarkers to determine distance, angles, and marker id.
    - Publishes this info continually to the aruco topic. 


## Aruco Location

Focuses on using info from Aruco Detector (to which this node publishes) to determine GPS coordinates of the drone.
