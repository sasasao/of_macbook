#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofBackground(255);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ard.connect("/dev/cu.usbmodem1421", 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;
    
    font.load("fonts/YuGothicStd-B.otf", 18);
    myImg.load("img/image.png");
    munch.load("img/a.jpg");
    camera.load("snd/camera-shutter1.mp3");
    
    
    stat = s02;
    n = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    ard.update();
    
    switch (stat) {
        case s01:
            break;
        case s02:
            if (time >= 5.0) {
                stat = s03;
                timeStump = ofGetElapsedTimef();
                camera.play();
                n++;
            }
            break;
        case s03:
            saveImg.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            saveImg.save(ofToString(n) + ".jpg");
            stat = s04;
            timeStump = ofGetElapsedTimef();
            break;
        case s04:
            timeStump = ofGetElapsedTimef();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    munch.draw(0, 0, 800, 800);
    
    if (!bSetupArduino){
        ofDrawBitmapStringHighlight("arduino not ready...\n", 20, 20);
    } else {
        ofDrawBitmapStringHighlight("arduino ready!", 20, 20);
    }
    
    time = ofGetElapsedTimef() - timeStump;
    imgX = ofMap(ard.getAnalog(0), 1000, 0, 200, 0);
    myImg.draw(420 - imgX/2, 380, imgX, 200);
    
    switch (stat) {
        case s01:
            break;
        case s02:
            font.drawString("Let's take a picture!  ", 20, 100);
            font.drawString(ofToString(int(5-time)), 20, 150);
            break;
            
        case s03:
            break;
        case s04:
            ofSetColor(255);
            font.drawString("Start : Press E", 20, 100);
            break;
        default:
            break;
    }
}

void ofApp::setupArduino(const int & version) {
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;
    
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    
}

void ofApp::updateArduino(){
    
}

void ofApp::keyPressed(int key){
    if (key == 'e') {
        stat = s02;
        timeStump = ofGetElapsedTimef();
    }
}


