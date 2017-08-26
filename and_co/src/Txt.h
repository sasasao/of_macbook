//
//  Particle.h
//  eas
//
//  Created by imo on 2015/10/08.
//
//

#ifndef __eas__Txt__
#define __eas__Txt__

#include <stdio.h>
#include "ofMain.h"

class Txt {
	
public:
	
	Txt(ofPath _txt, float _dir, ofPoint pos, float _sp, float _z);
	void move();
	
	ofPath txt;
	float oriD;
	float dir, sp, x, y, z, w, h, sc;
	float c = 0;
	float tm[2] = {30, 60};
	Boolean scaling = false;
	Boolean isDead = false;
	
};

#endif /* defined(__eas__Txt__) */
