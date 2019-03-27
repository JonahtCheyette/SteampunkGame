#pragma once
#include "stdafx.h"

class physicsApplied {
public:
    void update();
    void applyForce(float fx, float fy);
    void inelasticCollide(physicsApplied &a, bool xDir);
    //position, velocity, acceleration, mass, and max speeds (not initialized in this class, but for every child class to decide what to initialize these to)
    Object::AABB hitbox;
    float x, y;
    float initX, initY;
    float friction;
    bool airborne;
    float velX, velY;
    float accelX, accelY;
    float mass;
    float maxXSpeed, maxYSpeed;
};
