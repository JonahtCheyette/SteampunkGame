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
                        } else if(tileVector[whichTile].kind == 1) {
                            t.texture = tileVector[whichTile].passThroughBoth;
                        } else {
                            t.texture = tileVector[whichTile].middle;
                            t.clockWise = tileVector[whichTile].clockWise;
                            t.vertical = tileVector[whichTile].vertical;
                        }
                        tileGrid.push_back(t);
                    }
                }
            }
            //opening the map file
            std::vector<std::vector<int>> grid;
            std::string line;
            std::ifstream mapFile(level.path + "tiles.txt");
            while(std::getline(mapFile, line)){
                std::vector <int> row;
                for(int j = 0; j < line.length(); j++){
                    if(!isspace(line[j])){
                        row.push_back((int) line[j] - 48);
                    }
                }
                if(row.size() != 0){
                    grid.push_back(row);
                }
            }
            mapFile.close();
            //resizing the grid in case the edited section is outside of it
            while(grid.size() < fy) {
                std::vector<int> row;
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
                    l += std::to_string(grid[i][j]);
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

void developer::editAssets(Object::Camera c,Event e, Level &l, SDL_Renderer* renderer, SDL_Color color, TTF_Font* font){
    if(whichAsset == 0){
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
                s += std::to_string((int) l.hookList[i].initX);
                s += " ";
                s += std::to_string((int) l.hookList[i].initY);
                s += " ";
                s += std::to_string((int) l.hookList[i].limit1);
                s += " ";
                s += std::to_string((int) l.hookList[i].limit2);
                s += " ";
                s += std::to_string((int) l.hookList[i].moveSpeed);
                s += " ";
                s += std::to_string(l.hookList[i].vertical);
                if(i != l.hookList.size() + 1){
                    s += "\n";
                }
                hFile << s;
            }
            hFile.close();
        }
    } else if (whichAsset == 1) {
        //click to pick up, click to put down
        if(e.mouse1 && clickstate == 0){
            if(sqrt(pow(l.end.x - e.mouseX,2) + pow(l.end.y - e.mouseY,2)) <= 30){
                spawn = false;
            } else if (sqrt(pow(l.spawn.x - e.mouseX,2) + pow(l.spawn.y - e.mouseY,2)) <= 30) {
                spawn = true;
            }
            clickstate = 1;
        } else if(e.mouse1 && clickstate == 1){
            if(spawn){
                l.spawn.x = e.mouseX + c.x;
                l.spawn.y = e.mouseY + c.y;
            } else {
                l.end.x = e.mouseX + c.x;
                l.end.y = e.mouseY + c.y;
            }
            std::cout << l.end.x;
            std::ofstream seFile(l.path + "start-end.txt", std::ofstream::out | std::ofstream::trunc);
            seFile << l.spawn.x << " " << l.spawn.y << "\n";
            seFile << l.end.x << " " << l.end.y << "\n";
            seFile.close();
            clickstate = 0;
        }
    } else if(whichAsset == 2 || whichAsset == 3){
        if(e.mouse1 && whichHook == -1 && clickstate == 0){
            for(int i = (int) (l.hookList.size()) - 1; i >= 0; i--){
                if(sqrt(pow(l.hookList[i].x - (e.mouseX + c.x),2) + pow(l.hookList[i].y - (e.mouseY + c.y),2)) <= 30 && whichHook == -1 && l.hookList[i].moving){
                    whichHook = i;
                    clickstate = 1;
                    moveSpeedTexture = draw.loadFromRenderedText(std::to_string((int) l.hookList[i].moveSpeed), color, font, msW, msH, renderer);
                }
            }
            if(create){
                if(whichHook == -1){
                //makes a new hook, puts it into the vector
                    Object::Point newPoint (e.mouseX + c.x, e.mouseY + c.y, "hook");
                    newPoint.moving = true;
                    newPoint.moveSpeed = 2;
                    if(whichAsset == 2){
                        newPoint.limit1 = e.mouseX + c.x + 1;
                        newPoint.limit2 = e.mouseX + c.x - 1;
                        newPoint.vertical = false;
                    } else {
                        newPoint.limit1 = e.mouseY + c.y + 1;
                        newPoint.limit2 = e.mouseY + c.y - 1;
                        newPoint.vertical = true;
                    }
                    l.hookList.push_back(newPoint);
                }
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
                s += std::to_string((int) l.hookList[i].initX);
                s += " ";
                s += std::to_string((int) l.hookList[i].initY);
                s += " ";
                s += std::to_string((int) l.hookList[i].limit1);
                s += " ";
                s += std::to_string((int) l.hookList[i].limit2);
                s += " ";
                s += std::to_string((int) l.hookList[i].moveSpeed);
                s += " ";
                s += std::to_string(l.hookList[i].vertical);
                if(i != l.hookList.size() + 1){
                    s += "\n";
                }
                hFile << s;
            }
            hFile.close();
        } else if(clickstate == 1 && whichHook != -1 && e.mouse1){
            if(l.hookList[whichHook].vertical){
                if(abs((e.mouseX + c.x) - l.hookList[whichHook].x) <= 30 && abs((e.mouseY + c.y) - l.hookList[whichHook].limit1) <= 30){
                    whichLimit = 1;
                    clickstate = 2;
                } else if (abs((e.mouseX + c.x) - l.hookList[whichHook].x) <= 30 && abs((e.mouseY + c.y) - l.hookList[whichHook].limit2) <= 30){
                    whichLimit = 2;
                    clickstate = 2;
                }
            } else {
                if(abs((e.mouseX + c.x) - l.hookList[whichHook].limit1) <= 30 && abs((e.mouseY + c.y) - l.hookList[whichHook].y) <= 30){
                    whichLimit = 1;
                    clickstate = 2;
                } else if(abs((e.mouseX + c.x) - l.hookList[whichHook].limit2) <= 30 && abs((e.mouseY + c.y) - l.hookList[whichHook].y) <= 30){
                    whichLimit = 2;
                    clickstate = 2;
                }
            }
        } else if(clickstate == 2 && whichHook != -1 && e.mouse1){
            if(l.hookList[whichHook].vertical){
                if(whichLimit == 1){
                    l.hookList[whichHook].limit1 = e.mouseY + c.y;
                } else {
                    l.hookList[whichHook].limit2 = e.mouseY + c.y;
                }
                if(l.hookList[whichHook].limit1 < l.hookList[whichHook].y){
                    l.hookList[whichHook].limit1 = l.hookList[whichHook].y;
                } else if (l.hookList[whichHook].limit2 > l.hookList[whichHook].y){
                    l.hookList[whichHook].limit2 = l.hookList[whichHook].y;
                }
            } else {
                if(whichLimit == 1){
                    l.hookList[whichHook].limit1 = e.mouseX + c.x;
                } else {
                    l.hookList[whichHook].limit2 = e.mouseX + c.x;
                }
                if(l.hookList[whichHook].limit1 < l.hookList[whichHook].x){
                    l.hookList[whichHook].limit1 = l.hookList[whichHook].x;
                } else if (l.hookList[whichHook].limit2 > l.hookList[whichHook].x){
                    l.hookList[whichHook].limit2 = l.hookList[whichHook].x;
                }
            }
            std::ofstream hFile(l.path + "hooks.txt", std::ofstream::out | std::ofstream::trunc);
            for(int i = 0; i < l.hookList.size(); i++){
                std::string s = "";
                s += std::to_string((int) l.hookList[i].initX);
                s += " ";
                s += std::to_string((int) l.hookList[i].initY);
                s += " ";
                s += std::to_string((int) l.hookList[i].limit1);
                s += " ";
                s += std::to_string((int) l.hookList[i].limit2);
                s += " ";
                s += std::to_string((int) l.hookList[i].moveSpeed);
                s += " ";
                s += std::to_string(l.hookList[i].vertical);
                if(i != l.hookList.size() + 1){
                    s += "\n";
                }
                hFile << s;
            }
            hFile.close();
            clickstate = 0;
            whichHook = -1;
        }
    } else if (whichAsset == 4){
        if(e.mouse1){
            if(create){
                //makes a new hook, puts it into the vector
                l.crateList.push_back({(float) (e.mouseX + c.x),(float) (e.mouseY + c.y),50,50, renderer, draw, 15});
            } else {
                //deletes all hooks within 30 px of mouseclick
                for(int i = (int) (l.crateList.size()) - 1; i >= 0; i--){
                    if(sqrt(pow(l.crateList[i].x - (e.mouseX + c.x),2) + pow(l.crateList[i].y - (e.mouseY + c.y),2)) <= 30){
                        l.crateList.erase(l.crateList.begin() + i);
                    }
                }
            }
            //save to file
            std::ofstream cFile(l.path + "Crates.txt", std::ofstream::out | std::ofstream::trunc);
            for(int i = 0; i < l.crateList.size(); i++){
                std::string s = "";
                s += std::to_string((int) l.crateList[i].initX);
                s += " ";
                s += std::to_string((int) l.crateList[i].initY);
                s += " ";
                s += std::to_string((int) l.crateList[i].hitbox.width);
                s += " ";
                s += std::to_string((int) l.crateList[i].hitbox.height);
                s += " ";
                s += std::to_string((int) l.crateList[i].mass);
                if(i != l.crateList.size() + 1){
                    s += "\n";
                }
                cFile << s;
            }
            cFile.close();
        }
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
            if(whichAsset == 0){
                whichTexture = draw.loadFromRenderedText("hooks", color, font, whichW, whichH, renderer);
            } else if (whichAsset == 1) {
                whichTexture = draw.loadFromRenderedText("spawn/end points", color, font, whichW, whichH, renderer);
            }
            typeTexture = draw.loadFromRenderedText("click", color, font, typeW, typeH, renderer);
        } else {
            type = "drag";
            typeTexture = draw.loadFromRenderedText("drag", color, font, typeW, typeH, renderer);
            clickstate = 0;
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
        if(whichTile > (int) (tileVector.size() - 1)){
            whichTile = 0;
        } else if(whichTile < 0){
            whichTile = (int) (tileVector.size() - 1);
        }
        if(tileVector[whichTile].kind == 2){
            std::string assembleString = tileVector[whichTile].Dpath;
            assembleString += " ";
            if(tileVector[whichTile].vertical){
                assembleString += "vertical";
            } else {
                assembleString += "horizontal";
            }
            assembleString += " ";
            if(tileVector[whichTile].clockWise){
                assembleString += "clockwise";
            } else {
                assembleString += "counterclockwise";
            }
            whichTexture = draw.loadFromRenderedText(assembleString, color, font, whichW, whichH, renderer);
        } else {
            whichTexture = draw.loadFromRenderedText(tileVector[whichTile].Dpath, color, font, whichW, whichH, renderer);
        }
    } else {
        //other assets
        if(e.keyboard_state_array[SDL_SCANCODE_R] && !clicked3){
            whichAsset ++;
            clickstate = 0;
            clicked3 = true;
        } else if (!e.keyboard_state_array[SDL_SCANCODE_R]){
            clicked3 = false;
        }
        if (e.keyboard_state_array[SDL_SCANCODE_F] && ! clicked4){
            whichAsset --;
            clickstate = 0;
            clicked4 = true;
        } else if (!e.keyboard_state_array[SDL_SCANCODE_F]){
            clicked4 = false;
        }
        if(whichAsset < 0){
            whichAsset = 4;
        }
        if(whichAsset > 4){
            whichAsset = 0;
        }
        if(whichAsset == 0){
            whichTexture = draw.loadFromRenderedText("hooks", color, font, whichW, whichH, renderer);
        } else if (whichAsset == 1) {
            whichTexture = draw.loadFromRenderedText("spawn/end points", color, font, whichW, whichH, renderer);
        } else if (whichAsset == 2){
            whichTexture = draw.loadFromRenderedText("moving hooks (horizontal)", color, font, whichW, whichH, renderer);
        } else if (whichAsset == 3){
            whichTexture = draw.loadFromRenderedText("moving hooks (vertical)", color, font, whichW, whichH, renderer);
        } else if (whichAsset == 4){
            whichTexture = draw.loadFromRenderedText("crates", color, font, whichW, whichH, renderer);
        }
    }
}

