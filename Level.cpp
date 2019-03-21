#include "stdafx.h"

Level Level::levelInit(std::string path, SDL_Renderer* renderer){
    Level level;
    level.path = path;
    std::string line;
    int a, b;
    std::string type;
    std::ifstream mapFile(path + "tiles.txt");
    std::ifstream hookFile(path + "hooks.txt");
    while(std::getline(mapFile, line)){
        std::vector <float> row;
        for(int j = 0; j < line.length(); j++){
            if(!isspace(line[j])){
                row.push_back((float) line[j] - 48);
            }
        }
        if(row.size() != 0){
            level.tileGrid.push_back(row);
        }
    }
    while(hookFile >> a >> b){
        level.hookList.push_back(Object::Point(a, b, "hook"));
    }
    level.height = (int) level.tileGrid.size() * TILE_HEIGHT;
    level.width = (int) level.tileGrid[0].size() * TILE_WIDTH;
    if(level.width < SCREEN_WIDTH){
        level.width = SCREEN_WIDTH;
    }
    level.background.backgroundInit(path + "background.txt", renderer);
    mapFile.close();
    hookFile.close();
    return level;
}
