//
//  Particle.cpp
//  eas
//
//  Created by imo on 2015/10/08.
//
//

#include "Particle.h"

Particle::Particle(float _dir, float _sp) {
	dir = _dir;
	sp = _sp;
	w = ofGetWidth()/2;
	h = ofGetHeight()/2-60;
}

void Particle::draw(float val, ofColor c) {
	x += cos(dir)*sp;
	y += sin(dir)*sp;
	ofSetColor(c);
	ofFill();
	ofDrawCircle(x, y, val);
	if (x < -w || x > w || y < -h || y > h) isDead = true;
}
