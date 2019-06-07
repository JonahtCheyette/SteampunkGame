#include "stdafx.h"

Crate::Crate(float x, float y, float w, float h, float velX, float velY, float maxSpeed, SDL_Renderer* renderer, float mass) : physicsApplied(x, y, w, h, maxSpeed, velX, velY, 2, mass){
    this -> texture.load("Steampunk-Game/Assets/Images/Objects/TeenyCrate.png", renderer);
}

void Crate::collide(physicsApplied &a){
    if (a.pos.x + a.hitbox.width / 2 > (pos.x - hitbox.width / 2) && a.pos.x - a.hitbox.width / 2 < (pos.x + hitbox.width / 2) && a.pos.y + a.hitbox.height / 2 > (pos.y - hitbox.height / 2) && a.pos.y - a.hitbox.height / 2 < (pos.y + hitbox.height / 2)) {
        if ((a.pos.y + a.hitbox.height / 2 + velocity.y) <= (pos.y - hitbox.height / 2 + a.velocity.y)) {
            a.airborne = false;
            a.friction = coeff;
            overlap = abs((a.pos.y + a.hitbox.height / 2) - (pos.y - hitbox.height / 2));
            if(a.pushableUp && pushableDown){
                overlap /= (velocity.y + a.velocity.y);
                a.pos.y -= (overlap * a.velocity.y);
                pos.y += (overlap * velocity.y);
            } else if (!a.pushableUp) {
                pos.y += abs(overlap);
                pushableUp = false;
            } else {
                a.pos.y -= abs(overlap);
                a.pushableDown = false;
            }
            if(a.velocity.y >= 0){
                a.velocity.y = 0;
                a.airborne = false;
                a.friction = friction;
            }
        } else if ((a.pos.y - a.hitbox.height / 2 + velocity.y + 0.01) >= (pos.y + hitbox.height / 2 + a.velocity.y)){
            airborne = false;
            friction = a.coeff;
            overlap = abs((a.pos.y - a.hitbox.height / 2) - (pos.y + hitbox.height / 2));
            if(a.pushableDown && pushableUp){
                overlap /= (abs(mass) + abs(a.mass));
                a.pos.y += abs(overlap * a.mass);
                pos.y -= abs(overlap * mass);
                inelasticCollide(a, false);
            } else if (!a.pushableDown) {
                pos.y -= abs(overlap);
                velocity.y = 0;
                pushableDown = false;
            } else {
                a.pos.y += abs(overlap);
                a.velocity.y = 0;
                a.pushableUp = false;
            }
        } else if ((a.pos.x - a.hitbox.width / 2 + velocity.x) >= (pos.x + hitbox.width / 2 + a.velocity.x - 0.01)){
            overlap = abs((a.pos.x - a.hitbox.width / 2) - (pos.x + hitbox.width / 2));
            if(a.pushableRight && pushableLeft){
                overlap /= (abs(velocity.x) + abs(a.velocity.x));
                a.pos.x += abs(overlap * a.velocity.x);
                pos.x -= abs(overlap * velocity.x);
                inelasticCollide(a, true);
            } else if (!a.pushableRight) {
                pos.x -= abs(overlap);
                pushableRight = false;
                velocity.x = 0;
            } else {
                a.pos.x += abs(overlap);
                a.pushableLeft = false;
                a.velocity.x = 0;
            }
        } else {
            std::cout<<(a.pos.x - a.hitbox.width / 2 + velocity.x) - (pos.x + hitbox.width / 2 + a.velocity.x - 0.01)<<std::endl;
            overlap = abs(abs(a.pos.x - pos.x) - ((a.hitbox.width + hitbox.width) / 2));
            if(a.pushableLeft && pushableRight){
                overlap /= (abs(velocity.x) + abs(a.velocity.x));
                a.pos.x -= abs(overlap * a.velocity.x);
                pos.x += abs(overlap * velocity.x);
                inelasticCollide(a, true);
            } else if (!a.pushableLeft){
                pos.x += abs(overlap);
                pushableLeft = false;
                velocity.x = 0;
            } else {
                a.pos.x -= abs(overlap);
                a.pushableRight = false;
                a.velocity.x = 0;
            }
            inelasticCollide(a, true);
        }
    }
}

void Crate::doFriction(){
    if(!airborne){
        applyForce(-velocity.x * friction * mass * Gravity, 0);
    }
}

void Crate::draw(Object::Camera c, SDL_Renderer* renderer){
    hitbox.x = pos.x;
    hitbox.y = pos.y;
    texture.render(renderer, pos.x, pos.y, c.x, c.y, hitbox.width, hitbox.height);
}
