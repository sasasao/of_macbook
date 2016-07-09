#pragma once
#include "ofMain.h"

struct MemeA {
    float cadence;
};

struct MemeB {
    string user_id;
    string zone_date;
    float zone_focus;
    float zone_calm;
    float zone_posture;
};

class Pets {
public:
    Pets(string filePath_memeA, string filePath_memeB);
    void setup();
    void draw();
    void loadCsvToMemesA(string filePath_memeA);
    void loadCsvToMemesB(string filePath_memeB);
    
    
    //MEME
    vector<MemeA> memesA;
    float max_cadence,min_cadence;
    
    vector<MemeB> memesB;
    float max_focus, min_focus;
    float max_calm, min_calm;
    float max_posture, min_posture;
    float morph_focus;
    float morph_calm;
    float morph_posture;
    
    float next_focus;
    float next_calm;
    float next_posture;
    
    float focus;
    float calm;
    float posture;
    
    float percent = 0;
    int index = 0;

    
    //mesh
    ofMesh mesh;
    ofMesh mesh_line;
    ofMesh mesh_point;
    
    ofVec3f centerVelocity;
    ofVec3f centerPos;
    
    int wire_num;

};
