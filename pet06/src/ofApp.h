#pragma once

#include "ofMain.h"
#include "MyMesh.hpp"
#include "ofxGui.h"

struct Meme {
    //memeから取得したデータ各種を格納するクラス
    string user_id;
    string zone_data;
    float zone_focus;
    float zone_calm;
    float zone_posture;
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void loadCsvToMemes(string filePath);
    
    ofEasyCam cam;
    ofLight light;
    vector<Meme> memes;
    vector<MyMesh> mes;
    
    float max_focus, min_focus;
    float max_calm, min_calm;
    float max_posture, min_posture;
};
