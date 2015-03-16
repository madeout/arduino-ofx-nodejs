#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxJSON.h"

#include "sardine.h"
#include "sushi.h"

#define HOST "localhost"
#define PORT 8080
#define TIMESPEED 500.0
#define NOISEN 200.0
#define AMPLI 350
#define MARGE_X 300
#define MARGE_Y 600
#define NB_SARDINES 100
#define NB_SUSHIS 29
#define NB_COLORS 6

//--------------------------------------------------------
class ofApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxOscSender sender;

		ofSerial serial;
		char lastChar;
		ofxJSONElement jsonEl;
		std::string json;
		int ping;

        ofColor palette[NB_COLORS];
		Sardine sardines[NB_SARDINES];
		Sushi sushis[NB_SUSHIS];

		ofImage img;

		std::string image_names[NB_SUSHIS] = {"concertauditorium.png", "conflcd.png", "contesanimes.png", "Depardieu.png", "Dessin.png", "ecoutextrait.png", "fetedeslumieres.png", "Fnac.png", "Henriette.png", "Herve.png", "Histoire PD.png", "lampedesign.png", "Linaguitare.png", "Maelle.png", "Magali.png", "mathieuboogaerts.png", "naissancedelyon.png", "offreterroir.png", "ONL.png", "parking.png", "pausegourmande.png", "Rencontrebibli.png", "revoltecanuts.png", "theatrecelestins.png", "Tourcrayon.png", "Tournoi Foot.png", "UGCopera.png", "villalyon.png", "Villeubanecovoit.png"};


		ofVec2f quadVec[4];
};