void developer::init(Draw draw, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer){
    clickstate = 0;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    whichHook = -1;
    held = false;
    moveSpeed = 5;
    create = true;
    clicked1 = false;
    clicked2 = false;
    clicked3 = false;
    clicked4 = false;
    clicked5 = false;
    clicked6 = false;
    spawn = false;
    whichTile = 0;
    whichAsset = 0;
    typeTexture = draw.loadFromRenderedText("drag", color, font, typeW, typeH, renderer);
    createTexture = draw.loadFromRenderedText("create", color, font, createW, createH, renderer);
    whichTexture = draw.loadFromRenderedText("test1", color, font, whichW, whichH, renderer);
    moveSpeedTexture = draw.loadFromRenderedText("0", color, font, msW, msH, renderer);
}

void developer::renderDRect(SDL_Renderer* renderer, std::string type, Event e, Level l, Object::Camera c){
    //renders rect while being dragged
    if(clickstate == 1){
        if(type == "drag"){
            SDL_RenderDrawRect(renderer, &heldRect);
        } else if (whichAsset == 1){
            heldRect.w = TILE_WIDTH;
            heldRect.h = TILE_HEIGHT;
            heldRect.x = e.mouseX - TILE_WIDTH / 2;
            heldRect.y = e.mouseY - TILE_HEIGHT / 2;
            SDL_RenderCopy(renderer, l.Start_End, nullptr, &heldRect);
        }
    }
    if ((whichAsset == 2 || whichAsset == 3) && whichHook != -1){
        heldRect.w = 8;
        heldRect.h = 8;
        if(l.hookList[whichHook].vertical){
            heldRect.x = l.hookList[whichHook].x - 4 - c.x;
            heldRect.y = l.hookList[whichHook].limit1 - 4 - c.y;
            SDL_RenderDrawRect(renderer, &heldRect);
            heldRect.y = l.hookList[whichHook].limit2 - 4 - c.y;
            SDL_RenderDrawRect(renderer, &heldRect);
        } else {
            heldRect.y = l.hookList[whichHook].y - 4 - c.y;
            heldRect.x = l.hookList[whichHook].limit1 - 4 - c.x;
            SDL_RenderDrawRect(renderer, &heldRect);
            heldRect.x = l.hookList[whichHook].limit2 - 4 - c.x;
            SDL_RenderDrawRect(renderer, &heldRect);
        }
        heldRect.x = l.hookList[whichHook].x - (msW /2) - c.x;
        heldRect.y = l.hookList[whichHook].y - (msH/2) - 40 - c.y;
        heldRect.w = msW;
        heldRect.h = msH;
        SDL_RenderCopy(renderer, moveSpeedTexture, nullptr, &heldRect);
    }
}

