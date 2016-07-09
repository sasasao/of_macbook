#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    //ofBackground(149,170,194);
    ofBackground(0);
    ofEnableDepthTest();
    
    light.enable();
    light.setPosition(-100, 100, 1000);
//    light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5, 1.0));
//    light.setDiffuseColor(ofFloatColor(0.3, 0.3, 0.3, 1.0));
    
    light.setPointLight();
    
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    //myImage.allocate(ofGetWidth()*2, ofGetHeight()*2, OF_IMAGE_GRAYSCALE);
    //pixels = myImage.getPixels();
    
    //particleNum = 1;
    Particles *p;

    for (int i = 1; i < 6; i++) {
        p = new Particles(particleNum, "tamabi0" + ofToString(i) + ".csv", "00" + ofToString(i) + "_ST.csv");
        particles.push_back(p);
    }
    p = new Particles(particleNum, "tamabi08.csv", "008_ST.csv");
    particles.push_back(p);
    p = new Particles(particleNum, "tamabi09.csv", "009_ST.csv");
    particles.push_back(p);
    
    for (int i = 10; i < 15; i++) {
        p = new Particles(particleNum, "tamabi" + ofToString(i) + ".csv", "0" + ofToString(i) + "_ST.csv");
        particles.push_back(p);
    }
    
    
    /*p = new Particles(particleNum, "tamabi01.csv", "001_ST.csv");
    particles.push_back(p);
    p = new Particles(particleNum, "tamabi02.csv", "002_ST.csv");
    particles.push_back(p);
    p = new Particles(particleNum, "tamabi03.csv", "003_ST.csv");
    particles.push_back(p);
    p = new Particles(particleNum, "tamabi13.csv", "013_ST.csv");
    particles.push_back(p);*/
    
    
    
    for (int i = 0; i < particles.size(); i++) {
        ofVec3f position = ofVec3f(ofRandom(width), ofRandom(height));
        particles[i]->addParticle(position);
    }
    
    scaleX.addListener(this, &ofApp::scaleXChanged);
    scaleY.addListener(this, &ofApp::scaleYChanged);
    
    /*
    gui.setup();
    gui.add(speed.setup("speed", 0.1, 0.0, 0.5));
    gui.add(friction.setup("friction", 0.01, 0.0, 0.04));
    gui.add(scaleX.setup("scale x", 5.0, 1.0, 10.0));
    gui.add(scaleY.setup("scale y", 5.0, 1.0, 10.0));
    */
}

//--------------------------------------------------------------
void ofApp::scaleXChanged(float & scaleX){
    updateNoise();
}

//--------------------------------------------------------------
void ofApp::scaleYChanged(float & scaleY){
    updateNoise();
}

void ofApp::updateNoise(){
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            float noiseX = ofMap(i, 0, width, 0, 1.0);
            float noiseY = ofMap(j, 0, width, 0, 1.0);
            int noiseVal = ofNoise(noiseX, noiseY) * 255;
            pixels[j * width + i] = noiseVal;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->friction = friction;
        particles[i]->resetForce();
        particles[i]->addDampingForce();
        particles[i]->updatePos();
        particles[i]->resetOffWalls();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    ofPushMatrix();
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->draw();
    }
    
    ofPopMatrix();
    cam.end();
    
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    //gui.draw();
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
