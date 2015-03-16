#!/bin/bash

REP=/home/pi/openFrameworks/apps/myApps/arduino-ofx-nodejs


echo 'Launching OFX...'
# launch OFX 
2>/dev/null 1>/dev/null ${REP}/bin/arduino-ofx-nodejs &

echo 'Launching node server...'
# launch node
node ${REP}/node-server/app.js < /dev/null &

echo 'Launched'
