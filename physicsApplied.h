#pragma once
#include "stdafx.h"

class physicsApplied {
public:
    //physicsApplied(float x, float y, int w,int h, maxXspeed, maxYspeed, velX, velY, coeff, mass);
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
    float mass;
    //for kinematics, to deal with immovable level geometry
    bool pushableUp, pushableDown, pushableLeft, pushableRight;
    float accelX, accelY;
    float maxXSpeed, maxYSpeed;
    //coefficient of friction
    float coeff;
};
