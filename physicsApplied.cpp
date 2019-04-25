#include "stdafx.h"

void physicsApplied::update(){
    airborne = true;
    velY += Gravity;
    //add acceleration to velocity
    velX += accelX;
    velY += accelY;
    if(velX < -maxXSpeed){
        velX = -maxXSpeed;
    } else if (velX > maxXSpeed){
        velX = maxXSpeed;
    }
    if(velY < -maxYSpeed){
        velY = -maxYSpeed;
    } else if (velY > maxYSpeed){
        velY = maxYSpeed;
    }
    //add velocity to position
    x += velX;
    y += velY;
    //zero out Acceleration
    accelX = 0;
    accelY = 0;
    if(abs(velX) < 0.001) velX = 0;
    pushableUp = true;
    pushableDown = true;
    pushableLeft = true;
    pushableRight = true;
}

void physicsApplied::applyForce(float fx, float fy){
    //takes changes velocity based on forces
    accelX += (fx/mass);
    accelY += (fy/mass);
}

void physicsApplied::inelasticCollide(physicsApplied &a, bool xDir){
    if(xDir){
        velX = ((mass * velX) + (a.mass * a.velX))/(mass + a.mass);
        a.velX = velX;
    } else {
        velY = ((mass * velY) + (a.mass * a.velY))/(mass + a.mass);
        a.velY = velY;
    }
}
