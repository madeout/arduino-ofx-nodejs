#include "ofApp.h"

#define PING_MIN 5
#define PING_MAX 55


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

    ofSetFullscreen(true);
    ofHideCursor();

	image_names[0] = "concertauditorium.png";
    image_names[1] = "conflcd.png";
    image_names[2] = "contesanimes.png";
    image_names[3] = "Depardieu.png";
    image_names[4] = "Dessin.png";
    image_names[5] = "ecoutextrait.png";
    image_names[6] = "fetedeslumieres.png";
    image_names[7] = "Fnac.png";
    image_names[8] = "Henriette.png";
    image_names[9] = "Herve.png";
    image_names[10] = "Histoire PD.png";
    image_names[11] = "lampedesign.png";
    image_names[12] = "Linaguitare.png";
    image_names[13] = "Maelle.png";
    image_names[14] = "Magali.png";
    image_names[15] = "mathieuboogaerts.png";
    image_names[16] = "naissancedelyon.png";
    image_names[17] = "offreterroir.png";
    image_names[18] = "ONL.png";
    image_names[19] = "parking.png";
    image_names[20] = "pausegourmande.png";
    image_names[21] = "Rencontrebibli.png";
    image_names[22] = "revoltecanuts.png";
    image_names[23] = "theatrecelestins.png";
    image_names[24] = "Tourcrayon.png";
    image_names[25] = "Tournoi Foot.png";
    image_names[26] = "UGCopera.png";
    image_names[27] = "villalyon.png";
    image_names[28] = "Villeubanecovoit.png";

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

    // sushis
    for (int i =0; i < NB_SUSHIS; i++){
        sushis[i].init();
        std::string img_name = ofToString("sardines/"+image_names[i]);
        cout << img_name << endl;
        sushis[i].initSushi(i, img_name);
        sushis[i].pct = i*1.0/NB_SUSHIS;
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

            if( parsingSuccessful ){
                ping = jsonEl[ "ping" ].asInt();
                cout << "ping: " << ofToString( ping ) << endl;

            }
            json = "";
        }
    }

    for(int i = 0; i < NB_SUSHIS; i++) {


        // sushi on screen
        if(sushis[i].y > ofGetHeight()/2- 200 && sushis[i].y < ofGetHeight()/2 +200) {

            // cout << "sushi in FISHING ZONE: " << ofToString( sushis[i].id ) << endl;

            if( ping < PING_MIN && ping < PING_MAX ) {

             // if( abs( ofMap( ping, PING_MIN, PING_MAX, ofGetWidth(), 0, false) - sushis[i].x ) < 20){

                cout << "sushi catched : " << ofToString( sushis[i].id ) << endl;

                ofxOscMessage mOSC;
                mOSC.setAddress( "/sushi" );

                // mOSC.addIntArg( sushis[i] );
                mOSC.addStringArg( image_names[i] );

                sender.sendMessage(mOSC);
             }
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
    for (int x=-MARGE_X; x<ofGetWidth()+MARGE_X; x+=10) {
        ofBezier(
            x, -MARGE_Y,
            x + (ofNoise(x/NOISEN, -MARGE_Y, ofGetFrameNum()/TIMESPEED)-.5)*AMPLI, height/3,
            x + (ofNoise(x/NOISEN, height+MARGE_Y, ofGetFrameNum()/TIMESPEED)-.5)*AMPLI, 2*height/3,
            x, height+MARGE_Y
        );
    }


    for (int i =0; i < NB_SARDINES; i++){
        sardines[i].update();
        sardines[i].draw(palette);
    }


    for (int i =0; i < NB_SUSHIS; i++){
        sushis[i].update();
        sushis[i].draw();
    }

    /*

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
    */

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

