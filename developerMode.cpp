#include "stdafx.h"

void developerMode::moveCamera(Object::Camera &c){
    event.keyboard_state_array = SDL_GetKeyboardState(NULL);
    if(event.keyboard_state_array[SDL_SCANCODE_W]) c.y -= 5;
    if(event.keyboard_state_array[SDL_SCANCODE_S]) c.y += 5;
    if(event.keyboard_state_array[SDL_SCANCODE_A]) c.x -= 5;
    if(event.keyboard_state_array[SDL_SCANCODE_D]) c.x += 5;
    if(c.x < 0) c.x = 0;
    if(c.y < 0) c.y = 0;
}

void developerMode::addTiles(std::vector<Object::tileHolder> tileVector, Object::Camera camera, SDL_Renderer* renderer, int &initX, int & initY, int &clickstate, bool &held, Level level){
    SDL_Rect heldRect;
    if(event.mouse1 && clickstate == 0){
        heldRect.x = event.mouseX + camera.x;
        heldRect.y = event.mouseY + camera.y;
        initX = heldRect.x;
        initY = heldRect.y;
        heldRect.w = 0;
        heldRect.h = 0;
        clickstate = 1;
    }
    if(event.mouse1held && heldRect.x != 0 && heldRect.y != 0 && clickstate == 1){
        heldRect.x = initX - camera.x;
        heldRect.y = initY - camera.y;
        heldRect.w = event.mouseX - heldRect.x;
        heldRect.h = event.mouseY - heldRect.y;
        SDL_RenderDrawRect(renderer, &heldRect);
    }
    if(held && !event.mouse1held){
        clickstate = 2;
    }
    held = event.mouse1held;
    if (event.mouse1Released && heldRect.x != 0 && heldRect.y != 0 && clickstate == 2) {
        int xAmount = abs(round(heldRect.w / TILE_WIDTH));
        int yAmount = abs(round(heldRect.h / TILE_HEIGHT));
        int spX = round((heldRect.x + camera.x)/TILE_WIDTH) * TILE_WIDTH;
        int spY = round((heldRect.y + camera.y)/TILE_HEIGHT) * TILE_HEIGHT;
        int tx, ty;
        int sx = (spX/TILE_WIDTH);
        int fx = (spX/TILE_WIDTH);
        int sy = (spY/TILE_HEIGHT);
        int fy = (spY/TILE_HEIGHT);
        if(heldRect.w > 0){
            fx += xAmount;
        } else {
            sx -= xAmount;
        }
        if(heldRect.h > 0){
            fy += yAmount;
        } else {
            sy -= yAmount;
        }
        for(int i = 0; i < xAmount; i++){
            for(int j = 0; j < yAmount; j++){
                if(heldRect.w > 0){
                    tx = (i * TILE_WIDTH) + spX;
                } else {
                    tx = -1 * (i * TILE_WIDTH + TILE_WIDTH) + spX;
                }
                if(heldRect.h > 0){
                    ty = (j * TILE_HEIGHT) + spY;
                } else {
                    ty = -1 * (j * TILE_HEIGHT + TILE_HEIGHT) + spY;
                }
                Object::Tile t(tx, ty, tileVector[0].friction);
                t.texture = tileVector[0].single;
                tiles.loadedLevel.push_back(t);
            }
        }
        std::vector<std::vector<float>> grid;
        std::string line;
        std::ifstream mapFile(level.path + "tiles.txt");
        while(std::getline(mapFile, line)){
            std::vector <float> row;
            for(int j = 0; j < line.length(); j++){
                if(!isspace(line[j])){
                    row.push_back((float) line[j] - 48);
                }
            }
            if(row.size() != 0){
                grid.push_back(row);
            }
        }
        mapFile.close();
        if(fy >= grid.size()){
            for(int i = 0; i <= fy - grid.size() + 1; i++){
                std::vector<float> row;
                for(int j = 0; j < grid[0].size(); j++){
                    row.push_back(0);
                }
                grid.push_back(row);
            }
        }
        if(fx >= grid[0].size()){
            for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j <= fx - grid[0].size(); j++){
                    grid[i].push_back(0);
                }
            }
        }
        for(int i = sx; i < fx; i++){
            for(int j = sy; j < fy; j++){
                grid[j][i] = 1;
            }
        }
        int correctindex = -1;
        for(int i = (int) (grid.size() - 1); i >= 0; i--){
            for(int j = 0; j < grid[i].size(); j++){
                if(grid[i][j] != 0 && correctindex == -1){
                    correctindex = i;
                }
            }
        }
        for(int i = (int) (grid.size() - 1); i > correctindex; i--){
            grid.pop_back();
        }
        int chopEnd = -1;
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid[i].size(); j++){
                if(grid[i][j] != 0 && j > chopEnd){
                    chopEnd = j;
                }
            }
        }
        for(int i = 0; i < grid.size(); i++){
            for(int j = (int) (grid[i].size() - 1); j > chopEnd ; j--){
                grid[i].pop_back();
            }
        }
        std::ofstream mFile(level.path + "tiles.txt", std::ofstream::out | std::ofstream::trunc);
        for(int i = 0; i < grid.size(); i++){
            std::string l = "";
            for(int j = 0; j < grid[i].size(); j++){
                if(j > 0){
                    l += " ";
                }
                l += std::to_string((int) grid[i][j]);
            }
            if(i != grid.size() + 1){
                l += "\n";
            }
            mFile << l;
        }
        mFile.close();
        clickstate = 0;
    }
}

void developerMode::init(){
    
}
