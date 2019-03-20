#include "stdafx.h"

void Move::moveCamera(Object::Camera &a, Object::Player b, Level l) {
	a.x = (b.x + b.hitbox.width / 2) - SCREEN_WIDTH / 2;
	a.y = (b.y + b.hitbox.height / 2) - SCREEN_HEIGHT / 2;
    if(a.x + SCREEN_WIDTH > l.width) a.x = l.width - SCREEN_WIDTH;
	if (a.x < 0) a.x = 0;
    if(a.y < 0) a.y = 0;
    if(a.y + SCREEN_HEIGHT > l.height) a.y = l.height -SCREEN_HEIGHT;
}

void Move::movePlayer(Object::Player &a, SDL_Event& e, Level l, Object::Camera c, std::vector<Object::Tile> tileGrid) {
    
    a.accelY += Gravity;
    
	//key presses
	SDL_PollEvent(&e);
	event.keyboard_state_array = SDL_GetKeyboardState(NULL);
    if (a.hookState != 2) {
        if (event.keyboard_state_array[SDL_SCANCODE_A]) move.applyForce(a, -1 * a.acceleration, 0);
        if (event.keyboard_state_array[SDL_SCANCODE_D]) move.applyForce(a, a.acceleration, 0);
    }
    if(!a.airborne){
        if (event.keyboard_state_array[SDL_SCANCODE_W]){
            move.applyForce(a, 0, -250);
        }
    }
    if(!(event.keyboard_state_array[SDL_SCANCODE_LEFT] && event.keyboard_state_array[SDL_SCANCODE_RIGHT])){
        if (event.keyboard_state_array[SDL_SCANCODE_LEFT]) move.changeHooks(a, l.hookList, -1, c);
        if (event.keyboard_state_array[SDL_SCANCODE_RIGHT]) move.changeHooks(a, l.hookList, 1, c);
    }
    
    if (event.keyboard_state_array[SDL_SCANCODE_SPACE] && !a.grappling) {
        a.grappling = true;
        move.grapple(a, l.hookList[a.selectedHook], tileGrid, c);
    } else if (!event.keyboard_state_array[SDL_SCANCODE_SPACE] && a.grappling){
        a.grappling = false;
    }
    
    //friction
    if((!event.keyboard_state_array[SDL_SCANCODE_D] && a.velX > 0) || (!event.keyboard_state_array[SDL_SCANCODE_A] && a.velX < 0)){
        move.applyForce(a, a.velX * (-1 * a.friction * a.mass * Gravity), 0);
    }
    
	a.velX += a.accelX;
	a.velY += a.accelY;
    
	if (a.velX > a.maxXSpeed) a.velX = a.maxXSpeed;
	if (a.velX < -a.maxXSpeed) a.velX = -a.maxXSpeed;
    
    if (a.velY > a.maxYSpeed) a.velY = a.maxYSpeed;
    if (a.velY < -a.maxYSpeed) a.velY = -a.maxYSpeed;
    
	a.x += a.velX;
    a.y += a.velY;
    
	a.hitbox.x = a.x;
	a.hitbox.y = a.y;
    a.friction = 0;
    a.airborne = true;
    if(a.hitbox.x + a.hitbox.width / 2 > l.width){
        a.x = l.width - (a.hitbox.width/2);
    }
	if (a.hitbox.x - a.hitbox.width / 2 < 0) {
		a.x = a.hitbox.width / 2;
		a.velX = 0;
	}
    if(a.y - a.hitbox.height / 2 < 0){
        a.y = a.hitbox.height / 2;
        a.velY = 0;
    }
    //making it so that the hook doesn't change every frame you hold down an arrow
    if(a.changedHook && !(event.keyboard_state_array[SDL_SCANCODE_LEFT] || event.keyboard_state_array[SDL_SCANCODE_RIGHT])){
        a.changedHook = false;
    }
    
	a.accelX = 0;
    a.accelY = 0;
}

