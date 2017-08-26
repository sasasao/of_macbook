#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    stat = s01;
}

//--------------------------------------------------------------
void ofApp::update(){
    switch (stat) {
        case s01:
            if (space){
                stat = s02;
                timeStamp = ofGetElapsedTimef();
            }
            break;
            
        case s02:
            if (!space) {
                stat = s03;
                timeStamp = ofGetElapsedTimef();
                fiveSeconds.push_back(time); //記録
                bestScore = best(fiveSeconds, fiveSeconds.size());
            }
            break;
            
        case s03:
            if (time >= 5.0){
                stat = s01;
                timeStamp = ofGetElapsedTimef();
                if (fiveSeconds.size() >= 6) {
                    fiveSeconds.erase(fiveSeconds.begin());
                }
            }
            break;
            
        default:
            break;
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cout << stat << endl;
//    ofLog() << stat << endl;
    
    time = ofGetElapsedTimef() - timeStamp;
    string s;
    for (int i =0; i < fiveSeconds.size(); i++) {
        s += ofToString(i+1) + ": " + ofToString(fiveSeconds[i]) + "  ";
    }
    
    ofDrawBitmapStringHighlight(s, 20, 80);
    
    switch (stat) {
        case s01:
            ofDrawBitmapStringHighlight("type space key for 5 seconds", 20, 20);
            break;
            
        case s02:
            ofDrawBitmapStringHighlight("type space key for 5 seconds", 20, 20);
            break;
            
        case s03:
            ofDrawBitmapStringHighlight("your score is  " + ofToString(fiveSeconds.back()), 20,20);
            ofDrawBitmapStringHighlight("best score is  " + ofToString(bestScore), 20, 50);
            break;
            
        default:
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') space = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == ' ') space = false;
}

float ofApp::best(vector<float> n, int len) {
    float tmp;
    tmp = n[0];
    for (int i = 0; i < len; i++) {
        if (abs(5 - tmp) > abs(5 - n[i])) { //もしtmpがn[i]より大きかったら
            tmp = n[i];
        }
    }
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
