#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBeginSaveScreenAsPDF("text_print" + ofGetTimestampString() + " .ai");
    
    ofSetFrameRate(30);
    ofBackground(0);
    ofNoFill();
    ofSetLineWidth(0.1);
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    //dataフォルダに配置したcsvファイルの名前
    string filePath = "tamabi01.csv";
    loadCsvToMemes(filePath);
    
    //初期位置を画面の中心に
    pos.x = ofGetWidth()/2;
    pos.y = ofGetHeight()/2;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    //モーフィングの計算
    morph_focus = ofLerp(focus, next_focus,percent);

    //結果を四角形で可視化
    ofDrawRectangle(ofGetWindowWidth()/2, ofGetWindowHeight()/2, morph_focus, morph_focus);
    ofDrawBitmapString(morph_focus, ofGetWindowWidth()/2+morph_focus/2, ofGetWindowHeight()/2 + morph_focus/2+20);
    ofDrawBitmapString(memes[index].zone_date, 10, ofGetWindowHeight()-50);
    
        
    //モーフィングの割合を更新
    percent += 0.05;

    
    
    //モーフィングの割合が1になった時の処理
    if (percent >=1.0) {
        //noLoop();
        //表示するデータのインデックスを進める
        index += 1;
        
        //配列の最後に到達したら停止
        if (index == memes.size() - 1) {
            //
        } else {
            //表示するデータと、次に表示するデータを更新
            focus = memes[index].zone_focus;
            next_focus = memes[index+1].zone_focus;
            
        }
        
        //モーフィングの割合を初期化
        percent = 0;
    }
    
    if(loop){
        ofEndSaveScreenAsPDF();
        loop = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's')
        loop = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::loadCsvToMemes(string filePath){
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
            meme.zone_date = data[1];
            meme.zone_focus = ofToFloat(data[3]);
            meme.zone_calm = ofToFloat(data[4]);
            meme.zone_posture = ofToFloat(data[5]);
            memes.push_back(meme);
            
            
        }
    }
}


