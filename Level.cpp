#include "stdafx.h"

Level Level::levelInit(std::string path, SDL_Renderer* renderer, Draw draw){
    Level level;
    level.path = path;
    level.overlap = 0;
    level.spawn.x = -1;
    level.spawn.y = -1;
    std::string line;
    int a, b;
    std::string type;
    std::ifstream mapFile(path + "tiles.txt");
    std::ifstream hookFile(path + "hooks.txt");
    std::ifstream startend(path + "start-end.txt");
    while(std::getline(mapFile, line)){
        std::vector <int> row;
        for(int j = 0; j < line.length(); j++){
            if(!isspace(line[j])){
                row.push_back((int) line[j] - 48);
            }
        }
        if(row.size() != 0){
            level.tileGrid.push_back(row);
        }
    }
    while(hookFile >> a >> b){
        level.hookList.push_back(Object::Point(a, b, "hook"));
    }
    while(startend >> a >> b){
        if(level.spawn.x == -1 && level.spawn.y == -1){
            level.spawn.x = a;
            level.spawn.y = b;
        } else {
            level.end.x = a;
            level.end.y = b;
        }
    }
    level.height = (int) level.tileGrid.size() * TILE_HEIGHT;
    level.width = (int) level.tileGrid[0].size() * TILE_WIDTH;
    level.Start_End = draw.loadTexture("Steampunk-Game/Assets/Images/levelBasics/SPOT.png", renderer);
    if(level.width < SCREEN_WIDTH){
        level.width = SCREEN_WIDTH;
    }
    if(level.height < SCREEN_HEIGHT){
        level.overlap = level.height - SCREEN_HEIGHT;
    }
    level.background.backgroundInit(path + "background.txt", renderer);
    mapFile.close();
    hookFile.close();
    return level;
}

void Level::renderEnd(Object::Camera c, SDL_Renderer* renderer){
    if(spawn.x + TILE_WIDTH / 2 > c.x && spawn.x - TILE_WIDTH / 2 < c.x + SCREEN_WIDTH && spawn.y + TILE_HEIGHT / 2 > c.y && spawn.y - TILE_HEIGHT / 2 < c.y + SCREEN_HEIGHT){
        destination.y = spawn.y - TILE_HEIGHT / 2 - c.y;
        destination.x = spawn.x - TILE_WIDTH / 2 - c.x;
        destination.w = TILE_WIDTH;
        destination.h = TILE_HEIGHT;
        SDL_RenderCopy(renderer, Start_End, nullptr, &destination);
    }
    if(end.x + TILE_WIDTH / 2 > c.x && end.x - TILE_WIDTH / 2 < c.x + SCREEN_WIDTH && end.y + TILE_HEIGHT / 2 > c.y - TILE_HEIGHT / 2 && end.y < c.y + SCREEN_HEIGHT){
        destination.y = end.y - TILE_HEIGHT / 2 - c.y;
        destination.x = end.x - TILE_WIDTH / 2 - c.x;
        destination.w = TILE_WIDTH;
        destination.h = TILE_HEIGHT;
        SDL_RenderCopy(renderer, Start_End, nullptr, &destination);
    }
}
