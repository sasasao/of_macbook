//
//  Particle.cpp
//  vj3
//
//  Created by 森川沙紀 on 2017/07/28.
//
//

#include "Particle.hpp"
void Particle::setup(ofVec2f _position, ofVec2f _velocity){
    // 位置を設定
    position = _position;
    // 初期速度を設定
    velocity = _velocity;
}

void Particle::resetForce(){
    force.set(0, 0);
}

void Particle::addForce(ofVec2f _force){
    force = _force;
}

void Particle::updateForce(){
    force -= velocity * friction;
}

void Particle::updatePos(){
    velocity += force;
    position += velocity;
}

void Particle::checkBounds(float xmin, float ymin, float xmax, float ymax){
    // 画面の端でバウンドする
    if (position.x < xmin || position.x > xmax) {
        velocity.x *= -1;
    }
    if (position.y < ymin || position.y > ymax) {
        velocity.y *= -1;
    }
    
    // 枠内に収める
    if (position.x < xmin) {
        position.x = xmin + (xmin - position.x);
    }
    if (position.x > xmax) {
        position.x = xmax - (position.x - xmax);
    }
    if (position.y < ymin) {
        position.y = ymin + (ymin - position.y);
    }
    if (position.y > ymax) {
        position.y = ymax - (position.y - ymax);
    }
}

// 描画
void Particle::draw(){
//    ofSetHexColor(0x3399cc);
    ofCircle(position, radius);
}
