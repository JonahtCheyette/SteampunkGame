#pragma once
#include "stdafx.h"

class Level {
public:
    static Level levelInit(std::string path, SDL_Renderer* renderer, Draw draw);
    void renderEnd(Object::Camera c, SDL_Renderer* renderer);
    void update(physicsApplied &a, Object::Camera c, Tiles tiles);
    void draw(SDL_Renderer* renderer, Object::Camera c);
    
    SDL_Rect destination;
    int overlap;
    int height;
    int width;
    std::string path;
    std::vector< std::vector <int> > tileGrid;
    std::vector<Object::Point> hookList;
    std::vector<Crate> crateList;
    SDL_Texture* Start_End;
    Object::Animation CrateDroppers;
    Object::Point spawn;
    Object::Point end;
    backGround background;
    backGround foreground;
};
