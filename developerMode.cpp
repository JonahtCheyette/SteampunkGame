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
    //initializing the rectangle
    if(event.mouse1 && clickstate == 0){
        x = event.mouseX + camera.x;
        y = event.mouseY + camera.y;
        clickstate = 1;
    }
    //drawing the rectangle is handled by the renderDrect functin, this just manipulates its size
    if(event.mouse1held && clickstate == 1){
        heldRect.x = x - camera.x;
        heldRect.y = y - camera.y;
        heldRect.w = event.mouseX - heldRect.x;
        heldRect.h = event.mouseY - heldRect.y;
        w = heldRect.w;
        h = heldRect.h;
    }
    if(held && !event.mouse1held){
        clickstate = 2;
    }
    held = event.mouse1held;
    
    if (event.mouse1Released && clickstate == 2) {
        //how many tiles to add (for loops)
        int xAmount = abs(round(w/ TILE_WIDTH));
        int yAmount = abs(round(h/ TILE_HEIGHT));
        
        if(xAmount < 1000 && xAmount != 0){
            //sp = starting point, t = tile (for loops), s = starting, f = final
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
                    for(int k = 0; k < tileGrid.size(); k++){
                        if(tileGrid[k].x == tx && tileGrid[k].y == ty){
                            tileGrid.erase(tileGrid.begin() + k);
                        }
                    }
                    if(create){
                        Object::Tile t(tx, ty, tileVector[whichTile].friction, tileVector[whichTile].kind);
                        if(tileVector[whichTile].kind == 0){
                            t.texture = tileVector[whichTile].single;
                        } else {
                            t.texture = tileVector[whichTile].passThroughBoth;
                        }
                        tileGrid.push_back(t);
                    }
                }
            }
            //opening the map file
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
            //resizing the grid in case the edited section is outside of it
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
            //changing the grid to the correct num
            if(create){
                for(int i = sx; i < fx; i++){
                    for(int j = sy; j < fy; j++){
                        grid[j][i] = tileVector[whichTile].tileNum;
                    }
                }
            } else {
                for(int i = sx; i < fx; i++){
                    for(int j = sy; j < fy; j++){
                        grid[j][i] = 0;
                    }
                }
            }
            //for editing the grid to get rid of unnecessary rows of zeroes and zeroes on the end of rows
            //finding num of unnecessary rows at bottom
            int correctindex = -1;
            for(int i = (int) (grid.size() - 1); i >= 0; i--){
                for(int j = 0; j < grid[i].size(); j++){
                    if(grid[i][j] != 0 && correctindex == -1){
                        correctindex = i;
                    }
                }
            }
            //getting rid of those rows
            for(int i = (int) (grid.size() - 1); i > correctindex; i--){
                if(grid.size() != 1){
                    grid.pop_back();
                }
            }
            //finding num of unnecessary zeroes at end of level
            int chopEnd = -1;
            for(int i = 0; i < grid.size(); i++){
                for(int j = 0; j < grid[i].size(); j++){
                    if(grid[i][j] != 0 && j > chopEnd){
                        chopEnd = j;
                    }
                }
            }
            //getting rid of those
            for(int i = 0; i < grid.size(); i++){
                for(int j = (int) (grid[i].size() - 1); j > chopEnd ; j--){
                    if(!(i == 0 && grid[i].size() == 1)){
                        grid[i].pop_back();
                    }
                }
            }
            //saving to file
            std::ofstream mFile(level.path + "tiles.txt", std::ofstream::out | std::ofstream::trunc);
            for(int i = 0; i < grid.size(); i++){
                std::string l = "";
                for(int j = 0; j < grid[i].size(); j++){
                    if(j > 0){
                        l += " ";
                    }
                    l += std::to_string((int) grid[i][j]);
                }
                if(i != grid.size() - 1){
                    l += "\n";
                }
                mFile << l;
            }
            mFile.close();
        }
        clickstate = 0;
    }
}

void developer::showEditing(Draw draw, std::string type, SDL_Color color, TTF_Font* font, std::vector<Object::tileHolder> tileVector, SDL_Renderer* renderer){
    //this is what prints the mode to topleft corner of screen
    destination.y = 0;
    destination.w = typeW;
    destination.h = typeH;
    SDL_RenderCopy(renderer, typeTexture, nullptr, &destination);
    //move it down, edit bounding box
    destination.y = 50;
    destination.w = createW;
    destination.h = createH;
    SDL_RenderCopy(renderer, createTexture, nullptr, &destination);
    if(create || type != "drag"){
        destination.y = 100;
        destination.w = whichW;
        destination.h = whichH;
        SDL_RenderCopy(renderer, whichTexture, nullptr, &destination);
    }
}

