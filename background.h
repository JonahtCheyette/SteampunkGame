#pragma once
#include "stdafx.h"

class backGround {
    public:
        void backgroundInit(std::string path, SDL_Renderer* renderer);
        void drawBackground(SDL_Renderer* renderer, Object::Camera c);
    
        std::vector<Object::Layer> l;
        float s;
        int w, h;
        std::string iPath;
};
