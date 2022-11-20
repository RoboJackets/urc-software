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
const pdf_x_px = 1727;
const pdf_y_px = 2088;

const lat_per_px = (map_br_lat - map_tl_lat) / (br_y_px - tl_y_px);
const long_per_px = (map_br_long - map_tl_long) / (br_x_px - tl_x_px);

const pdf_tl_lat = map_tl_lat - tl_y_px * lat_per_px;
const pdf_tl_long = map_tl_long - tl_x_px * long_per_px;
const pdf_br_lat = map_br_lat + (pdf_y_px - br_y_px) * lat_per_px;
const pdf_br_long = map_br_long + (pdf_x_px - br_x_px) * long_per_px;

const ROVER_ANNOT_LONG_LENGTH = 5;
const ROVER_ANNOT_SHORT_LENGTH = 3;
const GOAL_ANNOT_DIAMETER = 10;

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
    var x_px = pdf_x_px * (long - pdf_tl_long) / (pdf_br_long - pdf_tl_long);
    var y_px = pdf_y_px * (lat - pdf_tl_lat) / (pdf_br_lat - pdf_tl_lat);
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
        //console.log("" + goal_x_px + " " + goal_y_px);
        
        goal_annot.setX(goal_x_px);
        goal_annot.setY(goal_y_px);
        annotationManager.redrawAnnotation(goal_annot);
    });
    
    gps_pos_subscriber.subscribe(function(message) {
        pos_lat = message.latitude;
        pos_long = message.longitude;

        var coords_px = getPixelCoordsFromGPS(pos_lat, pos_long);
        var pos_x_px = coords_px[0];
        var pos_x_px = coords_px[1];

        rover_annot.setPathPoint(0, pos_x_px + ROVER_ANNOT_LONG_LENGTH * Math.cos(rover_theta), pos_y_px + ROVER_ANNOT_LONG_LENGTH * Math.sin(rover_theta));
        rover_annot.setPathPoint(1, pos_x_px + ROVER_ANNOT_SHORT_LENGTH * Math.cos(rover_theta + Math.PI * 2/3), pos_y_px + ROVER_ANNOT_SHORT_LENGTH * Math.sin(rover_theta + Math.PI * 2/3));
        rover_annot.setPathPoint(2, pos_x_px + ROVER_ANNOT_SHORT_LENGTH * Math.cos(rover_theta - Math.PI * 2/3), pos_y_px + ROVER_ANNOT_SHORT_LENGTH * Math.sin(rover_theta - Math.PI * 2/3));
        rover_annot.setPathPoint(3, pos_x_px + ROVER_ANNOT_LONG_LENGTH * Math.cos(rover_theta), pos_y_px + ROVER_ANNOT_LONG_LENGTH * Math.sin(rover_theta));
        annotationManager.redrawAnnotation(rover_annot);
    });

    documentViewer.addEventListener("documentLoaded", () => {
        const doc = documentViewer.getDocument();
        doc.getLayersArray().then(layers => {
            layers.forEach((layer, index) => {
                console.log(layer.children[0].name);
                //layers[index].visible = false;
            })
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
            StrokeColor: new Annotations.Color(255, 0, 0, 1),
            FillColor: new Annotations.Color(255, 0, 0, 1),
            Locked: true,
        });

        goal_annot = new Annotations.EllipseAnnotation({
            PageNumber: 1,
            StrokeColor: new Annotations.Color(0, 255, 0, 1),
            Locked: true,
            X: -GOAL_ANNOT_DIAMETER,
            Y: -GOAL_ANNOT_DIAMETER,
            Width: GOAL_ANNOT_DIAMETER,
            Height: GOAL_ANNOT_DIAMETER,
        });

        var border_annot = new Annotations.PolygonAnnotation({
            PageNumber: 1,
            StrokeColor: new Annotations.Color(0, 0, 255, 1),
            FillColor: new Annotations.Color(0, 0, 0, 0),
            Locked: true,
        })

        rover_annot.addPathPoint(0, 0);
        rover_annot.addPathPoint(1, 0);
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
    });

    // documentViewer.addEventListener('annotationsLoaded', () => {
    //     const annot = new Annotations.PolygonAnnotation({
    //       PageNumber: 1,
    //       StrokeColor: new Annotations.Color(255, 0, 0, 1),
    //       FillColor: new Annotations.Color(255, 0, 0, 1),
    //       Locked: true,
    //     });
  
    //     annot.addPathPoint(50, 50);
    //     annot.addPathPoint(75, 100);
    //     annot.addPathPoint(100, 50);
    //     annot.addPathPoint(50, 50);
  
    //     annotationManager.addAnnotation(annot);
    //     annotationManager.redrawAnnotation(annot);
    //   });
    // documentViewer.addEventListener('mouseLeftDown', () => {
    //     const annot = new Annotations.PolygonAnnotation({
    //       PageNumber: 1,
    //       StrokeColor: new Annotations.Color(255, 0, 0, 1),
    //       FillColor: new Annotations.Color(255, 0, 0, 1),
    //       Locked: true,
    //     });
  
    //     annot.addPathPoint(150, 50);
    //     annot.addPathPoint(175, 100);
    //     annot.addPathPoint(200, 50);
    //     annot.addPathPoint(150, 50);
  
    //     annotationManager.addAnnotation(annot);
    //     annotationManager.redrawAnnotation(annot);
    //   });
    documentViewer.zoomTo(500, pdf_x_px/2, pdf_y_px/2);
})
