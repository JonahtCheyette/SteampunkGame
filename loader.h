#pragma once
#include "stdafx.h"

class Loader {
public:
    void loadTiles(std::vector<Object::tileHolder> &t, std::string path, SDL_Renderer* renderer);
    void loadLevels(std::vector<Level> &l, std::string path, SDL_Renderer* renderer, Draw draw);
    
    //Level level;
    struct dirent *de;
    float a;
    int tileNum;
    bool bo, bi;
    std::string fName;
    std::string iPath;
    DIR *dr;
};
