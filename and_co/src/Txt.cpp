//
//  Particle.cpp
//  eas
//
//  Created by imo on 2015/10/08.
//
//

#include "Txt.h"

Txt::Txt(ofPath _txt, float _dir, ofPoint pos, float _sp, float _z) {
	txt = _txt;
	dir = _dir;
	sp = _sp;
	x = pos.x + ofRandom(50)-25;
	y = pos.y + ofRandom(50)-25;
//	x = pos.x + ofRandom(100)-50;
//	y = pos.y + ofRandom(100)-50;
	z = _z;
	if (z < 0) z = 0.8;
	sc = ofRandom(1.5) + 0.5;
	w = ofGetWidth()/2;
	h = ofGetHeight()/2;
	if (floor(ofRandom(200)) == 0) scaling = true;
}

void Txt::move() {
	ofPushMatrix();
	ofTranslate(w, h);
	if (c < tm[0]) {
		dir += PI/180;
	} else {
		dir += 3*PI/180;
		if (scaling) sc *= 1.3;
	}
	x += cos(dir)*sp;
	y += sin(dir)*sp;
	sp *= 0.98;
	sc *= z;
	ofFill();
	ofPushMatrix();
	ofTranslate(x, y);
	ofScale(sc, sc);
	if (c < tm[0]) {
		txt.setFillColor(ofColor(255));
	} else if (c < tm[1]) {
		if (!scaling) txt.setFillColor(ofColor(255, 255*(1-(c-tm[0])/(tm[1]-tm[0]))));
	} else {
		ofSetColor(ofColor(255, 0));
		isDead = true;
	}
	txt.draw(0, 0);
	ofPopMatrix();
	ofPopMatrix();
	c++;
}
