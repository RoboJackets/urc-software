import * as ROSLIB from 'http://static.robotwebtools.org/roslibjs/current/roslib.min.js';

// Probably try interfacing with webRTC?

// Subscribing to a Topic
// ----------------------

var listener = new ROSLIB.Topic({
    ros : ros,
    name : '/listener',
    messageType : 'std_msgs/String'
  });
  listener.subscribe(function(message) {
    console.log('Received message on ' + listener.name + ': ' + message.data);
    listener.unsubscribe();
  });
  