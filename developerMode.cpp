#include "stdafx.h"

void developer::moveCamera(Object::Camera &camera, Event event){
    if(event.keyboard_state_array[SDL_SCANCODE_W]) camera.y -= moveSpeed;
    if(event.keyboard_state_array[SDL_SCANCODE_S]) camera.y += moveSpeed;
    if(event.keyboard_state_array[SDL_SCANCODE_A]) camera.x -= moveSpeed;
    if(event.keyboard_state_array[SDL_SCANCODE_D]) camera.x += moveSpeed;
    if(camera.x < 0) camera.x = 0;
    if(camera.y < 0) camera.y = 0;
}

void developer::editLevel(Object::Camera camera, std::vector<Object::tileHolder> tileVector, Level level, SDL_Renderer *renderer, Event event, std::vector<Object::Tile> &tileGrid){
    if(event.mouse1 && clickstate == 0){
        x = event.mouseX + camera.x;
        y = event.mouseY + camera.y;
        clickstate = 1;
    }
    if(event.mouse1held && clickstate == 1){
        SDL_Rect heldRect;
        heldRect.x = x - camera.x;
        heldRect.y = y - camera.y;
        heldRect.w = event.mouseX - heldRect.x;
        heldRect.h = event.mouseY - heldRect.y;
        w = heldRect.w;
        h = heldRect.h;
        SDL_RenderDrawRect(renderer, &heldRect);
    }
    if(held && !event.mouse1held){
        clickstate = 2;
    }
    held = event.mouse1held;
    if (event.mouse1Released && clickstate == 2) {
        int xAmount = abs(round(w/ TILE_WIDTH));
        int yAmount = abs(round(h/ TILE_HEIGHT));
        if(xAmount < 1000 && xAmount != 0){
            int spX = round(x/TILE_WIDTH) * TILE_WIDTH;
            int spY = round(y/TILE_HEIGHT) * TILE_HEIGHT;
            int tx, ty;
            int sx = (spX/TILE_WIDTH);
            int fx = (spX/TILE_WIDTH);
            int sy = (spY/TILE_HEIGHT);
            int fy = (spY/TILE_HEIGHT);
            if(w > 0){
                fx += xAmount;
            } else {
                sx -= xAmount;
            }
            if(h > 0){
                fy += yAmount;
            } else {
                sy -= yAmount;
            }
            for(int i = 0; i < xAmount; i++){
                for(int j = 0; j < yAmount; j++){
                    if(w > 0){
                        tx = (i * TILE_WIDTH) + spX;
                    } else {
                        tx = -1 * (i * TILE_WIDTH + TILE_WIDTH) + spX;
                    }
                    if(h > 0){
                        ty = (j * TILE_HEIGHT) + spY;
                    } else {
                        ty = -1 * (j * TILE_HEIGHT + TILE_HEIGHT) + spY;
                    }
                    Object::Tile t(tx, ty, tileVector[0].friction);
                    t.texture = tileVector[0].single;
                    tileGrid.push_back(t);
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
            while(grid.size() < fy) {
                std::vector<float> row;
                for(int j = 0; j < grid[0].size(); j++){
                    row.push_back(0);
                }
                grid.push_back(row);
            }
            if(fx >= grid[0].size()){
                int upperLimit = (int) (fx - grid[0].size());
                for(int i = 0; i < grid.size(); i++){
                    for(int j = 0; j <= upperLimit; j++){
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
        }
        clickstate = 0;
    }
}
