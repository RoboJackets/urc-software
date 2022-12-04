// GPS map updating
var goal_lat;
var goal_long;
var rover_lat;
var rover_long;
var rover_theta = 0;

const map_tl_lat = 38.4690
const map_tl_long = -110.8542
const map_br_lat = 38.3440
const map_br_long = -110.7292

const tl_x_px = 217;
const tl_y_px = 175;
const br_x_px = 1506;
const br_y_px = 1813;

const PIXELS_PER_METER = 0.117;
const ROVER_ANNOT_FW_RAD = 0.75;
const ROVER_ANNOT_BW_RAD = 0.75*1.414;
const ROVER_STROKE_THICKNESS = PIXELS_PER_METER/10;
const GOAL_STROKE_THICKNESS = PIXELS_PER_METER*1.5;
const GOAL_ANNOT_DIAMETER = 40 * PIXELS_PER_METER + GOAL_STROKE_THICKNESS * 2;

// from index.html
const VIEWER_WIDTH = 1066;
const VIEWER_HEIGHT = 600;

const INITIAL_ZOOM = 7;
const INITIAL_X_OFFSET = 5500;
const INITIAL_Y_OFFSET = 7000;

var rover_annot;
var goal_annot;

const gps_goal_subscriber = new ROSLIB.Topic({
    ros : ros,
    name : '/gps_goal',
    messageType : 'sensor_msgs/msg/NavSatFix'
})

const gps_pos_subscriber = new ROSLIB.Topic({
    ros: ros,
    name : '/gps_pos',
    messageType : 'sensor_msgs/msg/NavSatFix'
})

const rover_theta_subscriber = new ROSLIB.Topic({
    ros: ros,
    name : '/heading',
    messageType : 'std_msgs/msg/Float64'
})

rover_theta_subscriber.subscribe(function(message) {
    rover_theta = message.data;
})

function getPixelCoordsFromGPS(lat, long) {
    var x_px = (br_x_px - tl_x_px) * (long - map_tl_long) / (map_br_long - map_tl_long) + tl_x_px;
    var y_px = (br_y_px - tl_y_px) * (lat - map_tl_lat) / (map_br_lat - map_tl_lat) + tl_y_px;
    return [x_px, y_px];
}

WebViewer({
    path: 'js/WebViewer/lib',
    initialDoc: 'https://raw.githubusercontent.com/RoboJackets/urc-software/feat/gps_interface_pdftron/urc_teleop/gui/UT_75MinuteTopo1_20221012_234609624000_TM_geo.pdf',
    disabledElements: [
        "header",
        "toolsHeader",
    ]
}, document.getElementById('viewer')).then(instance => {
    const { documentViewer, annotationManager, Annotations } = instance.Core;

    gps_goal_subscriber.subscribe(function(message) {
        goal_lat = message.latitude;
        goal_long = message.longitude;

        var coords_px = getPixelCoordsFromGPS(goal_lat, goal_long);
        var goal_x_px = coords_px[0] - GOAL_ANNOT_DIAMETER/2;
        var goal_y_px = coords_px[1] - GOAL_ANNOT_DIAMETER/2;
        console.log("" + goal_x_px + " " + goal_y_px);
        
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

    documentViewer.addEventListener("documentLoaded", () => {
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

        border_annot.addPathPoint(tl_x_px, tl_y_px);
        border_annot.addPathPoint(br_x_px, tl_y_px);
        border_annot.addPathPoint(br_x_px, br_y_px);
        border_annot.addPathPoint(tl_x_px, br_y_px);
        border_annot.addPathPoint(tl_x_px, tl_y_px);

        annotationManager.addAnnotation(border_annot);
        annotationManager.redrawAnnotation(border_annot);

        documentViewer.zoomTo(INITIAL_ZOOM, INITIAL_X_OFFSET, INITIAL_Y_OFFSET);
    });
})
