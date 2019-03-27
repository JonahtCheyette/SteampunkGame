#pragma once
#include "stdafx.h"

class Level {
public:
    static Level levelInit(std::string path, SDL_Renderer* renderer, Draw draw);
    void renderEnd(Object::Camera c, SDL_Renderer* renderer);
    
    
    SDL_Rect destination;
    int overlap;
    int height;
    int width;
    std::string path;
    std::vector< std::vector <int> > tileGrid;
    std::vector<Object::Point> hookList;
    SDL_Texture* Start_End;
    Object::Point spawn;
    Object::Point end;
    backGround background;
    backGround foreground;
};
