# arduino-ofx-nodejs

OpenFrameworks and Arduino communication with NodeJS using [OSC communication](http://opensoundcontrol.org/introduction-osc). Tested on Raspberry Pi


## Use it

* On the Arduino board, install [SensorShieldLib](https://github.com/MAKIO135/sensorShieldLib), so The board will emit Json. 
* Download [ofxJSON](https://github.com/jefftimesten/ofxJSON) lib
* In ofApp.h, define host and port. 

	#define HOST "localhost"
	#define PORT 8080

* The script will forward JSON to a specific port using OSC
* You can then listen to the port with a nodejs or apache server to receive the data

