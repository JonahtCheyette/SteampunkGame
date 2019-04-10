#pragma once
#include "stdafx.h"

class Crate : public physicsApplied {
public:
    Crate(float x, float y, float w, float h, SDL_Renderer* renderer, Draw draw, float mass);
    void collide(physicsApplied &a);
    void doFriction();
    //the crate's coefficient of friction
    float coeff;
    //overlap of either the x or y for kinematic collisions
    float overlap;
    SDL_Texture* texture;
};
