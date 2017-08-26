#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(255);
    
    gui.setup();
    gui.add(one.setup("size", 100, 0, 700));
    gui.add(two.setup("strokes", 5, 3, 100));
    gui.add(three.setup("point", 1, 1, 10));

}

//--------------------------------------------------------------
void ofApp::update(){
    glPointSize(three);
    
    myMesh = ofSpherePrimitive(1000, two).getMesh();
    myMesh.setMode(OF_PRIMITIVE_POINTS);
    
    ofSetColor(255, 0, 0);
    myMesh02 = ofSpherePrimitive(80, two).getMesh();
    myMesh02.setMode(OF_PRIMITIVE_LINES);


    
    for (int i = 0; i < myMesh.getVertices().size(); i++) {
        ofVec3f loc = myMesh.getVertices()[i] / 100;
        float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, one);
        ofVec3f newLoc = loc.normalize() * noise;
        myMesh.setVertex(i, newLoc);
    }
    
    for (int i = 0; i < myMesh02.getVertices().size(); i++) {
        ofVec3f loc = myMesh02.getVertices()[i] / 100;
        float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, 100);
        ofVec3f newLoc = loc.normalize() * noise;
        myMesh02.setVertex(i, newLoc);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    ofPushMatrix();
    
//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
//    ofRotateX(ofGetElapsedTimef()*1000);
    ofTranslate(-ofGetWidth()/2, 0);
    for (int i = 0; i < ofGetWidth(); i+=100) {
        ofSetColor(0);
        ofTranslate(i, 0);
        myMesh.draw();
        myMesh02.draw();
    }

    ofPopMatrix();
    cam.end();
    
    ofSetColor(255);
    gui.draw();
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
