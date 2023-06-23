// GPS Map Updating
var goal_lat;
var goal_long;
var rover_lat;
var rover_long;
var rover_theta = 0;

// Map and Viewer Constants
const MAP_TL_LAT = 38.4690
const MAP_TL_LONG = -110.8542
const MAP_BR_LAT = 38.3440
const MAP_BR_LONG = -110.7292

const TL_X_PX = 217;
const TL_Y_PX = 175;
const BR_X_PX = 1506;
const BR_Y_PX = 1813;

const PIXELS_PER_METER = 0.117;
const ROVER_ANNOT_FW_RAD = 0.75;
const ROVER_ANNOT_BW_RAD = 0.75*1.414;
const ROVER_STROKE_THICKNESS = PIXELS_PER_METER/10;
const GOAL_STROKE_THICKNESS = PIXELS_PER_METER*1.5;
const GOAL_ANNOT_DIAMETER = 40 * PIXELS_PER_METER + GOAL_STROKE_THICKNESS * 2;

const viewer = document.getElementById('viewer');
const VIEWER_WIDTH = viewer.clientWidth;
const VIEWER_HEIGHT = viewer.clientHeight;

const INITIAL_ZOOM = 7;
const INITIAL_X_OFFSET = 5500;
const INITIAL_Y_OFFSET = 7000;

var rover_annot;
var goal_annot;

const landing_locations = [];

// Publishers and Subscribers
const gps_goal_subscriber = new ROSLIB.Topic({
    ros: ros,
    name: '/gps_goal',
    messageType: 'sensor_msgs/msg/NavSatFix'
});

const gps_pos_subscriber = new ROSLIB.Topic({
    ros: ros,
    name: '/gps_pos',
    messageType: 'sensor_msgs/msg/NavSatFix'
});

const rover_theta_subscriber = new ROSLIB.Topic({
    ros: ros,
    name: '/heading',
    messageType: 'std_msgs/msg/Float64'
});

const landing_location_publisher = new ROSLIB.Topic({
    ros: ros,
    name: '/landing',
    messageType: 'urc_msgs/msg/LandingLocations'
});

rover_theta_subscriber.subscribe(function(message) {
    rover_theta = message.data;
});

// GPS and Pixel Coordinates Conversion
function getPixelCoordsFromGPS(lat, long) {
    var x_px = (BR_X_PX - TL_X_PX) * (lat - MAP_TL_LAT) / (MAP_BR_LAT - MAP_TL_LAT) + TL_X_PX;
    var y_px = (BR_Y_PX - TL_Y_PX) * (long - MAP_TL_LONG) / (MAP_BR_LONG - MAP_TL_LONG) + TL_Y_PX;
    return [x_px, y_px];
}

function getGPSFromPixelCoords(x_px, y_px) {
    var lat = (MAP_BR_LAT - MAP_TL_LAT) * (x_px - TL_X_PX) / (BR_X_PX - TL_X_PX) + MAP_TL_LAT;
    var long = (MAP_BR_LONG - MAP_TL_LONG) * (y_px - TL_Y_PX) / (BR_Y_PX - TL_Y_PX) + MAP_TL_LONG;
    return [lat, long];
}

const input = document.getElementById('map_upload');

