#include "ofApp.h"

void ofApp::setup() {
    

    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetCircleResolution(64); //円の解像度設定
    fft.setup(16384);
    
    
    radius = 2;
    
    gui.setup();
    gui.add(radians.setup("radians", 45, 4, 180));
    gui.add(circlePos.setup("circlePos", 0, -ofGetWidth()/2, ofGetWidth()/2));
}

void ofApp::update() {
    fft.update();
}

void ofApp::draw() {
    ofBackground(255);
    ofSetColor(0,0,0,100);
    ofSetLineWidth(2);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateZ(circlePos);
    for (int i = 0; i < 360; i += radians) {
        plot(fft.getBins(), ofGetHeight()*2, 0, 0, i);
    }
    ofPopMatrix();
    
    
    
    string msg = ofToString((int) ofGetFrameRate()) + " fps";
    ofDrawBitmapString(msg, ofGetWidth() - 80, ofGetHeight() - 20);
    
    gui.draw();
}

void ofApp::plot(vector<float>& buffer, float scale, int x, int y, int r) {
    ofNoFill();
    int n = MIN(1024, buffer.size());
    ofPushMatrix();
//    ofTranslate(ofGetWidth()/2 - x, ofGetHeight()/2 - y);
    ofRotate(r);
    ofScale(1, -scale);
    
    ofBeginShape();
    for (int i = 0; i < n; i++) {
        ofVertex(i+circlePos, buffer[i]);
    }
    ofEndShape();
    
    ofPopMatrix();
}


