#include "sushi.h"

#include "ofMain.h"

void Sushi::initSushi(int i) {
    id = i;
    img.loadImage(ofToString(i+1)+"-0.png");
}

void Sushi::init(){

    x = int( ofRandom( -MARGE_X, ofGetWidth() + MARGE_X ) );
    pct = 0;
    a = ofPoint( x, -MARGE_Y );
    d = ofPoint( x, ofGetHeight() + MARGE_Y );
}

void Sushi::update() {
    pct += SPEED;
    if ( pct >= 1 ) {
        init();
    }

    b = ofPoint( x + (ofNoise(x/NOISEN, -MARGE_Y, ofGetFrameNum()/TIMESPEED)-.5)*AMPLI , ofGetHeight()/3 );
    c = ofPoint( x + (ofNoise(x/NOISEN, ofGetHeight()+MARGE_Y, ofGetFrameNum()/TIMESPEED)-.5)*AMPLI, 2*ofGetHeight()/3);


    point = ofBezierPoint(a,b,c,d, pct);
    y = point.y;
}

void Sushi::draw() {
    ofFill();
    ofSetColor(255);
    img.draw(point.x,point.y);
}
