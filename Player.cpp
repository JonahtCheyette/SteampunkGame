#include "stdafx.h"

Player::Player(SDL_Renderer* renderer) : physicsApplied(0, 0, 88, 64, 12, 0, 0, 1.5, 20), generalGrapple(0,0), grappleHead(0,0), target(0,0) {
    moveForce = 5;
    
    //vars for grapple movement
    distance = 0;
    pDistance = 0;
    selectedHook = 0;
    
    airborne = false;
    grappling = false;
    rope = false;
    hookState = 0;
    changedHook = false;
    clicked = false;
    player.load("Steampunk-Game/Assets/Images/Characters/Tpose.png", renderer);
    hitbox.width = player.getWidth();
    hitbox.height = player.getHeight();
}

void Player::move(SDL_Event& e, Level l, Object::Camera c, std::vector<Object::Tile> tileGrid, int &which, int maxLevel) {
    //key presses
    SDL_PollEvent(&e);
    event.keyboard_state_array = SDL_GetKeyboardState(NULL);
    if (hookState != 2) {
        if (event.keyboard_state_array[SDL_SCANCODE_A]) applyForce(-1 * moveForce, 0);
        if (event.keyboard_state_array[SDL_SCANCODE_D]) applyForce(moveForce, 0);
    }
    
    if(!airborne){
        if (event.keyboard_state_array[SDL_SCANCODE_W]){
            applyForce(0, -250);
        }
        if (event.keyboard_state_array[SDL_SCANCODE_UP] && sqrt(pow(l.end.x - pos.x,2) + pow(l.end.y - pos.y,2)) < 20){
            which ++;
            if(which == maxLevel){
                std::cout<<"YOU WIN!"<<std::endl;
                which = maxLevel - 1;
            }
        }
    }
    if(!(event.keyboard_state_array[SDL_SCANCODE_LEFT] && event.keyboard_state_array[SDL_SCANCODE_RIGHT]) && l.hookList.size() > 0){
        if (event.keyboard_state_array[SDL_SCANCODE_LEFT]) changeHooks(l.hookList, -1, c);
        if (event.keyboard_state_array[SDL_SCANCODE_RIGHT]) changeHooks(l.hookList, 1, c);
    }
    
    if (event.keyboard_state_array[SDL_SCANCODE_SPACE] && !grappling && l.hookList.size() > 0) {
        grappling = true;
        grapple(l.hookList[selectedHook], tileGrid, c);
    } else if (!event.keyboard_state_array[SDL_SCANCODE_SPACE] && grappling){
        grappling = false;
    }
    
    if((!event.keyboard_state_array[SDL_SCANCODE_D] && velocity.x > 0) || (!event.keyboard_state_array[SDL_SCANCODE_A] && velocity.x < 0)){
        applyForce(-1 * velocity.x * friction * mass * Gravity, 0);
    }
    
    update();
    
    friction = 0;
    if(hitbox.x + hitbox.width / 2 > l.width){
        pos.x = l.width - (hitbox.width/2);
        velocity.x = 0;
    }
    if (hitbox.x - hitbox.width / 2 < 0) {
        pos.x = hitbox.width / 2;
        velocity.x = 0;
    }
    if(hitbox.y - hitbox.height / 2 < l.overlap){
        pos.y =  l.overlap + hitbox.height / 2;
        velocity.y = 0;
    }
    if(hitbox.y - hitbox.height/2 > l.height){
        pos.y = l.spawn.y;
        pos.x = l.spawn.x;
        velocity.set(0, 0);
        grappling = false;
        hookState = 0;
    }
    //making it so that the hook doesn't change every frame you hold down  arrow
    if(changedHook && !(event.keyboard_state_array[SDL_SCANCODE_LEFT] || event.keyboard_state_array[SDL_SCANCODE_RIGHT])){
        changedHook = false;
    }
}

