#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxEasyFft.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    void plot(vector<float>& buffer, float scale, int x, int y, int r);
//    void mouseMoved(int x, int y);
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
    
    ofxEasyFft fft;
    
    
    float radius;
    
    
    ofxPanel gui;
    ofxFloatSlider radians;
    ofxIntSlider circlePos;
};