void Move::moveHook(Object::Player &a) {
    if(a.hookState == 3){
        a.gX = a.grappleHead.x - a.x;
        a.gY = a.grappleHead.y - a.y;
        a.distance = sqrt(pow(a.gX, 2) + pow(a.gY, 2));
        a.gX /= a.distance;
        a.gY /= a.distance;
        a.gX *= grappleStrength;
        a.gY *= grappleStrength;
        a.grappleHead.x += a.gX;
        a.grappleHead.y += a.gY;
        if(sqrt(pow(a.x - a.grappleHead.x, 2) + pow(a.y - a.grappleHead.y, 2)) <= a.grappleSpeed){
            a.hookState = 0;
        }
    } else if(a.hookState == 1){
        a.grappleHead.x -= a.gX;
        a.grappleHead.y -= a.gY;
        if(sqrt(pow(a.grappleHead.x - a.target.x, 2) + pow(a.grappleHead.y - a.target.y, 2)) <= a.grappleSpeed){
            a.pDistance = 0;
            a.grappleHead.x = a.target.x;
            a.grappleHead.y = a.target.y;
            if(a.target.type == "hook"){
                a.hookState = 2;
            } else {
                a.hookState = 3;
            }
        }
    } else if (a.hookState == 2){
        a.gX = a.x - a.target.x;
        a.gY = a.y - a.target.y;
        a.distance = sqrt(pow(a.gX, 2) + pow(a.gY, 2));
        a.gX /= a.distance;
        a.gY /= a.distance;
        a.gX *= grappleStrength;
        a.gY *= grappleStrength;
        
        move.applyForce(a, a.gX, a.gY);
        
        if(a.distance > a.pDistance && a.pDistance != 0){
            a.gX = a.x - a.target.x;
            a.gY = a.y - a.target.y;
            a.gX /= a.distance;
            a.gY /= a.distance;
            a.gX *= -10 * (a.distance - a.pDistance);
            a.gY *= -10 * (a.distance - a.pDistance);
            move.applyForce(a, a.gX, a.gY);
        }
        
        a.pDistance = a.distance;
        
        if(a.distance < 90) a.hookState = 0;
    }
}

//for applying forces with the actual physics engine
void Move:: applyForce(Object::Player &a,float forceX, float forceY){
    a.accelY += forceY/a.mass;
    a.accelX += forceX/a.mass;
}

void Move::grapple(Object:: Player &a, Object:: Point b, std::vector<Object::Tile> tileGrid, Object:: Camera c){
    if(a.hookState != 1 && a.hookState != 2){
        if(b.x > c.x && b.x < SCREEN_WIDTH + c.x && b.y < SCREEN_HEIGHT + c.y && b.y > c.y){
            a.grappleHead.x = a.x;
            a.grappleHead.y = a.y;
            a.hookState = 1;
            a.target = tiles.checkLineCollision(tileGrid, a.grappleHead, b);
            a.gX = a.grappleHead.x - a.target.x;
            a.gY = a.grappleHead.y - a.target.y;
            a.distance = sqrt(pow(a.gX, 2) + pow(a.gY, 2));
            a.grappleSpeed = a.distance / 6;
            a.gX /= a.distance;
            a.gY /= a.distance;
            a.gX *= a.grappleSpeed;
            a.gY *= a.grappleSpeed;
        }
    } else if (a.hookState != 3) {
        a.hookState = 0;
    }
}

void Move::changeHooks(Object:: Player &a, std::vector<Object:: Point> b , int change, Object::Camera c){
    if(!a.changedHook){
        if(change != -1 && change != 1){
            std::cout<< "you passed a bad number to the changeHooks function in move (the third thing passed in). fix it you twat" << std::endl;
        } else {
            int difference = SCREEN_WIDTH;
            int index = a.selectedHook;
            int x = b[a.selectedHook].x;
            if(x < c.x || x > SCREEN_WIDTH + c.x){
                if (change == -1) {
                    for(int i = 0; i < b.size(); i++){
                        if(b[i].x > c.x && b[i].x < SCREEN_WIDTH + c.x && b[i].y < SCREEN_HEIGHT + c.y && b[i].y > c.y){
                            if(abs(b[i].x) < difference){
                                difference = abs(b[i].x);
                                index = i;
                            }
                        }
                    }
                } else {
                    for(int i = 0; i < b.size(); i++){
                        if(b[i].x > c.x && b[i].x < SCREEN_WIDTH + c.x && b[i].y < SCREEN_HEIGHT + c.y && b[i].y > c.y){
                            if(abs(SCREEN_WIDTH - b[i].x) < difference){
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
            a.changedHook = true;
            a.selectedHook = index;
        }
    }
}
