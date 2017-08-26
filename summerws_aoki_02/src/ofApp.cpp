#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    stat = s01;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    switch (stat) {
        case s01:
            if (count == 1) {
                stat = s02;
                timeStump = ofGetElapsedTimef();
            }
            break;
            
        case s02:
            if (count == 2) {
                stat = s03;
                timeStump = ofGetElapsedTimef();
            }
            break;
            
        case s03:
            if (count == 3) {
                stat = s01;
                timeStump = ofGetElapsedTimef();
                count = 0;
            }
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    time = ofGetElapsedTimef() - timeStump;
    
    switch (stat) {
        case s01:
            ofDrawEllipse(0, 0, 100, 100);
            break;
            
        case s02:
            ofDrawEllipse(100, 100, 100, 100);
            break;
            
        case s03:
            ofDrawEllipse(200, 200, 100, 100);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    count += 1;
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
