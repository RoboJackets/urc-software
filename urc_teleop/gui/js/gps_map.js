// GPS map updating
var goal_lat;
var goal_long;
var pos_lat;
var pos_long;

var map_tl_lat = 38.4690
var map_tl_long = -110.8542
var map_br_lat = 38.3440
var map_br_long = -110.7292

var tl_x_px = 452;
var tl_y_px = 365;
var br_x_px = 3137;
var br_y_px = 3776;
var pdf_x_px = 3600;
var pdf_y_px = 4350;

var lat_per_px = (map_br_lat - map_tl_lat) / (br_y_px - tl_y_px);
var long_per_px = (map_br_long - map_tl_long) / (br_x_px - tl_x_px);

var pdf_tl_lat = map_tl_lat - tl_y_px * lat_per_px;
var pdf_tl_long = map_tl_long - tl_x_px * long_per_px;
var pdf_br_lat = map_br_lat + (pdf_y_px - br_y_px) * lat_per_px;
var pdf_br_long = map_br_long + (pdf_x_px - br_x_ps) * long_per_px;

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
    initialDoc: 'https://raw.githubusercontent.com/RoboJackets/urc-software/feat/gps_interface_pdftron/urc_teleop/gui/UT_75MinuteTopo1_20221012_234609624000_TM_geo.pdf'
}, document.getElementById('viewer')).then(instance => {
    const { documentViewer } = instance.Core;
})
