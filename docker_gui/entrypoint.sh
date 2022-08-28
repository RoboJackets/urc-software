#!/bin/bash
x11vnc -forever -usepw -create &

websockify -D --web=/usr/share/novnc/ --cert=/etc/ssl/certs/XRamp_Global_CA_Root.pem 8080 localhost:5900

# Start Terminal emulator
/bin/bash