void Player::moveHook(std::vector<Object::Point> a) {
    if(hookState == 3){
        generalGrapple = Vector::sub(grappleHead, pos);
        generalGrapple.scaleTo(grappleStrength);
        grappleHead.add(generalGrapple);
        if(Vector::sub(pos,grappleHead).mag() <= -grappleStrength){
            hookState = 0;
        }
    } else if(hookState == 1){
        grappleHead.sub(generalGrapple);
        if(sqrt(pow(grappleHead.x - target.x, 2) + pow(grappleHead.y - target.y, 2)) <= grappleSpeed){
            pDistance = 0;
            grappleHead.set(target.x, target.y);
            if(isTargetHook){
                hookState = 2;
            } else {
                hookState = 3;
            }
        }
    } else if (hookState == 2){
        target.x = a[selectedHookHolder].x;
        target.y = a[selectedHookHolder].y;
        generalGrapple = Vector::sub(pos, target.x, target.y);
        distance = generalGrapple.mag();
        if(!rope){
            generalGrapple.scaleTo(grappleStrength);
            applyForce(generalGrapple);
        }
        
        if(abs(velocity.x) > maxSpeed){
            if(velocity.x > 0){
                velocity.x = maxSpeed;
            } else {
                velocity.x = -maxSpeed;
            }
        } else if (abs(velocity.y) > maxSpeed) {
            if(velocity.y > 0){
                velocity.y = maxSpeed;
            } else {
                velocity.y = -maxSpeed;
            }
        }
        
        if(distance > pDistance && pDistance != 0){
            generalGrapple = Vector::sub(pos, target.x, target.y);
            generalGrapple.normalize();
            if(rope){
                generalGrapple.mult(distance - pDistance);
                velocity.sub(generalGrapple);
            } else {
                generalGrapple.mult(-10 * (distance - pDistance));
                applyForce(generalGrapple);
            }
        }
        
        pDistance = distance;
        
        if(distance < 90) hookState = 0;
    }
}

void Player::grapple(Object:: Point b, std::vector<Object::Tile> tileGrid, Object:: Camera c){
    if(hookState != 1 && hookState != 2){
        if(b.x > c.x && b.x < SCREEN_WIDTH + c.x && b.y < SCREEN_HEIGHT + c.y && b.y > c.y){
            grappleHead.set(pos.x,pos.y);
            target = Tiles::checkLineCollision(tileGrid, grappleHead, b);
            selectedHookHolder = selectedHook;
            generalGrapple = Vector::sub(grappleHead, target);
            distance = generalGrapple.mag();
            isTargetHook = !Tiles::getLineCollided();
            if(distance > grapplerange){
                generalGrapple.scaleTo(grapplerange);
                target.x = pos.x - generalGrapple.x;
                target.y = pos.y - generalGrapple.y;
                isTargetHook = false;
                generalGrapple = Vector::sub(grappleHead, target);
                distance = grapplerange;
            }
            grappleSpeed = distance / 6;
            generalGrapple.scaleTo(grappleSpeed);
            hookState = 1;
        }
    } else if (hookState != 3) {
        hookState = 0;
    }
}

void Player::changeHooks(std::vector<Object:: Point> b , int change, Object::Camera c){
    if(!changedHook){
        if(change != -1 && change != 1){
            std::cout<< "you passed bad number to the changeHooks function in player (the 2nd thing passed in). fix it you twat" << std::endl;
        } else {
            int difference = SCREEN_WIDTH;
            int index = selectedHook;
            int x = b[selectedHook].x;
            if(x < c.x || x > SCREEN_WIDTH + c.x){
                if (change == -1) {
                    for(int i = 0; i < b.size(); i++){
                        if(b[i].x > c.x && b[i].x < SCREEN_WIDTH + c.x && b[i].y < SCREEN_HEIGHT + c.y && b[i].y > c.y){
                            if(abs(b[i].x - c.x) < difference){
                                difference = abs(b[i].x);
                                index = i;
                            }
                        }
                    }
                } else {
                    for(int i = 0; i < b.size(); i++){
                        if(b[i].x > c.x && b[i].x < SCREEN_WIDTH + c.x && b[i].y < SCREEN_HEIGHT + c.y && b[i].y > c.y){
                            if(abs(SCREEN_WIDTH - (b[i].x - c.x)) < difference){
                                difference = abs(SCREEN_WIDTH - b[i].x);
                                index = i;
                            }
                        }
                    }
                }
            } else {
                if(change == -1){
                    for(int i = 0; i < b.size(); i++){
                        if(b[i].x > c.x && b[i].x < SCREEN_WIDTH + c.x && b[i].y < SCREEN_HEIGHT + c.y && b[i].y > c.y){
                            if(b[i].x < x && abs(b[i].x - x) < difference){
                                difference = abs(b[i].x - x);
                                index = i;
                            }
                        }
                    }
                } else {
                    for(int i = 0; i < b.size(); i++){
                        if(b[i].x > c.x && b[i].x < SCREEN_WIDTH + c.x && b[i].y < SCREEN_HEIGHT + c.y && b[i].y > c.y){
                            if(b[i].x > x && abs(b[i].x - x) < difference){
                                difference = abs(b[i].x - x);
                                index = i;
                            }
                        }
                    }
                }
            }
            changedHook = true;
            selectedHook = index;
        }
    }
}

void Player::draw(Object::Camera b, SDL_Renderer* renderer) {
    player.render(renderer, pos.x, pos.y, b.x, b.y, hitbox.width, hitbox.height);
}
