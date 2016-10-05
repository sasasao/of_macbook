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
    
    //Memeのデータを格納するmemes配列
    vector<Meme> memes;
    
    int index = 0;      //表示するデータのインデックス
    
    float focus;        //表示するデータ
    float next_focus;   //次に表示するデータ
    float morph_focus;  //データ間をモーフィングしたデータ
    
    float percent = 0;  //モーフィングの割合（lerp関数で使うため、1を超えないようにする）
    
    // 指定されたcsvを読み込んで、Memesの配列を作る関数
    void loadCsvToMemes(string filePath);
    
    ofVec2f pos;
    bool loop;

    
    
};
