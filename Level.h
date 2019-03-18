#pragma once
#include "stdafx.h"

class Level {
public:
    static Level levelInit(std::string path, SDL_Renderer* renderer);
    
    int height;
    int width;
    int overlap;
    std::string path;
    std::vector< std::vector <float> > tileGrid;
    std::vector<Object::Point> hookList;
    backGround background;
    backGround foreground;
};
