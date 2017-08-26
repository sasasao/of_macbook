#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetBackgroundAuto(false);
    ofBackground(0);
    
    now = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
    for (int i = 0; i < 50; i++) {
        to.push_back(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
    }
    fft.setup();
    fft.setNumFFTBins(16);
    fft.setNormalize(true);
    
    state = 3;
}

//--------------------------------------------------------------
void ofApp::update(){
    fft.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 15);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    time = ofGetElapsedTimef() - timeStamp;
    


    
    switch (state) {
        case 1:
            if (fft.getMidVal() >= 0.5) {
                timeStamp = ofGetElapsedTimef();
                state = 2;
                ofSetColor(255, 0, 0);
                toNum = int(ofRandom(50));
                from = now;
            }
            break;
        case 2:
            if (time <= easeEnd) {
                now.x = easeOutCubic(time, from.x, to[toNum].x - from.x, easeEnd);
                now.y = easeOutCubic(time, from.y, to[toNum].y - from.y, easeEnd);
                ofSetColor(255);
            }else {
                state = 1;
            }
            if (time > 0.2 && fft.getMidVal() > 0.5) {
                state = 1;
                timeStamp = ofGetElapsedTimef();
            }

            break;
        case 3:
            break;
            
        default:
            break;
    }
    
    ofDrawCircle(now.x, now.y, fft.getMidVal() * 100);
}

float ofApp::easeOutCubic(float t, float b, float c, float d){
    t /= d;
    t--;
    return (c*(t*t*t + 1) +b);
    //t = 経過時間　b = 異動前の場所 c = 移動差分 d = かける時間
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