// PDF Viewer
WebViewer({
    path: 'js/WebViewer/lib',
    disabledElements: [
        'header',
        'toolsHeader',
    ]
}, document.getElementById('viewer')).then(instance => {
    // Input File
    input.addEventListener('change', () => {
        if (input.files.length > 0) {
            instance.UI.loadDocument(input.files[0], { filename: input.files[0].name });
        }
    });    

    const { documentViewer, annotationManager, Annotations } = instance.Core;

    // GPS Subscribers
    gps_goal_subscriber.subscribe(function(message) {
        goal_lat = message.latitude;
        goal_long = message.longitude;

        var coords_px = getPixelCoordsFromGPS(goal_lat, goal_long);
        var goal_x_px = coords_px[0] - GOAL_ANNOT_DIAMETER/2;
        var goal_y_px = coords_px[1] - GOAL_ANNOT_DIAMETER/2;
        console.log(goal_x_px + ' ' + goal_y_px);
        
        goal_annot.setX(goal_x_px);
        goal_annot.setY(goal_y_px);
        annotationManager.redrawAnnotation(goal_annot);
    });
    
    gps_pos_subscriber.subscribe(function(message) {
        pos_lat = message.latitude;
        pos_long = message.longitude;

        var coords_px = getPixelCoordsFromGPS(pos_lat, pos_long);
        var pos_x_px = coords_px[0];
        var pos_y_px = coords_px[1];

        var angle = Math.PI * 3/4;
        rover_annot.StrokeThickNess = ROVER_STROKE_THICKNESS;
        rover_annot.setPathPoint(0, pos_x_px - ROVER_ANNOT_FW_RAD * Math.sin(rover_theta), pos_y_px - ROVER_ANNOT_FW_RAD * Math.cos(rover_theta));
        rover_annot.setPathPoint(1, pos_x_px - ROVER_ANNOT_BW_RAD * Math.sin(rover_theta + angle), pos_y_px - ROVER_ANNOT_BW_RAD * Math.cos(rover_theta + angle));
        rover_annot.setPathPoint(2, pos_x_px, pos_y_px);
        rover_annot.setPathPoint(3, pos_x_px - ROVER_ANNOT_BW_RAD * Math.sin(rover_theta - angle), pos_y_px - ROVER_ANNOT_BW_RAD * Math.cos(rover_theta - angle));
        rover_annot.setPathPoint(4, pos_x_px - ROVER_ANNOT_FW_RAD * Math.sin(rover_theta), pos_y_px - ROVER_ANNOT_FW_RAD * Math.cos(rover_theta));
        annotationManager.redrawAnnotation(rover_annot);
    });

    // Remove Popup Menus
    if (instance.contextMenuPopup.getItems().length > 3) {
        instance.contextMenuPopup.update([instance.contextMenuPopup.getItems()[3]]);
    }
    instance.textPopup.update([]);
    instance.annotationPopup.update([]);

    // Annotation Add/Delete Listener
    annotationManager.addEventListener('annotationChanged', (annotations, action) => {
        instance.Tools.FreeHandCreateTool.prototype.createDelay = 0;

        // Annotation Add
        if (action == 'add') {
            annotations.forEach((annotation) => {
                if (annotation.Color.toString() == 'rgba(228,66,52,1)') {
                    const annot = new Annotations.EllipseAnnotation({
                        PageNumber: 1,
                        StrokeColor: new Annotations.Color(0, 255, 0),
                        FillColor: new Annotations.Color(0, 255, 0),
                        X: annotation.X,
                        Y: annotation.Y,
                        Height: 2,
                        Width: 2
                    });
                    annotationManager.addAnnotation(annot);
                    annotationManager.redrawAnnotation(annot);
                    
                    landing_locations.push([annot.X, annot.Y]);
                    console.log(landing_locations);

                    annotationManager.deleteAnnotation(annotation);
                }
            });
        }

        // Annotation Delete
        if (action == 'delete') {
            annotations.forEach((annotation) => {
                if (annotation.Color.toString() == 'rgba(0,255,0,1)') {
                    for (var i = 0; i < landing_locations.length; ++i) {
                        if (landing_locations[i][0] == annotation.X && landing_locations[i][1] == annotation.Y) {
                            landing_locations.splice(i, 1);
                        }
                    }
                    console.log(landing_locations);
                }
            });
        }
    });

    documentViewer.addEventListener('documentLoaded', () => {
        // Remove Unnecessary PDF Layers
        const doc = documentViewer.getDocument();
        doc.getLayersArray().then(layers => {
            layers[0].visible = false;
            layers[1].visible = false;
            for (var i = 0; i < 9; i++) {
                if (i != 7) {
                    layers[2].children[i].visible = false;
                }
            }
            doc.setLayersArray(layers);
            documentViewer.refreshAll();
            documentViewer.updateView();
        })

        // Draw Rover, Goal, Border Annotations
        rover_annot = new Annotations.PolygonAnnotation({
            PageNumber: 1,
            StrokeColor: new Annotations.Color(255, 0, 0, 0),
            FillColor: new Annotations.Color(255, 0, 0, 0.5),
            Locked: true,
        });

        goal_annot = new Annotations.EllipseAnnotation({
            PageNumber: 1,
            StrokeColor: new Annotations.Color(0, 255, 0, 0.5),
            Locked: true,
            X: -GOAL_ANNOT_DIAMETER,
            Y: -GOAL_ANNOT_DIAMETER,
            Width: GOAL_ANNOT_DIAMETER,
            Height: GOAL_ANNOT_DIAMETER,
            StrokeThickness: GOAL_STROKE_THICKNESS,
        });

        var border_annot = new Annotations.PolygonAnnotation({
            PageNumber: 1,
            StrokeColor: new Annotations.Color(60, 60, 30, 1),
            FillColor: new Annotations.Color(0, 0, 0, 0),
            Locked: true,
        })

        rover_annot.addPathPoint(0, 0);
        rover_annot.addPathPoint(1, 0);
        rover_annot.addPathPoint(1, 1);
        rover_annot.addPathPoint(0, 1);
        rover_annot.addPathPoint(0, 0);
        annotationManager.addAnnotation(rover_annot);
        annotationManager.addAnnotation(goal_annot);

        border_annot.addPathPoint(TL_X_PX, TL_Y_PX);
        border_annot.addPathPoint(BR_X_PX, TL_Y_PX);
        border_annot.addPathPoint(BR_X_PX, BR_Y_PX);
        border_annot.addPathPoint(TL_X_PX, BR_Y_PX);
        border_annot.addPathPoint(TL_X_PX, TL_Y_PX);

        annotationManager.addAnnotation(border_annot);
        annotationManager.redrawAnnotation(border_annot);

        documentViewer.zoomTo(INITIAL_ZOOM, INITIAL_X_OFFSET, INITIAL_Y_OFFSET);
    });
});

// Publish Landing Locations
setInterval(function() {
    var latitudes = new Float64Array(100);
    var longitudes = new Float64Array(100);

    var i = 0;
    landing_locations.forEach((location) => {
        var gps_coords = getGPSFromPixelCoords(location[0], location[1]);
        latitudes[i] = gps_coords[0];
        longitudes[i] = gps_coords[1];
        ++i;
    });

    let landing_message = new ROSLIB.Message({
        size: i,
        latitudes: latitudes,
        longitudes: longitudes
    });

    landing_location_publisher.publish(landing_message);
}, 15);