void developer::editAssets(Object::Camera c,Event e, Level &l, SDL_Renderer* renderer){
    if(hooks){
        if(e.mouse1){
            if(create){
                //makes a new hook, puts it into the vector
                Object::Point newPoint(e.mouseX + c.x, e.mouseY + c.y, "hook");
                l.hookList.push_back(newPoint);
            } else {
                //deletes all hooks within 30 px of mouseclick
                for(int i = (int) (l.hookList.size()) - 1; i >= 0; i--){
                    if(sqrt(pow(l.hookList[i].x - (e.mouseX + c.x),2) + pow(l.hookList[i].y - (e.mouseY + c.y),2)) <= 30){
                        l.hookList.erase(l.hookList.begin() + i);
                    }
                }
            }
            //save to file
            std::ofstream hFile(l.path + "hooks.txt", std::ofstream::out | std::ofstream::trunc);
            for(int i = 0; i < l.hookList.size(); i++){
                std::string s = "";
                s += std::to_string((int)l.hookList[i].x);
                s += " ";
                s += std::to_string((int)l.hookList[i].y);
                if(i != l.hookList.size() + 1){
                    s += "\n";
                }
                hFile << s;
            }
            hFile.close();
        }
    } else {
        //WIP
        if(e.mouse1 && clickstate == 0){
            if(sqrt(pow(l.end.x - e.mouseX,2) + pow(l.end.y - e.mouseY,2)) <= 30){
                spawn = false;
                clickstate = 1;
            } else if (sqrt(pow(l.spawn.x - e.mouseX,2) + pow(l.spawn.y - e.mouseY,2)) <= 30) {
                spawn = true;
                clickstate = 1;
            }
        }
        if(event.mouse1held && clickstate == 1){
            heldRect.x = e.mouseX - TILE_WIDTH / 2;
            heldRect.y = e.mouseY - TILE_HEIGHT / 2;
            heldRect.w = TILE_WIDTH;
            heldRect.h = TILE_HEIGHT;
            SDL_RenderCopy(renderer, l.Start_End, nullptr, &heldRect);
        }
        if(held && !event.mouse1held){
            clickstate = 2;
        }
        held = event.mouse1held;
    }
}

void developer::createSwitch(Event e, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer){
    //just switches create to destroy and back again as well as changing the texture to show it
    if(e.keyboard_state_array[SDL_SCANCODE_Q] && !clicked1){
        create = !create;
        if(create){
            createTexture = draw.loadFromRenderedText("create", color, font, createW, createH, renderer);
        } else {
            createTexture = draw.loadFromRenderedText("destroy", color, font, createW, createH, renderer);
        }
        clicked1 = true;
    } else if (!e.keyboard_state_array[SDL_SCANCODE_Q]){
        clicked1 = false;
    }
}

void developer::typeSwitch(Event e, std::string &type, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer, Draw draw){
    //swithes type from drag to clck and changes appropriate texture
    if(e.keyboard_state_array[SDL_SCANCODE_E] && !clicked2){
        if(type == "drag"){
            type = "click";
            clickstate = 0;
            held = false;
            if(hooks){
                whichTexture = draw.loadFromRenderedText("hooks", color, font, whichW, whichH, renderer);
            } else {
                whichTexture = draw.loadFromRenderedText("spawn/end points", color, font, whichW, whichH, renderer);
            }
            typeTexture = draw.loadFromRenderedText("click", color, font, typeW, typeH, renderer);
        } else {
            type = "drag";
            typeTexture = draw.loadFromRenderedText("drag", color, font, typeW, typeH, renderer);
        }
        clicked2 = true;
    } else if (!e.keyboard_state_array[SDL_SCANCODE_E]){
        clicked2 = false;
    }
}

void developer::switchTile(Event e, std::vector<Object::tileHolder> tileVector, std::string type, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer){
    //changes what asset your editing
    if(type == "drag"){
        //tiles
        if(e.keyboard_state_array[SDL_SCANCODE_R] && ! clicked3){
            whichTile++;
            clicked3 = true;
        } else if (!e.keyboard_state_array[SDL_SCANCODE_R]){
            clicked3 = false;
        }
        if(e.keyboard_state_array[SDL_SCANCODE_F] && !clicked4){
            whichTile--;
            clicked4 = true;
        } else if (!e.keyboard_state_array[SDL_SCANCODE_F]){
            clicked4 = false;
        }
        if(whichTile > (tileVector.size() - 1)){
            whichTile = 0;
        } else if(whichTile < 0){
            whichTile = (int) (tileVector.size() - 1);
        }
        whichTexture = draw.loadFromRenderedText(tileVector[whichTile].Dpath, color, font, whichW, whichH, renderer);
    } else {
        //other assets
        if((e.keyboard_state_array[SDL_SCANCODE_R] || e.keyboard_state_array[SDL_SCANCODE_F]) && ! clicked3){
            hooks = !hooks;
            if(hooks){
                whichTexture = draw.loadFromRenderedText("hooks", color, font, whichW, whichH, renderer);
            } else {
                whichTexture = draw.loadFromRenderedText("spawn/end points", color, font, whichW, whichH, renderer);
            }
            clicked3 = true;
        }
        if (!e.keyboard_state_array[SDL_SCANCODE_R] && !e.keyboard_state_array[SDL_SCANCODE_F]){
            clicked3 = false;
        }
    }
}

void developer::init(Draw draw, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer){
    clickstate = 0;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    held = false;
    moveSpeed = 5;
    create = true;
    clicked1 = false;
    clicked2 = false;
    clicked3 = false;
    clicked4 = false;
    hooks = false;
    spawn = false;
    whichTile = 0;
    destination.x = 0;
    typeTexture = draw.loadFromRenderedText("drag", color, font, typeW, typeH, renderer);
    createTexture = draw.loadFromRenderedText("create", color, font, createW, createH, renderer);
    whichTexture = draw.loadFromRenderedText("test1", color, font, whichW, whichH, renderer);
}

void developer::renderDRect(SDL_Renderer* renderer, std::string type){
    //renders rect while being dragged
    if(type == "drag" && clickstate == 1){
        SDL_RenderDrawRect(renderer, &heldRect);
    }
}
