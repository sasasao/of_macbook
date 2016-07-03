#include "MyMesh.hpp"


MyMesh::MyMesh(float _zone_focus, float _zone_calm, float _zone_posture) {
    zone_focus = _zone_focus;
    zone_calm = _zone_calm;
    zone_posture = _zone_posture;
    
    //初期位置を画面の中心に
    pos.x = 0;
    pos.y = 0;
    
    //球からメッシュを生成
    meshA = ofSpherePrimitive(100, 50).getMesh();
    //メッシュの色を設定
    for (int i = 0; i < meshA.getVertices().size(); i++) {
        meshA.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }

}

void MyMesh::draw(){
    //頂点の数だけ繰り返し
    /*for (int i = 0; i < meshA.getVertices().size(); i++) {
        int m = ofMap(i, 0, meshA.getVertices().size(), 0, memes.size());
        Meme meme = memes[m];
        float calm_loc = ofMap(meme.zone_calm, min_calm, max_calm, 50, 200);
        
        //頂点の位置を取得
        ofVec3f loc = meshA.getVertices()[i] / calm_loc;
        //perlinノイズを生成
        float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, min_focus, max_focus);
        float pos_noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, min_focus, max_focus);
        //ノイズの値で頂点位置を変更
        ofVec3f newLoc = loc.normalize()* noise;
        meshA.setVertex(i, newLoc);
        
        //頂点の色を設定
        //float c = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()),0, 1, 0.5, 1.0);
        float R = ofMap(meme.zone_focus, min_focus, max_focus, 0, 1.0);
        float G = ofMap(meme.zone_calm, min_calm, max_calm, 0, 1.0);
        float B = ofMap(meme.zone_posture, min_posture, max_posture, 0, 1.0);
        
        //meshA.setColor(i, ofFloatColor(c, c, c, 1.0));
        meshA.setColor(i, ofFloatColor(R,G,B,1));
        
    }*/

    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    meshA.draw();
    ofPopMatrix();
}
