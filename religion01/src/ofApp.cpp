#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    // FFTのサンプル数(2の累乗)を指定して初期化
    fft.setup(pow(2.0, 12.0));
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    myImage.load("1.png");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    fft.update(); // FFT更新
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    //myImage.draw(0,0, ofGetWidth()/10, ofGetHeight());
    unsigned char * pixels = myImage.getPixels();
    int w = myImage.getWidth();
    int h = myImage.getHeight();
    int alpha = 100;
    
    //画像を8ピクセル間隔でスキャン
    for (int i = 0; i < w; i+=8){
        for (int j = 0; j < h; j+=8){
            //ピクセルのRGBの値を取得
            int valueR = pixels[j*3 * w + i*3];
            int valueG = pixels[j*3 * w + i*3+1];
            int valueB = pixels[j*3 * w + i*3+2];
            //取得したRGB値をもとに、円を描画
            //取得したピクセルの明るさを、円の半径に対応させている
            ofSetColor(255, 0, 0, alpha);
            ofDrawCircle(i, j, 10*valueR/255.0);
            ofSetColor(0, 255, 0, alpha);
            ofDrawCircle(i, j, 10*valueG/255.0);
            ofSetColor(0, 0, 255, alpha);
            ofDrawCircle(i, j, 10*valueB/255.0);
        }
    }
    
            
            // float型の配列にFFT結果を格納
            vector<float> buffer;
            buffer = fft.getBins();
            
            // グラフに描画
            //ofNoFill();
            ofSetLineWidth(ofGetWidth() / float(buffer.size()) / 2.0 - 0.5);
            
            for (int i = 0; i < buffer.size(); i++) {
                float hue = ofMap(i, 0, buffer.size(), 0, 160);
                ofColor col;
                col.setHsb(hue, 255, 255);
                ofSetColor(col);
                
                
                float rx = ofMap(i, 0, buffer.size(), ofGetWidth() / 2.0, ofGetWidth());
                float lx = ofMap(i, 0, buffer.size(), ofGetWidth() / 2.0, 0);
                float y = ofMap(buffer[i], 0, 1, ofGetHeight()/2, 0) ;
                ofDrawLine(rx, ofGetHeight()/2, rx, y);
                ofDrawLine(lx, ofGetHeight()/2, lx, y);
            }
            

    
    
    //float r = buffer.size() *100;
    //ofDrawEllipse(ofGetWidth()/2, ofGetHeight()/2, r,r);
    
    
    
    
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
