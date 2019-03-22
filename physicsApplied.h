#pragma once
#include "stdafx.h"

class physicsApplied {
public:
    void update();
    void applyForce(float fx, float fy);
    float x, y;
    float velX, velY;
    float accelX, accelY;
    float mass;
    float maxXSpeed, maxYSpeed;
};
