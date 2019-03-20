#pragma once
#include "stdafx.h"

class developerMode {
    public:
        void moveCamera(Object::Camera &c);
        void addTiles(std::vector<Object::tileHolder> tileVector, Object::Camera camera, SDL_Renderer* renderer, int &initX, int & initY, int &clickstate, bool &held, Level level);
        void init();
};
