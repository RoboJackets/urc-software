// GPS map updating
var goal_lat;
var goal_long;
var rover_lat;
var rover_long;
var rover_theta;

const map_tl_lat = 38.4690
const map_tl_long = -110.8542
const map_br_lat = 38.3440
const map_br_long = -110.7292

const tl_x_px = 452;
const tl_y_px = 365;
const br_x_px = 3137;
const br_y_px = 3776;
const pdf_x_px = 3600;
const pdf_y_px = 4350;

const lat_per_px = (map_br_lat - map_tl_lat) / (br_y_px - tl_y_px);
const long_per_px = (map_br_long - map_tl_long) / (br_x_px - tl_x_px);

const pdf_tl_lat = map_tl_lat - tl_y_px * lat_per_px;
const pdf_tl_long = map_tl_long - tl_x_px * long_per_px;
const pdf_br_lat = map_br_lat + (pdf_y_px - br_y_px) * lat_per_px;
const pdf_br_long = map_br_long + (pdf_x_px - br_x_px) * long_per_px;

const gps_goal_subscriber = new ROSLIB.Topic({
    ros : ros,
    name : '/gps_goal',
    messageType : 'sensor_msgs/msg/NavSatFix'
})

gps_goal_subscriber.subscribe(function(message) {
    goal_lat = message.latitude;
    goal_long = message.longitude;
});

const gps_pos_subscriber = new ROSLIB.Topic({
    ros: ros,
    name : '/gps_pos',
    messageType : 'sensor_msgs/msg/NavSatFix'
})

gps_pos_subscriber.subscribe(function(message) {
    rover_lat = message.latitude;
    rover_long = message.longitude;
})

WebViewer({
    path: 'js/WebViewer/lib', //'home/matthewhannay/colcon_ws/src/urc-software/urc_teleop/gui/js/WebViewer/lib',
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
        


        const annot = new Annotations.PolygonAnnotation({
            PageNumber: 1,
            StrokeColor: new Annotations.Color(255, 0, 0, 1),
            FillColor: new Annotations.Color(255, 0, 0, 1),
            Locked: true,
        });
    
        annot.addPathPoint(50, 50);
        annot.addPathPoint(75, 100);
        annot.addPathPoint(100, 50);
        annot.addPathPoint(50, 50);
    
        annotationManager.addAnnotation(annot);
        annotationManager.redrawAnnotation(annot);

    });
    
    gps_pos_subscriber.subscribe(function(message) {
        pos_lat = message.latitude;
        pos_long = message.longitude;
    })

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
    });
    documentViewer.addEventListener('annotationsLoaded', () => {
        const annot = new Annotations.PolygonAnnotation({
          PageNumber: 1,
          StrokeColor: new Annotations.Color(255, 0, 0, 1),
          FillColor: new Annotations.Color(255, 0, 0, 1),
          Locked: true,
        });
  
        annot.addPathPoint(50, 50);
        annot.addPathPoint(75, 100);
        annot.addPathPoint(100, 50);
        annot.addPathPoint(50, 50);
  
        annotationManager.addAnnotation(annot);
        annotationManager.redrawAnnotation(annot);
      });
    documentViewer.addEventListener('mouseLeftDown', () => {
        const annot = new Annotations.PolygonAnnotation({
          PageNumber: 1,
          StrokeColor: new Annotations.Color(255, 0, 0, 1),
          FillColor: new Annotations.Color(255, 0, 0, 1),
          Locked: true,
        });
  
        annot.addPathPoint(150, 50);
        annot.addPathPoint(175, 100);
        annot.addPathPoint(200, 50);
        annot.addPathPoint(150, 50);
  
        annotationManager.addAnnotation(annot);
        annotationManager.redrawAnnotation(annot);
      });
    documentViewer.zoomTo(50);
})
