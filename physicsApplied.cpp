#include "stdafx.h"

void physicsApplied::update(){
    velY += Gravity;
    //add acceleration to velocity
    velX += accelX;
    velY += accelY;
    //add velocity to position
    x += velX;
    y += velY;
    //zero out velocity
    accelX = 0;
    accelY = 0;
    if(abs(velX) < 0.001) velX = 0;
}

void physicsApplied::applyForce(float fx, float fy){
    //takes changes velocity based on forces
    accelX += (fx/mass);
    accelY += (fy/mass);
}

