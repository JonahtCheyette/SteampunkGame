#pragma once
#include "stdafx.h"

class Level {
public:
    static Level levelInit(std::string path, SDL_Renderer* renderer);
    void renderEnd(Object::Camera c, SDL_Renderer* renderer);
    void update(physicsApplied &a, Object::Camera c, Tiles tiles);
    void draw(SDL_Renderer* renderer, Object::Camera c);
    
    int overlap;
    int height;
    int width;
    std::vector< std::vector <int> > tileGrid;
    std::vector<Object::Point> hookList;
    std::vector<Crate> crateList;
    Object::Point spawn;
    Object::Point end;
    backGround background;
    backGround foreground;
    std::string path;
    Sprite Start_End;
    Object::Animation CrateDroppers;
    
};
