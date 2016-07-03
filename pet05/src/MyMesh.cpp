#include "MyMesh.hpp"


MyMesh::MyMesh(int _maxParticles){
    string filePath = "tamabi01.csv";
    //string filePath = "001_ST.csv";
    loadCsvToMemes(filePath);
    
    maxParticles = _maxParticles;
    numParticles = 0;
    friction = 0.01;
    
    pos.x = 0;
    pos.y = 0;
    
    meshA = ofSpherePrimitive(100, 50).getMesh();
    for (int i = 0; i < meshA.getVertices().size(); i++) {
        meshA.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
}

void MyMesh::resetForce(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec2f(0, 0);
    }
}

void MyMesh::addForce(int count, ofVec2f force){
    forces[count] += force;
}

void MyMesh::addDampingForce(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] -= velocitys[i] * friction;
    }
}

void MyMesh::resetOffWalls(){
    float meshSize = 0;
    float minx = meshSize;
    float miny = meshSize;
    float maxx = ofGetWidth() -meshSize;
    float maxy = ofGetHeight() -meshSize;
    
    for(int i = 0; i < positions.size(); i++){
        if (positions[i].x > maxx){
            //positions[i].x = minx;
            positions[i].x --;
        }
        if (positions[i].y > maxy){
            //positions[i].y = miny;
            positions[i].x --;
        }
        if (positions[i].x < minx){
            //positions[i].x = maxx;
            positions[i].x  ++;
        }
        if (positions[i].y < miny){
            //positions[i].y = maxy;
            positions[i].x ++;
        }
    }
}

void MyMesh::updatePos(){
    for(int i = 0; i < positions.size(); i++){
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
    }
}

void MyMesh::update(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec2f(0, 0);
        forces[i] -= velocitys[i] * friction;
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
    }
    
}




void MyMesh::draw(){
    //頂点の数だけ繰り返し
    for (int i = 0; i < meshA.getVertices().size(); i++) {
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
    }
    
    ofPushMatrix();
    for (int i = 0; i < positions.size(); i++) {
        ofTranslate(positions[i].x, positions[i].y);
    }
    meshA.draw();
    ofPopMatrix();
}


//--------------------------------------------------------------
void MyMesh::loadCsvToMemes(string filePath){
    ofFile file(filePath);
    
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }
    
    ofBuffer buffer(file);
    
    //データをVector(配列)に読み込む
    //CSVファイルを読み込んで、1行ごとに配列linesの要素として読み込む
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        vector<string> data = ofSplitString(line, ",");
        if (data.size()>=6) {
            
            Meme meme;
            meme.user_id = data[0];
            meme.zone_data = data[1];
            meme.zone_focus = ofToFloat(data[3]);
            meme.zone_calm = ofToFloat(data[4]);
            meme.zone_posture = ofToFloat(data[5]);
            
            memes.push_back(meme);
            
            if(it == buffer.getLines().begin()){
                max_focus = min_focus = meme.zone_focus;
                max_calm = min_calm = meme.zone_calm;
                max_posture  = min_posture = meme.zone_posture;
                
            }
            else{
                //データをひとつずつ比較しながら最小値最大値を調べる
                max_focus = (meme.zone_focus > max_focus) ? meme.zone_focus : max_focus;
                min_focus = (meme.zone_focus < min_focus) ? meme.zone_focus : min_focus;
                max_calm = (meme.zone_calm > max_calm) ? meme.zone_calm : max_calm;
                min_calm = (meme.zone_calm < min_calm) ? meme.zone_calm : min_calm;
                max_posture = (meme.zone_posture > max_posture) ? meme.zone_posture : max_posture;
                min_posture = (meme.zone_posture < min_posture) ? meme.zone_posture : min_posture;
                
            }
            
        }
    }
}









