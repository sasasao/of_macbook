#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0, 162, 166);
    ofSetFrameRate(1);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 100);
    ofNoFill();
    ofTranslate(ofGetWidth()/2, 0);
    
    for(int i=0; i < ofGetHeight(); i+=40){
        for(int j=0; j < ofGetHeight(); j+=100){
            
                ofSetLineWidth(ofRandom(3));
            //float y = sin(j);
                //ofTranslate(i, j);
                ofRotate(1);
            ofSetCircleResolution(ofRandom(3,6));
            ofDrawCircle(i, j, ofRandom(50));
            ofSetCircleResolution(ofRandom(3,6));
            ofDrawCircle(i, j, 10);
            }
        
    }
    
    //ofDrawEllipse(100, 100, ofGetWidth()/2, <#float height#>)
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        // ここでファイルを保存!!
        //draw関数内で
        ofSetColor(255,130,0);
        ofFill();
        ofDrawCircle(100,100,50);
        // keyPressed関数内で
        img.grabScreen(0,0,2500,5000);
        
        img.save("myPic.jpg");
    }
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
