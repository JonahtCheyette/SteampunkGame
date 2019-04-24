#pragma once
#include "stdafx.h"

class Crate : public physicsApplied {
public:
    Crate(float x, float y, float w, float h, SDL_Renderer* renderer, float mass);
    void collide(physicsApplied &a);
    void doFriction();
    void draw(Object::Camera c, SDL_Renderer* renderer);
    
private:
    //overlap of either the x or y for kinematic collisions
    float overlap;
    Sprite texture;
};
