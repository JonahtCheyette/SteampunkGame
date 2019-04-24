#include "stdafx.h"

Crate::Crate(float x, float y, float w, float h, SDL_Renderer* renderer, float mass){
    this -> x = x;
    this -> y = y;
    this -> hitbox.x = x;
    this -> hitbox.y = y;
    this -> hitbox.width = w;
    this -> hitbox.height = h;
    this -> texture.load("Steampunk-Game/Assets/Images/Objects/TeenyCrate.png", renderer);
    this -> coeff = 2;
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
        if ((a.y + a.hitbox.height / 2 + velY) <= (y - hitbox.height / 2 + a.velY)) {
            a.airborne = false;
            a.friction = coeff;
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
        } else if ((a.y - a.hitbox.height / 2 + velY + 0.01) >= (y + hitbox.height / 2 + a.velY)){
            airborne = false;
            friction = a.coeff;
            overlap = abs((a.y - a.hitbox.height / 2) - (y + hitbox.height / 2));
            if(a.pushableDown && pushableUp){
                overlap /= (abs(mass) + abs(a.mass));
                a.y += abs(overlap * a.mass);
                y -= abs(overlap * mass);
                inelasticCollide(a, false);
            } else if (!a.pushableDown) {
                y -= abs(overlap);
                velY = 0;
                pushableDown = false;
            } else {
                a.y += abs(overlap);
                a.velY = 0;
                a.pushableUp = false;
            }
        } else if ((a.x - a.hitbox.width / 2 + velX) >= (x + hitbox.width / 2 + a.velX - 0.01)){
            overlap = abs((a.x - a.hitbox.width / 2) - (x + hitbox.width / 2));
            if(a.pushableRight && pushableLeft){
                overlap /= (abs(velX) + abs(a.velX));
                a.x += abs(overlap * a.velX);
                x -= abs(overlap * velX);
                inelasticCollide(a, true);
            } else if (!a.pushableRight) {
                x -= abs(overlap);
                pushableRight = false;
                velX = 0;
            } else {
                a.x += abs(overlap);
                a.pushableLeft = false;
                a.velX = 0;
            }
        } else {
            std::cout<<(a.x - a.hitbox.width / 2 + velX) - (x + hitbox.width / 2 + a.velX - 0.01)<<std::endl;
            overlap = abs(abs(a.x - x) - ((a.hitbox.width + hitbox.width) / 2));
            if(a.pushableLeft && pushableRight){
                overlap /= (abs(velX) + abs(a.velX));
                a.x -= abs(overlap * a.velX);
                x += abs(overlap * velX);
                inelasticCollide(a, true);
            } else if (!a.pushableLeft){
                x += abs(overlap);
                pushableLeft = false;
                velX = 0;
            } else {
                a.x -= abs(overlap);
                a.pushableRight = false;
                a.velX = 0;
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

void Crate::draw(Object::Camera c, SDL_Renderer* renderer){
    hitbox.x = x;
    hitbox.y = y;
    texture.render(renderer, x, y, c.x, c.y, hitbox.width, hitbox.height);
}
