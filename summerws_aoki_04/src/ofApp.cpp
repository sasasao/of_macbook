#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(20);
    ofSetFullscreen(true);
    ofSetCircleResolution(100);
    
    
    reciver.setup(8888);
    scene = 1;
    
    fft.setup();
    fft.setNumFFTBins(16);
    fft.setNormalize(true);
    
    now = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
    for (int i = 0; i < 50; i++) {
        to.push_back(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
    }
    state = 3;
}

//--------------------------------------------------------------
void ofApp::update(){
    fft.update();
    
    while (reciver.hasWaitingMessages()) {
        ofxOscMessage m;
        reciver.getNextMessage(m);
        value = m.getArgAsFloat(0);
        items = ofSplitString(m.getAddress(), "/");
        address = ofToChar(items.back());
        
        switch (address) {
            case 'a':
                fader01 = value;
                break;
            case 'b':
                fader02 = value;
                break;
            case 'c':
                fader03 = value;
                break;
            case '1':
                scene = 1;
                break;
            case '2':
                scene = 2;
                break;
            case '3':
                scene = 3;
                break;
                
            default:
                break;
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofNoFill();
    ofSetColor(255);
    
    time = ofGetElapsedTimef() - timeStamp;
    //----
    switch (state) {
        case 1:
            if (fft.getMidVal() >= 0.5) {
                timeStamp = ofGetElapsedTimef();
                from = now;
                toNum = int(ofRandom(50));
                state = 2;
            }
            break;
        case 2:
            if (time <= easeEnd) {
                now.x = easeOutCubic(time, from.x, to[toNum].x - from.x, easeEnd);
                now.y = easeOutCubic(time, from.y, to[toNum].y - from.y, easeEnd);
            }
            else {
                state = 1;
            }
            if (time > 0.2 && fft.getMidVal() > 0.5) {
                state = 1;
                timeStamp = ofGetElapsedTimef();
            }
            break;
        default:
            break;
    }
    
    //----
    switch (scene) {
        case 1:
            
            ofSetBackgroundAuto(true);
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            glPointSize(fft.getLowVal()*10);
            
            myMesh = ofSpherePrimitive(1000, fader02*100).getMesh();
            myMesh.setMode(OF_PRIMITIVE_POINTS);
            
            for (int i = 0; i < myMesh.getVertices().size(); i++) {
                ofVec3f loc = myMesh.getVertices()[i] / 100;
                float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, fader03 * 1000);
                ofVec3f newLoc = loc.normalize() * noise;
                myMesh.setVertex(i, newLoc);
            }
            
            myMesh.draw();
            
            if(fft.getHighVal() >= 0.5){
                ofSetColor(255);
                myMesh02 = ofSpherePrimitive(80, fader02*100).getMesh();
                myMesh02.setMode(OF_PRIMITIVE_LINES);
                
                for (int i = 0; i < myMesh02.getVertices().size(); i++) {
                    ofVec3f loc = myMesh02.getVertices()[i] / 100;
                    float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, fader03 * 1000);
                    ofVec3f newLoc = loc.normalize() * noise;
                    myMesh02.setVertex(i, newLoc);
                }

                myMesh02.draw();
                myMesh02.setMode(OF_PRIMITIVE_LINES);
            }
            ofPopMatrix();
            
            break;
            
            
        case 2:
            ofSetBackgroundAuto(true);
            
            glPointSize(fft.getLowVal()*10);
            
            myMesh = ofSpherePrimitive(1000, fader02*100).getMesh();
            myMesh.setMode(OF_PRIMITIVE_POINTS);
            
            for (int i = 0; i < myMesh.getVertices().size(); i++) {
                ofVec3f loc = myMesh.getVertices()[i] / 100;
                float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, fader03 * 1000);
                ofVec3f newLoc = loc.normalize() * noise;
                myMesh.setVertex(i, newLoc);
            }
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 4, ofGetHeight() / 2);
            myMesh.draw();
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 4 * 2, ofGetHeight() / 2);
            myMesh.draw();
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 4 * 3, ofGetHeight() / 2);
            myMesh.draw();
            ofPopMatrix();
            
            if(fft.getHighVal() >= 0.5){
                ofSetColor(255);
                myMesh02 = ofSpherePrimitive(80, fader02*100).getMesh();
                myMesh02.setMode(OF_PRIMITIVE_LINES);
                
                for (int i = 0; i < myMesh02.getVertices().size(); i++) {
                    ofVec3f loc = myMesh02.getVertices()[i] / 100;
                    float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, fader03 * 1000);
                    ofVec3f newLoc = loc.normalize() * noise;
                    myMesh02.setVertex(i, newLoc);
                }
                
                ofPushMatrix();
                ofTranslate(ofGetWidth() / 4, ofGetHeight() / 2);
                myMesh02.draw();
                myMesh02.setMode(OF_PRIMITIVE_LINES);
                ofPopMatrix();
                
                ofPushMatrix();
                ofTranslate(ofGetWidth() / 4 * 2, ofGetHeight() / 2);
                myMesh02.draw();
                myMesh02.setMode(OF_PRIMITIVE_LINES);
                ofPopMatrix();
                
                ofPushMatrix();
                ofTranslate(ofGetWidth() / 4 * 3, ofGetHeight() / 2);
                myMesh02.draw();
                myMesh02.setMode(OF_PRIMITIVE_LINES);
                ofPopMatrix();
                
            }
            

            

            break;
        case 3:
            if(fft.getHighVal() >= fader01){
                ofSetLineWidth(4);
                ofPushMatrix();
                ofSetColor(255, 0, 0);
                ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
                ofRotateX(ofGetElapsedTimef()*100);
                ofRotateY(ofGetElapsedTimef()*100);
                ofRotateZ(ofGetElapsedTimef()*100);
                ofDrawCircle(0, 0, 400);
                ofPopMatrix();
                
                ofPushMatrix();
                ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
                ofRotateX(ofGetElapsedTimef()*150);
                ofRotateY(ofGetElapsedTimef()*150);
                ofRotateZ(ofGetElapsedTimef()*150);
                ofDrawCircle(0, 0, 400);
                ofPopMatrix();
            }

            ofSetBackgroundAuto(true);
            ofPushMatrix();
            ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
            glPointSize(fader01*10);
            
            myMesh = ofSpherePrimitive(1000, fft.getHighVal() * 100).getMesh();
            myMesh.setMode(OF_PRIMITIVE_POINTS);
            
            ofSetColor(255);
            myMesh02 = ofSpherePrimitive(80, fft.getHighVal() * 100).getMesh();
            myMesh02.setMode(OF_PRIMITIVE_LINES);
            
            for (int i = 0; i < myMesh.getVertices().size(); i++) {
                ofVec3f loc = myMesh.getVertices()[i] / 100;
                float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, fader03 * 500);
                ofVec3f newLoc = loc.normalize() * noise;
                myMesh.setVertex(i, newLoc);
            }
            
            for (int i = 0; i < myMesh02.getVertices().size(); i++) {
                ofVec3f loc = myMesh02.getVertices()[i] / 100;
                float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, 100);
                ofVec3f newLoc = loc.normalize() * noise;
                myMesh02.setVertex(i, newLoc);
            }

            myMesh.draw();
            myMesh02.draw();
            
            ofPopMatrix();
            break;
        default:
            break;
        }
    }

float ofApp::easeOutCubic(float t, float b, float c, float d) {
    t /= d ;
    t-- ;
    return (c*(t*t*t + 1) + b) ;
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
