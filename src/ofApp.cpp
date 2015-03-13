#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(3, 54, 73);

    //init commmunication with Arduino
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    int baud = 9600;
    serial.setup("/dev/ttyACM0", baud);
    json = "";

	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);

	//creating palette
	palette[0] = ofColor::fromHex(0x69D2E7);
	palette[1] = ofColor::fromHex(0xA7DBD8);
	palette[2] = ofColor::fromHex(0xE0E4CC);
	palette[3] = ofColor::fromHex(0xF38630);
	palette[4] = ofColor::fromHex(0xFA6900);

    ofSetCircleResolution(100);
    for (int i =0; i < NB_SARDINES; i++){
        sardines[i].init();
        sardines[i].pct = ofRandom(1);
    }

    quadVec[0] = ofVec2f(10,10);
    quadVec[1] = ofVec2f(500,10);
    quadVec[2] = ofVec2f(500,500);
    quadVec[3] = ofVec2f(10,500);
}

//--------------------------------------------------------------
void ofApp::update(){
    if( serial.available() ){
        //cout << "\tavailable: " << ofToString( serial.available() ) << endl;
        while( serial.available() ){
            lastChar = char( serial.readByte() );
            json += ofToString( lastChar );
        }

        if(lastChar == '\n'){
            bool parsingSuccessful = jsonEl.parse( json );
            //std::cout << json << std::endl;
            //std::cout << "parsingSuccessful: " << ofToString( parsingSuccessful ) << std::endl;

            if( parsingSuccessful ){
                int ping = jsonEl[ "ping" ].asInt();
                cout << "ping: " << ofToString( ping ) << endl;

                ofxOscMessage m;
                m.setAddress( "/ping" );
                m.addIntArg( ping );

                // check sardine ID
                /*

                ping, ofGetHeight(),

                if (ping == s.x) {

                }
                */
            }
            json = "";
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	// display instructions
	//string buf;
	//buf = "sending osc messages to " + string(HOST) + ":" + ofToString(PORT);
	//ofDrawBitmapString(buf, 10, 20);

    ofSetColor(0, 150);
    ofSetLineWidth(10);
    ofNoFill();
    int height = ofGetHeight();
    for (int x=-MARGE; x<ofGetWidth()+MARGE; x+=10) {
        ofBezier(
            x, -MARGE,
            x + (ofNoise(x/NOISEN, -MARGE, ofGetFrameNum()/TIMESPEED)-.5)*AMPLI, height/3,
            x + (ofNoise(x/NOISEN, height+MARGE, ofGetFrameNum()/TIMESPEED)-.5)*AMPLI, 2*height/3,
            x, height+MARGE
        );
    }

    for (int i =0; i < NB_SARDINES; i++){
        sardines[i].update();
        sardines[i].draw(palette);
    }

    ofImage theScreen; //declare variable
    theScreen.grabScreen(0,0,ofGetWidth(),ofGetHeight());

    ofFill();
    ofSetColor(0);
    ofRect(0,0,ofGetWidth(),ofGetHeight());

    ofSetColor(255);
    //theScreen.draw(ofGetMouseX(), ofGetMouseY());

    theScreen.bind();
    glBegin (GL_QUADS);
    glTexCoord2f (0.0, 0.0);
    glVertex3f (quadVec[0].x, quadVec[0].y, 0.0);
    glTexCoord2f (ofGetWidth(), 0.0);
    glVertex3f (quadVec[1].x, quadVec[1].y, 0.0);
    glTexCoord2f (ofGetWidth(), ofGetHeight());
    glVertex3f (quadVec[2].x, quadVec[2].y, 0.0);
    glTexCoord2f (0.0, ofGetHeight());
    glVertex3f (quadVec[3].x, quadVec[3].y, 0.0);
    glEnd ();
    theScreen.unbind();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    for(int i=0; i<4;i++){
        if(ofDistSquared(x,y,quadVec[i].x,quadVec[i].y)<400){
            quadVec[i].set(x,y);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