void developer::changeHookMoveSpeed(Event e, std::vector<Object::Point> &hooks, SDL_Color color, TTF_Font *font, SDL_Renderer *renderer, std::string path){
    if ((whichAsset == 2 || whichAsset == 3) && whichHook != -1){
        if(e.keyboard_state_array[SDL_SCANCODE_UP] && !clicked5){
            hooks[whichHook].moveSpeed++;
            moveSpeedTexture = draw.loadFromRenderedText(std::to_string((int) hooks[whichHook].moveSpeed), color, font, msW, msH, renderer);
            std::ofstream hFile(path + "hooks.txt", std::ofstream::out | std::ofstream::trunc);
            for(int i = 0; i < hooks.size(); i++){
                std::string s = "";
                s += std::to_string((int) hooks[i].initX);
                s += " ";
                s += std::to_string((int) hooks[i].initY);
                s += " ";
                s += std::to_string((int) hooks[i].limit1);
                s += " ";
                s += std::to_string((int) hooks[i].limit2);
                s += " ";
                s += std::to_string((int) hooks[i].moveSpeed);
                s += " ";
                s += std::to_string(hooks[i].vertical);
                if(i != hooks.size() + 1){
                    s += "\n";
                }
                hFile << s;
            }
            hFile.close();
            clicked6 = true;
        } else if (!e.keyboard_state_array[SDL_SCANCODE_UP]){
            clicked5 = false;
        }
        if(e.keyboard_state_array[SDL_SCANCODE_DOWN] && !clicked6){
            hooks[whichHook].moveSpeed--;
            moveSpeedTexture = draw.loadFromRenderedText(std::to_string((int) hooks[whichHook].moveSpeed), color, font, msW, msH, renderer);
            std::ofstream hFile(path + "hooks.txt", std::ofstream::out | std::ofstream::trunc);
            for(int i = 0; i < hooks.size(); i++){
                std::string s = "";
                s += std::to_string((int) hooks[i].initX);
                s += " ";
                s += std::to_string((int) hooks[i].initY);
                s += " ";
                s += std::to_string((int) hooks[i].limit1);
                s += " ";
                s += std::to_string((int) hooks[i].limit2);
                s += " ";
                s += std::to_string((int) hooks[i].moveSpeed);
                s += " ";
                s += std::to_string(hooks[i].vertical);
                if(i != hooks.size() + 1){
                    s += "\n";
                }
                hFile << s;
            }
            hFile.close();
            clicked6 = true;
        } else if (!e.keyboard_state_array[SDL_SCANCODE_DOWN]){
            clicked6 = false;
        }
    }
}

void developer::reset(Level &l){
    for(int i = 0; i < l.hookList.size(); i++){
        l.hookList[i].x = l.hookList[i].initX;
        l.hookList[i].y = l.hookList[i].initY;
    }
    for(int i = 0; i < l.crateList.size(); i++){
        l.crateList[i].x = l.crateList[i].initX;
        l.crateList[i].y = l.crateList[i].initY;
    }
}
