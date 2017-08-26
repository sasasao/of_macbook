#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
//    ofSetVerticalSync(true);
    ofBackground(63);
    
    fft.setup(pow(2.0, 10.0));
    gui.setup();
    gui.add(saturation.setup("Saturation", 100, 0, 255));
//    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    fft.update();
    for(int i = 0; i < NUM; i++){
//        float posX = ofRandom(ofGetWidth());
//        float posY = ofRandom(ofGetHeight());
        particle[i].resetForce();
        particle[i].addForce(ofVec2f(0, 0.25));
        particle[i].updateForce();
        particle[i].updatePos();
        particle[i].checkBounds(0, -1000, ofGetWidth(), ofGetHeight());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    vector<float> buffer;
//    buffer = fft.getBins();
//    if (buffer.size()>0) {
//        for(int i = 0; i < NUM; i++){
//            float posX = ofRandom(ofGetWidth());
//            float posY = ofRandom(ofGetHeight());
//            ofVec2f pos = ofVec2f(posX, posY);
//            float length = ofRandom(60);
//            float angle = ofRandom(PI * 2);
//            ofVec2f vel = ofVec2f(cos(angle) * length, sin(angle) * length);
//            for (int i = 0; i < buffer.size(); i++) {
//                float br = ofMap(buffer[i], 0, 1, 0, 255);
//                particle[i].setup(pos, vel);
//                particle[i].radius = buffer[i];
//                particle[i].friction = 0.01;
//                particle[i].draw();
//            }
//        }
//    }
    
    
    
    
//    for(int i = 0; i < NUM; i++){
//        particle[i].draw();
//    }
    
    vector<float> buffer;
    buffer = fft.getBins();
//    ofSetLineWidth(ofGetWidth() / float(buffer.size()) / 2.0);
//    ofPushMatrix();
//    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for (int i = 0; i < buffer.size(); i++) {
        float hue = ofMap(i, 0, buffer.size(), 0, 160);
        float br = ofMap(buffer[i], 0, 1, 0, 255);
        ofColor col;
        col.setHsb(hue, saturation, br);
        ofSetColor(col);
//        float rx = ofMap(i, 0, buffer.size(), 0, ofGetWidth() / 2.0);
//        ofDrawBox(rx, -ofGetWidth() / 2.0, rx, ofGetWidth() / 2.0);
//        ofLine(rx, -ofGetWidth() / 2.0, rx, ofGetWidth() / 2.0);
//        float lx = ofMap(i, 0, buffer.size(), 0, -ofGetWidth() / 2.0);
//        ofLine(lx, -ofGetWidth() / 2.0, lx, ofGetWidth() / 2.0);
        
            particle[i].draw();
        
    }
//    ofPopMatrix();
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//    vector<float> buffer;
//    buffer = fft.getBins();
//    if (buffer.size()>0) {
//        for(int i = 0; i < NUM; i++){
////            float posX = ofRandom(ofGetWidth());
////            float posY = ofRandom(ofGetHeight());
//            ofVec2f pos = ofVec2f(x, y);
//            float length = ofRandom(60);
//            float angle = ofRandom(PI * 2);
//            ofVec2f vel = ofVec2f(cos(angle) * length, sin(angle) * length);
//            for (int i = 0; i < buffer.size(); i++) {
//                float br = ofMap(buffer[i], 0, 1, 0, 255);
//                particle[i].setup(pos, vel);
//                particle[i].radius = buffer[i]*10;
//                particle[i].friction = 0.01;
//                particle[i].draw();
//            }
//        }
//    }

//    
//        for(int i = 0; i < NUM; i++){
//            ofVec2f pos = ofVec2f(x, y);
//            float length = ofRandom(60);
//            float angle = ofRandom(PI * 2);
//            ofVec2f vel = ofVec2f(cos(angle) * length, sin(angle) * length);
//            particle[i].setup(pos, vel);
//            particle[i].radius = 4;
//            particle[i].friction = 0.01;
//            }
//    
    

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    vector<float> buffer;
    buffer = fft.getBins();
//    if (buffer.size()>0) {
        for(int i = 0; i < NUM; i++){
            for (int t = 0; t < buffer.size(); t++) {
                if (buffer[t]>0) {
                    
                
            float rx = ofMap(t, 0, buffer.size(), 0, ofGetWidth() / 2.0);
            //            float posX = ofRandom(ofGetWidth());
            //            float posY = ofRandom(ofGetHeight());
            x = ofRandom(ofGetWidth());
            y = ofRandom(ofGetHeight());
            ofVec2f pos = ofVec2f(x, y);
            float length = ofRandom(60);
            float angle = ofRandom(PI * 2);
            ofVec2f vel = ofVec2f(cos(angle) * length, sin(angle) * length);
                particle[i].setup(pos, vel);
                particle[i].radius = 4;
                particle[i].friction = 0.01;
//                particle[i].draw();
            }
            }
        }
//    }

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
