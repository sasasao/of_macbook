#pragma once
#include "ofMain.h"

class MyMesh{
    
public:
    MyMesh(int maxParticles, float _zone_focus, float _zone_calm, float _zone_posture);
    void update();
    void draw();
    
    void addParticle(ofVec2f position,
                     ofVec2f velocity = ofVec2f(0, 0),
                     ofColor color = 0xffffff);
    void resetForce();
    void addForce(int count, ofVec2f force);
    void addDampingForce();
    void resetOffWalls();
    void updatePos();
    
    
    //particles
    int maxParticles;
    float pointSize;
    
    int numParticles;
    deque<ofVec2f> positions;
    deque<ofVec2f> velocitys;
    deque<ofVec2f> forces;
    deque<ofColor> colors;
    float friction;
    
    
    float zone_focus;
    float zone_calm;
    float zone_posture;
    
    //mesh
    ofMesh meshA;
    ofVec2f pos;
    
};