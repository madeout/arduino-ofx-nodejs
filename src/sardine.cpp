#include "sardine.h"
#include "ofApp.h"

void Sardine::init(){
    speed = ofRandom(0.0005, 0.0020);
    x = int( ofRandom( -MARGE_X, ofGetWidth() + MARGE_X ) );
    colorId = int( ofRandom( NB_COLORS ) );
    pct = 0;
    a = ofPoint( x, -MARGE_Y );
    d = ofPoint( x, ofGetHeight() + MARGE_Y );
}

void Sardine::update() {
    pct += speed;
    if ( pct >= 1 ) {
        init();
    }

    b = ofPoint( x + (ofNoise(x/NOISEN, -MARGE_Y, ofGetFrameNum()/TIMESPEED)-.5)*AMPLI , ofGetHeight()/3 );
    c = ofPoint( x + (ofNoise(x/NOISEN, ofGetHeight()+MARGE_Y, ofGetFrameNum()/TIMESPEED)-.5)*AMPLI, 2*ofGetHeight()/3);
    for (int i=0; i<NBPOINTS; i++) {
        float pctN = pct + (i*PCTDIST);
        ofPoint p = ofBezierPoint(a,b,c,d, pctN);
        points[i].set(p.x, p.y);
    }
}

void Sardine::draw(ofColor * colors) {
    ofSetColor( colors[ colorId ] );
    ofFill();
    fatLine(points, NBPOINTS, false);
}

void Sardine::fatLine(ofVec2f * pts, int len, bool showSpine){
    ofCircle(pts[0], SARDINEWIDTH);
    for(int i=1;i<len;i++){
        ofCircle(pts[i], SARDINEWIDTH);

        ofVec2f segment = pts[i] - pts[i-1];
        ofVec2f u = segment.getPerpendicular();
        u.scale(SARDINEWIDTH);
        ofVec2f v = u.getRotated(180);

        ofVec2f w = pts[i-1] + u;
        ofVec2f x = pts[i-1] + v;
        ofVec2f y = pts[i] + u;
        ofVec2f z = pts[i] + v;

        ofBeginShape();
            ofVertex(w.x,w.y);
            ofVertex(x.x,x.y);
            ofVertex(z.x,z.y);
            ofVertex(y.x,y.y);
        ofEndShape(true);
    }

    if(showSpine){
        ofSetColor(0);
        ofNoFill();
        ofBeginShape();
        for(int i=0;i<len;i++){
            ofVertex(pts[i].x+2.5, pts[i].y+2.5);
        }
        ofEndShape();

        ofFill();
        for(int i=0;i<len;i++){
            ofRect(pts[i],5,5);
        }
    }
}
