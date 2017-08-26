#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxProcessFFT.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    

    
    float easeOutCubic(float t, float b, float c, float d);
		
    ofxOscReceiver reciver;
    float value, fader01, fader02, fader03;
    vector<string> items;
    char address;
    int scene;
    
    int n;
    float angle, speed;
    float a1, a2, a3;
    bool first = true;
    
    ProcessFFT fft;
    
    ofMesh myMesh;
    ofMesh myMesh02;
    
    float time, timeStamp;
    vector<ofVec2f> to;
    ofVec2f from, now;
    float easeEnd = 0.4;
    int toNum;
    int state;
    
    float x,y;
    float t = 0;
    float A = 60;
    float B = 60;
    float rc = 0.5;
    float rm =0.45;

};
