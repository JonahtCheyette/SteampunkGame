#pragma once
#include "stdafx.h"

class developer {
public:
    void addTiles(Object::Camera camera, int &clickstate, int &initX, int &initY, int &W, int &H, bool &held, std::vector<Object::tileHolder> tileVector, Level level, SDL_Renderer* renderer, Event event, std::vector<Object::Tile> &tileGrid);
};
