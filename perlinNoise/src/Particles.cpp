#include "Particles.hpp"

Particles::Particles(int _maxParticles){
    maxParticles = _maxParticles;
    numParticles = 0;
    friction = 0.01;
    //mesh.setMode(OF_PRIMITIVE_POINTS);
    
    mesh = ofSpherePrimitive(200, 72).getMesh();
    
    for (int i = 0; i < mesh.getVertices().size(); i++) {
        mesh.addColor(ofFloatColor(1.0, 1.0, 1.0, 1.0));
    }
}


void Particles::resetForce(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec2f(0, 0);
    }
}

void Particles::addForce(int count, ofVec2f force){
    forces[count] += force;
}

void Particles::addDampingForce(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] -= velocitys[i] * friction;
    }
}

void Particles::resetOffWalls(){
    float meshSize = 0;
    float minx = meshSize;
    float miny = meshSize;
    float maxx = ofGetWidth() -meshSize;
    float maxy = ofGetHeight() -meshSize;
    
    for(int i = 0; i < positions.size(); i++){
        if (positions[i].x > maxx){
            //positions[i].x = minx;
            positions[i].x --;
        }
        if (positions[i].y > maxy){
            //positions[i].y = miny;
            positions[i].x --;
        }
        if (positions[i].x < minx){
            //positions[i].x = maxx;
            positions[i].x  ++;
        }
        if (positions[i].y < miny){
            //positions[i].y = maxy;
            positions[i].x ++;
        }
    }
}

void Particles::updatePos(){
    for(int i = 0; i < positions.size(); i++){
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
    }
}

void Particles::update(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec2f(0, 0);
        forces[i] -= velocitys[i] * friction;
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
    }
    
}

void Particles::draw(){
    
    for (int i = 0; i < mesh.getVertices().size(); i++) {
        //頂点の位置を取得
        ofVec3f loc = mesh.getVertices()[i] / 300.0;
        //perlinノイズを生成
        float noise = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()), 0, 1, 80, 240);
        //ノイズの値で頂点位置を変更
        ofVec3f newLoc = loc.normalize()* noise;
        mesh.setVertex(i, newLoc);
        //頂点の色を設定
        float c = ofMap(ofNoise(loc.x, loc.y, loc.z, ofGetElapsedTimef()),0, 1, 0.5, 1.0);
        mesh.setColor(i, ofFloatColor(c, c, c, 1.0));
    }
    
    for (int i = 0; i < positions.size(); i++) {
        ofTranslate(positions[i].x, positions[i].y);
    }
    
    //mesh.clear();
    /*for (int i = 0; i < positions.size(); i++) {
        mesh.addVertex(ofVec3f(positions[i].x,
                               positions[i].y));
        mesh.addColor(ofFloatColor(1.0,1.0,1.0));
    }*/
    mesh.draw();
}

void Particles::addParticle(ofVec2f _position, ofVec2f _velocity, ofColor _color){
    positions.push_back(_position);
    velocitys.push_back(_velocity);
    colors.push_back(_color);
    forces.push_back(ofVec2f(0, 0));
    numParticles++;
    
    if (positions.size() > maxParticles) {
        positions.pop_front();
        colors.pop_front();
        velocitys.pop_front();
        forces.pop_front();
        numParticles--;
    }
}