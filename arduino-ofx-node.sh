#!/bin/bash

REP=/home/pi/openFrameworks/apps/myApps/arduino-ofx-nodejs


echo 'Launching OFX...'
# launch OFX 
2>/dev/null 1>/dev/null su pi -c "${REP}/bin/arduino-ofx-nodejs" &

echo 'Launching node server...'
# launch node
su pi -c "node ${REP}/node-server/app.js" < /dev/null &

echo 'Launched'
