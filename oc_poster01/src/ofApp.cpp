#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    currentIndex = 0;

    
    //string filePath = "morse.csv";
    string filePath = "meme_sample.csv";
    
    font.load("frabk.ttf", 122);
    ofFile file(filePath);
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }
    ofBuffer buffer(file);
    
    memes = *new vector <Meme>;
    
    
    //Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        Meme meme = *new Meme();
        vector<string> data = ofSplitString(line, ",");
        
        meme.user_id = data[0];
        meme.zone_date = data[1];
        meme.zone_focus = ofToFloat(data[2]);
        meme.zone_calm = ofToFloat(data[3]);
        meme.zone_posture = ofToFloat(data[4]);
        
        memes.push_back(meme);
    }
    
    cout << "格納されたmemeオブジェクトの個数は" << memes.size() << endl;
    cout << "---------------------------------";
    
    //Load our Morse code sounds
    player.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    //Update our MorseCodePlayer with the app
    player.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i=0; i<10; i++) {
        Meme meme = memes.get(i);
        cout << meme.user_id << ":" << meme.zone_focus << endl;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
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
