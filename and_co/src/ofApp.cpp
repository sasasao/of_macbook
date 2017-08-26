#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	ofSetCircleResolution(100);
	ofBackground(bc);
	ofSetLineWidth(1);
	
	w = ofGetWidth();
	h = ofGetHeight();
	
	leap.open();

	fft.setup(16384);
	fft.setUseNormalization(false);

	pdf.load("logo.pdf");
	mid.load("txt_mid.pdf");
	light.load("txt_light.pdf");
	for (int i=0; i<mid.getNumPath(); i++){
		vector<ofPath> path;
		path.push_back(mid.getPathAt(i));
		path.push_back(light.getPathAt(i));
		txtPath.push_back(path);
	}

	fbo.allocate(w, h, GL_RGB, 4);
	glitch.setup(&fbo);
	
	gw = w / space;
	gh = (h-m) / space - 1;
	for (int i=0; i<=gh; i++) {
		for (int j=0; j<=gw; j++) {
			grid.push_back(ofPoint(j, i, 0));
		}
	}
	
	for (int i=0; i< 10; i++) {
		vector<float> v(1000);
		tmps.push_back(v);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	if (isStop) {
		st++;
		if (st == 15) {
			isStop = false;
			flag = 0;
			st = 0;
		}
	} else {
		if (floor(ofRandom(300)) == 0) {
			isStop = true;
			flag = floor(ofRandom(10))+1;
		}
	}
	
	glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, false);
	glitch.setFx(OFXPOSTGLITCH_SHAKER, false);
	glitch.setFx(OFXPOSTGLITCH_CUTSLIDER, false);
	glitch.setFx(OFXPOSTGLITCH_TWIST, false);
	glitch.setFx(OFXPOSTGLITCH_NOISE, false);
	glitch.setFx(OFXPOSTGLITCH_SLITSCAN, false);
	glitch.setFx(OFXPOSTGLITCH_SWELL, false);
	switch (flag) {
		case 3:
			glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
		break;
		case 4:
			glitch.setFx(OFXPOSTGLITCH_SHAKER, true);
		break;
		case 5:
			glitch.setFx(OFXPOSTGLITCH_CUTSLIDER, true);
		break;
		case 6:
			glitch.setFx(OFXPOSTGLITCH_TWIST, true);
		break;
		case 7:
			glitch.setFx(OFXPOSTGLITCH_NOISE, true);
		break;
		case 8:
			glitch.setFx(OFXPOSTGLITCH_SLITSCAN, true);
		break;
		case 9:
			glitch.setFx(OFXPOSTGLITCH_SWELL, true);
		break;
		case 10:
			if (st < 5) {
				glitch.setFx(OFXPOSTGLITCH_TWIST, true);
			} else if (st < 10) {
				glitch.setFx(OFXPOSTGLITCH_SLITSCAN, true);
			} else {
				glitch.setFx(OFXPOSTGLITCH_CONVERGENCE, true);
			}
		break;
	}
	if (first) {
		end = floor(ofRandom(5*fps)) + 5*fps;
		first = false;
	}
	t++;
	if (t > end) {
		reset();
		d++;
		if (d > 6) d = 0;
		t = 0;
		first = true;
	}
	
	hands = leap.getSimpleHands();
	oldPos = nowPos;
	nowPos.clear();
	if (leap.isFrameNew() && hands.size()) {
		leap.setMappingX(-300, 300, -w/2, w/2);
		leap.setMappingY(50, 450, h/2-m, -h/2+m);
//		leap.setMappingZ(-150, 150, 0.5, 1.5);
		leap.setMappingZ(-150, 150, 0.8, 1.2);
		
		for (int i=0; i<hands.size(); i++) {
			ofPoint pos = hands[i].handPos;
			nowPos.push_back(pos);
		}
		int c = oldPos.size();
		while (nowPos.size() > oldPos.size()) {
			oldPos.push_back(nowPos[c]);
			c++;
		}
	} else {
		nowPos.clear();
		oldPos.clear();
	}
	leap.markFrameAsOld();
	
	buffer = fft.getBins();
	wave = fft.getAudio();
	fft.update();
	normalize(wave);
	int numFFTbins = 32;
	float FFTpercentage = 0.14;
	float exponent = 1.0;
	float graphMaxSize = 200; //approx 10sec of history at 60fps
	float accumMaxSounds = 0;
	
	maxSound = 0;
	fftSpectrum.clear();
	
	for (int i = 0; i<numFFTbins; i++) {
		fftSpectrum.push_back(0); //init the vector for each pass
	}
	
	for (int i=0; i<fftSpectrum.size(); i++){ //for the number of columns
		float bin_size = buffer.size()*FFTpercentage;
		
		for (int j=(bin_size*((float)i/numFFTbins)); j<bin_size*((float)1/numFFTbins)+(bin_size*((float)i/numFFTbins)) ; j++) { //for each i position, average the values in i's+offset
			fftSpectrum[i] += buffer[j]*10000; //sum values in each section of buffers. Multiply by 10000 so you're not dealing with tiny numbers.
		}
		
		fftSpectrum[i] = abs((fftSpectrum[i]/(bin_size*(float)1/numFFTbins))*(1+pow(i, exponent)/numFFTbins));//Then make low frequency values weighted lower than high frequency with pow
		
		//find maximum band
		if (maxSound<fftSpectrum[i]) {
			maxSound = fftSpectrum[i];
		}
	}
	
	if(graphMaxSound.size()>graphMaxSize){ //make sure this is always running!
		graphMaxSound.erase(graphMaxSound.begin());
	}
	graphMaxSound.push_back(maxSound); //accumulate loudest sounds
	
	for (int i =0; i<graphMaxSound.size(); i++) {
		accumMaxSounds += graphMaxSound[i]; //add up all loudest sounds
	}
	
	for (int i=0; i<fftSpectrum.size(); i++){ //for the number of columns
		fftSpectrum[i] = ofMap(fftSpectrum[i], 0, accumMaxSounds/graphMaxSound.size(), 0, 1, true); //normalize each frame to 0-1
	}
	
	normalize(buffer);
}

