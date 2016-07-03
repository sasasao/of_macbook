#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
        
        
    ofEnableDepthTest();
    //対象からの距離の初期値を指定
    cam.setDistance(300);
    
    //画面基本設定
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableDepthTest();
    
    //ライトを配置
    light.enable();
    light.setPosition(-100, 100, 500);
    
   }

//--------------------------------------------------------------
void ofApp::update(){
        
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    cam.begin();
    
    ofBackground(0);
    Me.draw();
    
    
    
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

