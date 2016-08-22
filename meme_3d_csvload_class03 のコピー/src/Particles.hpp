#pragma once
#include "ofMain.h"
struct Meme {
    //memeから取得したデータ各種を格納するクラス
    string user_id;
    string zone_date;
    float zone_focus;
    float zone_calm;
    float zone_posture;
};
struct First {
    float cadence;
};



class Particles {
public:
    ofVec3f centerVelocity;
    Particles(int maxParticles, string filePath_meme, string filePath_first);
    void setup();
    void draw();
    void addParticle(ofVec2f position,
                     ofVec2f velocity = ofVec2f(0, 0),
                     ofColor color = 0xffffff);
    void resetOffWalls();
    void updatePos();
    void loadCsvToMemes(string filePath_meme);
    void loadCsvToMemes02(string filePath_first);
    
    
    //Meme
    vector<Meme> memes;
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
    
    //First
    vector<First> firsts;
    float max_cadence,min_cadence;
    
    
    //mesh
    ofMesh mesh;
    ofMesh outside;
    ofVboMesh mesh_line;
    int line_w, line_h;
    int wire;
    
    int maxParticles;
    float pointSize;
    
    int numParticles;
    deque<ofVec2f> positions;
    deque<ofColor> colors;
    float friction;
    
    ofVec3f centerPos;
    
};

