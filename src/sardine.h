#ifndef SARDINE_H
#define SARDINE_H

#include "ofMain.h"

#define NBPOINTS 3
#define TIMESPEED 500.0
#define NOISEN 200.0
#define AMPLI 350
#define MARGE 300
#define PCTDIST 0.08
#define SARDINEWIDTH 30

class Sardine
{
    public:
        //Sardine();

        float SPEED;
        int X;
        float pct;
        int colorId;
        ofColor * color;
        void init();
        void update();
        void draw(ofColor * colors);

        ofPoint a;
        ofPoint b;
        ofPoint c;
        ofPoint d;
        void fatLine(ofVec2f *pts, int n, bool showSpine);
        ofVec2f points[NBPOINTS];
};

#endif // SARDINE_H