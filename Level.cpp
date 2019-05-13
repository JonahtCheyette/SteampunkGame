#include "stdafx.h"

Level Level::levelInit(std::string path, SDL_Renderer* renderer){
    Level level;
    level.path = path;
    level.overlap = 0;
    level.spawn.x = -1;
    level.spawn.y = -1;
    std::string line;
    float a, b, c, d, e;
    bool v;
    std::string type;
    std::ifstream mapFile(path + "tiles.txt");
    std::ifstream hookFile(path + "hooks.txt");
    std::ifstream startend(path + "start-end.txt");
    std::ifstream cFile(path + "Crates.txt");
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
    while(hookFile >> a >> b >> c >> d >> e >> v){
        level.hookList.push_back({a, b, "hook", c, d, e, v});
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
    while(cFile >> a >> b >> c >> d >> e){
        level.crateList.push_back({a, b, c, d, 0, 0, 10, renderer, e});
    }
    level.height = (int) level.tileGrid.size() * TILE_HEIGHT;
    level.width = (int) level.tileGrid[0].size() * TILE_WIDTH;
    level.Start_End.load("Steampunk-Game/Assets/Images/levelBasics/SPOT.png", renderer, 1);
    level.CrateDroppers = {"Steampunk-Game/Assets/Animations/crateDropper", renderer};
    if(level.width < SCREEN_WIDTH){
        level.width = SCREEN_WIDTH;
    }
    if(level.height < SCREEN_HEIGHT){
        level.overlap = level.height - SCREEN_HEIGHT;
    }
    for(int i = 0; i < level.hookList.size(); i++){
        if(level.hookList[i].x > level.width){
            level.width = level.hookList[i].x + 8;
        }
    }
    level.background.backgroundInit(path + "background.txt", renderer);
    mapFile.close();
    hookFile.close();
    startend.close();
    cFile.close();
    return level;
}

void Level::renderEnd(Object::Camera c, SDL_Renderer* renderer){
    if(spawn.x + TILE_WIDTH / 2 > c.x && spawn.x - TILE_WIDTH / 2 < c.x + SCREEN_WIDTH && spawn.y + TILE_HEIGHT / 2 > c.y && spawn.y - TILE_HEIGHT / 2 < c.y + SCREEN_HEIGHT){
        Start_End.render(renderer, spawn.x, spawn.y, c.x, c.y);
    }
    if(end.x + TILE_WIDTH / 2 > c.x && end.x - TILE_WIDTH / 2 < c.x + SCREEN_WIDTH && end.y + TILE_HEIGHT / 2 > c.y - TILE_HEIGHT / 2 && end.y < c.y + SCREEN_HEIGHT){
        Start_End.render(renderer, end.x, end.y, c.x, c.y);
    }
}

void Level::update(physicsApplied &a, Object::Camera c, Tiles tiles){
    for(int i = 0; i < hookList.size(); i++){
        if (hookList[i].y > c.y - 50 && hookList[i].y < c.y + SCREEN_HEIGHT + 50 && hookList[i].x > c.x - 50 && hookList[i].x < c.x + SCREEN_WIDTH + 50){
            if(hookList[i].vertical){
                hookList[i].y += hookList[i].moveSpeed * hookList[i].moveDir;
                if(hookList[i].y > hookList[i].limit1 || hookList[i].y < hookList[i].limit2){
                    hookList[i].moveDir *= -1;
                }
            } else {
                hookList[i].x += hookList[i].moveSpeed * hookList[i].moveDir;
                if(hookList[i].x > hookList[i].limit1 || hookList[i].x < hookList[i].limit2){
                    hookList[i].moveDir *= -1;
                }
            }
        }
    }
    for(int i = 0; i < crateList.size(); i++){
        if (crateList[i].pos.y + crateList[i].hitbox.height / 2 > c.y - physUpdateRange && crateList[i].pos.y - crateList[i].hitbox.height / 2 < c.y + SCREEN_HEIGHT + physUpdateRange && crateList[i].pos.x + crateList[i].hitbox.width / 2 > c.x - physUpdateRange && crateList[i].pos.x - crateList[i].hitbox.width / 2 < c.x + SCREEN_WIDTH + physUpdateRange){
            crateList[i].update();
            tiles.checkCollision(tiles.loadedLevel, crateList[i]);
            crateList[i].collide(a);
            crateList[i].doFriction();
        }
    }
}

void Level::draw(SDL_Renderer* renderer, Object::Camera c){
    for(int i = 0; i < crateList.size(); i++){
        if (crateList[i].pos.y + crateList[i].hitbox.height / 2 > c.y && crateList[i].pos.y - crateList[i].hitbox.height / 2 < c.y + SCREEN_HEIGHT && crateList[i].pos.x + crateList[i].hitbox.width / 2 > c.x && crateList[i].pos.x - crateList[i].hitbox.width / 2 < c.x + SCREEN_WIDTH){
            crateList[i].draw(c, renderer);
        }
    }
    //My Shitty, temporary cratedropper drawing code
    CrateDroppers.renderAnimation(CrateDroppers, renderer, 4679 - c.x, -c.y, 200, 200);
}
