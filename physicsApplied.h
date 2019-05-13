#pragma once
#include "stdafx.h"

class physicsApplied {
public:
    physicsApplied(float x, float y, int w, int h, float maxSpeed, float velX, float velY, float coeff, float mass);
    void update();
    void applyForce(float fx, float fy);
    void applyForce(Vector force);
    void inelasticCollide(physicsApplied &a, bool xDir);
    
    //position, velocity, acceleration, mass, and max speeds (not initialized in this class, but for every child class to decide what to initialize these to)
    Object::AABB hitbox;
    Vector pos;
    Vector initialPos;
    float friction;
    bool airborne;
    Vector velocity;
    float mass;
    //for kinematics, to deal with immovable level geometry
    bool pushableUp, pushableDown, pushableLeft, pushableRight;
    Vector acceleration;
    float maxSpeed;
    //coefficient of friction
    float coeff;
};
