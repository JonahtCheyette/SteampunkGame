#pragma once
#include "stdafx.h"

class developerMode {
    public:
        void moveCamera(Object::Camera &c);
        void addTiles(std::vector<Object::tileHolder> tileVector, Object::Camera camera, SDL_Renderer* renderer, int &initX, int & initY, int &clickstate, bool &held, Level level, bool mouse1, bool mouse1held, bool mouse1Released, int x, int y);
        void init();
};
