#include "stdafx.h"

Crate::Crate(float x, float y, float w, float h, SDL_Renderer* renderer, Draw draw, float mass){
    this -> x = x;
    this -> y = y;
    this -> hitbox.x = x;
    this -> hitbox.y = y;
    this -> hitbox.width = w;
    this -> hitbox.height = h;
    this -> texture = draw.loadTexture("Steampunk-Game/Assets/Images/Objects/TeenyCrate.png", renderer);
    this -> coeff = 1;
    this -> mass = mass;
    this -> initX = x;
    this -> initY = y;
}

void Crate::collide(physicsApplied &a){
    if (a.x + a.hitbox.width / 2 > (x - hitbox.width / 2) && a.x - a.hitbox.width / 2 < (x + hitbox.width / 2) && a.y +  a.hitbox.height / 2 > (y - hitbox.height / 2) && a.y - a.hitbox.height / 2 < (y + hitbox.height / 2)) {
        a.friction = coeff;
        if ((a.y + a.hitbox.height / 2 - velY) <= (y - hitbox.height / 2 + a.velY)) {
            a.y = y - hitbox.height / 2 - a.hitbox.height / 2;
            if(a.velY >= 0){
                a.velY = 0;
                a.airborne = false;
                a.friction = friction;
            }
        } else if ((a.y - a.hitbox.height / 2 + velY) >= (y + hitbox.height / 2 + a.velY)){
            if(a.airborne){
                a.y = y + hitbox.height / 2 + a.hitbox.height / 2;
                a.velY = 0;
            } else {
                y = a.y - hitbox.height / 2 - a.hitbox.height / 2;
                velY = 0;
            }
        } else if ((a.x - a.hitbox.width / 2 + velX) >= (x + hitbox.width / 2 + a.velX - 0.01)){
            a.x = x + hitbox.width / 2 + a.hitbox.width / 2;
            inelasticCollide(a, true);
        } else {
            a.x = x - hitbox.width / 2 - a.hitbox.width / 2;
            inelasticCollide(a, true);
        }
    }
}

void Crate::doFriction(){
    applyForce(-1 * velX * friction * mass * Gravity,0);
}