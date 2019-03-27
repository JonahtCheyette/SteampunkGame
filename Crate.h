#pragma once
#include "stdafx.h"

class Crate : public physicsApplied {
public:
    Crate(float x, float y, float w, float h, SDL_Renderer* renderer, Draw draw, float mass);
    void collide(physicsApplied &a);
    void doFriction();
    float coeff;
    SDL_Texture* texture;
};
