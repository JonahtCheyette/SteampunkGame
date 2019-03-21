#pragma once
#include "stdafx.h"

class developer {
public:
    void moveCamera(Object::Camera &camera, Event event);
    void editLevel(Object::Camera camera, std::vector<Object::tileHolder> tileVector, Level level, SDL_Renderer* renderer, Event event, std::vector<Object::Tile> &tileGrid);
    void editAssets(Object::Camera c,Event e, Level &l);
    void createSwitch(Event e);
    void typeSwitch(Event e, std::string &type);
    int x, y;
    int w, h;
    int clickstate;
    bool held;
    int moveSpeed;
    bool create;
};
