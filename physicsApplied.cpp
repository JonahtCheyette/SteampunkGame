#include "stdafx.h"

void physicsApplied::update(){
    //add acceleration to velocity
    velX += accelX;
    velY += accelY;
    //add velocity to position
    x += velX;
    y += velY;
    //zero out velocity
    accelX = 0;
    accelY = 0;
}

void physicsApplied::applyForce(float fx, float fy){
    //takes changes velocity based on forces
    accelX += (fx/mass);
    accelY += (fy/mass);
}