void ofApp::normalize(vector<float>& data) {
	float maxValue = 0;
	for(int i = 0; i < data.size(); i++) {
		if(abs(data[i]) > maxValue) {
			maxValue = abs(data[i]);
		}
	}
	if (maxValue != 0) {
		for(int i = 0; i < data.size(); i++) {
			data[i] /= maxValue;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetRectMode(OF_RECTMODE_CENTER);
	if (isStop) fbo.begin();
	pc = 255;
	if (maxSound > 500) {
		fc = 0;
		bc = 255;
		pc = fabs(pc - 255);
	} else {
		fc = 255;
		bc = 0;
	}
	ofBackground(bc);
	ofPushMatrix();
	if (flag == 1) {
		ofTranslate(ofMap(ofRandom(1), 0, 1, -50, 50), 0);
	} else {
		ofTranslate(0, 0);
	}
	if (flag == 2) {
		insertWave();
	} else {
		switch (d) {
			case 0:
				draw0();
			break;
			case 1:
				draw1();
			break;
			case 2:
				draw2();
			break;
			case 3:
				draw3();
			break;
			case 4:
				draw4();
			break;
			case 5:
				draw5();
			break;
			case 6:
				draw6();
			break;
		}
	}
	
	for (int i=0; i<nowPos.size(); i++) {
		float sp = sqrt(pow((nowPos[i].x-oldPos[i].x), 2) + pow((nowPos[i].y-oldPos[i].y), 2));
		if (sp > 20) {
			int max = floor(ofRandom(10)) + 10;
			if (t < 10*fps || t > 60*fps) max = floor(ofRandom(5)) + 5;
			for (int j=0; j<max; j++) {
				txts.push_back(Txt(txtPath[tt][floor(ofRandom(2))], atan2(nowPos[i].y-oldPos[i].y, nowPos[i].x-oldPos[i].x), nowPos[i], sp+ofRandom(10)-5, nowPos[i].z-oldPos[i].z+1));
//				txts.push_back(Txt(txtPath[tt][floor(ofRandom(2))], atan2(nowPos[i].y-oldPos[i].y, nowPos[i].x-oldPos[i].x), ofPoint(nowPos[i].x - (nowPos[i].x-oldPos[i].x)*ofRandom(1), nowPos[i].y - (nowPos[i].y-oldPos[i].y)*ofRandom(1)), sp+ofRandom(10)-5, nowPos[i].z-oldPos[i].z+1));
				tt++;
				if (tt >= txtPath.size()) tt = 0;
			}
		}
	}
	for (int i=txts.size()-1; i>=0; i--) {
		txts[i].move();
		if (txts[i].isDead) txts.erase(txts.begin()+i);
	}
	
	if (isStop) {
		ofPushMatrix();
		ofTranslate(w/2, h/2);
		pdf.getPathAt(0).setFillColor(ofColor(pc));
		pdf.draw();
		ofPopMatrix();
	}
	
	ofSetColor(bc);
	ofFill();
	ofDrawRectangle(w/2, 30, w, m);
	ofDrawRectangle(w/2, h-30, w, m);
	
	ofPopMatrix();
	
	if (isStop) {
		fbo.end();
		
		ofSetRectMode(OF_RECTMODE_CORNER);
		glitch.generateFx();
		ofSetColor(255);
		fbo.draw(0, 0);
	}
}

void ofApp::reset() {
	t = 0;
	n = 0;
	for (int i=0; i<tmps.size(); i++) {
		tmps[i].clear();
	}
}

void ofApp::draw0() {
	pc = fabs(pc - 255);
	float tm = 20;
	ofPushMatrix();
	ofTranslate(w/2, h/2);
	
	drawWave(480, 1);
	
	ofSetColor(fc);
	ofNoFill();
	float r, fw, fh = 720;
	for (int i=0; i<360; i++) {
		r = (i/2.0+90+n/5)*PI/180;
		fw = -ofMap(buffer[i*2], 0, 1, 1, 960);
		ofDrawLine(cos(r) * fh, sin(r) * fh, cos(r) * (fh + fw), sin(r) * (fh + fw));
		r = (i/2.0-90+n/5)*PI/180;
		fw = -ofMap(buffer[i*2+1], 0, 1, 1, 960);
		ofDrawLine(cos(r) * fh, sin(r) * fh, cos(r) * (fh + fw), sin(r) * (fh + fw));
	}
	ofPopMatrix();
	
	ofPushMatrix();
	if (n < tm) {
		ofTranslate((w-pdf.getWidth())/2, (h-pdf.getHeight())/2, (tm-n)*100);
	} else {
		ofTranslate((w-pdf.getWidth())/2, (h-pdf.getHeight())/2, 0);
	}
	ofPopMatrix();
	n++;
}

void ofApp::draw1(){
	float tm = 30;
	
	if (n == 0) {
		while (tmps[0].size() < 75) {
			int nn = floor(ofRandom(360));
			Boolean in = true;
			for (int i=0; i<tmps[0].size(); i++) {
				if (nn == tmps[0][i]) {
					in = false;
					break;
				}
			}
			if (in) {
				tmps[0].push_back(nn);
			}
		}
	}
	
	ofPushMatrix();
	ofTranslate(w/2, h/2);
	float r, fw, fh = 720;
	if (n < tm) {
		drawWave(480, 1-n/tm);
		
		ofSetColor(fc);
		ofNoFill();
		for (int i=0; i<tmps[0].size(); i++) {
			if (i < 50) {
				r = (tmps[0][i]/2+90)*PI/180;
				fw = -ofMap(buffer[i*2], 0, 1, 1, h);
				ofDrawLine((i*space - w/2 - cos(r)*fh)*n/tm + cos(r)*fh,
					   (-h/2+m - sin(r)*fh)*n/tm + sin(r)*fh,
					   (i*space - w/2 - cos(r)*(fh + fw))*n/tm + cos(r)*(fh + fw),
					   (-h/2+m-fw - sin(r)*(fh + fw))*n/tm + sin(r)*(fh + fw));
				
				r = (tmps[0][i]/2-90)*PI/180;
				fw = -ofMap(buffer[i*2+1], 0, 1, 1, h);
				ofDrawLine(((50-i)*space - w/2 - cos(r)*fh)*n/tm + cos(r)*fh,
					   (h/2-m - sin(r)*fh)*n/tm + sin(r)*fh,
					   ((50-i)*space - w/2 - cos(r)*(fh + fw))*n/tm + cos(r)*(fh + fw),
					   (h/2-m+fw - sin(r)*(fh + fw))*n/tm + sin(r)*(fh + fw));
			} else {
				r = (tmps[0][i]/2+90)*PI/180;
				fw = -ofMap(buffer[i*2], 0, 1, 1, w);
				ofDrawLine((-w/2 - cos(r)*fh)*n/tm + cos(r)*fh,
					   ((i-50)*space - h/2+m - sin(r)*fh)*n/tm + sin(r)*fh,
					   (-w/2-fw - cos(r)*(fh + fw))*n/tm + cos(r)*(fh + fw),
					   ((i-50)*space - h/2+m - sin(r)*(fh + fw))*n/tm + sin(r)*(fh + fw));
				
				r = (tmps[0][i]/2-90)*PI/180;
				fw = -ofMap(buffer[i*2+1], 0, 1, 1, w);
				ofDrawLine((w/2 - cos(r)*fh)*n/tm + cos(r)*fh,
					   ((tmps[0].size()-1 - i)*space - h/2+m - sin(r)*fh)*n/tm + sin(r)*fh,
					   (w/2+fw - cos(r)*(fh + fw))*n/tm + cos(r)*(fh + fw),
					   ((tmps[0].size()-1 - i)*space - h/2+m - sin(r)*(fh + fw))*n/tm + sin(r)*(fh + fw));
			}
		}
	} else {
		ofSetColor(fc);
		ofNoFill();
		for (int i=0; i<tmps[0].size(); i++) {
			if (i < 50) {
				fw = -ofMap(buffer[i*2], 0, 1, 1, h);
				ofDrawLine(i*space - w/2, -h/2+m, i*space - w/2, -h/2+m - fw);
				
				fw = -ofMap(buffer[i*2+1], 0, 1, 1, h);
				ofDrawLine((50-i)*space - w/2, h/2-m, (50-i)*space - w/2, h/2-m + fw);
			} else {
				fw = -ofMap(buffer[i*2], 0, 1, 1, w);
				ofDrawLine(-w/2, (i-50)*space - h/2+m, -w/2 - fw, (i-50)*space - h/2+m);
				
				fw = -ofMap(buffer[i*2+1], 0, 1, 1, w);
				ofDrawLine(w/2, (tmps[0].size()-1 - i)*space - h/2+m, w/2 + fw, (tmps[0].size()-1 - i)*space - h/2+m);
			}
		}
	}
	ofPopMatrix();
	
	ofPushMatrix();
	ofTranslate((w-pdf.getWidth())/2, (h-pdf.getHeight())/2);
	ofPopMatrix();
	
	n++;
}

void ofApp::draw2() {
	float tm[2] = {30, 40};
	float rot;
	
	if (n < tm[0]) {
		ofSetColor(fc);
		ofNoFill();
		float fw0, fw1;
		for (int i=0; i<75; i++) {
			if (i < 50) {
				if (i % 2 == 0) {
					fw0 = -ofMap(buffer[i*2], 0, 1, 1+n/tm[0]*(h-1), h);
					fw1 = -ofMap(buffer[i*2], 0, 1, 1*(1-n/tm[0]), h*(1-n/tm[0]));
				} else {
					fw0 = -ofMap(buffer[i*2], 0, 1, 1*(1-n/tm[0]), h*(1-n/tm[0]));
					fw1 = -ofMap(buffer[i*2], 0, 1, 1+n/tm[0]*(h-1), h);
				}
				ofDrawLine(i*space, m, i*space, m-fw0);
				ofDrawLine((50-i)*space, h-m, (50-i)*space, h-m + fw1);
			} else {
				if (i % 2 == 0) {
					fw0 = -ofMap(buffer[i*2], 0, 1, 1+n/tm[0]*(w-1), w);
					fw1 = -ofMap(buffer[i*2], 0, 1, 1*(1-n/tm[0]), w*(1-n/tm[0]));
				} else {
					fw0 = -ofMap(buffer[i*2], 0, 1, 1*(1-n/tm[0]), w*(1-n/tm[0]));
					fw1 = -ofMap(buffer[i*2], 0, 1, 1+n/tm[0]*(w-1), w);
				}
				ofDrawLine(0, (i-50)*space+m, -fw0, (i-50)*space+m);
				ofDrawLine(w, (75-1 - i)*space+m, w + fw1, (75-1 - i)*space+m);
			}
		}
	} else if (n < tm[1]) {
		moveGrid(0);
	} else {
		moveGrid(1);
	}
	n++;
}

void ofApp::draw3() {
	float tm[2] = {30, 60};
	if (n < tm[0]) {
		moveGrid(1 - n/tm[0]);
	} else if (n < tm[1]) {
		drawRect((n-tm[0])/tm[1], 1-(n-tm[0])/(tm[1]-tm[0])*0.7, false);
	} else {
		drawRect(0, 0.3, true);
	}
	n++;
}

void ofApp::draw4() {
	float tm[5] = {30, 75, 135, 140, 180};
	if (n < tm[0]) {
		drawRect(n/tm[0], 0.3, true);
	} else if (n < tm[1]) {
		ofSetColor(fc);
		ofFill();
		for (int i=0; i<grid.size()-gw; i++) {
			ofPushMatrix();
			ofTranslate((grid[i].x*space-space/2 - w/2)*(1-(n-tm[0])/(tm[1]-tm[0])) + w/2,
						((grid[i].y*space-space/2+m+space)-h/2)*(1-(n-tm[0])/(tm[1]-tm[0])) + h/2);
			ofRotate(n*i*3+1);
			ofDrawRectangle(0, 0, space*0.3*(1-(n-tm[0])/(tm[1]-tm[0]))*ofMap(buffer[i%200], 0, 1, 1, 5), space*0.3*(1-(n-tm[0])/(tm[1]-tm[0]))*ofMap(buffer[i%200], 0, 1, 1, 5));
			ofPopMatrix();
		}
	} else if (n < tm[2]) {
		ofSetColor(fc, 255*(1-(floor((n-tm[1])/30)+1)/3));
		ofFill();
		for (int i=0; i<grid.size()-gw; i++) {
			ofPushMatrix();
			ofTranslate((grid[i].x*space-space/2 - w/2)*(1-float((n-int(tm[1]))%30)/30) + w/2,
						((grid[i].y*space-space/2+m+space)-h/2)*(1-float((n-int(tm[1]))%30)/30) + h/2);
			ofRotate(n*i*3+1);
			ofDrawRectangle(0, 0, space*0.3*(1-float((n-int(tm[1]))%30)/30)*ofMap(buffer[i%200], 0, 1, 1, 5), space*0.3*(1-float((n-int(tm[1]))%30)/30)*ofMap(buffer[i%200], 0, 1, 1, 5));
			ofPopMatrix();
		}
	} else if (n < tm[3]) {
		for (int i=0; i<1000; i++) {
			particles.push_back(Particle(ofRandom(360)*PI/180, ofRandom(30)+20));
		}
		ofPushMatrix();
		ofTranslate(w/2, h/2);
		for (int i=particles.size()-1; i>=0; i--) {
			particles[i].draw(MIN(5, fabs(ofMap(buffer[i*10], 0, 1, 1, 5))), fc);
			if (particles[i].isDead) particles.erase(particles.begin()+i);
		}
		ofPopMatrix();
	} else if (n < tm[4]) {
		ofPushMatrix();
		ofTranslate(w/2, h/2);
		for (int i=particles.size()-1; i>=0; i--) {
			particles[i].draw(MIN(5, fabs(ofMap(buffer[i*10], 0, 1, 1, 5))), fc);
			if (particles[i].isDead) particles.erase(particles.begin()+i);
		}
		ofPopMatrix();
	} else {
		showParticle();
		moveParticle();
	}
	n++;
}

void ofApp::draw5() {
	showParticle();
	moveParticle();
	n++;
}

void ofApp::draw6() {
	float tm[3] = {60, 120, float(end-30)};
	ofPushMatrix();
	ofTranslate(w/2, h/2);
	pc = fabs(pc - 255);
	if (n < tm[0]) {
		pc = fabs(pc - 255);		
	} else if(n < tm[1]) {
		drawWave(480*(n-tm[0])/(tm[1]-tm[0]), 1);
	} else if(n < tm[2]) {
		drawWave(480, 1);
		if (maxSound > 200) {
			for (int i=0; i<180; i++) {
				particles.push_back(Particle((i/2.0+90+n*20)*PI/180, w/2/60));
				particles.push_back(Particle((i/2.0-90+n*20)*PI/180, w/2/60));
			}
		}
		for (int i=particles.size()-1; i>=0; i--) {
			particles[i].draw(1, fc);
			if (particles[i].isDead) particles.erase(particles.begin()+i);
		}
	} else {
		if (n == tm[2]) particles.clear();
		float r, fh = 720*MIN(1, (n-tm[2])/30);
		drawWave(480, 1);
		ofSetColor(fc);
		ofNoFill();
		for (int i=0; i<360; i++) {
			r = (i/2.0+90+n/5)*PI/180;
			ofDrawCircle(cos(r) * fh, sin(r) * fh, 1);
			r = (i/2.0-90+n/5)*PI/180;
			ofDrawCircle(cos(r) * fh, sin(r) * fh, 1);
		}
	}
	ofPopMatrix();
	if (n < tm[1]) moveParticle();
	n++;
}

void ofApp::drawWave(float h, float a) {
	float r, w;
	int len = 256;
	for (int i=0; i<4; i++) {
		ofSetColor(fc, (i+1)*255.0/6*a);
		ofFill();
		ofBeginShape();
		for (int j=i*len; j<(i+1)*len; j++) {
			r = (360.0/len*j+i*45)*PI/180;
			w = 1 + wave[j];
			ofCurveVertex(cos(r) * (h-i*h/8)  * w, sin(r) * (h-i*h/8) * w);
			if (j == i*len || j == (i+1)*len - 1) ofCurveVertex(cos(r) * (h-i*h/8)  * w, sin(r) * (h-i*h/8) * w);
		}
		ofEndShape(true);
	}
}

void ofApp::moveGrid(float move) {
	float x = 0, y = 0, z = 0;
	ofSetColor(fc);
	ofNoFill();
	for (int i=0; i<grid.size(); i++) {
		x = cos(atan2(grid[i].y*space - h/2, grid[i].x*space - w/2))*buffer[i]*500*move;
		y = sin(atan2(grid[i].y*space - h/2, grid[i].x*space - w/2))*buffer[i+500]*1000*move;
		z = buffer[i+1000]*100*move;
		if (i % (gw+1) == 0) ofBeginShape();
		ofVertex(grid[i].x*space + x, grid[i].y*space+m + y, z);
		if (i % (gw+1) == gw) ofEndShape();
	}
	for (int j=0; j<=gw; j++) {
		ofBeginShape();
		for (int i=0; i<grid.size(); i++) {
			x = cos(atan2(grid[i].y*space - h/2, grid[i].x*space - w/2))*buffer[i]*500*move;
			y = sin(atan2(grid[i].y*space - h/2, grid[i].x*space - w/2))*buffer[i+500]*1000*move;
			z = buffer[i+1000]*100*move;
			if (i%(gw+1) == j) ofVertex(grid[i].x*space + x, grid[i].y*space+m + y, z);
		}
		ofEndShape();
	}
}

void ofApp::drawRect(float alpha, float sc, Boolean snd) {
	for (int i=0; i<grid.size()-gw; i++) {
		if (snd) {
			ofPushMatrix();
			ofTranslate(grid[i].x*space-space/2, grid[i].y*space-space/2+m+space);
			ofRotate(n*i*3+1);
			ofSetColor(fc);
			ofNoFill();
			ofDrawRectangle(0, 0, space*sc*ofMap(buffer[i%200], 0, 1, 1, 5), space*sc*ofMap(buffer[i%200], 0, 1, 1, 5));
			ofSetColor(fc, 255*alpha);
			ofFill();
			ofDrawRectangle(0, 0, space*sc*ofMap(buffer[i%200], 0, 1, 1, 5), space*sc*ofMap(buffer[i%200], 0, 1, 1, 5));
			ofPopMatrix();
		} else {
			ofSetColor(fc);
			ofNoFill();
			ofDrawRectangle(grid[i].x*space-space/2, grid[i].y*space-space/2+m+space, space*sc, space*sc);
			ofSetColor(fc, 255*alpha);
			ofFill();
			ofDrawRectangle(grid[i].x*space-space/2, grid[i].y*space-space/2+m+space, space*sc, space*sc);
		}
	}
}

void ofApp::showParticle() {
	for (int i=0; i<MIN(100, floor(maxSound/5)); i++) {
		particles.push_back(Particle((n*(i+1)+20)*PI/180, MIN(100, ofMap(buffer[i*10], 0, 1, 5, 20))));
	}
}

void ofApp::moveParticle() {
	ofPushMatrix();
	ofTranslate(w/2, h/2);
	for (int i=particles.size()-1; i>=0; i--) {
		particles[i].draw(MIN(5, fabs(ofMap(buffer[i*10], 0, 1, 1, 5))), fc);
		if (particles[i].isDead) particles.erase(particles.begin()+i);
	}
	ofPopMatrix();
}

void ofApp::insertWave() {
	ofSetColor(fc);
	ofNoFill();
	for (int i=0; i<(h-m*2)/20; i++) {
		ofBeginShape();
		for (int j=0; j<=w/20; j++) {
			ofCurveVertex(j*20, (h-m) - i*20 - ofMap(buffer[(j*2+st*2+i*2)%500], 0, 1, 1, 160-i*3));
			if (j ==0 || j == w/20) ofCurveVertex(j*20, (h-m) - i*20 - ofMap(buffer[(j*2+st*2+i*2)%500], 0, 1, 1, 160-i*3));
		}
		ofEndShape();
	}
}

void ofApp::ofSetHSVColor(float _h, float _s, float _v, float _a) {
	float s = (float)_s/100, v = (float)_v/100;
	if (s==0) {
		ofSetColor(255*v, 255*v, 255*v, _a);
		return;
	}
	float r,g,b;
	int hi = (int)(floor((double)_h/60))%6;
	float f = (float)_h/60-(float)hi;
	float p = v*(1-s);
	float q = v*(1-f*s);
	float t = v*(1-(1-f)*s);
	switch (hi) {
		case 0:
			r=v;
			g=t;
			b=p;
			break;
		case 1:
			r=q;
			g=v;
			b=p;
			break;
		case 2:
			r=p;
			g=v;
			b=t;
			break;
		case 3:
			r=p;
			g=q;
			b=v;
			break;
		case 4:
			r=t;
			g=p;
			b=v;
			break;
		case 5:
			r=v;
			g=p;
			b=q;
			break;
		default:
			break;
	}
	ofSetColor(255*r, 255*g, 255*b, _a);
}

float ofApp::easeOut(float n, float s, float e, float t) {
	float c = e - s;
	n /= t;
	n = n - 1;
	return c*(n*n*n + 1) + s;
}

float ofApp::linear(float n, float s, float e, float t) {
	return (e-s)*n/t + s;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7') {
		reset();
		particles.clear();
	}
	if (key == 'q' || key == 'w' || key == 'e' || key == 'r' || key == 't' || key == 'y' || key == 'u' || key == 'i' || key == 'o' || key == 'p') {
		isStop = true;
	}
	switch (key) {
		case '1':
			d = 0;
		break;
		case '2':
			d = 1;
		break;
		case '3':
			d = 2;
		break;
		case '4':
			d = 3;
		break;
		case '5':
			d = 4;
		break;
		case '6':
			d = 5;
		break;
		case '7':
			d = 6;
		break;
			
		case 'q':
			flag = 1;
		break;
		case 'w':
			flag = 2;
		break;
		case 'e':
			flag = 3;
		break;
		case 'r':
			flag = 4;
		break;
		case 't':
			flag = 5;
		break;
		case 'y':
			flag = 6;
		break;
		case 'u':
			flag = 7;
		break;
		case 'i':
			flag = 8;
		break;
		case 'o':
			flag = 9;
		break;
		case 'p':
			flag = 10;
		break;
	}
	
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
