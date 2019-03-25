#pragma once
#include "stdafx.h"

class backGround {
public:
    void backgroundInit(std::string path, SDL_Renderer* renderer);
    void drawBackground(SDL_Renderer* renderer, Object::Camera c, int h);
    
    std::vector<SDL_Rect> destinations;
    std::vector<Object::Layer> l;
    int xAmount, yAmount;
    int start;
    SDL_Rect destination;
    float s;
    int w, h;
    std::string iPath;
};
