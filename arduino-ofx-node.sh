#

# $root = "/home/pi/"

echo 'Launching OFX...'
# launch OFX 
2>/dev/null 1>/dev/null ./bin/arduino-ofx-nodejs &

echo 'Launching node server...'
# launch node
node node-server/app.js < /dev/null &

echo 'Launched'
