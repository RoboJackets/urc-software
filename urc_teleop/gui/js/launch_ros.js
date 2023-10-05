var ros = new ROSLIB.Ros({
    url : 'ws://192.168.8.150:9090'
});

ros.on('connection', function() {
    console.log('Connected to websocket server.');
    document.getElementById('connecting').style.display = 'none';
    document.getElementById('error').style.display = 'none';
    document.getElementById('closed').style.display = 'none';
    document.getElementById('connected').style.display = 'inline';
});

ros.on('error', function(error) {
    console.log('Error connecting to websocket server: ', error);
    document.getElementById('connecting').style.display = 'none';
    document.getElementById('connected').style.display = 'none';
    document.getElementById('closed').style.display = 'none';
    document.getElementById('error').style.display = 'inline';
});

ros.on('close', function() {
    console.log('Connection to websocket server closed.');
    document.getElementById('connecting').style.display = 'none';
    document.getElementById('connected').style.display = 'none';
    document.getElementById('closed').style.display = 'inline';
});