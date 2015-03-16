#ifndef SUSHI_H
#define SUSHI_H

#include "ofMain.h"

#define TIMESPEED 500.0
#define NOISEN 200.0
#define AMPLI 350
#define MARGE_X 300
#define MARGE_Y 20000
#define SPEED 0.00025

class Sushi
{
    public:
        void init();
        void initSushi(int i,  std::string img_name);
        void draw();
        void update();
        int id;
        int x;
        float y;
        ofImage img;

        float pct;
        ofPoint a;
        ofPoint b;
        ofPoint c;
        ofPoint d;

        ofVec2f point;

    protected:
    private:
};

#endif // SUSHI_H
