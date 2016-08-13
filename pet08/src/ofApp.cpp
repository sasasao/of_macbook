#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();
    
    light.enable();
    light.setPosition(-100, 100, 1000);
//  light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5, 1.0));
//  light.setDiffuseColor(ofFloatColor(0.3, 0.3, 0.3, 1.0));
    light.setPointLight();
    cam.setDistance(3000);
    
    Pets *p;
    p = new Pets("tamabi08.csv", "008_ST.csv");
    pets.push_back(p);
    p = new Pets("tamabi09.csv", "009_ST.csv");
    pets.push_back(p);
    
     for (int i = 1; i < 6; i++) {
     p = new Pets("tamabi0" + ofToString(i) + ".csv", "00" + ofToString(i) + "_ST.csv");
     pets.push_back(p);
     }
        for (int i = 10; i < 15; i++) {
        p = new Pets("tamabi" + ofToString(i) + ".csv", "0" + ofToString(i) + "_ST.csv");
        pets.push_back(p);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    for (int i = 0; i < pets.size(); i++) {
        pets[i]->draw();
    }
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
