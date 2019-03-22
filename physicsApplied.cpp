#include "stdafx.h"

void physicsApplied::update(){
    velX += accelX;
    velY += accelY;
    x += velX;
    y += velY;
    accelX = 0;
    accelY = 0;
}

void physicsApplied::applyForce(float fx, float fy){
    accelX += (fx/mass);
    accelY += (fy/mass);
}
