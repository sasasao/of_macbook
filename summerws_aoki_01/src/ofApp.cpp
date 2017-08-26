#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    stat = s01;
    
    sound.load("sound/s01.mp3");
    video.load("video/fingers.mov");
    
}

//--------------------------------------------------------------
void ofApp::update(){
//プロセス的な処理、更新・数値的な処理
    switch (stat) {
        case s01:
            if (time >= 5.0) {
                timeStamp = ofGetElapsedTimef();
                stat = s02;
                sound.play();
            }
            break;
            
        case s02:
            if (time >= 2.0) {
                timeStamp = ofGetElapsedTimef();
                stat = s03;
                sound.stop();
                video.play();
            }
            break;
            
        case s03:
            video.update();
            if (time >= 4.0) {
                timeStamp = ofGetElapsedTimef();
                stat = s01;
                video.stop();
            }
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //各経過時間 = アプリ立ち上げ後の経過時間 - タイムスタンプ
    time = ofGetElapsedTimef() - timeStamp;
    
    
    switch (stat) {
        case s01:
            ofSetColor(255, 0, 0);
            ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2, 100, 100);
            break;
            
        case s02:
            ofSetColor(0, 255, 0);
            ofDrawEllipse(ofGetWidth(), ofGetHeight()/2, 100, 100);
            break;
            
        case s03:
            video.draw(0, 0, ofGetWidth(), ofGetHeight());
            ofSetColor(0, 0, 255);
            ofDrawEllipse(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), 100, 100);
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
