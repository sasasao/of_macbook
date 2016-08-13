#include "Particles.hpp"

Particles::Particles(int _maxParticles, string filePath_meme, string filePath_first){
    
    centerPos = ofVec3f(ofRandom(-1000, 1000), ofRandom(-1000, 1000), -1000);
    
    centerVelocity = ofVec3f(ofRandom(-10, max_cadence), ofRandom(-10, max_cadence), ofRandom(-10, max_cadence));
    
    cout << min_cadence << "," << max_cadence << endl;
    
    loadCsvToMemes(filePath_meme);
    loadCsvToMemes02(filePath_first);
    
    maxParticles = _maxParticles;
    numParticles = 0;
    friction = 0.01;
    
    line_w = 100;
    line_h = 100;
    wire = 20;
    
    mesh = ofSpherePrimitive(2, wire).getMesh();
    outside = ofSpherePrimitive(2, wire).getMesh();
    mesh_line = ofSpherePrimitive(2, wire).getMesh();
    
    glPointSize(3.0);
    mesh_line.setMode(OF_PRIMITIVE_POINTS);
    
    for (int i = 0; i < mesh.getVertices().size(); i++) {
        mesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
    for (int i = 0; i < outside.getVertices().size(); i++) {
        outside.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
    for (int i = 0; i < mesh_line.getVertices().size(); i++) {
        mesh_line.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
}

void Particles::resetOffWalls(){
    float meshSize = 0;
    float minx = -1000;
    float miny = -300;
    float minz = -700;
    float maxx = 1000;
    float maxy = 300;
    float maxz = 100;
    
    if (centerPos.x > maxx || centerPos.x < minx){
        centerVelocity.x *= -1;
    }
    if (centerPos.y > maxy || centerPos.x < miny){
        centerVelocity.y *= -1;
    }

    if (centerPos.z > maxz|| centerPos.x < minz){
        centerVelocity.z *= -1;
    }

}

void Particles::updatePos(){
    centerPos += centerVelocity;
}

void Particles::draw(){
    ofPushMatrix();
    ofTranslate(centerPos);
    
    for (int i = 0; i < mesh.getVertices().size(); i++) {
        int m = ofMap(i, 0, mesh.getVertices().size(), 0, memes.size());
        int f = ofMap(i, 0, mesh.getVertices().size(), 0, firsts.size());
        Meme meme = memes[m];
        First first = firsts[f];
        
        morph_focus = ofLerp(focus, next_focus, percent);
        morph_calm = ofLerp(calm, next_calm, percent);
        morph_posture = ofLerp(posture, next_posture, percent);
        
        float posture_loc = ofMap(morph_posture, min_posture, max_posture, 0, 500);
        ofVec3f loc = mesh.getVertices()[i] / posture_loc;

        float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80,240);
        ofVec3f newLoc = loc.normalize()* noise;
        mesh.setVertex(i, newLoc);
        mesh_line.setVertex(i, newLoc*1.2);
        outside.setVertex(i, newLoc*1.2);
        
        float R = ofMap(meme.zone_focus, min_focus, max_focus, 0, 1.0);
        float G = ofMap(meme.zone_calm, min_calm, max_calm, 0, 1.0);
        float B = ofMap(meme.zone_posture, min_posture, max_posture, 0, 1.0);
        
        mesh.setColor(i, ofFloatColor(R,G,B,1));
        outside.setColor(i, ofFloatColor(1.0, 1.0, 1.0, 0.1));
        mesh_line.setColor(i, ofFloatColor(R,G,B,0.5));
    }
    
    for (int i = 0; i < positions.size(); i++) {
        int f = ofMap(i, 0, positions.size(), 0, firsts.size());
        ofTranslate(positions[i].x,
                    positions[i].y);
    }
    
    ofSetLineWidth(0.5);
    mesh.draw();
    ofDisableLighting();
    mesh_line.draw();
    ofEnableLighting();
    outside.drawWireframe();
    
    percent += 0.01;
    if(percent >= 1.0){
        index += 1;
        
        if(index == memes.size() - 1){
            
        }else {
            focus = memes[index].zone_focus;
            calm = memes[index].zone_calm;
            posture = memes[index].zone_posture;
            next_focus = memes[index+1].zone_focus;
            next_calm = memes[index+1].zone_calm;
            next_posture = memes[index+1].zone_posture;
        }
        percent = 0;
    }
    ofPopMatrix();
}


void Particles::addParticle(ofVec2f _position, ofVec2f _velocity, ofColor _color){
    colors.push_back(_color);
    
    if (positions.size() > maxParticles) {
        colors.pop_front();
    }
}

//--------------------------------------------------------------
void Particles::loadCsvToMemes(string filePath_meme){
    ofFile file_meme(filePath_meme);
    
    if(!file_meme.exists()){
        ofLogError("The file " + filePath_meme + " is missing");
    }
    
    ofBuffer buffer(file_meme);
    
    //データをVector(配列)に読み込む
    //CSVファイルを読み込んで、1行ごとに配列linesの要素として読み込む
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        vector<string> data = ofSplitString(line, ",");
        if (data.size()>=6) {
            
            Meme meme;
            meme.user_id = data[0];
            meme.zone_date = data[1];
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
//--------------------------------------------------------------
void Particles::loadCsvToMemes02(string filePath_first){
    ofFile file_first(filePath_first);
    
    if(!file_first.exists()){
        ofLogError("The file " + filePath_first + " is missing");
    }
    ofBuffer buffer(file_first);
    
    //データをVector(配列)に読み込む
    //CSVファイルを読み込んで、1行ごとに配列linesの要素として読み込む
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        vector<string> data = ofSplitString(line, ",");
        if (data.size()>=6) {
            
            First first;
            first.cadence = ofToFloat(data[10]);
            firsts.push_back(first);
            
            if(it == buffer.getLines().begin()){
                max_cadence = min_cadence = first.cadence;
            }
            else{
                //データをひとつずつ比較しながら最小値最大値を調べる
                max_cadence = (first.cadence > max_cadence) ? first.cadence : max_cadence;
                
            }
            
        }
    }
}

