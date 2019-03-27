#include "stdafx.h"

Player::Player(SDL_Renderer* renderer, Draw draw){
    x = 500;
    y = 0;
    velX = 0;
    velY = 0;
    accelX = 0;
    accelY = Gravity;
    mass = 20;
    
    hitbox.height = 96;
    hitbox.width = 48;

    maxXSpeed = 10;
    maxYSpeed = 10;
    acceleration = 5;
    
    //vars for grapple movement
    distance = 0;
    pDistance = 0;
    gX = 0;
    gY = 0;
    selectedHook = 0;
    
    airborne = false;
    grappling = false;
    rope = false;
    hookState = 0;
    changedHook = false;
    clicked = false;
    player = draw.loadTexture("Steampunk-Game/Assets/Images/Characters/Square.png", renderer);
}

void Player::move(SDL_Event& e, Level l, Object::Camera c, std::vector<Object::Tile> tileGrid, int &which, int maxLevel) {
    //key presses
    SDL_PollEvent(&e);
    event.keyboard_state_array = SDL_GetKeyboardState(NULL);
    if (hookState != 2) {
        if (event.keyboard_state_array[SDL_SCANCODE_A]) applyForce(-1 * acceleration, 0);
        if (event.keyboard_state_array[SDL_SCANCODE_D]) applyForce(acceleration, 0);
    }
    if(!airborne){
        if (event.keyboard_state_array[SDL_SCANCODE_W]){
            applyForce(0, -250);
        }
        if (event.keyboard_state_array[SDL_SCANCODE_UP] && sqrt(pow(l.end.x - x,2) + pow(l.end.y - y,2)) < 20){
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
    
    if (event.keyboard_state_array[SDL_SCANCODE_E] && !clicked && hookState != 2) {
        rope = !rope;
        clicked = true;
    }
    if(!event.keyboard_state_array[SDL_SCANCODE_E]){
        clicked = false;
    }
    
    if (event.keyboard_state_array[SDL_SCANCODE_SPACE] && !grappling && l.hookList.size() > 0) {
        grappling = true;
        grapple(l.hookList[selectedHook], tileGrid, c);
    } else if (!event.keyboard_state_array[SDL_SCANCODE_SPACE] && grappling){
        grappling = false;
    }
    
    if((!event.keyboard_state_array[SDL_SCANCODE_D] && velX > 0) || (!event.keyboard_state_array[SDL_SCANCODE_A] && velX < 0)){
        applyForce(velX * (-1 * friction * mass * Gravity), 0);
    }
    
    update();
    
    if (velX > maxXSpeed) velX = maxXSpeed;
    if (velX < -maxXSpeed) velX = -maxXSpeed;

    if(hookState == 2){
        if (velY > maxYSpeed) velY = maxYSpeed;
        if (velY < -maxYSpeed) velY = -maxYSpeed;
    }
    
    hitbox.x = x;
    hitbox.y = y;
    friction = 0;
    airborne = true;
    if(hitbox.x + hitbox.width / 2 > l.width){
        x = l.width - (hitbox.width/2);
        velX = 0;
    }
    if (hitbox.x - hitbox.width / 2 < 0) {
        x = hitbox.width / 2;
        velX = 0;
    }
    if(hitbox.y - hitbox.height / 2 < l.overlap){
        y =  l.overlap + hitbox.height / 2;
        velY = 0;
    }
    if(hitbox.y - hitbox.height/2 > l.height){
        y = l.spawn.y;
        x = l.spawn.x;
        velX = 0;
        velY = 0;
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
        gX = grappleHead.x - x;
        gY = grappleHead.y - y;
        distance = sqrt(pow(gX, 2) + pow(gY, 2));
        gX /= distance;
        gY /= distance;
        gX *= grappleStrength;
        gY *= grappleStrength;
        grappleHead.x += gX;
        grappleHead.y += gY;
        if(sqrt(pow(x - grappleHead.x, 2) + pow(y - grappleHead.y, 2)) <=  -grappleStrength){
            hookState = 0;
        }
    } else if(hookState == 1){
        grappleHead.x -= gX;
        grappleHead.y -= gY;
        if(sqrt(pow(grappleHead.x - target.x, 2) + pow(grappleHead.y - target.y, 2)) <= grappleSpeed){
            pDistance = 0;
            grappleHead.x = target.x;
            grappleHead.y = target.y;
            if(target.type == "hook"){
                hookState = 2;
            } else {
                hookState = 3;
            }
        }
    } else if (hookState == 2){
        target.x = a[selectedHookHolder].x;
        target.y = a[selectedHookHolder].y;
        gX = x - target.x;
        gY = y - target.y;
        distance = sqrt(pow(gX, 2) + pow(gY, 2));
        if(!rope){
            gX /= distance;
            gY /= distance;
            gX *= grappleStrength;
            gY *= grappleStrength;
            applyForce(gX, gY);
        }
        
        if(distance > pDistance && pDistance != 0){
            gX = x - target.x;
            gY = y - target.y;
            gX /= distance;
            gY /= distance;
            if(rope){
                gX *= distance - pDistance;
                gY *= distance - pDistance;
                velX -= gX;
                velY -= gY;
            } else {
                gX *= -10 * (distance - pDistance);
                gY *= -10 * (distance - pDistance);
                applyForce(gX, gY);
            }
        }
        
        pDistance = distance;
        
        if(distance < 90) hookState = 0;
    }
}

void Player::grapple(Object:: Point b, std::vector<Object::Tile> tileGrid, Object:: Camera c){
    if(hookState != 1 && hookState != 2){
        if(b.x > c.x && b.x < SCREEN_WIDTH + c.x && b.y < SCREEN_HEIGHT + c.y && b.y > c.y){
            grappleHead.x = x;
            grappleHead.y = y;
            target = tiles.checkLineCollision(tileGrid, grappleHead, b);
            selectedHookHolder = selectedHook;
            gX = grappleHead.x - target.x;
            gY = grappleHead.y - target.y;
            distance = sqrt(pow(gX, 2) + pow(gY, 2));
            if(distance > grapplerange){
                gX /= distance;
                gY /= distance;
                gX *= grapplerange;
                gY *= grapplerange;
                target.x = x - gX;
                target.y = y - gY;
                target.type = "N/A";
                gX = grappleHead.x - target.x;
                gY = grappleHead.y - target.y;
                distance = grapplerange;
            }
            grappleSpeed = distance / 6;
            gX /= distance;
            gY /= distance;
            gX *= grappleSpeed;
            gY *= grappleSpeed;
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
    SDL_Rect destination;
    destination.x = x - hitbox.width / 2 - b.x;
    destination.y = y - hitbox.height / 2 - b.y;
    destination.w = hitbox.width;
    destination.h = hitbox.height;
    SDL_RenderCopy(renderer, player, nullptr, &destination);
}
