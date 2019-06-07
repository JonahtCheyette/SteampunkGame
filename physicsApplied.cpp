#include "stdafx.h"

physicsApplied::physicsApplied(float x, float y, int w, int h, float maxSpeed, float velX, float velY, float coeff, float mass) : pos(x,y), initialPos(x,y), velocity(velX,velY), acceleration(0,0){
    hitbox.x = x;
    hitbox.y = y;
    hitbox.width = w;
    hitbox.height = h;
    this -> maxSpeed = maxSpeed;
    pushableUp = true;
    pushableDown = true;
    pushableLeft = true;
    pushableRight = true;
    this -> mass = mass;
}

void physicsApplied::update(){
    airborne = true;
    velocity.y += Gravity;
    //add acceleration to velocity
    velocity.add(acceleration);
    if(abs(velocity.x) > maxSpeed){
        if(velocity.x > 0){
            velocity.x = maxSpeed;
        } else {
            velocity.x = -maxSpeed;
        }
    }
    //add velocity to position
    pos.add(velocity);
    //zero out Acceleration
    acceleration.mult(0);
    if(abs(velocity.x) < 0.1) velocity.mult(0, 1);
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    pushableUp = true;
    pushableDown = true;
    pushableLeft = true;
    pushableRight = true;
}

void physicsApplied::applyForce(float fx, float fy){
    //takes changes velocity based on forces
    acceleration.add(fx / mass, fy / mass);
}

void physicsApplied::applyForce(Vector force){
    //takes changes velocity based on forces
    acceleration.add(Vector::div(force, mass));
}

void physicsApplied::inelasticCollide(physicsApplied &a, bool xDir){
    if(xDir){
        velocity.x = ((mass * velocity.x) + (a.mass * a.velocity.x))/(mass + a.mass);
        a.velocity.x = velocity.x;
    } else {
        velocity.y = ((mass * velocity.y) + (a.mass * a.velocity.y))/(mass + a.mass);
        a.velocity.y = velocity.y;
    }
}
