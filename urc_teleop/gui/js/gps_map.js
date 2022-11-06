// GPS map updating
var goal_lat;
var goal_long;
var pos_lat;
var pos_long;

var map_tl_lat = 38.4690
var map_tl_long = -110.8542
var map_br_lat = 38.3440
var map_br_long = -110.7292

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
    pos_lat = message.latitude;
    pos_long = message.longitude;
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
