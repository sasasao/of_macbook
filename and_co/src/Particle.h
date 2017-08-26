//
//  Particle.h
//  eas
//
//  Created by imo on 2015/10/08.
//
//

#ifndef __eas__Particle__
#define __eas__Particle__

#include <stdio.h>
#include "ofMain.h"

class Particle {
	
public:
	
	Particle(float _dir, float _sp);
	void draw(float val, ofColor c);
	
	float dir, sp, x = 0, y = 0;
	float w, h;
	Boolean isDead = false;
	
};

#endif /* defined(__eas__Particle__) */
