#pragma once
#include "stdafx.h"

class Loader {
public:
    void loadTiles(std::vector<Object::tileHolder> &t, std::string path, SDL_Renderer* renderer);
    void loadLevels(std::vector<Level> &l, std::string path, SDL_Renderer* renderer);
    
    //Level level;
    struct dirent *de;
    int a;
    float b, c;
    std::string fName;
    std::string iPath;
    DIR *dr;
};
