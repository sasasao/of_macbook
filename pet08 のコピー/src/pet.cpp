#include "pet.hpp"

Pets::Pets(string filePath_memeA, string filePath_memeB){
    centerPos = ofVec3f(ofRandom(-1000,1000), ofRandom(-1000,1000), ofRandom(-1000,1000));
    centerVelocity = ofVec3f(ofRandom(-1,1),ofRandom(-1,1),  ofRandom(-1,1));
    
    loadCsvToMemesA(filePath_memeA);
    loadCsvToMemesB(filePath_memeB);
    
    wire_num = 20;
    mesh = ofSpherePrimitive(200, wire_num).getMesh();
    
    glPointSize(3.0);
    
    for (int i=0; i<mesh.getVertices().size(); i++) {
        mesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
    for (int i=0; i<mesh_line.getVertices().size(); i++) {
        mesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
    for (int i=0; i<mesh_point.getVertices().size(); i++) {
        mesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
}

void Pets::draw(){
    ofTranslate(centerPos);
    for (int i=0; i<mesh.getVertices().size(); i++) {
        int mA = ofMap(i, 0, mesh.getVertices().size(), 0, memesA.size());
        int mB = ofMap(i, 0, mesh.getVertices().size(), 0, memesB.size());
        
        MemeA memeA = memesA[mA];
        MemeB memeB = memesB[mB];
        
        morph_posture = ofLerp(posture, next_posture, percent);
        
        float posture_loc = ofMap(morph_posture, min_posture, max_posture, 0, 500);
        ofVec3f loc = mesh.getVertices()[i] / posture_loc;
        
        float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, 240);
        ofVec3f newLoc = loc.normalize() * noise;
        
        mesh.setVertex(i, newLoc);
        mesh_line.setVertex(i, newLoc * 1.2);
        mesh_point.setVertex(i, newLoc * 1.2);
        
        float R = ofMap(memeB.zone_focus, min_focus, max_focus, 0, 1.0);
        float G = ofMap(memeB.zone_calm, min_calm, max_calm, 0, 1.0);
        float B = ofMap(memeB.zone_posture, min_posture, max_posture, 0, 1.0);
        mesh.setColor(i, ofFloatColor(R,G,B,1));
        mesh_line.setColor(i, ofFloatColor(1.0, 1.0, 1.0, 0.1));
        mesh_point.setColor(i, ofFloatColor(R,G,B,0.5));
    }
    
    ofSetLineWidth(0.5);
    mesh.draw();
    mesh_line.draw();
    mesh_point.draw();
    
    percent += 0.01;
    if(percent >= 1.0){
        index += 1;
        
        if(index == memesB.size() - 1){
            
        }else {
            focus = memesB[index].zone_focus;
            calm = memesB[index].zone_calm;
            posture = memesB[index].zone_posture;
            next_focus = memesB[index+1].zone_focus;
            next_calm = memesB[index+1].zone_calm;
            next_posture = memesB[index+1].zone_posture;
        }
        percent = 0;
    }

}


//--------------------------------------------------------------
void Pets::loadCsvToMemesB(string filePath_memeB){
    ofFile file_memeB(filePath_memeB);
    
    if(!file_memeB.exists()){
        ofLogError("The file " + filePath_memeB + " is missing");
    }
    
    ofBuffer buffer(file_memeB);
    
    //データをVector(配列)に読み込む
    //CSVファイルを読み込んで、1行ごとに配列linesの要素として読み込む
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        vector<string> data = ofSplitString(line, ",");
        if (data.size()>=6) {
            
            MemeB memeB;
            memeB.user_id = data[0];
            memeB.zone_date = data[1];
            memeB.zone_focus = ofToFloat(data[3]);
            memeB.zone_calm = ofToFloat(data[4]);
            memeB.zone_posture = ofToFloat(data[5]);
            memesB.push_back(memeB);
            
            if(it == buffer.getLines().begin()){
                max_focus = min_focus = memeB.zone_focus;
                max_calm = min_calm = memeB.zone_calm;
                max_posture  = min_posture = memeB.zone_posture;
            }
            else{
                //データをひとつずつ比較しながら最小値最大値を調べる
                max_focus = (memeB.zone_focus > max_focus) ? memeB.zone_focus : max_focus;
                min_focus = (memeB.zone_focus < min_focus) ? memeB.zone_focus : min_focus;
                max_calm = (memeB.zone_calm > max_calm) ? memeB.zone_calm : max_calm;
                min_calm = (memeB.zone_calm < min_calm) ? memeB.zone_calm : min_calm;
                max_posture = (memeB.zone_posture > max_posture) ? memeB.zone_posture : max_posture;
                min_posture = (memeB.zone_posture < min_posture) ? memeB.zone_posture : min_posture;
            }
        }
    }
}

void Pets::loadCsvToMemesA(string filePath_memeA){
    ofFile file_memeA(filePath_memeA);
    
    if(!file_memeA.exists()){
        ofLogError("The file " + filePath_memeA + " is missing");
    }
    ofBuffer buffer(file_memeA);
    
    //データをVector(配列)に読み込む
    //CSVファイルを読み込んで、1行ごとに配列linesの要素として読み込む
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        vector<string> data = ofSplitString(line, ",");
        if (data.size()>=6) {
            
            MemeA memeA;
            memeA.cadence = ofToFloat(data[10]);
            memesA.push_back(memeA);
            
            if(it == buffer.getLines().begin()){
                max_cadence = min_cadence = memeA.cadence;
            }
            else{
                //データをひとつずつ比較しながら最小値最大値を調べる
                max_cadence = (memeA.cadence > max_cadence) ? memeA.cadence : max_cadence;
                
            }
            
        }
    }
}

