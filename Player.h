#pragma once
#include "stdafx.h"

class Player : public physicsApplied {
public:
    Player(SDL_Renderer* renderer, Draw draw);
    void move(SDL_Event& e, Level l, Object::Camera c, std::vector<Object::Tile> tileGrid);
    void moveHook();
    void grapple(Object::Point b, std::vector<Object::Tile> tileGrid, Object::Camera c);
    void changeHooks(std::vector<Object:: Point> b, int change, Object::Camera c);
    void draw(Object::Camera b, SDL_Renderer* renderer);
    
    Object::AABB hitbox;
    float acceleration;
    float friction;
    float distance;
    float pDistance;
    float gX;
    float gY;
    float grappleSpeed;
    int selectedHook;
    
    bool airborne;
    bool grappling;
    int hookState;
    bool changedHook;
    
    Object::Point target;
    Object::Point grappleHead;
    SDL_Texture* player;
};
