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
    path: '/webviewer/lib', //'home/matthewhannay/colcon_ws/src/urc-software/urc_teleop/gui/js/WebViewer/lib',
    initialDoc: 'https://drive.google.com/file/d/1ht-cYEJDlVmYhDctEeTPMD_Hx26T3e8q/view?usp=sharing'
}, document.getElementById('viewer')).then(instance => {
    const { documentViewer } = instance.Core;
})
