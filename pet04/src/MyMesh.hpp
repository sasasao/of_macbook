#pragma once
#include "ofMain.h"



class MyMesh{
    
public:
    MyMesh(float _zone_focus, float _zone_calm, float _zone_posture);
    void draw();
    
    float zone_focus;
    float zone_calm;
    float zone_posture;
    
    ofMesh meshA;
    ofMesh meshB;
    
    ofVec2f pos;


};