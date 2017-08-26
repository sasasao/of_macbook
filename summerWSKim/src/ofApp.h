#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void keyPressed(int key);
    
        void setupArduino(const int & version);
        void digitalPinChanged(const int & pinNum);
        void analogPinChanged(const int & pinNum);
        void updateArduino();
    
    const int pin = 0;
    const int get_a0 = 0;
    
    ofArduino	ard;
    bool		bSetupArduino;
    
    string buttonState;
    string potValue;
    
    ofTrueTypeFont font;
    ofImage myImg, saveImg, munch;
    ofSoundPlayer camera;
    float imgX;
    float time, timeStump;
    float xd, yd;
    int n, key;
    vector<ofFbo> rectImg;
    
    enum Status{s01, s02, s03, s04};
    Status stat;
    
};
