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
    pushableUp = true;
    pushableDown = true;
    pushableLeft = true;
    pushableRight = true;
}

void Crate::collide(physicsApplied &a){
    if (a.x + a.hitbox.width / 2 > (x - hitbox.width / 2) && a.x - a.hitbox.width / 2 < (x + hitbox.width / 2) && a.y + a.hitbox.height / 2 > (y - hitbox.height / 2) && a.y - a.hitbox.height / 2 < (y + hitbox.height / 2)) {
        a.friction = coeff;
        if ((a.y + a.hitbox.height / 2 + velY) <= (y - hitbox.height / 2 + a.velY)) {
            overlap = abs((a.y + a.hitbox.height / 2) - (y - hitbox.height / 2));
            if(a.pushableUp && pushableDown){
                overlap /= (velY + a.velY);
                a.y -= (overlap * a.velY);
                y += (overlap * velY);
            } else if (!a.pushableUp) {
                y += abs(overlap);
                pushableUp = false;
            } else {
                a.y -= abs(overlap);
                a.pushableDown = false;
            }
            if(a.velY >= 0){
                a.velY = 0;
                a.airborne = false;
                a.friction = friction;
            }
        } else if ((a.y - a.hitbox.height / 2 + velY) >= (y + hitbox.height / 2 + a.velY)){
            overlap = abs((a.y - a.hitbox.height / 2) - (y + hitbox.height / 2));
            if(a.pushableDown && pushableUp){
                overlap /= (abs(velY) + abs(a.velY));
                a.y += abs(overlap * a.velY);
                y -= abs(overlap * velY);
            } else if (!a.pushableDown) {
                y -= abs(overlap);
                pushableDown = false;
            } else {
                a.y += abs(overlap);
                a.pushableUp = false;
            }
            inelasticCollide(a, false);
        } else if ((a.x - a.hitbox.width / 2 + velX) >= (x + hitbox.width / 2 + a.velX - 0.01)){
            overlap = abs((a.x - a.hitbox.width / 2) - (x + hitbox.width / 2));
            if(a.pushableRight && pushableLeft){
                overlap /= (abs(velX) + abs(a.velX));
                a.x += abs(overlap * a.velX);
                x -= abs(overlap * velX);
            } else if (!a.pushableRight) {
                x -= abs(overlap);
                pushableRight = false;
            } else {
                a.x += abs(overlap);
                a.pushableLeft = false;
            }
            inelasticCollide(a, true);
        } else {
            overlap = abs(abs(a.x - x) - ((a.hitbox.width + hitbox.width) / 2));
            if(a.pushableLeft && pushableRight){
                overlap /= (abs(velX) + abs(a.velX));
                a.x -= abs(overlap * a.velX);
                x += abs(overlap * velX);
            } else if (!a.pushableLeft){
                x += abs(overlap);
                pushableLeft = false;
            } else {
                a.x -= abs(overlap);
                a.pushableRight = false;
            }
            inelasticCollide(a, true);
        }
    }
}

void Crate::doFriction(){
    if(!airborne){
        applyForce(-1 * velX * friction * mass * Gravity, 0);
    }
}
