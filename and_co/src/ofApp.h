#pragma once

#include "ofMain.h"
#include "ofxPDF.h"
#include "ofxEasyFft.h"
#include "ofxLeapMotion2.h"
#include "ofxPostGlitch.h"

#include "Particle.h"
#include "Txt.h"

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
	
	float w, h;
	float m = 60;
	int fps = 60;
	ofColor fc = 255, bc = 0;
	int pc = 255;
	Boolean isStop = false, first = true;
	int t = 0, st = 0, n = 0, d = 0, end = 0, tt = 0;
	int flag = 0;
	int space = 40, gw, gh;
	vector<vector<float> > tmps;
	vector<ofPoint> grid;
	
	ofxPDF pdf;
	ofxPDF mid;
	ofxPDF light;
	vector<vector<ofPath> > txtPath;
	
	ofxEasyFft fft;
	ofxEasyFft norFFT;
	void fftUpdate();
	void normalize(vector<float>& data);
	vector<float> wave;
	vector<float> buffer;
	vector<float> fftSpectrum;
	vector<float> graphMaxSound;
	float maxSound;
	
	ofxLeapMotion leap;
	vector<ofxLeapMotionSimpleHand> hands;
	vector<ofPoint> nowPos;
	vector<ofPoint> oldPos;
	
	deque<Particle> particles;
	deque<Txt> txts;

	ofFbo fbo;
	ofxPostGlitch glitch;
	
	void ofSetHSVColor(float _h, float _s, float _v, float _a = 255);
	float easeOut(float n, float s, float e, float t);
	float linear(float n, float s, float e, float t);
	
	void reset();
	
	void draw0();
	void draw1();
	void draw2();
	void draw3();
	void draw4();
	void draw5();
	void draw6();
	
	void insertWave();
	
	void drawWave(float h, float a);
	void moveGrid(float move);
	void drawRect(float alpha, float sc, Boolean snd);
	void showParticle();
	void moveParticle();
	
};
